#include "Sensors.h"


Sensor_Typedef	Encoder;
Sensor_ABZ_Signal_Typedef	Encoder_abz;

/****************************** Encoder ******************************/

/**
  * @brief  编码器初始化
  * @param  NULL
  * @retval NULL
**/
void Sensor_Init(void)
{
#ifndef Sensor_Mode
	#error "NO define Sensor_Mode"
#endif
#if   (Sensor_Mode == Sensor_Mode_PWM)
	Sensor_PWM_Signal_Init();		//初始化PWM接口
#elif (Sensor_Mode == Sensor_Mode_SPI)
	Sensor_SPI_Signal_Init();		//初始化SPI接口
#elif (Sensor_Mode == Sensor_Mode_ABZ)
	Sensor_ABZ_Signal_Init();		//初始化ABZ接口
#else
	#error "Sensors_Mode Invalid !!!"
#endif
	
	//初始化阶段获取一次角度数据(过滤错误数据)(暂未查明复位后第一次读取数据丢失的原因)
	Sensor_Get_AngleData();

}


/**
  * @brief  获取角度数据
  * @param  NULL
  * @retval NULL
**/
void Sensor_Get_AngleData(void)
{
#ifndef Sensor_Mode
	#error "NO define MT6816_Mode"
#endif
#if   (Sensor_Mode == MT6816_Mode_PWM)
	REIN_MT6816_PWM_Get_AngleData();	//MT6816_PWM获取角度数据
	mt6816.angle_data = mt6816_pwm.angle;
	mt6816.rectify_angle = Read_QuickCali_DATA[mt6816.angle_data];
#elif (Sensor_Mode == MT6816_Mode_SPI)
	RINE_MT6816_SPI_Get_AngleData();
	mt6816.angle_data = mt6816_spi.angle;
	mt6816.rectify_angle = Read_QuickCali_DATA[mt6816.angle_data];
#elif (Sensor_Mode == Sensor_Mode_ABZ)
	Sensor_ABZ_Get_AngleData();	//ABZ获取角度数据
	
#else
	#error "Sensor_Mode Invalid !!!"
#endif
}

/****************************** ABZ ******************************/

/**
  * @brief  ABZ采集初始化
  * @param  NULL
  * @retval NULL
**/
void Sensor_ABZ_Signal_Init(void)
{
	//采集数据
	Encoder_abz.MechAngle = 0;
	//输出数据
//	Encoder_abz.OffsetAngle = 0;
	Encoder_abz.ElecAngle = 0;
	Encoder_abz.angle = 0;

	//配置外设
	TIM_Encoder_ABZ_Init();
//	GPIO_Encoder_ABZ_Init();//Z信号
}

/**
  * @brief  ABZ采集Z脉冲中断回调
  * @param  NULL
  * @retval NULL
**/
void Sensor_ABZ_ZPulse_Callback(void)
{
	//清除定时器计数值
	__HAL_TIM_SET_COUNTER(&ABZ_Get_HTIM, 0);
}

/**
  * @brief  ABZ获取角度数据
  * @param  NULL
  * @retval NULL
**/
void Sensor_ABZ_Get_AngleData(void)
{
	Encoder_abz.MechAngle = __HAL_TIM_GET_COUNTER(&ABZ_Get_HTIM);	//读取定时器计数值0~3999	
	Encoder_abz.ElecAngle = Encoder_abz.MechAngle%80;		//4000/50=80,获得电角度0~79（50极对数）
}


/**
  * @brief  GPIO初始化(Z)
  * @param  NULL
  * @retval NULL
*/
void REIN_GPIO_MT6816_ABZ_Init(void)
{
#ifdef MT6816_ABZ_Z_GPIO_CLK_ENABLE
	
	 GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* GPIO Ports Clock Enable */
  MT6816_ABZ_Z_GPIO_CLK_ENABLE();			//启用ABZ_Z端口时钟
  /*Configure GPIO pins*/
  GPIO_InitStruct.Pin = MT6816_ABZ_Z_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;		//上升沿触发中断
  GPIO_InitStruct.Pull = GPIO_NOPULL;						//禁用上下拉
  HAL_GPIO_Init(MT6816_ABZ_Z_GPIO_Port, &GPIO_InitStruct);
  /* EXTI interrupt init*/
  HAL_NVIC_EnableIRQ(MT6816_ABZ_Z_EXTI_IRQn);		//启用Z中断
#endif
}
