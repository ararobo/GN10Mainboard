/**
 * @file md_data_master.hpp
 * @author gn10g (8gn24gn25@gmail.com)
 * @brief MDのデータを扱うクラス
 * @version 2.1
 * @date 2025-05-10
 * @note 各ハードウェアに対応するCANDriverクラスを継承して使う
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include "can_config.hpp"
#include "md_config.hpp"
#include "stm32_fdcan2_driver.hpp"

class MDDataMaster : public STM32FDCAN2Driver
{
private:
    struct md_data_t
    {
        uint8_t init_buffer[1];    // 初期化バッファ
        uint8_t target_buffer[2];  // 目標値バッファ
        uint8_t gain_buffer[3][4]; // ゲインバッファ
        uint8_t limit_switch[1];   // リミットスイッチバッファ
        /* 受信フラグ */
        bool init_flag;         // 初期化フラグ
        bool target_flag;       // 目標値フラグ
        bool limit_switch_flag; // リミットスイッチフラグ
        bool gain_flag[3];      // ゲインフラグ
    } md_data[16];              // 16基板分のデータを保持

    /* 一時処理用変数 */
    uint8_t packet_direction;  // 進行方向
    uint8_t packet_board_type; // 基板の種類
    uint8_t packet_board_id;   // 基板のID
    uint8_t packet_data_type;  // データの種類

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
    MDDataMaster();

    /**
     * @brief CANの初期化
     *
     * @param id 基板のID
     * @param config MDの設定
     */
    void send_init(uint8_t id, md_config_t *config);

    /**
     * @brief 目標値の送信
     *
     * @param id 基板のID
     * @param target 目標値
     */
    void send_target(uint8_t id, int16_t target);

    /**
     * @brief 4つの基板に目標値を送信
     *
     * @param id 基板のIDのオフセット(0,4,8,12)
     * @param target 目標値の配列
     * @note 送信する基板のIDは id + 0, id + 1, id + 2, id + 3
     */
    void send_multi_target(uint8_t id, int16_t target[4]);

    /**
     * @brief ゲインの送信
     *
     * @param id 基板のID
     * @param gain_type ゲインの種類 0: Pゲイン、1: Iゲイン、2: Dゲイン
     * @param gain ゲイン
     */
    void send_gain(uint8_t id, uint8_t gain_type, float gain);

    /**
     * @brief 初期化フラグの取得
     *
     * @param id 基板のID
     * @param md_type MDの種類
     * @return true 初期化フラグが立っている
     * @return false 初期化フラグが立っていない
     */
    bool get_init(uint8_t id, uint8_t *md_type);

    /**
     * @brief エンコーダーの取得
     *
     * @param id 基板のID
     * @param encoder エンコーダーの値
     * @return true エンコーダーの値が取得できた
     * @return false エンコーダーの値が取得できなかった
     */
    bool get_encoder(uint8_t id, int16_t *encoder);

    /**
     * @brief リミットスイッチの取得
     *
     * @param id 基板のID
     * @param limit_switch リミットスイッチの値(bitごとに各スイッチの状態を保持)
     * @return true リミットスイッチの値が取得できた
     * @return false リミットスイッチの値が取得できなかった
     */
    bool get_limit_switch(uint8_t id, uint8_t *limit_switch);

    /**
     * @brief ゲインの取得
     *
     * @param id 基板のID
     * @param gain_type ゲインの種類 0: Pゲイン、1: Iゲイン、2: Dゲイン
     * @param gain ゲイン
     * @return true ゲインが取得できた
     * @return false ゲインが取得できなかった
     */
    bool get_gain(uint8_t id, uint8_t gain_type, float *gain);
};