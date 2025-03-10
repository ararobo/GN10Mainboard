#include "app.hpp"
#include "serial_printf.hpp"
#include "seven_segment_led.hpp"
#include "can_driver.hpp"

CANDriver can_driver_0(0);

void App::init()
{
    // SYSTEMATIC LOVE
    SevenSegmentLED::set_blank();
    log_printf(LOG_ERROR, "SYSTEMATIC LOVE\n");
    read_DIP_switches();
    log_printf(LOG_INFO, "DIP switches: %d %d %d %d\n", dip_switche_states[0], dip_switche_states[1], dip_switche_states[2], dip_switche_states[3]);
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
    log_printf(LOG_INFO, "initilized\n");
    can_driver_0.init();
    log_printf(LOG_INFO, "CAN initialized\n");
    md_config_t md_config;
    md_config.max_output = 3199;
    md_config.max_acceleration = 100;
    md_config.control_period = 1;
    md_config.encoder_period = 10;
    md_config.encoder_type = 0;
    md_config.limit_switch_behavior = 0;
    md_config.option = 0;
    can_driver_0.send_init(md_config);
    log_printf(LOG_INFO, "send init\n");
}

void App::loop()
{
    led_brink();
    SevenSegmentLED::set_number(seven_segment_led_number);
    can_driver_0.send_target(target);
    target++;
    if (target > 3199)
    {
        target = -3199;
    }
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
        seven_segment_led_number++;
        if (seven_segment_led_number > 9)
        {
            seven_segment_led_number = 0;
        }
    }
}

void App::read_DIP_switches()
{
    dip_switche_states[0] = HAL_GPIO_ReadPin(DIP_1_GPIO_Port, DIP_1_Pin);
    dip_switche_states[1] = HAL_GPIO_ReadPin(DIP_2_GPIO_Port, DIP_2_Pin);
    dip_switche_states[2] = HAL_GPIO_ReadPin(DIP_3_GPIO_Port, DIP_3_Pin);
    dip_switche_states[3] = HAL_GPIO_ReadPin(DIP_4_GPIO_Port, DIP_4_Pin);
}