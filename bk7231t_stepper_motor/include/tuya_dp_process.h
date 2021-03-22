#ifndef __TUYA_DP_PROCESS_H__
#define __TUYA_DP_PROCESS_H__
/* Includes ------------------------------------------------------------------*/
#include "tuya_cloud_types.h"
#include "tuya_iot_com_api.h"

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

/* Exported types ------------------------------------------------------------*/
typedef UINT8_T SENSOR_DP_T;
#define DPID_SWITCH 101

typedef struct  {
    SENSOR_DP_T dp_id_switch;

    UINT16_T power;
}SENSOR_STATE_T;

extern SENSOR_STATE_T sensor_state;

/* Exported constants --------------------------------------------------------*/              
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
VOID_T hw_report_all_dp_status(VOID_T);
VOID_T deal_dp_proc(IN CONST TY_OBJ_DP_S *root);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TUYA_DP_PROCESS */