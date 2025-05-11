#include "pc_data_master.hpp"
#include <cstring>

PCDataMaster::PCDataMaster(uint8_t board_id_) : board_id(board_id_)
{
    // 受信フラグの初期化
    this->init_flag = false;
    this->cmd_vel_flag = false;
    this->target_flag = false;
    velocity_scale = 1000; // 送信時のベクトルの係数
}

void PCDataMaster::send_init(uint8_t config)
{
    uint8_t data[1] = {config};
    this->send(can_config::encode_id(can_config::direction::slave,
                                     can_config::board_type::pc, this->board_id,
                                     can_config::data_type::pc::init),
               data, sizeof(data));
}

void PCDataMaster::send_odometry(float x, float y, float theta)
{
    uint8_t data[6];
    int16_t buffer[3];
    // 整数値に変換
    buffer[0] = (int16_t)(x * velocity_scale);
    buffer[1] = (int16_t)(y * velocity_scale);
    buffer[2] = (int16_t)(theta * velocity_scale);
    // 送信データの作成
    data[0] = (uint8_t)(buffer[0] & 0x00FF);
    data[1] = (uint8_t)((buffer[0] >> 8) & 0x00FF);
    data[2] = (uint8_t)(buffer[1] & 0x00FF);
    data[3] = (uint8_t)((buffer[1] >> 8) & 0x00FF);
    data[4] = (uint8_t)(buffer[2] & 0x00FF);
    data[5] = (uint8_t)((buffer[2] >> 8) & 0x00FF);
    // 送信
    this->send(can_config::encode_id(can_config::direction::slave,
                                     can_config::board_type::pc, this->board_id,
                                     can_config::data_type::pc::cmd_vel),
               data, sizeof(data));
}

bool PCDataMaster::get_init(uint8_t *config)
{
    if (this->init_flag)
    {
        std::memcpy(config, this->init_buffer, sizeof(this->init_buffer));
        this->init_flag = false;
        return true;
    }
    return false;
}

bool PCDataMaster::get_cmd_vel(float *vx, float *vy, float *omega)
{
    if (this->cmd_vel_flag)
    {
        *vx = (float)((int16_t)(this->cmd_vel_buffer[1] << 8 | this->cmd_vel_buffer[0])) / velocity_scale;
        *vy = (float)((int16_t)(this->cmd_vel_buffer[3] << 8 | this->cmd_vel_buffer[2])) / velocity_scale;
        *omega = (float)((int16_t)(this->cmd_vel_buffer[5] << 8 | this->cmd_vel_buffer[4])) / velocity_scale;
        this->cmd_vel_flag = false;
        return true;
    }
    return false;
}

void PCDataMaster::receive(uint16_t id, uint8_t *data, uint8_t len)
{
    can_config::decode_id(id, this->packet_direction, this->packet_board_type,
                          this->packet_board_id, this->packet_data_type);

    if (this->packet_direction == can_config::direction::master &&
        this->packet_board_type == can_config::board_type::pc &&
        this->packet_board_id == this->board_id)
    {
        switch (this->packet_data_type)
        {
        case can_config::data_type::pc::init:
            std::memcpy(this->init_buffer, data, sizeof(this->init_buffer));
            this->init_flag = true;
            break;

        case can_config::data_type::pc::cmd_vel:
            std::memcpy(this->cmd_vel_buffer, data, sizeof(this->cmd_vel_buffer));
            this->cmd_vel_flag = true;
            break;

        default:
            break;
        }
    }
}