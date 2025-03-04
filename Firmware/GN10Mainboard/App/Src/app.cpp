#include "app.hpp"
#include "serial_printf.hpp"

void App::init()
{
    log_printf(LOG_ERROR, "SYSTEMATIC LOVE\n");
    read_DIP_switches();
    log_printf(LOG_INFO, "DIP switches: %d %d %d %d\n", dip_switche_states[0], dip_switche_states[1], dip_switche_states[2], dip_switche_states[3]);
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
    log_printf(LOG_INFO, "initilized\n");
}

void App::loop()
{
    led_brink();
    HAL_Delay(1);
}

void App::CAN_callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
}

void App::led_brink()
{
    if (led_brink_counter++ > led_brink_period)
    {
        led_brink_counter = 0;
        HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin);
    }
}

void App::read_DIP_switches()
{
    dip_switche_states[0] = HAL_GPIO_ReadPin(DIP_1_GPIO_Port, DIP_1_Pin);
    dip_switche_states[1] = HAL_GPIO_ReadPin(DIP_2_GPIO_Port, DIP_2_Pin);
    dip_switche_states[2] = HAL_GPIO_ReadPin(DIP_3_GPIO_Port, DIP_3_Pin);
    dip_switche_states[3] = HAL_GPIO_ReadPin(DIP_4_GPIO_Port, DIP_4_Pin);
}