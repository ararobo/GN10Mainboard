#include "odom_calculator.hpp"

OdomCalculator::OdomCalculator(float encoder_resolution, float wheel_radius)
    : encoder_resolution(encoder_resolution), wheel_radius(wheel_radius)
{
    robot_velocity[0] = 0.0f; // x軸方向の速度
    robot_velocity[1] = 0.0f; // y軸方向の速度
}

void OdomCalculator::set_encoder_count(int16_t vx_count, int16_t vy_count)
{
    robot_velocity[0] = (float)vx_count * 2.0f * M_PI * wheel_radius / encoder_resolution; // x軸方向の速度
    robot_velocity[1] = (float)vy_count * 2.0f * M_PI * wheel_radius / encoder_resolution; // y軸方向の速度
}

void OdomCalculator::get_robot_coord(float *x, float *y, float theta, float period)
{
    float vx = robot_velocity[0];
    float vy = robot_velocity[1];
    convert_coord(&vx, &vy, theta); // ロボット座標系からフィールド座標系に変換
    robot_coord[0] += vx * period;  // x座標を更新
    robot_coord[1] += vy * period;  // y座標を更新
    *x = robot_coord[0];            // x座標を返す
    *y = robot_coord[1];            // y座標を返す
}

void OdomCalculator::convert_coord(float *vx, float *vy, float theta)
{
    *vx = cos(theta) * *vx + sin(theta) * *vy;  // x軸方向の速度
    *vy = -sin(theta) * *vx + cos(theta) * *vy; // y軸方向の速度
}

void OdomCalculator::reset_robot_coord()
{
    robot_coord[0] = 0.0f; // x座標をリセット
    robot_coord[1] = 0.0f; // y座標をリセット
}