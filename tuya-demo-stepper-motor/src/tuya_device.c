/**
* @file tuya_device.c
* @author zzw
* @email: huanling.zhang@tuya.com
* @brief tuya_device module is used to application file entry
* @version 0.1
* @date 2021-08-26
*
* @copyright Copyright (c) tuya.inc 2021
*
*/

/*********************************************************************
********************************includes******************************
*********************************************************************/
#include "uni_log.h"
#include "gw_intf.h"
#include "mf_test.h"
#include "tuya_key.h"
#include "tuya_led.h"
#include "tuya_gpio.h"
#include "tuya_hal_system.h"
#include "tuya_iot_com_api.h"
#include "tuya_iot_wifi_api.h"
#include "tuya_cloud_error_code.h"
/*********************************************************************
****************************private includes**************************
*********************************************************************/
#include "tuya_motor.h"
#include "tuya_device.h"
/*********************************************************************
******************************macro define****************************
*********************************************************************/
#define _TUYA_DEVICE_GLOBAL
/*********************************************************************
****************************typedef define****************************
*********************************************************************/


/*********************************************************************
****************************variable define***************************
*********************************************************************/

/*********************************************************************
****************************function define***************************
*********************************************************************/
/**
 * @Function:mf_user_pre_gpio_test_cb 
 * @Description: 
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: none
 */
VOID mf_user_pre_gpio_test_cb(VOID_T) 
{
    return;
}

/**
 * @Function:mf_user_enter_callback 
 * @Description: 
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: none
 */
VOID mf_user_enter_callback(VOID_T) 
{
    return;
}

/**
 * @Function: hw_reset_flash_data
 * @Description: hardware reset, erase user data from flash
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
VOID hw_reset_flash_data(VOID)
{
    return;
}

/**
 * @Function: mf_user_callback
 * @Description: 授权回调函数
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 清空flash中存储的数据
 */
VOID mf_user_callback(VOID_T) 
{
    hw_reset_flash_data();
    return;
}

/**
 * @Function:mf_user_product_test_cb 
 * @Description: 
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: none
 */
OPERATE_RET mf_user_product_test_cb(USHORT_T cmd, UCHAR_T *data, UINT_T len, OUT UCHAR_T **ret_data,OUT USHORT_T *ret_len) 
{
    return OPRT_OK;
}
/**
 * @Function:pre_app_init 
 * @Description: 
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: none
 */
VOID pre_app_init(VOID_T) 
{
    mf_test_ignore_close_flag();    // close 15 min mf_test
    return;
}

/**
 * @Function:app_init 
 * @Description: 
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: none
 */
VOID app_init(VOID_T) 
{
    /* stepper motor init */
    tuya_motor_pin_init(PH1, PH2, PH3, PH4);
    return;
}

/**
 * @Function:pre_device_init 
 * @Description: 
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: none
 */
VOID pre_device_init(VOID_T) 
{
    PR_DEBUG("%s",tuya_iot_get_sdk_info());
    PR_DEBUG("%s:%s", APP_BIN_NAME, DEV_SW_VERSION);
    PR_NOTICE("firmware compiled at %s %s", __DATE__, __TIME__);
    PR_NOTICE("system reset reason:[%s]",tuya_hal_system_get_rst_info());

    SetLogManageAttr(TY_LOG_LEVEL_DEBUG);

    return;
}

/**
 * @Function: hw_report_all_dp_status
 * @Description: 上报所有 dp 点
 * @Input: none
 * @Output: none
 * @Return: none
 * @Others: 
 */
VOID hw_report_all_dp_status(VOID)
{
    //report all dp status
}

/**
 * @Function: status_changed_cb
 * @Description: network status changed callback
 * @Input: status: current status
 * @Output: none
 * @Return: none
 * @Others: none
 */
VOID status_changed_cb(IN CONST GW_STATUS_E status)
{
    PR_NOTICE("status_changed_cb is status:%d",status);

    if(GW_NORMAL == status) {
        hw_report_all_dp_status();
    }else if(GW_RESET == status) {
        PR_NOTICE("status is GW_RESET");
    }
}

/**
 * @Function: upgrade_notify_cb
 * @Description: firmware download finish result callback
 * @Input: fw: firmware info
 * @Input: download_result: 0 means download succes. other means fail
 * @Input: pri_data: private data
 * @Output: none
 * @Return: none
 * @Others: none
 */
VOID upgrade_notify_cb(IN CONST FW_UG_S *fw, IN CONST INT_T download_result, IN PVOID_T pri_data)
{
    PR_DEBUG("download  Finish");
    PR_DEBUG("download_result:%d", download_result);
}

/**
 * @Function: get_file_data_cb
 * @Description: firmware download content process callback
 * @Input: fw: firmware info
 * @Input: total_len: firmware total size
 * @Input: offset: offset of this download package
 * @Input: data && len: this download package
 * @Input: pri_data: private data
 * @Output: remain_len: the size left to process in next cb
 * @Return: OPRT_OK: success  Other: fail
 * @Others: none
 */
OPERATE_RET get_file_data_cb(IN CONST FW_UG_S *fw, IN CONST UINT_T total_len, IN CONST UINT_T offset,
                                     IN CONST BYTE_T *data, IN CONST UINT_T len, OUT UINT_T *remain_len, IN PVOID_T 
pri_data)
{
    PR_DEBUG("Rev File Data");
    PR_DEBUG("Total_len:%d ", total_len);
    PR_DEBUG("Offset:%d Len:%d", offset, len);

    return OPRT_OK;
}


