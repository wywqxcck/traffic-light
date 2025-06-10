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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Nixie.h"
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
#define EW_SCL_Pin GPIO_PIN_4
#define EW_SCL_GPIO_Port GPIOA
#define EW_SDI_Pin GPIO_PIN_5
#define EW_SDI_GPIO_Port GPIOA
#define EW_LOAD_Pin GPIO_PIN_6
#define EW_LOAD_GPIO_Port GPIOA
#define EW_RED_Pin GPIO_PIN_12
#define EW_RED_GPIO_Port GPIOB
#define EW_YELLOW_Pin GPIO_PIN_13
#define EW_YELLOW_GPIO_Port GPIOB
#define EW_GREEN_Pin GPIO_PIN_14
#define EW_GREEN_GPIO_Port GPIOB
#define POWER_OUT_Pin GPIO_PIN_15
#define POWER_OUT_GPIO_Port GPIOB
#define SWITCH_Pin GPIO_PIN_8
#define SWITCH_GPIO_Port GPIOA
#define POWER_IN_Pin GPIO_PIN_15
#define POWER_IN_GPIO_Port GPIOA
#define NS_SCL_Pin GPIO_PIN_3
#define NS_SCL_GPIO_Port GPIOB
#define NS_SDI_Pin GPIO_PIN_4
#define NS_SDI_GPIO_Port GPIOB
#define NS_LOAD_Pin GPIO_PIN_5
#define NS_LOAD_GPIO_Port GPIOB
#define NS_RED_Pin GPIO_PIN_6
#define NS_RED_GPIO_Port GPIOB
#define NS_YELLOW_Pin GPIO_PIN_7
#define NS_YELLOW_GPIO_Port GPIOB
#define NS_GREEN_Pin GPIO_PIN_8
#define NS_GREEN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
