/* Includes ------------------------------------------------------------------*/
#include "uni_log.h"
#include "tuya_dp_process.h"
#include "tuya_gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "uni_thread.h"

/* Private includes ----------------------------------------------------------*/
#include "tuya_stepper_motor.h"
#include "tuya_dp_process.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MOTOR_A TY_GPIOA_6 //PWM0
#define MOTOR_B TY_GPIOA_7 //PWM1
#define MOTOR_C TY_GPIOA_8 //PWM2
#define MOTOR_D TY_GPIOA_9 //PWM3

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


VOID_T motor_speed_set(UINT16 MS)
{
    //A->1, other -> 0
    tuya_gpio_write(MOTOR_A, TRUE);
    tuya_gpio_write(MOTOR_B, FALSE);
    tuya_gpio_write(MOTOR_C, FALSE);
    tuya_gpio_write(MOTOR_D, FALSE);
    tuya_hal_system_sleep(MS);

    //A,B -> 1, other -> 0
    tuya_gpio_write(MOTOR_A, TRUE);
    tuya_gpio_write(MOTOR_B, TRUE);
    tuya_gpio_write(MOTOR_C, FALSE);
    tuya_gpio_write(MOTOR_D, FALSE);
    tuya_hal_system_sleep(MS);

    //B -> 1, other -> 0
    tuya_gpio_write(MOTOR_A, FALSE);
    tuya_gpio_write(MOTOR_B, TRUE);
    tuya_gpio_write(MOTOR_C, FALSE);
    tuya_gpio_write(MOTOR_D, FALSE);
    tuya_hal_system_sleep(MS);

    //B, C -> 1, other -> 0
    tuya_gpio_write(MOTOR_A, FALSE);
    tuya_gpio_write(MOTOR_B, TRUE);
    tuya_gpio_write(MOTOR_C, TRUE);
    tuya_gpio_write(MOTOR_D, FALSE);
    tuya_hal_system_sleep(MS);

    //C -> 1, other -> 0
    tuya_gpio_write(MOTOR_A, FALSE);
    tuya_gpio_write(MOTOR_B, FALSE);
    tuya_gpio_write(MOTOR_C, TRUE);
    tuya_gpio_write(MOTOR_D, FALSE);
    tuya_hal_system_sleep(MS);

    //C,D -> 1, other -> 0
    tuya_gpio_write(MOTOR_A, FALSE);
    tuya_gpio_write(MOTOR_B, FALSE);
    tuya_gpio_write(MOTOR_C, TRUE);
    tuya_gpio_write(MOTOR_D, TRUE);
    tuya_hal_system_sleep(MS);

    //D -> 1, other -> 0
    tuya_gpio_write(MOTOR_A, FALSE);
    tuya_gpio_write(MOTOR_B, FALSE);
    tuya_gpio_write(MOTOR_C, FALSE);
    tuya_gpio_write(MOTOR_D, TRUE);
    tuya_hal_system_sleep(MS);

    //D,A -> 1, other -> 0
    tuya_gpio_write(MOTOR_A, TRUE);
    tuya_gpio_write(MOTOR_B, FALSE);
    tuya_gpio_write(MOTOR_C, FALSE);
    tuya_gpio_write(MOTOR_D, TRUE);
    tuya_hal_system_sleep(MS);
}

VOID_T motor_stop(VOID_T)
{
    tuya_gpio_write(MOTOR_A, FALSE);
    tuya_gpio_write(MOTOR_B, FALSE);
    tuya_gpio_write(MOTOR_C, FALSE);
    tuya_gpio_write(MOTOR_D, FALSE);
    tuya_hal_system_sleep(500);
}

VOID_T motor_task(VOID_T)
{
    while(1) {
        if (sensor_state.power == TRUE) {
            motor_speed_set(5);
        } else {
            motor_stop();
        }
        
    }
}


VOID_T stepper_motor_init(VOID_T)
{
    tuya_gpio_inout_set(MOTOR_A, FALSE);
    tuya_gpio_inout_set(MOTOR_B, FALSE);
    tuya_gpio_inout_set(MOTOR_C, FALSE);
    tuya_gpio_inout_set(MOTOR_D, FALSE);

    tuya_gpio_write(MOTOR_A, FALSE);
    tuya_gpio_write(MOTOR_B, FALSE);
    tuya_gpio_write(MOTOR_C, FALSE);
    tuya_gpio_write(MOTOR_D, FALSE);

    tuya_hal_thread_create(NULL, "step motor run", 512 * 4, TRD_PRIO_2, motor_task, NULL);
}
