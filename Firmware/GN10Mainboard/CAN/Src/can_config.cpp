/**
 * @file can_config.cpp
 * @author gn10g (8gn24gn25@gmail.com)
 * @brief CAN通信のID設定を行う
 * @version 2.0
 * @date 2025-04-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "can_config.hpp"

namespace can_config
{
    uint16_t encode_id(uint8_t direction, uint8_t board_type, uint8_t board_id, uint8_t data_type)
    {
        return ((direction & 0x1) << 10) | ((board_type & 0x7) << 7) | ((board_id & 0xf) << 3) | (data_type & 0x7);
    }

    void decode_id(uint16_t can_id, uint8_t &direction, uint8_t &board_type, uint8_t &board_id, uint8_t &data_type)
    {
        direction = (can_id >> 10) & 0x1;
        board_type = (can_id >> 7) & 0x7;
        board_id = (can_id >> 3) & 0xf;
        data_type = can_id & 0x7;
    }
}