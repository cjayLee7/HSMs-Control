/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
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
/* Includes ------------------------------------------------------------------*/
#include "tim.h"
#include "sensors\Sensors.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim1;//A
TIM_HandleTypeDef htim8;//PWM
TIM_HandleTypeDef htim3;//encoder

//CCR
__IO uint16_t ChannelPulse2 = 0;
__IO uint32_t Prescaler2 =2;

/******************************  PWM  ******************************/

/* TIM8 init function */
void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */
    __HAL_RCC_TIM8_CLK_ENABLE();

  /* USER CODE END TIM8_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  
// TIMxCLK = HCLK=168MHz 
// TIMxCLK/(TIM_Prescaler+1)= 84MHz
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = Prescaler2-1;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 1680-1;//42000000/1680=25000hz=40us
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
	
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
	
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = ChannelPulse2;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
//	  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
//  {
//    Error_Handler();
//  }

	
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_1;
  sBreakDeadTimeConfig.DeadTime = 0x0A;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */
	HAL_TIM_MspPostInit(&htim8);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
//	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
//	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);
  /* USER CODE END TIM8_Init 2 */

}

//void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
//{

//  if(tim_baseHandle->Instance==TIM1)
//  {
//  /* USER CODE BEGIN TIM1_MspInit 0 */

//  /* USER CODE END TIM1_MspInit 0 */
//    /* TIM1 clock enable */
//    __HAL_RCC_TIM1_CLK_ENABLE();
//  /* USER CODE BEGIN TIM1_MspInit 1 */

//  /* USER CODE END TIM1_MspInit 1 */
//  }
//}

//void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim_pwmHandle)
//{

//  if(tim_pwmHandle->Instance==TIM8)
//  {
//  /* USER CODE BEGIN TIM8_MspInit 0 */

//  /* USER CODE END TIM8_MspInit 0 */
//    /* TIM8 clock enable */
//    __HAL_RCC_TIM8_CLK_ENABLE();
//  /* USER CODE BEGIN TIM8_MspInit 1 */

//  /* USER CODE END TIM8_MspInit 1 */
//  }
//}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(timHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspPostInit 0 */

  /* USER CODE END TIM1_MspPostInit 0 */
    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**TIM1 GPIO Configuration
    PE14     ------> TIM1_CH4
    PE13     ------> TIM1_CH3
    PE9     ------> TIM1_CH1
    PE11     ------> TIM1_CH2
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM1_MspPostInit 1 */

  /* USER CODE END TIM1_MspPostInit 1 */
  }
  else if(timHandle->Instance==TIM8)
  {
  /* USER CODE BEGIN TIM8_MspPostInit 0 */

  /* USER CODE END TIM8_MspPostInit 0 */

    __HAL_RCC_GPIOI_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
    /**TIM8 GPIO Configuration
    PI5     ------> TIM8_CH1
    PI6     ------> TIM8_CH2
    PI7     ------> TIM8_CH3
    PC9     ------> TIM8_CH4
    */

    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM8_MspPostInit 1 */

  /* USER CODE END TIM8_MspPostInit 1 */
  }

}

//void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
//{

//  if(tim_baseHandle->Instance==TIM1)
//  {
//  /* USER CODE BEGIN TIM1_MspDeInit 0 */

//  /* USER CODE END TIM1_MspDeInit 0 */
//    /* Peripheral clock disable */
//    __HAL_RCC_TIM1_CLK_DISABLE();
//  /* USER CODE BEGIN TIM1_MspDeInit 1 */

//  /* USER CODE END TIM1_MspDeInit 1 */
//  }
//}

//void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* tim_pwmHandle)
//{

//  if(tim_pwmHandle->Instance==TIM8)
//		
//  {
//  /* USER CODE BEGIN TIM8_MspDeInit 0 */

//  /* USER CODE END TIM8_MspDeInit 0 */
//    /* Peripheral clock disable */
//    __HAL_RCC_TIM8_CLK_DISABLE();
//  /* USER CODE BEGIN TIM8_MspDeInit 1 */

//  /* USER CODE END TIM8_MspDeInit 1 */
//  }
//}

/* USER CODE BEGIN 1 */
/******************************  Encoder  ******************************/
/******************************  Encoder  ******************************/
/******************************  Encoder  ******************************/
	
void TIM_Encoder_ABZ_Init(void)
{ 
	/* GPIO InitStruct */
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/*GPIO Ports Clock Enable*/
	ABZ_A_GPIO_CLK_ENABLE();		
	ABZ_B_GPIO_CLK_ENABLE();		
	/*Configure GPIO pins*/
	GPIO_InitStruct.Pin = ABZ_A_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;	
	GPIO_InitStruct.Pull = GPIO_PULLUP;			
  GPIO_InitStruct.Alternate = GPIO_CH1_AFx_TIMx;
	HAL_GPIO_Init(ABZ_A_GPIO_Port, &GPIO_InitStruct);
	/*Configure GPIO pins*/
	GPIO_InitStruct.Pin = ABZ_B_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;	
	GPIO_InitStruct.Pull = GPIO_PULLUP;			
	HAL_GPIO_Init(ABZ_B_GPIO_Port, &GPIO_InitStruct);
	
	TIM_Encoder_InitTypeDef sConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	ABZ_TIM_CLK_ENABLE();
	ABZ_Get_HTIM.Instance = ABZ_Get_TIM;
	ABZ_Get_HTIM.Init.Prescaler = 0;																										
	ABZ_Get_HTIM.Init.CounterMode = TIM_COUNTERMODE_UP;									
	ABZ_Get_HTIM.Init.Period = (4000 - 1);																	
	ABZ_Get_HTIM.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;							
	ABZ_Get_HTIM.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;	
	sConfig.EncoderMode = TIM_ENCODERMODE_TI12;				
	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;			
	sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;	
	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;						
	sConfig.IC1Filter = 0;														
	sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;			
	sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;	
	sConfig.IC2Prescaler = TIM_ICPSC_DIV1;						
	sConfig.IC2Filter = 0;														
	if (HAL_TIM_Encoder_Init(&ABZ_Get_HTIM, &sConfig) != HAL_OK)
	{
	  Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;							
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;		
	if (HAL_TIMEx_MasterConfigSynchronization(&ABZ_Get_HTIM, &sMasterConfig) != HAL_OK)
	{
	  Error_Handler();
	}
	/*begin work*/
//	HAL_TIM_Base_Stop(&ABZ_Get_HTIM);
	HAL_TIM_Encoder_Start(&ABZ_Get_HTIM, TIM_CHANNEL_ALL);
}

	


/* USER CODE END 1 */
