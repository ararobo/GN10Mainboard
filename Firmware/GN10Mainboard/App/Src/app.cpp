#include "app.hpp"
#include "serial_printf.hpp"
#include "set_md_config.hpp"
#include "mecanum_wheel.hpp"
#include "pc_data_master.hpp"
#include "odom_calculator.hpp"

#define period_odom 0.01f // オドメトリの計算周期[s]

MDDataMaster md_data_master;
PCDataMaster pc_data_master(0); // PCのIDを指定
MecanumWheel mecanum_wheel(
    0.5f,   // 車体の幅[m]
    0.5f,   // 車体の長さ[m]
    0.001f, // 車輪の半径[m]
    45.0f   // メカナムホイールの角度[deg]
);
OdomCalculator odom(
    4096.0f, // エンコーダの分解能[CPR]
    0.001f   // 車輪の半径[m]
);

void App::setup()
{
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET); // LEDを点灯
    log_printf(LOG_INFO, "App# Setup\n");
    // FDCANの初期化
    md_data_master.init(0, 0); // フィルタIDとマスクを設定
    pc_data_master.init(0, 0); // フィルタIDとマスクを設定
    // MDの設定
    set_md_config();
    // MDの初期化
    for (uint8_t i = 0; i < md_num; i++)
    {
        md_data_master.send_init(i, &md_config[i]); // 初期化データの送信
        HAL_Delay(10);                              // 10ms待機
    }

    log_printf(LOG_INFO, "MD# Init\n");
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET); // LEDを消灯
}

void App::loop()
{
    // メカナムホイールの制御
    if (pc_data_master.get_cmd_vel(&vx, &vy, &omega))
    {
        mecanum_wheel.calculate_wheel_speed(vx, vy, omega);                                                                       // 車輪の速度を計算
        mecanum_wheel.get_wheel_angular_velocity(&wheel_velocity[0], &wheel_velocity[1], &wheel_velocity[2], &wheel_velocity[3]); // 車輪の速度を取得
        log_printf(LOG_DEBUG, "wheel_velocity: ");
        for (uint8_t i = 0; i < md_num; i++)
        {
            md_target[i] = int(wheel_velocity[i]); // 車輪の速度を整数値に変換
            serial_printf("%d ", md_target[i]);    // 車輪の速度を表示
        }
        serial_printf("\n");
        md_data_master.send_multi_target(0, md_target); // 車輪の速度をMDに送信
    }
    // 接地エンコーダの値を取得
    md_data_master.get_encoder(0, &odom_encoder_count[0]);
    md_data_master.get_encoder(1, &odom_encoder_count[1]);
    // LEDの点滅
    led_blink();
}

void App::timer6_process()
{
    // オドメトリの計算
    odom.set_encoder_count(odom_encoder_count[0], odom_encoder_count[1]);                               // エンコーダの値を設定
    odom.get_robot_coord(&odom_robot_coord[0], &odom_robot_coord[1], odom_robot_coord[2], period_odom); // ロボットの座標を取得
    // ロボットの座標を送信
    pc_data_master.send_odometry(odom_robot_coord[0], odom_robot_coord[1], odom_robot_coord[2]); // ロボットの座標を送信
}

void App::can_callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    if (hfdcan->Instance == hfdcan2.Instance)
    {
        md_data_master.can_callback_process(hfdcan, RxFifo0ITs);
    }
    else if (hfdcan->Instance == hfdcan3.Instance)
    {
        pc_data_master.can_callback_process(hfdcan, RxFifo0ITs);
    }
}

void App::led_blink()
{
    led_blink_counter++;
    if (led_blink_counter >= led_blink_interval)
    {
        HAL_GPIO_TogglePin(LED_BLUE_GPIO_Port, LED_BLUE_Pin); // LEDをトグル
        led_blink_counter = 0;
    }
}

void App::timer_callback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6)
    {
        timer6_process();
    }
}