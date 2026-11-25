## Build

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

Build and flash with `west`.

```
$ west flash
$ cp build/nrf_rid_scanner/zephyr/zephyr.uf2 /media/user/XIAO-BOOT
```

[XIAO nRF52840](https://www.seeedstudio.com/Seeed-XIAO-BLE-nRF52840-p-5201.html)
uses UF2 bootloader. Trigger it with double pressing reset. Then build and
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
[00:22:21.156,530] <inf> nrf_rid_scan: librid=0.7.0-dev
[00:22:21.156,547] <inf> nrf_rid_scan: board=xiao_nrf54lm20a soc=nrf54lm20a
...
{"mac": "EF:2E:A0:2A:4C:4B", "rssi": -52, "counter": 212, "protocol_version":2,"message_type":15,"message_count":6,"messages":[{"protocol_version":2,"message_type":2,"auth_type":5,"page_count":6,"timestamp":0,"length":121,"signature":"03ba65dc0e3266dc0e0ce79e693652db2c2eabba6070c9782faeca7044659c38cab754b1dd4ecdf212200100380000040593cfd8a8ed5c93c64131f6fe11530f6a8751737f4641d0e0f88750117bb124c8ca70b75148be4957e2f2ca7520715e6ef025c2aad7215bc8c9617cafe56db9312dfd90d9d03e7b08"}]}
{"mac": "DE:61:0C:28:01:CA", "rssi": -25, "counter": 1, "protocol_version":2,"message_type":0,"id_type":1,"ua_type":0,"uas_id":"1596A30D001FEC3"}
{"mac": "DE:61:0C:28:01:CA", "rssi": -27, "counter": 1, "protocol_version":2,"message_type":5,"id_type":0,"operator_id":"FIN87astrdge12k8"}
{"mac": "EF:2E:A0:2A:4C:4B", "rssi": -47, "counter": 156, "protocol_version":2,"message_type":0,"id_type":1,"ua_type":0,"uas_id":"22041B"}
{"mac": "DE:61:0C:28:01:CA", "rssi": -29, "counter": 20, "protocol_version":2,"message_type":1,"latitude":null,"longitude":null,"geodetic_altitude":null,"pressure_altitude":-10.00,"height":0.00,"height_type":0,"speed":null,"vertical_speed":null,"track_direction":null,"operational_status":1,"horizontal_accuracy":0,"vertical_accuracy":0,"speed_accuracy":0,"baro_altitude_accuracy":0,"timestamp":33870,"timestamp_accuracy":1}
{"mac": "EF:2E:A0:2A:4C:4B", "rssi": -49, "counter": 212, "protocol_version":2,"message_type":15,"message_count":6,"messages":[{"protocol_version":2,"message_type":2,"auth_type":5,"page_count":6,"timestamp":0,"length":121,"signature":"03ba65dc0e3266dc0e0ce79e693652db2c2eabba6070c9782faeca7044659c38cab754b1dd4ecdf212200100380000040593cfd8a8ed5c93c64131f6fe11530f6a8751737f4641d0e0f88750117bb124c8ca70b75148be4957e2f2ca7520715e6ef025c2aad7215bc8c9617cafe56db9312dfd90d9d03e7b08"}]}
{"mac": "DE:61:0C:28:01:CA", "rssi": -29, "counter": 20, "protocol_version":2,"message_type":4,"operator_location_type":0,"classification_type":1,"ua_classification_category":1,"ua_classification_class":0,"operator_latitude":null,"operator_longitude":null,"operator_altitude":null,"area_count":1,"area_radius":0,"area_ceiling":null,"area_floor":null,"timestamp":249324987}
{"mac": "DE:61:0C:28:01:CA", "rssi": -24, "counter": 22, "protocol_version":2,"message_type":15,"message_count":4,"messages":[{"protocol_version":2,"message_type":0,"id_type":1,"ua_type":0,"uas_id":"1596A30D001FEC3"},{"protocol_version":2,"message_type":1,"latitude":null,"longitude":null,"geodetic_altitude":null,"pressure_altitude":-10.00,"height":0.00,"height_type":0,"speed":null,"vertical_speed":null,"track_direction":null,"operational_status":1,"horizontal_accuracy":0,"vertical_accuracy":0,"speed_accuracy":0,"baro_altitude_accuracy":0,"timestamp":33870,"timestamp_accuracy":1},{"protocol_version":2,"message_type":4,"operator_location_type":0,"classification_type":1,"ua_classification_category":1,"ua_classification_class":0,"operator_latitude":null,"operator_longitude":null,"operator_altitude":null,"area_count":1,"area_radius":0,"area_ceiling":null,"area_floor":null,"timestamp":249324987},{"protocol_version":2,"message_type":5,"id_type":0,"operator_id":"FIN87astrdge12k8"}]}
{"mac": "EF:2E:A0:2A:4C:4B", "rssi": -49, "counter": 194, "protocol_version":2,"message_type":1,"latitude":62.6834720,"longitude":21.9749440,"geodetic_altitude":76.50,"pressure_altitude":-15.00,"height":4.50,"height_type":0,"speed":0.00,"vertical_speed":null,"track_direction":0,"operational_status":0,"horizontal_accuracy":0,"vertical_accuracy":0,"speed_accuracy":0,"baro_altitude_accuracy":6,"timestamp":33860,"timestamp_accuracy":0}
{"mac": "DE:61:0C:28:01:CA", "rssi": -27, "counter": 1, "protocol_version":2,"message_type":5,"id_type":0,"operator_id":"FIN87astrdge12k8"}
...
ctrl-a ctrl-x

```

Output when compiled with `CONFIG_RID_OUTPUT_CSV=y`.

```
$ picocom -b 115200 /dev/ttyACM0
Terminal ready
*** Booting nRF Connect SDK v3.4.99-0581fccc95ff ***
*** Using Zephyr OS v4.4.99-474bc1411799 ***
[00:22:21.156,530] <inf> nrf_rid_scan: librid=0.7.0-dev
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
