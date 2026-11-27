An [ASTM F3411](https://store.astm.org/f3411-22a.html) and
[DIN EN 4709-002](https://stan-shop.org/en/catalog/item/74958) Remote
ID scanner for Nordic Semiconductor development boards. It uses
[librid](https://github.com/tuupola/librid) for parsing the messages.
[Drone Remote ID Protocol (DRIP)](https://datatracker.ietf.org/group/drip/documents/)
support is provided by [libdrip](https://github.com/tuupola/libdrip).

## Build

Download the code.

```
$ git clone --recursive https://github.com/tuupola/nrf_rid_scanner.git
```

### XIAO

For flashing you might need these udev rules.

```
$ cat /etc/udev/rules.d/99-seeed-xiao.rules

SUBSYSTEM=="hidraw", ATTRS{idVendor}=="2886", ATTRS{idProduct}=="0068", MODE="0660", GROUP="plugdev"
SUBSYSTEM=="usb", ATTR{idVendor}=="2886", ATTR{idProduct}=="0068", MODE="0666"
```

[XIAO nRF54LM20A](https://www.seeedstudio.com/Seeed-Studio-XIAO-nRF54LM20A-p-6841.html) also needs recent NCS for building. Build and flash with `west`.

```
$ nrfutil sdk-manager toolchain launch --ncs-version v3.5.0-preview4 --shell
(v3.5.0-preview4) host% source ~/ncs/v3.5.0-preview4/zephyr/zephyr-env.sh
(v3.5.0-preview4) host% west build -b xiao_nrf54lm20a/nrf54lm20a/cpuapp --pristine
(v3.5.0-preview4) host% west flash
```

[XIAO nRF52840](https://www.seeedstudio.com/Seeed-XIAO-BLE-nRF52840-p-5201.html)
uses UF2 bootloader. Trigger it by double pressing reset. Then build and
"flash" by copying the firmware to the boot disk.

```
$ nrfutil sdk-manager toolchain launch --ncs-version v3.5.0-preview4 --shell

(v3.5.0-preview4) host% source ~/ncs/v3.5.0-preview4/zephyr/zephyr-env.sh
(v3.5.0-preview4) host% west build -b xiao_ble/nrf52840 --pristine
(v3.5.0-preview4) moose% cp build/nrf_rid_scanner/zephyr/zephyr.uf2 /media/user/XIAO-BOOT
```

## Connect

Output when compiled with `CONFIG_RID_OUTPUT_JSON=y`.

```
$ picocom -b 115200 /dev/ttyACM0
Terminal ready
*** Booting nRF Connect SDK v3.4.99-0581fccc95ff ***
*** Using Zephyr OS v4.4.99-474bc1411799 ***
[00:22:21.156,530] <inf> nrf_rid_scan: librid=0.7.0-dev libdrip=0.1.0-dev
[00:22:21.156,547] <inf> nrf_rid_scan: board=xiao_nrf54lm20a soc=nrf54lm20a
...
{"mac": "EF:2E:A0:2A:4C:4B", "rssi": -41, "counter": 58, "protocol_version":2,"message_type":15,"message_count":6,"messages":[{"protocol_version":2,"message_type":2,"auth_type":5,"page_count":6,"timestamp":0,"length":121,"signature":{"sam_type":3,"vnb":249421758,"vna":249421878,"previous_hash":"5912b49d699b6e5e","current_hash":"87789e08f95f0fa2","link_hash":"aeca7044659c38ca","evidence_count":1,"evidence":["c0e6c4221fd51f41"],"det":"200100380000040593cfd8a8ed5c93c6","signature":"a98cddf39d517fb63ed25390c4ffffed7e74be51bb3332033590eaaf2a25071900ff4b4f2e183248fdae119f8e38307b7e1c53e5eace2438437c72c53982530d"}}]}
{"mac": "EF:2E:A0:2A:4C:4B", "rssi": -43, "counter": 59, "protocol_version":2,"message_type":15,"message_count":7,"messages":[{"protocol_version":2,"message_type":2,"auth_type":5,"page_count":7,"timestamp":0,"length":137,"signature":{"sam_type":1,"vnb":249314272,"vna":257090272,"child_det":"200100380000040593cfd8a8ed5c93c6","child_hi":"dc2a61ba45139d2a8deeae006e4443c11f5885f257ccd84d1a9b79f451b0550d","parent_det":"2001003800000405474eae3655b7d4ea","signature":"a12c560aa102b13dd6c04871e95ea9871a2c5e263f07c256870b910c82ac8a4b57611033d183a9ac6847a62127f5595e5dd97b2ed6c6f6e9af39915c739e4200"}}]}
{"mac": "EF:2E:A0:2A:4C:4B", "rssi": -52, "counter": 151, "protocol_version":2,"message_type":0,"id_type":1,"ua_type":0,"uas_id":"22041B"}
{"mac": "DE:61:0C:28:01:CA", "rssi": -23, "counter": 7, "protocol_version":2,"message_type":4,"operator_location_type":0,"classification_type":1,"ua_classification_category":1,"ua_classification_class":0,"operator_latitude":null,"operator_longitude":null,"operator_altitude":null,"area_count":1,"area_radius":0,"area_ceiling":null,"area_floor":null,"timestamp":249421759}
{"mac": "EF:2E:A0:2A:4C:4B", "rssi": -42, "counter": 204, "protocol_version":2,"message_type":1,"latitude":null,"longitude":null,"geodetic_altitude":0.00,"pressure_altitude":-67.50,"height":-1.00,"height_type":0,"speed":null,"vertical_speed":null,"track_direction":null,"operational_status":0,"horizontal_accuracy":0,"vertical_accuracy":0,"speed_accuracy":0,"baro_altitude_accuracy":6,"timestamp":29590,"timestamp_accuracy":0}
{"mac": "EF:2E:A0:2A:4C:4B", "rssi": -42, "counter": 59, "protocol_version":2,"message_type":15,"message_count":7,"messages":[{"protocol_version":2,"message_type":2,"auth_type":5,"page_count":7,"timestamp":0,"length":137,"signature":{"sam_type":1,"vnb":249314272,"vna":257090272,"child_det":"200100380000040593cfd8a8ed5c93c6","child_hi":"dc2a61ba45139d2a8deeae006e4443c11f5885f257ccd84d1a9b79f451b0550d","parent_det":"2001003800000405474eae3655b7d4ea","signature":"a12c560aa102b13dd6c04871e95ea9871a2c5e263f07c256870b910c82ac8a4b57611033d183a9ac6847a62127f5595e5dd97b2ed6c6f6e9af39915c739e4200"}}]}
{"mac": "DE:61:0C:28:01:CA", "rssi": -21, "counter": 1, "protocol_version":2,"message_type":5,"id_type":0,"operator_id":"FIN87astrdge12k8"}
{"mac": "DE:61:0C:28:01:CA", "rssi": -21, "counter": 7, "protocol_version":2,"message_type":1,"latitude":null,"longitude":null,"geodetic_altitude":null,"pressure_altitude":-62.00,"height":0.00,"height_type":0,"speed":null,"vertical_speed":null,"track_direction":null,"operational_status":1,"horizontal_accuracy":0,"vertical_accuracy":0,"speed_accuracy":0,"baro_altitude_accuracy":0,"timestamp":29590,"timestamp_accuracy":1}
{"mac": "DE:61:0C:28:01:CA", "rssi": -21, "counter": 1, "protocol_version":2,"message_type":0,"id_type":1,"ua_type":0,"uas_id":"1596A30D001FEC3"}
{"mac": "EF:2E:A0:2A:4C:4B", "rssi": -41, "counter": 153, "protocol_version":2,"message_type":0,"id_type":1,"ua_type":0,"uas_id":"22041B"}
{"mac": "EF:2E:A0:2A:4C:4B", "rssi": -52, "counter": 154, "protocol_version":2,"message_type":0,"id_type":4,"ua_type":0,"uas_id":"01200100380000040593cfd8a8ed5c93c6000000"}
...
ctrl-a ctrl-x

```

Output when compiled with `CONFIG_RID_OUTPUT_CSV=y`. The message itself is
hex encoded.

```
$ picocom -b 115200 /dev/ttyACM0
Terminal ready
*** Booting nRF Connect SDK v3.4.99-0581fccc95ff ***
*** Using Zephyr OS v4.4.99-474bc1411799 ***
[00:22:21.156,530] <inf> nrf_rid_scan: librid=0.7.0-dev libdrip=0.1.0-dev
[00:22:21.156,547] <inf> nrf_rid_scan: board=xiao_nrf54lm20a soc=nrf54lm20a
...
EF:2E:A0:2A:4C:4B,-52,123,024001200100380000040593CFD8A8ED5C93C6000000000000
DE:61:0C:28:01:CA,-41,1,520046494E38376173747264676531326B3800000000000000
EF:2E:A0:2A:4C:4B,-48,97,F2190302103232303431420000000000000000000000000000000000024001200100380000040593CFD8A8ED5C93C6000000000000120000007E20BD5C25401C190DB2076E08D90700603E030000
EF:2E:A0:2A:4C:4B,-47,97,F21906225005790000000003E466DC0E5C67DC0EDE0C84FB229ACA03225176299D09F931CF3BAECA7044659C38CA81951707692A332252AE200100380000040593CFD8A8ED5C93C644F5F5D895C82253720249BB4A221C3915EA6B84BAAE2228F6EC388EEACBB522549FB436F2869D2976A13DE8E36B314F875E0DFBFA46B65E22554BDC78D4DF408C77F52A9D0E0000000000000000000000
DE:61:0C:28:01:CA,-41,58,4204000000000000000001000000000000100000E466DC0E00
EF:2E:A0:2A:4C:4B,-47,124,02103232303431420000000000000000000000000000000000
DE:61:0C:28:01:CA,-40,1,02103135393641333044303031464543330000000000000000
EF:2E:A0:2A:4C:4B,-49,97,F2190302103232303431420000000000000000000000000000000000024001200100380000040593CFD8A8ED5C93C6000000000000120000007E20BD5C25401C190DB2076E08D90700603E030000
EF:2E:A0:2A:4C:4B,-49,97,F21906225005790000000003E466DC0E5C67DC0EDE0C84FB229ACA03225176299D09F931CF3BAECA7044659C38CA81951707692A332252AE200100380000040593CFD8A8ED5C93C644F5F5D895C82253720249BB4A221C3915EA6B84BAAE2228F6EC388EEACBB522549FB436F2869D2976A13DE8E36B314F875E0DFBFA46B65E22554BDC78D4DF408C77F52A9D0E0000000000000000000000
DE:61:0C:28:01:CA,-40,1,520046494E38376173747264676531326B3800000000000000
```

You can parse the hex for example with the
[rid](https://github.com/tuupola/librid/tree/master/examples/cli) command line
tool.

```
$ rid 520046494E38376173747264676531326B3800000000000000 | jq
{
  "protocol_version": 2,
  "message_type": 5,
  "id_type": 0,
  "operator_id": "FIN87astrdge12k8"
}
```
