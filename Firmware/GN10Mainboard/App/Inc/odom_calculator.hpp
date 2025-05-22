#pragma once
#include <math.h>
#include <stdint.h>

/**
 * @brief 接地エンコーダーからのオドメトリ計算を行うクラス
 *
 */
class OdomCalculator
{
private:
    /* 機体固有値 */
    float encoder_resolution; // エンコーダの分解能
    float wheel_radius;       // 車輪の半径
    /* 内部使用変数 */
    float robot_velocity[2]; // ロボットの速度 (x, y)
    float robot_coord[2];    // ロボットの座標 (x, y)

    /**
     * @brief ロボット座標系からフィールド座標系に変換する
     * @param vx x軸方向の速度[m/s]
     * @param vy y軸方向の速度[m/s]
     * @param theta 機体の角度[rad]
     */
    void convert_coord(float *vx, float *vy, float theta);

public:
    /**
     * @brief コンストラクタ
     * @param encoder_resolution エンコーダの分解能[CPR]
     * @param wheel_radius 車輪の半径[m]
     */
    OdomCalculator(float encoder_resolution, float wheel_radius);

    /**
     * @brief エンコーダの値を設定する
     * @param vx_count x軸方向のエンコーダの値
     * @param vy_count y軸方向のエンコーダの値
     */
    void set_encoder_count(int16_t vx_count, int16_t vy_count);

    /**
     * @brief ロボットの座標を取得する
     *
     * @param x x座標[m]
     * @param y y座標[m]
     * @param theta 機体の角度[rad]
     * @param period 計算周期[s]
     * @details ロボットの座標は、ロボットの初期位置からの相対座標である。
     * @note エンコーダーのサンプリング周期に合わせて実行してください。
     */
    void get_robot_coord(float *x, float *y, float theta, float period);

    /**
     * @brief ロボットの座標をリセットする
     * @details ロボットの座標をリセットする。ロボットの初期位置からの相対座標を0にする。
     *
     */
    void reset_robot_coord();
};