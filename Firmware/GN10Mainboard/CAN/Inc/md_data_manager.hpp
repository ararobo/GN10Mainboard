#include "can_config.hpp"
#include "md_config.hpp"

using namespace can_config;

template <bool is_master>
class MDDataManager
{
private:
    uint8_t md_id;
    bool is_received_init;
    bool is_received_target;
    bool is_received_limit_switch;
    bool is_received_gain;
    uint8_t md_kind;
    md_config_t md_config;
    int16_t target;
    uint8_t limit_switch;
    float pid_gain[3];

    void send_gain(uint8_t gain_type, float gain)
    {
        uint8_t data[5];
        uint32_t gain_int = static_cast<uint32_t>(gain);
        data[0] = gain_type;
        data[1] = gain_int & 0xFF;
        data[2] = (gain_int >> 8) & 0xFF;
        data[3] = (gain_int >> 16) & 0xFF;
        data[4] = (gain_int >> 24) & 0xFF;

#if is_master
        send(encode_id(direction::slave, board_type::md, md_id, data_type::md::gain), data, sizeof(data));
#else
        send(encode_id(direction::master, board_type::md, md_id, data_type::md::gain), data, sizeof(data));
#endif
    }

protected:
    virtual void send(uint16_t id, uint8_t *data, uint8_t len)
    {
    }

    void receive(uint16_t id, uint8_t *data, uint8_t len)
    {
        uint8_t direction, board_type, board_id, data_type;
        decode_id(id, direction, board_type, board_id, data_type);
        if (board_type != board_type::md || board_id != md_id)
        {
            return;
        }
        switch (data_type)
        {
        case data_type::md::init:
#if is_master
            md_kind = data[0];
#else
            for (uint8_t i = 0; i < sizeof(md_config_t); i++)
            {
                md_config.code[i] = data[i];
            }
#endif
            is_received_init = true;
            break;
        case data_type::md::target:
            target = static_cast<int16_t>((data[1] << 8) | data[0]);
            is_received_target = true;
            break;
        case data_type::md::limit_switch:
            limit_switch = data[0];
            is_received_limit_switch = true;
            break;
        case data_type::md::gain:
            pid_gain[data[0]] = static_cast<float>((data[4] << 24) | (data[3] << 16) | (data[2] << 8) | data[1]);
            is_received_gain = true;
            break;
        default:
            break;
        }
    }

public:
    MDDataManager(uint8_t md_id) : md_id(md_id), is_received_init(false), is_received_target(false), is_received_limit_switch(false), is_received_gain(false) {};

    void set_md_id(uint8_t md_id)
    {
        this->md_id = md_id;
    }

    void send_init(md_config_t md_config)
    {
        static_assert(is_master, "This function is only for master.");
        send(encode_id(direction::slave, board_type::md, md_id, data_type::md::init), md_config.code, sizeof(md_config.code));
    }

    void send_init(uint8_t md_kind)
    {
        static_assert(!is_master, "This function is only for slave.");
        send(encode_id(direction::master, board_type::md, md_id, data_type::md::init), &md_kind, sizeof(md_kind));
    }

    void send_target(int16_t target)
    {
        uint8_t data[2];
        data[0] = target & 0xFF;
        data[1] = (target >> 8) & 0xFF;
#if is_master
        send(encode_id(direction::slave, board_type::md, md_id, data_type::md::target), data, sizeof(data));
#else
        send(encode_id(direction::master, board_type::md, md_id, data_type::md::target), data, sizeof(data));
#endif
    }

    void send_limit_switch(uint8_t limit_switch)
    {
        static_assert(!is_master, "This function is slave only.");
        send(encode_id(direction::master, board_type::md, md_id, data_type::md::limit_switch), &limit_switch, sizeof(limit_switch));
    }

    void send_gain(float p_gain, float i_gain, float d_gain)
    {
        send_gain(0, p_gain);
        send_gain(1, i_gain);
        send_gain(2, d_gain);
    }

    bool is_md_init()
    {
        return is_received_init;
    }

    md_config_t get_md_config()
    {
        static_assert(!is_master, "This function is only for slave.");
        return md_config;
    }

    uint8_t get_md_kind()
    {
        static_assert(is_master, "This function is only for master.");
        return md_kind;
    }

    bool get_target(int16_t *target)
    {
        if (is_received_target)
        {
            *target = this->target;
            is_received_target = false;
            return true;
        }
        return false;
    }

    bool get_limit_switch(uint8_t *limit_switch)
    {
        static_assert(is_master, "This function is only for master.");
        if (is_received_limit_switch)
        {
            *limit_switch = this->limit_switch;
            is_received_limit_switch = false;
            return true;
        }
        return false;
    }

    bool get_gain(float *p_gain, float *i_gain, float *d_gain)
    {
        if (is_received_gain)
        {
            *p_gain = pid_gain[0];
            *i_gain = pid_gain[1];
            *d_gain = pid_gain[2];
            is_received_gain = false;
            return true;
        }
        return false;
    }
};