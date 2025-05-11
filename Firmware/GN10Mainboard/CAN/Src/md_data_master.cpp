/**
 * @file md_data_master.cpp
 * @author gn10g (8gn24gn25@gmail.com)
 * @brief MDのデータを扱うクラス
 * @version 2.1
 * @date 2025-05-10
 * @note 各ハードウェアに対応するCANDriverクラスを継承して使う
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "md_data_master.hpp"
#include <cstring>

MDDataMaster::MDDataMaster()
{
    // 受信フラグの初期化
    for (int i = 0; i < 16; i++)
    {
        md_data[i].init_flag = false;
        md_data[i].target_flag = false;
        md_data[i].limit_switch_flag = false;
        for (int j = 0; j < 3; j++)
        {
            md_data[i].gain_flag[j] = false;
        }
    }
}

void MDDataMaster::receive(uint16_t id, uint8_t *data, uint8_t len)
{
    // 受信パケットのCAN-IDからパケットの情報を取得
    can_config::decode_id(id, this->packet_direction, this->packet_board_type,
                          this->packet_board_id, this->packet_data_type);

    if (this->packet_direction == can_config::direction::master &&
        this->packet_board_type == can_config::board_type::md)
    {
        switch (this->packet_data_type)
        {
        case can_config::data_type::md::init:
            if (len != 1)
                return;
            std::memcpy(this->md_data[this->packet_board_id].init_buffer, data, len);
            this->md_data[this->packet_board_id].init_flag = true;
            break;

        case can_config::data_type::md::target:
            if (len != 2)
                return;
            std::memcpy(this->md_data[this->packet_board_id].target_buffer, data, len);
            this->md_data[this->packet_board_id].target_flag = true;
            break;

        case can_config::data_type::md::gain:
            if (len != 5)
                return;
            std::memcpy(this->md_data[this->packet_board_id].gain_buffer[data[0]], data + 1, len);
            this->md_data[this->packet_board_id].gain_flag[data[0]] = true;
            break;

        case can_config::data_type::md::limit_switch:
            if (len != 1)
                return;
            std::memcpy(this->md_data[this->packet_board_id].limit_switch, data, len);
            this->md_data[this->packet_board_id].limit_switch_flag = true;
            break;

        default:
            break;
        }
    }
}

void MDDataMaster::send_init(uint8_t id, md_config_t *config)
{
    uint8_t data[8] = {0};
    std::memcpy(data, config, sizeof(md_config_t));
    this->send(can_config::encode_id(can_config::direction::slave,
                                     can_config::board_type::md, id,
                                     can_config::data_type::md::init),
               data, sizeof(md_config_t));
}

void MDDataMaster::send_target(uint8_t id, int16_t target)
{
    uint8_t data[2] = {0};
    std::memcpy(data, &target, sizeof(int16_t));
    this->send(can_config::encode_id(can_config::direction::slave,
                                     can_config::board_type::md, id,
                                     can_config::data_type::md::target),
               data, sizeof(int16_t));
}

void MDDataMaster::send_multi_target(uint8_t id, int16_t target[4])
{
    uint8_t data[8] = {0};
    std::memcpy(data, target, sizeof(int16_t) * 4);
    this->send(can_config::encode_id(can_config::direction::slave,
                                     can_config::board_type::md, id,
                                     can_config::data_type::md::multi_target),
               data, sizeof(int16_t) * 4);
}

void MDDataMaster::send_gain(uint8_t id, uint8_t gain_type, float gain)
{
    uint8_t data[5] = {0};
    std::memcpy(data + 1, &gain, sizeof(float));
    data[0] = gain_type;
    this->send(can_config::encode_id(can_config::direction::slave,
                                     can_config::board_type::md, id,
                                     can_config::data_type::md::gain),
               data, sizeof(float) + 1);
}

bool MDDataMaster::get_init(uint8_t id, uint8_t *md_type)
{
    if (this->md_data[id].init_flag)
    {
        std::memcpy(md_type, this->md_data[id].init_buffer, sizeof(uint8_t));
        this->md_data[id].init_flag = false;
        return true;
    }
    return false;
}

bool MDDataMaster::get_encoder(uint8_t id, int16_t *encoder)
{
    if (this->md_data[id].target_flag)
    {
        std::memcpy(encoder, this->md_data[id].target_buffer, sizeof(int16_t));
        this->md_data[id].target_flag = false;
        return true;
    }
    return false;
}

bool MDDataMaster::get_limit_switch(uint8_t id, uint8_t *limit_switch)
{
    if (this->md_data[id].limit_switch_flag)
    {
        std::memcpy(limit_switch, this->md_data[id].limit_switch, sizeof(uint8_t));
        this->md_data[id].limit_switch_flag = false;
        return true;
    }
    return false;
}

bool MDDataMaster::get_gain(uint8_t id, uint8_t gain_type, float *gain)
{
    if (this->md_data[id].gain_flag[gain_type])
    {
        std::memcpy(gain, this->md_data[id].gain_buffer[gain_type], sizeof(float));
        this->md_data[id].gain_flag[gain_type] = false;
        return true;
    }
    return false;
}