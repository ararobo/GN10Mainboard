#pragma once
#include <stdint.h>
#include "fdcan.h"
#include "gpio.h"
#include "main.h"

class App
{
private:
    bool dip_switche_states[4];

    uint16_t led_brink_counter = 0;
    uint16_t led_brink_period = 500;

    uint8_t seven_segment_led_number = 0;

    int16_t target = 0;

    uint8_t uart1_rx_buffer[10];
    uint8_t uart2_rx_buffer[10];

    void led_brink();
    void read_DIP_switches();

public:
    void init();
    void loop();
    void CAN_callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);
    void UART_callback(UART_HandleTypeDef *huart);
};
