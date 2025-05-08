/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
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
#include "usart.h"
#include "parameter\parameter.h"
#include "pid_cale\pid_cale.h"
#include "psi_cale_ab\psi_cale_ab.h"
#include "..\bsp\loop\loop.h"
/* USER CODE BEGIN 0 */
uint8_t RxBuffer[1];
uint16_t RxLine = 0;
uint8_t DataBuff[200];
uint8_t tail[4]={0x00, 0x00, 0x80, 0x7f};//VOFA+ Frame tail

extern vary_parameter_typedef vary;
extern motor_parameter_typedef P_motor1;
extern control_parameter_typedef P_control1;

extern PID_typedef pid_current_id;
extern PID_typedef pid_current_iq;
extern PID_typedef pid_speed;

extern bool foc_start;
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usartx_tx;
/* USART1 init function */
void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */
    __HAL_RCC_GPIOB_CLK_ENABLE();

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */
  
  HAL_UART_Receive_IT(&huart1,(uint8_t *)RxBuffer,1);

  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_DMA2_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PB6     ------> USART1_TX
    PB7     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn,2,1);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */
    /* DMA Initialization */
    hdma_usartx_tx.Instance = DMA2_Stream7;
    hdma_usartx_tx.Init.Channel = DMA_CHANNEL_4; 
    hdma_usartx_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usartx_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usartx_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usartx_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usartx_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usartx_tx.Init.Mode = DMA_NORMAL;
    hdma_usartx_tx.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_usartx_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	
    HAL_DMA_Init(&hdma_usartx_tx);
    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usartx_tx);
    
    HAL_NVIC_SetPriority(DMA2_Stream7_IRQn,2, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);  

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PB6     ------> USART1_TX
    PB7     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */
    HAL_DMA_DeInit(uartHandle->hdmatx);
  /* USER CODE END USART1_MspDeInit 1 */
  }
}


//Serial port receiving interrupt callback function
 void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    if(UartHandle->Instance==USART1)
    {
        RxLine++;                      
        DataBuff[RxLine-1]=RxBuffer[0];  
        if(RxBuffer[0]==0x21)            
        {
//            printf("RXLen=%d\r\n",RxLine);
            for(int i=0;i<RxLine;i++)
//                printf("UART DataBuff[%d] = %c\r\n",i,DataBuff[i]);
            USART_PID_Adjust();
            memset(DataBuff,0,sizeof(DataBuff));  
            RxLine=0; 
        }
        RxBuffer[0]=0;
        HAL_UART_Receive_IT(&huart1, (uint8_t *)RxBuffer, 1); 
    }
}

//Receive data parsing
float Get_Data(void)
{
    uint8_t data_Start_Num = 0; 
    uint8_t data_End_Num = 0; 
    uint8_t data_Num = 0; 
    uint8_t minus_Flag = 0; 
    float data_return = 0; 
    for(uint8_t i=0;i<200;i++) 
    {
        if(DataBuff[i] == '=') data_Start_Num = i + 1; 
        if(DataBuff[i] == '!')
        {
            data_End_Num = i - 1;
            break;
        }
    }
    if(DataBuff[data_Start_Num] == '-') 
    {
        data_Start_Num += 1; 
        minus_Flag = 1;
    }
    data_Num = data_End_Num - data_Start_Num + 1;
    if(data_Num == 4) 
    {
        data_return = (DataBuff[data_Start_Num]-48)  + (DataBuff[data_Start_Num+2]-48)*0.1f +
                (DataBuff[data_Start_Num+3]-48)*0.01f;
    }
    else if(data_Num == 5) 
    {
        data_return = (DataBuff[data_Start_Num]-48)*10 + (DataBuff[data_Start_Num+1]-48) + (DataBuff[data_Start_Num+3]-48)*0.1f +
                (DataBuff[data_Start_Num+4]-48)*0.01f;
    }
    else if(data_Num == 6) 
    {
        data_return = (DataBuff[data_Start_Num]-48)*100 + (DataBuff[data_Start_Num+1]-48)*10 + (DataBuff[data_Start_Num+2]-48) +
                (DataBuff[data_Start_Num+4]-48)*0.1f + (DataBuff[data_Start_Num+5]-48)*0.01f;
    }
    else if(data_Num == 7) //The data consists of 7 digits, including 4 integers and 2 decimals
    {
        data_return = (DataBuff[data_Start_Num]-48)*1000 + (DataBuff[data_Start_Num+1]-48)*100 + (DataBuff[data_Start_Num+2]-48)*10 +
                (DataBuff[data_Start_Num+3]-48)+(DataBuff[data_Start_Num+5]-48)*0.1f + (DataBuff[data_Start_Num+6]-48)*0.01f;
    }

    if(minus_Flag == 1)  data_return = -data_return;
//    printf("data=%.2f\r\n",data_return);
    return data_return;
}

