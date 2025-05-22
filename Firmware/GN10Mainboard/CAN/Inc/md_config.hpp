/**
 * @file md_config.hpp
 * @author gn10g (8gn24gn25@gmail.com)
 * @brief MDの設定を扱う型
 * @version 2.0
 * @date 2025-04-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <stdint.h>

union md_config_t
{
    struct
    {
        uint16_t max_output;           // 最大出力 duty
        uint8_t max_acceleration;      // 台形制御の最大加速 duty/10ms
        uint8_t control_period;        // 制御周期 ms
        uint8_t encoder_period;        // エンコーダーのサンプリング周期 ms
        uint8_t encoder_type;          // 0:無し、1:インクリメンタル、2:アブソリュート
        uint8_t limit_switch_behavior; // リミットスイッチの動作設定
        uint8_t option;                // 基板の固有機能や使用用途に合わせて決定（未定義）
    } __attribute__((__packed__));
    uint8_t code[8]; // 送信バイト配列
} __attribute__((__packed__));