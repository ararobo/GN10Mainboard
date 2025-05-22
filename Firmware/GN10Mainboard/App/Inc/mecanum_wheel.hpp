/**
 * @file    mecanum_wheel.hpp
 * @author  Tooda Haruki, aiba-gento
 * @brief   メカナム逆運動学を解くクラス
 * @version 2.0
 * @date    2025-05-08
 */
#pragma once

#include <math.h>

class MecanumWheel
{
private:
    /* 機体固有値 */
    float chassis_width;  // 車体の幅
    float chassis_length; // 車体の長さ
    float wheel_radius;   // 車輪の半径
    float mecanum_angle;  // メカナムホイールの角度
    /* 内部使用変数 */
    float chassis_diagonal;  // 車体の対角線の長さ
    float wheel_velocity[4]; // 車輪の速度 (右前, 左前, 左後, 右後)
    float mecanum_cos;       // メカナムホイールのcos値
    float mecanum_sin;       // メカナムホイールのsin値

public:
    /**
     * @brief コンストラクタ
     * @param chassis_width 車体の幅[m]
     * @param chassis_length 車体の長さ[m]
     * @param wheel_radius 車輪の半径[m]
     * @param mecanum_angle メカナムホイールの角度[deg]
     */
    MecanumWheel(float chassis_width, float chassis_length, float wheel_radius, float mecanum_angle);

    /**
     * @brief ロボット座標系からフィールド座標系に変換する
     * @param vx x軸方向の速度[m/s]
     * @param vy y軸方向の速度[m/s]
     * @param theta 機体の角度[rad/s](ジャイロセンサの値等)
     */
    void convert_coord(float *vx, float *vy, float theta);

    /**
     * @brief メカナムホイールの速度を計算する
     * @param vx x軸方向の速度[m/s]
     * @param vy y軸方向の速度[m/s]
     * @param omega 回転速度[rad/s]
     */
    void calculate_wheel_speed(float vx, float vy, float omega);

    /**
     * @brief 車輪の角速度を取得する
     * @param front_right 右前車輪の角速度
     * @param front_left 左前車輪の角速度
     * @param back_left 左後車輪の角速度
     * @param back_right 右後車輪の角速度
     */
    void get_wheel_angular_velocity(float *front_right, float *front_left, float *back_left, float *back_right);

    /**
     * @brief 車輪の速度を取得する
     * @param front_right 右前車輪の速度
     * @param front_left 左前車輪の速度
     * @param back_left 左後車輪の速度
     * @param back_right 右後車輪の速度
     */
    void get_wheel_velocity(float *front_right, float *front_left, float *back_left, float *back_right);
};
