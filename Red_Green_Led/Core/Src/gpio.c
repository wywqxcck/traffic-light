/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, EW_SCL_Pin|EW_SDI_Pin|EW_LOAD_Pin|SWITCH_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, EW_RED_Pin|EW_YELLOW_Pin|EW_GREEN_Pin|POWER_OUT_Pin
                          |NS_SCL_Pin|NS_SDI_Pin|NS_LOAD_Pin|NS_RED_Pin
                          |NS_YELLOW_Pin|NS_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : EW_SCL_Pin EW_SDI_Pin EW_LOAD_Pin */
  GPIO_InitStruct.Pin = EW_SCL_Pin|EW_SDI_Pin|EW_LOAD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : EW_RED_Pin EW_YELLOW_Pin EW_GREEN_Pin POWER_OUT_Pin
                           NS_RED_Pin NS_YELLOW_Pin NS_GREEN_Pin */
  GPIO_InitStruct.Pin = EW_RED_Pin|EW_YELLOW_Pin|EW_GREEN_Pin|POWER_OUT_Pin
                          |NS_RED_Pin|NS_YELLOW_Pin|NS_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : SWITCH_Pin */
  GPIO_InitStruct.Pin = SWITCH_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(SWITCH_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : POWER_IN_Pin */
  GPIO_InitStruct.Pin = POWER_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(POWER_IN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : NS_SCL_Pin NS_SDI_Pin NS_LOAD_Pin */
  GPIO_InitStruct.Pin = NS_SCL_Pin|NS_SDI_Pin|NS_LOAD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
