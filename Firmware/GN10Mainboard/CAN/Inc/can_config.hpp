/**
 * @file can_config.hpp
 * @author gn10g (8gn24gn25@gmail.com)
 * @brief CAN通信のID設定を行う
 * @version 2.2
 * @date 2025-05-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <stdint.h>

namespace can_config
{
    namespace direction
    {
        static constexpr uint8_t slave = 0;
        static constexpr uint8_t master = 1;
    }
    namespace board_type
    {
        static constexpr uint8_t ems = 0;
        static constexpr uint8_t md = 1;
        static constexpr uint8_t servo = 2;
        static constexpr uint8_t solenoid = 3;
        static constexpr uint8_t pc = 4;
        static constexpr uint8_t sensor = 5;
        static constexpr uint8_t led = 6;
    }
    namespace data_type
    {
        namespace ems
        {
            static constexpr uint8_t init = 0;
            static constexpr uint8_t status = 1;
            static constexpr uint8_t emergency_stop = 2;
        }
        namespace md
        {
            static constexpr uint8_t init = 0;
            static constexpr uint8_t target = 1;
            static constexpr uint8_t limit_switch = 2;
            static constexpr uint8_t gain = 3;
            static constexpr uint8_t multi_target = 4;
        }
        namespace servo
        {
            static constexpr uint8_t init = 0;
            static constexpr uint8_t target = 1;
            static constexpr uint8_t frequency = 2;
        }
        namespace solenoid
        {
            static constexpr uint8_t init = 0;
            static constexpr uint8_t target = 1;
        }
        namespace pc
        {
            static constexpr uint8_t init = 0;
            static constexpr uint8_t target = 1;
            static constexpr uint8_t cmd_vel = 2;
        }
        namespace sensor
        {
            static constexpr uint8_t init = 0;
            static constexpr uint8_t tof = 1;
        }
        namespace led
        {
            static constexpr uint8_t init = 0;
        }
    }
    /**
     * @brief CAN IDをエンコードする。
     *
     * @param direction 通信方向 to_slave:0, to_master:1
     * @param board_type 基板の種類 emergency_stop_board:0, motor_driver:1, servo_driver:2, solenoid_driver:3, led_board:4, sensor_board:5, wireless_board:6, other:7
     * @param board_id 基板のID
     * @param data_type データの種類
     * @return uint16_t 生成したCAN ID
     */
    uint16_t encode_id(uint8_t direction, uint8_t board_type, uint8_t board_id, uint8_t data_type);

    /**
     * @brief CAN IDをデコードする。
     *
     * @param can_id CAN ID
     * @param direction 通信方向 to_slave:0, to_master:1
     * @param board_type 基板の種類 emergency_stop_board:0, motor_driver:1, servo_driver:2, solenoid_driver:3, led_board:4, sensor_board:5, wireless_board:6, other:7
     * @param board_id 基板のID
     * @param data_type データの種類
     */
    void decode_id(uint16_t can_id, uint8_t &direction, uint8_t &board_type, uint8_t &board_id, uint8_t &data_type);
}