# Tuya IoTOS Embeded Demo WiFi & BLE Stepper Motor

<br>

## Introduction 

This demo is based on [Tuya IoT Platform](https://iot.tuya.com/), Tuya Smart APP, IoTOS Embeded WiFi&Ble SDK, using Tuya WiFi/WiFi+Ble series modules quickly build a wireless printer application. With the function of printing text and simple pictures.

<br>


## Quick start 

### Compile & Burn

- After creating a product on [Tuya IoT Platform](https://iot.tuya.com/), download the SDK from the development materials of hardware development.

- Download the demo to the demos directory of the SDK:

  ```bash
  $ cd demos
  $ git clone https://github.com/Tuya-Community/tuya-iotos-embeded-demo-wifi-ble-wireless-printer.git
  ```

- Execute the following command in the SDK root directory to start compiling:

  ```bash
  sh build_app.sh demos/tuya-demo-stepper-motor tuya-demo-stepper-motor 1.0.0
  ```

- Firmware burn-in license information please refer to: [General Wi-Fi SDK programming authorization instructions](https://developer.tuya.com/cn/docs/iot/tuya-common-wifi-sdk-burning-and-authorization?id=K9ip0gbawnkn7)  

<br>

### File description 

```
├── include /* Header files */
│   ├── driver
│   │   └── tuya_motor.h /* Stepper motor drive */
│   └── tuya_device.h /* Entry file of application layer */
└── src
|    ├── driver
|    │   └── tuya_motor.c /* Stepper motor drive */
|    └── tuya_device.c /* Entry file of application layer */
├── README.md
├── README_zh.md   
```

<br>

### Entry to application

Entry file: /demos/src/tuya_device.c

Important function：`device_init()`

- Call the `tuya_iot_wf_soc_dev_init_param()` interface to initialize the SDK, configure the working mode, network distribution mode, and register various callback functions and save the firmware key and PID.
- Call the `tuya_iot_reg_get_wf_nw_stat_cb()` interface to register the device network status callback function.

<br>

### Data point (DP)

- Report dp point interface: dev_report_dp_json_async()

| Function name | OPERATE_RET dev_report_dp_json_async(IN CONST CHAR_T *dev_id,IN CONST TY_OBJ_DP_S *dp_data,IN CONST UINT_T cnt) |
| ------------- | ------------------------------------------------------------ |
| devid         | device id (if gateway, MCU, SOC class device then devid = NULL; if sub-device, then devid = sub-device_id) |
| dp_data       | dp structure array name                                      |
| cnt           | Number of elements of the dp structure array                 |
| Return        | OPRT_OK: Success Other: Failure                              |

<br>

### I/O list

| PCI             | I/O  |
| --------------- | ---- |
| MOTOR0_AOUT1 A  | PA26 |
| MOTOR0_AOUT1 /A | PA6  |
| MOTOR0_AOUT1 B  | PA7  |
| MOTOR0_AOUT1 /B | PA8  |

<br>

## Reference

- [General Wi-Fi SDK Instruction](https://developer.tuya.com/en/docs/iot/tuya-common-wifi-sdk?id=K9glcmvw4u9ml) 
- [General Wi-Fi SDK Demo Instruction](https://developer.tuya.com/en/docs/iot/tuya-wifi-sdk-demo-instructions?id=K9oce5ayw5xem) 
- [Tuya Project Hub](https://developer.tuya.com/demo)

<br>

## Technical Support

You can get support from Tuya with the following methods:

- [Tuya IoT Developer Platform](https://developer.tuya.com/en/)
- [Help Center](https://support.tuya.com/en/help)
- [Service & Support](https://service.console.tuya.com)

<br>

