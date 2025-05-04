/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
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
#include "adc.h"

/* USER CODE BEGIN 0 */

/* 私有变量 ------------------------------------------------------------------*/
__IO uint32_t ADC_ConvertedValueLocal[ADC_CHANNEL_NUMBER]; // 用于保存平均后的转换值
__IO uint16_t ADC_ConvertedValue[ADC_CHANNEL_NUMBER];// AD转换结果值,半字，与ADC设置对应
uint32_t ADC_Add_DATA[COVER_BUFFER_SIZE*ADC_CHANNEL_NUMBER]; //一整个采样所存储的全部数据

/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
int32_t ADC_offset[3]={0};
/* ADC1 init function */
/**
  * 函数功能: AD转换初始化
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */

void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */
  __HAL_RCC_ADC1_CLK_ENABLE();
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;//APB2,最大频率36MHZ。4分频,84/4=21MHz
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;//ADC 12位分辨率
  hadc1.Init.ScanConvMode = ENABLE;//扫描模式使能
  hadc1.Init.ContinuousConvMode = ENABLE;//连续转换,需和DMA的循环模式共用，不然数据读取混乱
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;//软件触发
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;//软件触发
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;//数据右对齐
  hadc1.Init.NbrOfConversion = ADC_CHANNEL_NUMBER;//规则通道2个
  hadc1.Init.DMAContinuousRequests = ENABLE;//DMA连续请求使能
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;//采样完成进入中断
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
   配置采样通道
 */	
	sConfig.Channel = ADC_CHANNEL1;//pc0
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;//采样周期
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
  
  sConfig.Channel = ADC_CHANNEL2;//PC3
  sConfig.Rank = 2;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
  
//  sConfig.Channel = ADC_CHANNEL3;//PB0
//  sConfig.Rank = 3;
//  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
  
//  HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&ADC_ConvertedValue,ADC_CHANNEL_NUMBER);  

  /* USER CODE BEGIN ADC1_Init 2 */
  __HAL_RCC_DMA2_CLK_ENABLE();
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

  /* USER CODE END ADC1_Init 2 */

}
/**
  * 函数功能: ADC外设初始化配置
  * 输入参数: adcHandle：AD外设句柄类型指针
  * 返 回 值: 无
  * 说    明: 该函数被HAL库内部调用
  */

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PC0     ------> ADC1_IN10
    PC3     ------> ADC1_IN13
    */
		GPIO_InitStruct.Pin = ADC_GPIO_PIN1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
		
    GPIO_InitStruct.Pin = ADC_GPIO_PIN2;
    HAL_GPIO_Init(ADC_GPIO2, &GPIO_InitStruct);
    
//    GPIO_InitStruct.Pin = ADC_GPIO_PIN3;
//    HAL_GPIO_Init(ADC_GPIO3, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    __HAL_RCC_DMA2_CLK_ENABLE();

    hdma_adc1.Instance = DMA2_Stream0;
    hdma_adc1.Init.Channel = DMA_CHANNEL_0;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;//外设到内存
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;//外设地址自增失能
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;//存储器地址自增使能
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;//循环模式
    hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    hdma_adc1.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
    hdma_adc1.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_adc1.Init.PeriphBurst = DMA_PBURST_SINGLE;    

    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PC0     ------> ADC1_IN10
    PC3     ------> ADC1_IN13
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0|GPIO_PIN_3);
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(adcHandle->DMA_Handle);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
}

//int32_t ADC_value_3[ADC_CHANNEL_NUMBER][COVER_BUFFER_SIZE]={0};//第i通道的第j个数据
//int32_t ADC_max[ADC_CHANNEL_NUMBER][2]={0};
//int32_t ADC_min[ADC_CHANNEL_NUMBER][2]={4096};

/* USER CODE BEGIN 1 */
/**
  * 函数功能: ADC转换完成回调函数
  * 输入参数: hadc：ADC外设设备句柄
  * 返 回 值: 无
  * 说    明: 无
  */
