#pragma once
#include "can_config.hpp"
#include "stm32_fdcan3_driver.hpp"

class PCDataMaster : public STM32FDCAN3Driver
{
private:
    uint8_t board_id;       // 基板のID
    int16_t velocity_scale; // 送信時のベクトルの係数
    /* 一時処理用変数 */
    uint8_t packet_direction;  // 進行方向
    uint8_t packet_board_type; // 基板の種類
    uint8_t packet_board_id;   // 基板のID
    uint8_t packet_data_type;  // データの種類
    /* 受信バッファとフラグ */
    uint8_t init_buffer[1];    // 初期化バッファ
    uint8_t target_buffer[8];  // 目標値バッファ
    uint8_t cmd_vel_buffer[6]; // cmd_velバッファ
    bool init_flag;            // 初期化フラグ
    bool target_flag;          // 目標値フラグ
    bool cmd_vel_flag;         // cmd_velフラグ

protected:
    /**
     * @brief 受信データの処理を行う
     *
     * @param id CANのID
     * @param data 受信データ
     * @param len データの長さ
     */
    void receive(uint16_t id, uint8_t *data, uint8_t len) override;

public:
    PCDataMaster(uint8_t board_id_ = 0);

    void send_init(uint8_t config);

    void send_odometry(float x, float y, float theta);

    bool get_init(uint8_t *config);

    bool get_cmd_vel(float *vx, float *vy, float *omega);
};