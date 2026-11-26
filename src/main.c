#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/net_buf.h>
#include <zephyr/sys/byteorder.h>

#include <drip/version.h>
#include <rid/message.h>
#include <rid/transport.h>
#include <rid/version.h>

LOG_MODULE_REGISTER(nrf_rid_scan, LOG_LEVEL_INF);

#define BT_MIN_DATA_LEN (RID_TRANSPORT_BT_MESSAGE_OFFSET + RID_MESSAGE_SIZE)

static bool filter_rid(struct bt_data *data, void *user_data) {
    const uint8_t **buffer = user_data;

    /* Must be service data with a 16-bit UUID. */
    if (data->type != BT_DATA_SVC_DATA16) {
        return true;
    }

    /* Must be atleast 29 bytes. */
    if (data->data_len < BT_MIN_DATA_LEN) {
        return true;
    }

    /* Check for 0xFFFA. */
    if (sys_get_le16(data->data) != RID_TRANSPORT_BT_SERVICE_UUID) {
        return true;
    }

    /* Check for 0x0D. */
    if (data->data[RID_TRANSPORT_BT_SERVICE_UUID_SIZE] != RID_TRANSPORT_BT_APP_CODE) {
        return true;
    }

    /* Point buffer at the service data for later use. */
    *buffer = data->data;
    return false;
}

#if defined(CONFIG_RID_OUTPUT_JSON)
static int print_json(
    const bt_addr_t *addr, int8_t rssi, uint8_t counter, const rid_message_t *message
) {
    int rc;
    static char json[2048];

    /* Convert the message to JSON. */
    rc = rid_message_to_json(message, json, sizeof(json), NULL);
    if (rc < 0) {
        LOG_ERR("JSON encode failed: %s", rid_error_to_string(rc));
        return rc;
    }

    /* Add mac, counter and rssi to the JSON and print. */
    printf(
        "{\"mac\": \"%s\", \"rssi\": %hhd, \"counter\": %hhu, %s\n",
        bt_addr_str(addr),
        rssi,
        counter,
        json + 1
    );
    return 0;
}
#endif

#if defined(CONFIG_RID_OUTPUT_CSV)
static void print_csv(
    const bt_addr_t *addr, int8_t rssi, uint8_t counter, const rid_message_t *message
) {
    const uint8_t *bytes = (const uint8_t *)message;
    size_t size = rid_message_size(message);

    printf("%s,%hhd,%hhu,", bt_addr_str(addr), rssi, counter);
    for (size_t i = 0; i < size; i++) {
        printf("%02X", bytes[i]);
    }
    printf("\n");
}
#endif

static void
callback(const bt_addr_le_t *addr, int8_t rssi, uint8_t type, struct net_buf_simple *ad) {
    uint8_t counter;
    const uint8_t *buffer = NULL;
    const rid_message_t *message;
    struct net_buf_simple_state state;

    /* Save ad state so we can LOG_HEXDUMP_DBG it later. */
    net_buf_simple_save(ad, &state);
    bt_data_parse(ad, filter_rid, &buffer);
    net_buf_simple_restore(ad, &state);

    /* Buffer points to data only if we got a Remote ID. */
    if (buffer == NULL) {
        return;
    }

    /* Get the message and counter from the buffer. */
    message = (const rid_message_t *)(buffer + RID_TRANSPORT_BT_MESSAGE_OFFSET);
    counter = buffer[RID_TRANSPORT_BT_COUNTER_OFFSET];

    LOG_DBG("%s rssi=%d type=%u len=%u", bt_addr_le_str(addr), rssi, type, ad->len);
    LOG_HEXDUMP_DBG(ad->data, ad->len, "ad");

#if defined(CONFIG_RID_OUTPUT_JSON)
    print_json(&addr->a, rssi, counter, message);
#endif
#if defined(CONFIG_RID_OUTPUT_CSV)
    print_csv(&addr->a, rssi, counter, message);
#endif
}

int main(void) {
    int rc;

    /* Give console some time to catch up. */
    k_msleep(1000);

    LOG_INF("librid=%s libdrip=%s", rid_version_to_string(), drip_version_to_string());
    LOG_INF("board=%s soc=%s", CONFIG_BOARD, CONFIG_SOC);

    rc = bt_enable(NULL);
    if (rc < 0) {
        LOG_ERR("Bluetooth init failed: %d", rc);
        return rc;
    }

    rc = bt_le_scan_start(BT_LE_SCAN_CODED_PASSIVE, callback);
    if (rc < 0) {
        LOG_ERR("Bluetooth LE scan start failed: %d", rc);
        return rc;
    }

    LOG_INF("Bluetooth LE scan started...");
    return 0;
}