/*
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    
    for(uint8_t x=0;x<ADC_CHANNEL_NUMBER;x++)
	{
	  ADC_Add_DATA[COVER_BUFFER_SIZE*x+DMA_Transfer_Complete_Count]=(uint32_t)ADC_ConvertedValue[x];
	}
    DMA_Transfer_Complete_Count++;
    
	if(DMA_Transfer_Complete_Count==COVER_BUFFER_SIZE)
	{
	  DMA_Transfer_Complete_Count=0;
	  finish_flag=1;
	}
    //（重要）转换完一次之后，若没有达到目标次数，需要再开启转换，因为不是循坏模式 ，循环模式不需要这段
    else
    {
        HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&ADC_ConvertedValue,ADC_CHANNEL_NUMBER);
    }
    finish_convert=1;

    uint8_t i=0,j=0;
    int32_t ADC_value[ADC_CHANNEL_NUMBER]={0};
    int32_t ADC_max[ADC_CHANNEL_NUMBER][2]={0};
    int32_t ADC_min[ADC_CHANNEL_NUMBER][2]={4096};

    if(finish_flag==1)
    {
        for(uint8_t y=0;y<ADC_CHANNEL_NUMBER;y++)
		{
			for(i=0;i<COVER_BUFFER_SIZE;i++) //i等于0起，不去掉刚开始采样的第一组数据
			{
			//将数据累加至ADC_value变量 
				ADC_value[y]+=ADC_Add_DATA[COVER_BUFFER_SIZE*y+i];
                ADC_value_3[y][i]=ADC_Add_DATA[COVER_BUFFER_SIZE*y+i];
			}
		}
//去掉最大最小值法
        for(i=0; i<ADC_CHANNEL_NUMBER; i++)
        {
             ADC_max[i][0]=0;//最大值
//             ADC_max[i][1]=0;//次大值
             ADC_min[i][0]=4096;//最小值
//             ADC_min[i][1]=4096;//次小值
            for(j=0; j<COVER_BUFFER_SIZE; j++)
            {
                if(ADC_value_3[i][j] > ADC_max[i][0])//选取最大以及第二大的值
                {
//                    ADC_max[i][1]= ADC_max[i][0];
                    ADC_max[i][0]= ADC_value_3[i][j];
                } 
//                else if(ADC_value_3[i][j] > ADC_max[i][1])
//                {
//                    ADC_max[i][1]= ADC_value_3[i][j];
//                }
                
                if(ADC_value_3[i][j] < ADC_min[i][0]) //选取最小以及第二小的值
                {
//                    ADC_min[i][1]=ADC_min[i][0];
                    ADC_min[i][0]=ADC_value_3[i][j];
                }
//                else if(ADC_value_3[i][j] < ADC_min[i][1])
//                {
//                    ADC_min[i][1]=ADC_value_3[i][j];
//                }
            }
        }
        for(j=0;j<ADC_CHANNEL_NUMBER;j++)
		{
            //减去两个最大值和最小值，然后取平均;当输入为3.3V时，AD转换结果为4096
			ADC_ConvertedValueLocal[j] =(ADC_value[j]-ADC_max[j][0]-ADC_min[j][0])>>1;
            
			ADC_value[j]=0;
		}

//平均数法
//        for(j=0;j<ADC_CHANNEL_NUMBER;j++)
//		{
//            ADC_value[j]=ADC_value[j]>>2;// 除以COVER_BUFFER_SIZE-1=4，取后4次采样的平均值，舍去第一次的
//			//3.3为AD转换的参考电压值，stm32的AD转换为12bit，2^12=4096，
//			//即当输入为3.3V时，AD转换结果为4096 
//			ADC_ConvertedValueLocal[j] =ADC_value[j]; 
//			ADC_value[j]=0;
//		}
		finish_flag=0;
        finish_convert=0;
        HAL_ADC_Stop_DMA(&hadc1);       //完成一整个采样后停止 ADC 采样，等待下一次软件激活
	}
    
}

*/
//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
//{

