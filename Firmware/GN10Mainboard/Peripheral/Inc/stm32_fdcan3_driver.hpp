/**
 * @file stm32_fdcan3_driver.hpp
 * @author gn10g (8gn24gn25@gmail.com)
 * @brief STM32のFDCAN3通信用クラス
 * @version 0.1
 * @date 2025-04-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <stdint.h>
#include "fdcan.h"

class STM32FDCAN3Driver
{
private:
    FDCAN_RxHeaderTypeDef RxHeader;
    FDCAN_FilterTypeDef RxFilter;
    FDCAN_TxHeaderTypeDef TxHeader;
    uint8_t RxData[8];

protected:
    /**
     * @brief CANの受信処理(オーバーライドしてください)
     *
     * @param id CANのID
     * @param data 受信データ
     * @param len データの長さ
     */
    virtual void receive(uint16_t id, uint8_t *data, uint8_t len);

public:
    /**
     * @brief CANの初期化
     *
     * @param filter_id
     * @param filter_mask
     */
    void init(uint32_t filter_id, uint32_t filter_mask);

    /**
     * @brief CANの送信処理
     *
     * @param id CANのID
     * @param data 送信するデータ
     * @param len データの長さ
     */
    void send(uint16_t id, uint8_t *data, uint8_t len);

    /**
     * @brief CANのコールバック処理
     *
     * @param hcan CANのハンドル
     */
    void can_callback_process(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);
};