/**
 * @Function: gw_ug_inform_cb
 * @Description: gateway ota firmware available nofity callback
 * @Input: fw: firmware info
 * @Output: none
 * @Return: int:
 * @Others: 
 */
INT_T gw_ug_inform_cb(IN CONST FW_UG_S *fw)
{
    PR_DEBUG("Rev GW Upgrade Info");
    PR_DEBUG("fw->fw_url:%s", fw->fw_url);
    PR_DEBUG("fw->sw_ver:%s", fw->sw_ver);
    PR_DEBUG("fw->file_size:%d", fw->file_size);

    return tuya_iot_upgrade_gw(fw, get_file_data_cb, upgrade_notify_cb, NULL);
}

/**
 * @Function: gw_reset_cb
 * @Description: gateway restart callback, app remove the device 
 * @Input: type:gateway reset type
 * @Output: none
 * @Return: none
 * @Others: reset factory clear flash data
 */
VOID gw_reset_cb(IN CONST GW_RESET_TYPE_E type)
{
    PR_DEBUG("gw_reset_cb type:%d",type);
    if(GW_REMOTE_RESET_FACTORY != type) {
        PR_DEBUG("type is GW_REMOTE_RESET_FACTORY");
        return;
    }

    hw_reset_flash_data();
}

/**
 * @Function: dev_obj_dp_cb
 * @Description: obj dp info cmd callback, tuya cloud dp(data point) received
 * @Input: dp:obj dp info
 * @Output: none
 * @Return: none
 * @Others: app send data by dpid  control device stat
 */
VOID dev_obj_dp_cb(IN CONST TY_RECV_OBJ_DP_S *dp)
{
    PR_DEBUG("dp->cid:%s dp->dps_cnt:%d",dp->cid,dp->dps_cnt);
    UCHAR_T i = 0;

    // for(i = 0; i < dp->dps_cnt; i++) {
    //     tuya_printer_deal_dp_proc(&(dp->dps[i]));
    //     dev_report_dp_json_async(get_gw_cntl()->gw_if.id, dp->dps, dp->dps_cnt);
    // }
}

/**
 * @Function: dev_raw_dp_cb
 * @Description: raw dp info cmd callback, tuya cloud dp(data point) received (hex data)
 * @Input: dp: raw dp info
 * @Output: none
 * @Return: none
 * @Others: none
 */
VOID dev_raw_dp_cb(IN CONST TY_RECV_RAW_DP_S *dp)
{
    PR_DEBUG("raw data dpid:%d",dp->dpid);
    PR_DEBUG("recv len:%d",dp->len);
#if 1 
    INT_T i = 0;
    for(i = 0;i < dp->len;i++) {
        PR_DEBUG_RAW("%02X ",dp->data[i]);
    }
#endif
    PR_DEBUG_RAW("\n");
    PR_DEBUG("end");
    return;
}

/**
 * @Function: dev_dp_query_cb
 * @Description: dp info query callback, cloud or app actively query device info
 * @Input: dp_qry: query info
 * @Output: none
 * @Return: none
 * @Others: none
 */
STATIC VOID dev_dp_query_cb(IN CONST TY_DP_QUERY_S *dp_qry) 
{
    PR_NOTICE("Recv DP Query Cmd");

    hw_report_all_dp_status();
}

/**
 * @Function: wf_nw_status_cb
 * @Description: tuya-sdk network state check callback
 * @Input: stat: curr network status
 * @Output: none
 * @Return: none
 * @Others: none
 */
VOID wf_nw_status_cb(IN CONST GW_WIFI_NW_STAT_E stat)
{
    PR_NOTICE("wf_nw_status_cb,wifi_status:%d", stat);
    // wifi_state_led_reminder(stat);

    if(stat == STAT_AP_STA_CONN || stat >= STAT_STA_CONN) {
        hw_report_all_dp_status();
    }
}

/**
 * @Function: device_init
 * @Description: device initialization process 
 * @Input: none
 * @Output: none
 * @Return: OPRT_OK: success  Other: fail
 * @Others: none
 */
OPERATE_RET device_init(VOID_T) 
{
    OPERATE_RET op_ret = OPRT_OK;

    TY_IOT_CBS_S wf_cbs = {
        status_changed_cb,\
        gw_ug_inform_cb, \ 
        gw_reset_cb,\
        dev_obj_dp_cb,\
        dev_raw_dp_cb,\
        dev_dp_query_cb,\
        NULL,
    };
    
    op_ret = tuya_iot_wf_soc_dev_init_param(WIFI_WORK_MODE_SEL, WF_START_SMART_FIRST, &wf_cbs, NULL, PRODECT_ID, DEV_SW_VERSION);
    if(OPRT_OK != op_ret) {
        PR_ERR("tuya_iot_wf_soc_dev_init_param error,err_num:%d",op_ret);
        return op_ret;
    }

    op_ret = tuya_iot_reg_get_wf_nw_stat_cb(wf_nw_status_cb);
    if(OPRT_OK != op_ret) {
        PR_ERR("tuya_iot_reg_get_wf_nw_stat_cb is error,err_num:%d",op_ret);
        return op_ret;
    }

    tuya_motor_feedPaper_line(200, FORWARD, 2);
    tuya_motor_idle_motor();

    return op_ret;
}
