#pragma once
#include "md_data_master.hpp"
#include "tim.h"

class App
{
private:
    uint8_t md_num = 4;      // MDの数
    float vx;                // x軸方向の速度[m/s]
    float vy;                // y軸方向の速度[m/s]
    float omega;             // 回転速度[rad/s]
    float wheel_velocity[4]; // 車輪の速度 (右前, 左前, 左後, 右後)
    int16_t md_target[16];
    uint16_t led_blink_counter = 0;     // LED点滅カウンタ
    uint16_t led_blink_interval = 1000; // LED点滅間隔[ms]
    int16_t odom_encoder_count[2];      // 接地エンコーダの値(x, y)
    float odom_robot_coord[3];          // ロボットの座標 (x, y, theta)

    void led_blink();
    void timer6_process();

public:
    void setup();
    void loop();
    void can_callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);
    void timer_callback(TIM_HandleTypeDef *htim);
};