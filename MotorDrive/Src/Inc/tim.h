/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include ".\loop\loop_port.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim3;
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */
/******************************  Encoder  ******************************/
/******************************  Encoder  ******************************/
#define ABZ_TIM_CLK_ENABLE()			__HAL_RCC_TIM3_CLK_ENABLE()		//TIM3
#define	ABZ_Get_TIM							(TIM3)
#define	ABZ_Get_HTIM							(htim3)
void TIM_Encoder_ABZ_Init(void);//TIM≥ı ºªØ(ABZ)

void MX_TIM1_Init(void);
void MX_TIM8_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);



/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

