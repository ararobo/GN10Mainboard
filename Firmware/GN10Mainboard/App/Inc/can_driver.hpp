#pragma once
#include "md_data_manager.hpp"
#include "fdcan.h"
#include "serial_printf.hpp"

class CANDriver : public MDDataManager<true>
{
private:
    FDCAN_RxHeaderTypeDef RxHeader;
    FDCAN_FilterTypeDef RxFilter;
    FDCAN_TxHeaderTypeDef TxHeader;
    uint8_t RxData[8];

    void send(uint16_t id, uint8_t *data, uint8_t len) override
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
        if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan3, &TxHeader, data) != HAL_OK)
        {
            Error_Handler();
        }
    }

public:
    CANDriver(uint8_t md_id) : MDDataManager(md_id) {}

    void init()
    {
        // CANのフィルタ設定
        RxFilter.IdType = FDCAN_STANDARD_ID;             // 標準ID
        RxFilter.FilterIndex = 0;                        // フィルタインデックス
        RxFilter.FilterType = FDCAN_FILTER_MASK;         // マスク
        RxFilter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0; // FIFO0にフィルタ
        RxFilter.FilterID1 = 0x000;
        RxFilter.FilterID2 = 0x000;
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

    void can_callback_process(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
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
};