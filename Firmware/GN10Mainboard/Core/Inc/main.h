/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DIP_1_Pin GPIO_PIN_2
#define DIP_1_GPIO_Port GPIOC
#define DIP_2_Pin GPIO_PIN_3
#define DIP_2_GPIO_Port GPIOC
#define DIP_3_Pin GPIO_PIN_0
#define DIP_3_GPIO_Port GPIOA
#define DIP_4_Pin GPIO_PIN_1
#define DIP_4_GPIO_Port GPIOA
#define LED_DP_Pin GPIO_PIN_4
#define LED_DP_GPIO_Port GPIOA
#define LED_G_Pin GPIO_PIN_5
#define LED_G_GPIO_Port GPIOA
#define LED_F_Pin GPIO_PIN_6
#define LED_F_GPIO_Port GPIOA
#define LED_E_Pin GPIO_PIN_7
#define LED_E_GPIO_Port GPIOA
#define LED_D_Pin GPIO_PIN_4
#define LED_D_GPIO_Port GPIOC
#define LED_C_Pin GPIO_PIN_5
#define LED_C_GPIO_Port GPIOC
#define LED_B_Pin GPIO_PIN_0
#define LED_B_GPIO_Port GPIOB
#define LED_A_Pin GPIO_PIN_1
#define LED_A_GPIO_Port GPIOB
#define LED_RED_Pin GPIO_PIN_12
#define LED_RED_GPIO_Port GPIOB
#define LED_GREEN_Pin GPIO_PIN_13
#define LED_GREEN_GPIO_Port GPIOB
#define LED_BLUE_Pin GPIO_PIN_14
#define LED_BLUE_GPIO_Port GPIOB
#define BLE_UART_MODE_Pin GPIO_PIN_9
#define BLE_UART_MODE_GPIO_Port GPIOC
#define SPI3_CS_Pin GPIO_PIN_15
#define SPI3_CS_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
