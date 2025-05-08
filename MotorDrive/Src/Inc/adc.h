/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
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
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include ".\loop\loop_port.h"

/* USER CODE BEGIN Includes */

#define ADC_GPIO_ClK_ENABLE()            (__HAL_RCC_GPIOC_CLK_ENABLE();)
#define ADC_CHANNEL_NUMBER               2 
#define COVER_BUFFER_SIZE   ((uint32_t)7)// Number of scans for each channel


#define ADC_GPIO_PIN1                    GPIO_PIN_0   
#define ADC_GPIO1                        GPIOC
#define ADC_CHANNEL1                     ADC_CHANNEL_10  

#define ADC_GPIO_PIN2                    GPIO_PIN_3   
#define ADC_GPIO2                        GPIOC
#define ADC_CHANNEL2                     ADC_CHANNEL_13  

#define ADC_GPIO_PIN3                    GPIO_PIN_0    
#define ADC_GPIO3                        GPIOB
#define ADC_CHANNEL3                     ADC_CHANNEL_8    
  
/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_ADC1_Init(void);
void Offset_CurrentReading(void);
//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void ADC_start_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

