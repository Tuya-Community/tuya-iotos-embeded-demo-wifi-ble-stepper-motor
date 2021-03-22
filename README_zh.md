# Tuya IoTOS Embeded Demo WiFi & BLE Stepper-Motor

[English](./README.md) | [中文](./README_zh.md)

## 简介 

本Demo通过涂鸦智能云平台、涂鸦智能APP、IoTOS Embeded WiFi &Ble SDK实现对步进电机的控制，使用涂鸦WiFi/WiFi+BLE系列模组，实现远程控制。

已实现功能：

+ 控制电机启动/停止




## 快速上手 

### 编译与烧录
+ 下载[Tuya IoTOS Embeded WiFi & BLE sdk](https://github.com/tuya/tuya-iotos-embeded-sdk-wifi-ble-bk7231t) 

+ 下载Demo至SDK目录的apps目录下 

  ```bash
  $ cd apps
  $ git clone https://github.com/Tuya-Community/tuya-iotos-embeded-demo-wifi-ble-stepper-motor
  ```
  
+ 在SDK根目录下执行以下命令开始编译：

  ```bash
  sh build_app.sh apps/bk7231t_stepper_motor bk7231t_stepper_motor 1.0.0 
  ```

+ 固件烧录授权相关信息请参考：[Wi-Fi + BLE 系列模组烧录授权](https://developer.tuya.com/cn/docs/iot/device-development/burn-and-authorization/burn-and-authorize-wifi-ble-modules/burn-and-authorize-wb-series-modules?id=Ka78f4pttsytd) 

 

 ### 文件介绍 

```bash
├── include
│   ├── tuya_device.h
│   ├── tuya_dp_process.h
│   └── tuya_stepper_motor.h
└── src
    ├── tuya_device.c
    ├── tuya_dp_process.c
    └── tuya_stepper_motor.c
```



 ### Demo信息 

|  产品ID  |                      fueqoozoznq6f4yp                      |
| :------: | :--------------------------------------------------------: |
| 芯片平台 |                          BK7231T                           |
| 编译环境 | ty_iot_wf_bt_sdk_bk_bk7231t_1.0.2（涂鸦IOT平台 SDK 1.0.2） |

  

### Demo入口

入口文件：tuya_device.c

重要函数：device_init()

+ 调用 tuya_iot_wf_soc_dev_init_param() 接口进行SDK初始化，配置了工作模式、配网模式，同时注册了各种回调函数并存入了固件key和PID。

+ 调用 tuya_iot_reg_get_wf_nw_stat_cb() 接口注册设备网络状态回调函数。

+ 调用应用层初始化函数 stepper_motor_init()

 

### DP点相关

+ 上报dp点接口: dev_report_dp_json_async()

| 函数名  | OPERATE_RET dev_report_dp_json_async(IN CONST CHAR_T *dev_id,IN CONST TY_OBJ_DP_S *dp_data,IN CONST UINT_T cnt) |
| ------- | ------------------------------------------------------------ |
| devid   | 设备id（若为网关、MCU、SOC类设备则devid = NULL;若为子设备，则devid = sub-device_id) |
| dp_data | dp结构体数组名                                               |
| cnt     | dp结构体数组的元素个数                                       |
| Return  | OPRT_OK: 成功  Other: 失败                                   |

 

### I/O 列表 

| 步进电机引脚 |   wb3s引脚   |
| :----------: | :----------: |
|  `MOTOR_A`   | `TY_GPIOA_6` |
|  `MOTOR_B`   | `TY_GPIOA_6` |
|  `MOTOR_C`   | `TY_GPIOA_6` |
|  `MOTOR_D`   | `TY_GPIOA_6` |

 

## 相关文档

涂鸦Demo中心：https://developer.tuya.com/demo



## 技术支持

您可以通过以下方法获得涂鸦的支持:

- 开发者中心：https://developer.tuya.com
- 帮助中心: https://support.tuya.com/help
- 技术支持工单中心: [https://service.console.tuya.com](https://service.console.tuya.com/) 