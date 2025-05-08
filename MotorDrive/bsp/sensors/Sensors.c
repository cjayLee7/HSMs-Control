#include "Sensors.h"

Sensor_Typedef	Encoder;
Sensor_ABZ_Signal_Typedef	Encoder_abz;

/****************************** Encoder ******************************/

void Sensor_Init(void)
{
	Sensor_Get_AngleData();
}

void Sensor_Get_AngleData(void)
{
	Sensor_ABZ_Get_AngleData();	
}

/****************************** ABZ ******************************/

//Encoder ABZ signal processing
void Sensor_ABZ_Signal_Init(void)
{
	Encoder_abz.MechAngle = 0;
//	Encoder_abz.OffsetAngle = 0;
	Encoder_abz.ElecAngle = 0;
	Encoder_abz.angle = 0;
	TIM_Encoder_ABZ_Init();
	GPIO_Encoder_ABZ_Init(); // Z signal
}
//Z Pulse Interrupt callback function
void Sensor_ABZ_ZPulse_Callback(void)
{
	__HAL_TIM_SET_COUNTER(&ABZ_Get_HTIM, 0);
}

void Sensor_ABZ_Get_AngleData(void)
{
	Encoder_abz.MechAngle = __HAL_TIM_GET_COUNTER(&ABZ_Get_HTIM);	//0~3999	
	Encoder_abz.ElecAngle = Encoder_abz.MechAngle%80;		//4000/50=80
}


//Encoder initialization
void REIN_GPIO_MT6816_ABZ_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* GPIO Ports Clock Enable */
  MT6816_ABZ_Z_GPIO_CLK_ENABLE();			
  /*Configure GPIO pins*/
  GPIO_InitStruct.Pin = MT6816_ABZ_Z_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;		
  GPIO_InitStruct.Pull = GPIO_NOPULL;						
  HAL_GPIO_Init(MT6816_ABZ_Z_GPIO_Port, &GPIO_InitStruct);
  /* EXTI interrupt init*/
  HAL_NVIC_EnableIRQ(MT6816_ABZ_Z_EXTI_IRQn);		
}
