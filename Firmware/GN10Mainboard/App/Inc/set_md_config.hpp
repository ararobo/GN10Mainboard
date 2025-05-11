#pragma once
#include "md_config.hpp"

md_config_t md_config[16];

/**
 * @brief MDの設定を行う関数
 * @details MDの設定を行う関数です。各MDの設定はmd_config配列に格納されます。
 *          各MDの設定は、max_output、max_acceleration、control_period、encoder_period、encoder_type、limit_switch_behavior、optionで構成されています。
 */
void set_md_config()
{
    /* 足回り 右前 */
    md_config[0].max_output = 3199;         // 最大出力 duty
    md_config[0].max_acceleration = 100;    // 台形制御の最大加速 duty/制御周期
    md_config[0].control_period = 10;       // 制御周期 ms
    md_config[0].encoder_period = 10;       // エンコーダーのサンプリング周期 ms
    md_config[0].encoder_type = 1;          // 0:無し、1:インクリメンタル、2:アブソリュート
    md_config[0].limit_switch_behavior = 0; // リミットスイッチの動作設定
    md_config[0].option = 0;                // 基板の固有機能や使用用途に合わせて決定（未定義）
    /* 足回り 左前 */
    md_config[1].max_output = 3199;         // 最大出力 duty
    md_config[1].max_acceleration = 100;    // 台形制御の最大加速 duty/制御周期
    md_config[1].control_period = 10;       // 制御周期 ms
    md_config[1].encoder_period = 10;       // エンコーダーのサンプリング周期 ms
    md_config[1].encoder_type = 1;          // 0:無し、1:インクリメンタル、2:アブソリュート
    md_config[1].limit_switch_behavior = 0; // リミットスイッチの動作設定
    md_config[1].option = 0;                // 基板の固有機能や使用用途に合わせて決定（未定義）
    /* 足回り 左後 */
    md_config[2].max_output = 3199;         // 最大出力 duty
    md_config[2].max_acceleration = 100;    // 台形制御の最大加速 duty/制御周期
    md_config[2].control_period = 10;       // 制御周期 ms
    md_config[2].encoder_period = 10;       // エンコーダーのサンプリング周期 ms
    md_config[2].encoder_type = 0;          // 0:無し、1:インクリメンタル、2:アブソリュート
    md_config[2].limit_switch_behavior = 0; // リミットスイッチの動作設定
    md_config[2].option = 0;                // 基板の固有機能や使用用途に合わせて決定（未定義）
    /* 足回り 右後 */
    md_config[3].max_output = 3199;         // 最大出力 duty
    md_config[3].max_acceleration = 100;    // 台形制御の最大加速 duty/制御周期
    md_config[3].control_period = 10;       // 制御周期 ms
    md_config[3].encoder_period = 10;       // エンコーダーのサンプリング周期 ms
    md_config[3].encoder_type = 0;          // 0:無し、1:インクリメンタル、2:アブソリュート
    md_config[3].limit_switch_behavior = 0; // リミットスイッチの動作設定
    md_config[3].option = 0;                // 基板の固有機能や使用用途に合わせて決定（未定義）

    md_config[4].max_output = 3199;         // 最大出力 duty
    md_config[4].max_acceleration = 100;    // 台形制御の最大加速 duty/制御周期
    md_config[4].control_period = 10;       // 制御周期 ms
    md_config[4].encoder_period = 10;       // エンコーダーのサンプリング周期 ms
    md_config[4].encoder_type = 0;          // 0:無し、1:インクリメンタル、2:アブソリュート
    md_config[4].limit_switch_behavior = 0; // リミットスイッチの動作設定
    md_config[4].option = 0;                // 基板の固有機能や使用用途に合わせて決定（未定義）
}