//    for(uint8_t x=0;x<ADC_CHANNEL_NUMBER;x++)
//    {
//        ADC_value_3[x][DMA_Transfer_Complete_Count]=(uint32_t)ADC_ConvertedValue[x];
//    }
//    DMA_Transfer_Complete_Count++;
//    if(DMA_Transfer_Complete_Count==COVER_BUFFER_SIZE)
//    {
//        DMA_Transfer_Complete_Count=0;
//        finish_flag=1;
//    }
//    //（重要）转换完一次之后，若没有达到目标次数，需要再开启转换，因为不是循坏模式 ，循环模式不需要这段
//    else
//    {
//        HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&ADC_ConvertedValue,ADC_CHANNEL_NUMBER);
//    }
//    
//    if(finish_flag==1)
//    {
//        for(int i=0; i<ADC_CHANNEL_NUMBER; i++)
//        {
//             ADC_max[i][0]=ADC_value_3[i][0];//最大值
////             ADC_max[i][1]=0;//次大值
//             ADC_min[i][0]=ADC_value_3[i][0];//最小值
////             ADC_min[i][1]=4096;//次小值
//            for(int j=1; j<COVER_BUFFER_SIZE; j++)
//            {
//                if(ADC_value_3[i][j] > ADC_max[i][0])//选取最大以及第二大的值
//                {
////                    ADC_max[i][1]= ADC_max[i][0];
//                    ADC_max[i][0]= ADC_value_3[i][j];
//                } 
////                else if(ADC_value_3[i][j] > ADC_max[i][1])
////                {
////                    ADC_max[i][1]= ADC_value_3[i][j];
////                }
//                
//                if(ADC_value_3[i][j] < ADC_min[i][0]) //选取最小以及第二小的值
//                {
////                    ADC_min[i][1]=ADC_min[i][0];
//                    ADC_min[i][0]=ADC_value_3[i][j];
//                }
////                else if(ADC_value_3[i][j] < ADC_min[i][1])
////                {
////                    ADC_min[i][1]=ADC_value_3[i][j];
////                }
//            }
//        }
//        
//        for(int j=0;j<ADC_CHANNEL_NUMBER;j++)
//		{
//            //减去两个最大值和最小值，然后取平均;当输入为3.3V时，AD转换结果为4096
//			ADC_ConvertedValueLocal[j] =(ADC_value_3[j][0]+ADC_value_3[j][1]+ADC_value_3[j][2]+ADC_value_3[j][3]-ADC_max[j][0]-ADC_min[j][0])>>1;
//		}
//        finish_flag=0;
//        HAL_ADC_Stop_DMA(&hadc1);//完成一整个采样后停止 ADC 采样，等待下一次软件激活
//    }
//    
//}



void Offset_CurrentReading(void)
{
	uint8_t i;  
  //4*4次采样求平均值，电流传感器初始校准   
	for(i=0; i<16; i++)   
    {
        //对于相电流和母线电流的电阻法测量电流,需要上电读取初始偏执电压
        //开启ADC转换，采集ia，ib，vbus
//        HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&ADC_ConvertedValue,ADC_CHANNEL_NUMBER);
        HAL_Delay(100);
        ADC_offset[0] += (int32_t)ADC_ConvertedValueLocal[0];
        ADC_offset[1] += (int32_t)ADC_ConvertedValueLocal[1];
    //        ADC_offset[2] += ADC_ConvertedValueLocal[2];//Vbus不需要测上电偏差
        

//        printf("%d,%d\n",ADC_ConvertedValueLocal[0],ADC_ConvertedValueLocal[1]);

    }
    //求64次电压信号平均值，作为上电初值
    ADC_offset[0] = ADC_offset[0]>>4;  //Va
    ADC_offset[1]= ADC_offset[1]>>4;     //Vb
    ADC_offset[2]=0;      //Vbus

}

/* USER CODE END 1 */
