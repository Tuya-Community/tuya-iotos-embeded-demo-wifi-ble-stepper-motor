/* Includes ------------------------------------------------------------------*/
#include "uni_log.h"
#include "tuya_cloud_wifi_defs.h"

/* Private includes ----------------------------------------------------------*/
#include "tuya_dp_process.h"

/* Private typedef -----------------------------------------------------------*/
SENSOR_STATE_T sensor_state = {
    .dp_id_switch = DPID_SWITCH,
    .power = FALSE,
};

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
VOID_T deal_dp_proc(IN CONST TY_OBJ_DP_S *root)
{
    UCHAR_T dpid;

    dpid = root->dpid;
    PR_DEBUG("dpid:%d",dpid);

    if (dpid == DPID_SWITCH) {
        sensor_state.power = root->value.dp_bool;
    }

    hw_report_all_dp_status();
}

VOID_T hw_report_all_dp_status(VOID_T)
{

    OPERATE_RET op_ret = OPRT_OK;
    GW_WIFI_NW_STAT_E wifi_state = 0xFF;

    INT_T dp_cnt = 0;
    dp_cnt = 1;

    /* 没有连接到路由器，退出 */
    op_ret = get_wf_gw_nw_status(&wifi_state);
    if (OPRT_OK != op_ret) {
        PR_ERR("get wifi state err");
        return;
    }
    if (wifi_state <= STAT_AP_STA_DISC || wifi_state == STAT_STA_DISC) {
        return;
    }


    TY_OBJ_DP_S *dp_arr = (TY_OBJ_DP_S *)Malloc(dp_cnt*SIZEOF(TY_OBJ_DP_S));
    if(NULL == dp_arr) {
        PR_ERR("malloc failed");
        return;
    }

    memset(dp_arr, 0, dp_cnt*SIZEOF(TY_OBJ_DP_S));

    /*  */
    dp_arr[0].dpid = sensor_state.dp_id_switch;
    dp_arr[0].type = PROP_VALUE;
    dp_arr[0].time_stamp = 0;
    dp_arr[0].value.dp_value = sensor_state.power;

    op_ret = dev_report_dp_json_async(NULL , dp_arr, dp_cnt);
    Free(dp_arr);
    dp_arr = NULL;
    if(OPRT_OK != op_ret) {
        PR_ERR("dev_report_dp_json_async relay_config data error,err_num",op_ret);
    }

    PR_DEBUG("dp_query report_all_dp_data");
    
    return;
}

