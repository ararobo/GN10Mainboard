/**
 * @file stm32_fdcan3_driver.cpp
 * @author gn10g (8gn24gn25@gmail.com)
 * @brief STM32のFDCAN3通信用クラス
 * @version 1.0
 * @date 2025-05-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "stm32_fdcan3_driver.hpp"

void STM32FDCAN3Driver::init(uint32_t filter_id, uint32_t filter_mask)
{
    // CANのフィルタ設定
    RxFilter.IdType = FDCAN_STANDARD_ID;             // スタンダードID
    RxFilter.FilterIndex = 0;                        // フィルタインデックス
    RxFilter.FilterType = FDCAN_FILTER_MASK;         // マスクフィルタ
    RxFilter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0; // フィルタ設定
    RxFilter.FilterID1 = filter_id;                  // フィルタID1
    RxFilter.FilterID2 = filter_mask;                // フィルタID2
    // フィルタ設定
    if (HAL_FDCAN_ConfigFilter(&hfdcan3, &RxFilter) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_FDCAN_Start(&hfdcan3) != HAL_OK)
    {
        Error_Handler();
    }
    // 割り込み有効
    if (HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
    {
        Error_Handler();
    }
}

void STM32FDCAN3Driver::can_callback_process(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
    if (hfdcan->Instance == hfdcan3.Instance && RxFifo0ITs == FDCAN_IT_RX_FIFO0_NEW_MESSAGE)
    {
        if (HAL_FDCAN_GetRxMessage(&hfdcan3, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
        {
            Error_Handler();
        }
        receive(RxHeader.Identifier, RxData, RxHeader.DataLength);
    }
}

void STM32FDCAN3Driver::send(uint16_t id, uint8_t *data, uint8_t len)
{
    if (len > 8)
    {
        Error_Handler();
    }
    TxHeader.Identifier = id;
    TxHeader.IdType = FDCAN_STANDARD_ID;
    TxHeader.TxFrameType = FDCAN_DATA_FRAME;
    TxHeader.DataLength = len;
    TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
    TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
    TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    TxHeader.MessageMarker = 0;
    // 送信FIFOが空になるまで待機
    while (HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan3) == 0)
        ;
    // 送信
    if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan3, &TxHeader, data) != HAL_OK)
    {
        Error_Handler();
    }
}

void STM32FDCAN3Driver::receive(uint16_t id, uint8_t *data, uint8_t len)
{
    // 受信処理をオーバーライドしてください
}