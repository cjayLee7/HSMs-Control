#include "Sensors.h"


Sensor_Typedef	Encoder;
Sensor_ABZ_Signal_Typedef	Encoder_abz;

/****************************** Encoder ******************************/

/**
  * @brief  ��������ʼ��
  * @param  NULL
  * @retval NULL
**/
void Sensor_Init(void)
{
#ifndef Sensor_Mode
	#error "NO define Sensor_Mode"
#endif
#if   (Sensor_Mode == Sensor_Mode_PWM)
	Sensor_PWM_Signal_Init();		//��ʼ��PWM�ӿ�
#elif (Sensor_Mode == Sensor_Mode_SPI)
	Sensor_SPI_Signal_Init();		//��ʼ��SPI�ӿ�
#elif (Sensor_Mode == Sensor_Mode_ABZ)
	Sensor_ABZ_Signal_Init();		//��ʼ��ABZ�ӿ�
#else
	#error "Sensors_Mode Invalid !!!"
#endif
	
	//��ʼ���׶λ�ȡһ�νǶ�����(���˴�������)(��δ������λ���һ�ζ�ȡ���ݶ�ʧ��ԭ��)
	Sensor_Get_AngleData();

}


/**
  * @brief  ��ȡ�Ƕ�����
  * @param  NULL
  * @retval NULL
**/
void Sensor_Get_AngleData(void)
{
#ifndef Sensor_Mode
	#error "NO define MT6816_Mode"
#endif
#if   (Sensor_Mode == MT6816_Mode_PWM)
	REIN_MT6816_PWM_Get_AngleData();	//MT6816_PWM��ȡ�Ƕ�����
	mt6816.angle_data = mt6816_pwm.angle;
	mt6816.rectify_angle = Read_QuickCali_DATA[mt6816.angle_data];
#elif (Sensor_Mode == MT6816_Mode_SPI)
	RINE_MT6816_SPI_Get_AngleData();
	mt6816.angle_data = mt6816_spi.angle;
	mt6816.rectify_angle = Read_QuickCali_DATA[mt6816.angle_data];
#elif (Sensor_Mode == Sensor_Mode_ABZ)
	Sensor_ABZ_Get_AngleData();	//ABZ��ȡ�Ƕ�����
	
#else
	#error "Sensor_Mode Invalid !!!"
#endif
}

/****************************** ABZ ******************************/

/**
  * @brief  ABZ�ɼ���ʼ��
  * @param  NULL
  * @retval NULL
**/
void Sensor_ABZ_Signal_Init(void)
{
	//�ɼ�����
	Encoder_abz.MechAngle = 0;
	//�������
//	Encoder_abz.OffsetAngle = 0;
	Encoder_abz.ElecAngle = 0;
	Encoder_abz.angle = 0;

	//��������
	TIM_Encoder_ABZ_Init();
//	GPIO_Encoder_ABZ_Init();//Z�ź�
}

/**
  * @brief  ABZ�ɼ�Z�����жϻص�
  * @param  NULL
  * @retval NULL
**/
void Sensor_ABZ_ZPulse_Callback(void)
{
	//�����ʱ������ֵ
	__HAL_TIM_SET_COUNTER(&ABZ_Get_HTIM, 0);
}

/**
  * @brief  ABZ��ȡ�Ƕ�����
  * @param  NULL
  * @retval NULL
**/
void Sensor_ABZ_Get_AngleData(void)
{
	Encoder_abz.MechAngle = __HAL_TIM_GET_COUNTER(&ABZ_Get_HTIM);	//��ȡ��ʱ������ֵ0~3999	
	Encoder_abz.ElecAngle = Encoder_abz.MechAngle%80;		//4000/50=80,��õ�Ƕ�0~79��50��������
}


/**
  * @brief  GPIO��ʼ��(Z)
  * @param  NULL
  * @retval NULL
*/
void REIN_GPIO_MT6816_ABZ_Init(void)
{
#ifdef MT6816_ABZ_Z_GPIO_CLK_ENABLE
	
	 GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* GPIO Ports Clock Enable */
  MT6816_ABZ_Z_GPIO_CLK_ENABLE();			//����ABZ_Z�˿�ʱ��
  /*Configure GPIO pins*/
  GPIO_InitStruct.Pin = MT6816_ABZ_Z_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;		//�����ش����ж�
  GPIO_InitStruct.Pull = GPIO_NOPULL;						//����������
  HAL_GPIO_Init(MT6816_ABZ_Z_GPIO_Port, &GPIO_InitStruct);
  /* EXTI interrupt init*/
  HAL_NVIC_EnableIRQ(MT6816_ABZ_Z_EXTI_IRQn);		//����Z�ж�
#endif
}