//Update of control parameters
void USART_PID_Adjust(void)
{
    float data_Get = Get_Data(); 
//    printf("data=%.2f\r\n",data_Get);
    if(DataBuff[0]=='C' && DataBuff[1]=='P') 
    {
////        pid_speed.kp =(int32_t)data_Get;
        pid_current_id.kp =(int32_t)data_Get;
        pid_current_iq.kp = (int32_t)data_Get;
    }
    else if(DataBuff[0]=='C' && DataBuff[1]=='I') 
    {
//        pid_speed.ki =(int32_t)data_Get;

        pid_current_id.ki = (int32_t)data_Get;
        pid_current_iq.ki = (int32_t)data_Get;
    }
    else if(DataBuff[0]=='C' && DataBuff[1]=='D') 
    {
//        pid_speed.kd =(int32_t)data_Get;
        pid_current_id.kd = (int32_t)data_Get;
        pid_current_iq.kd = (int32_t)data_Get;
    }
    else if(DataBuff[0]=='S' && DataBuff[1]=='p') // speed
        vary.speed = data_Get;
    else if(DataBuff[0]=='X' && DataBuff[1]=='d') // distance
        vary.distance = data_Get;
    else if(DataBuff[0]=='A' && DataBuff[1]=='c') // acc
        vary.acc_d = data_Get;

    else if(DataBuff[0]=='K' && DataBuff[1]=='1') // K1
        P_control1.k1 = data_Get;
    else if(DataBuff[0]=='K' && DataBuff[1]=='2') // K2
        P_control1.k2 = data_Get/100;
    else if(DataBuff[0]=='K' && DataBuff[1]=='3') // K3
        P_control1.k3 = data_Get;

    else if(DataBuff[0]=='K' && DataBuff[1]=='p') // Kp
        P_control1.kp = data_Get/10;
    else if(DataBuff[0]=='K' && DataBuff[1]=='i') // Ki
        P_control1.ki = data_Get;
    else if(DataBuff[0]=='K' && DataBuff[1]=='d') // Kd
        P_control1.kd = data_Get;

    else if(DataBuff[0]=='W' && DataBuff[1]=='c') // Wc
        P_control1.Wc = data_Get;
    else if(DataBuff[0]=='W' && DataBuff[1]=='s') // Ws
        P_control1.Ws = data_Get;

    else if(DataBuff[0]=='T' && DataBuff[1]=='e') // Te
        vary.tau_d = data_Get;
    else if(DataBuff[0]=='M' && DataBuff[1]=='c') //mode
        vary.model_change=(bool)data_Get;

    else if((DataBuff[0]=='G' && DataBuff[1]=='O')) //foc_start
        foc_start =(bool)data_Get;
    else if((DataBuff[0]=='N' && DataBuff[1]=='M')) //new move
        vary.new_move =(bool)data_Get;
}

//Send data
void Serial_DMA_Float(float *data,uint16_t number)
{

    uint8_t *pool=(uint8_t *)data;
    pool[4*number]=0x00;
    pool[4*number+1]=0x00;
    pool[4*number+2]=0x80;
    pool[4*number+3]=0x7f;
    HAL_UART_Transmit_DMA(&huart1,pool,4*number+4);
}


int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}

int fgetc(FILE * f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart1,&ch, 1, 0xffff);
  return ch;
}

/* USER CODE END 1 */
