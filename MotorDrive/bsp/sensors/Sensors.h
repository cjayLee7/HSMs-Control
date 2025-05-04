#ifndef SENSORS_H
#define SENSORS_H

#ifdef __cplusplus
extern "C" {
#endif

	
#include ".\loop\loop_port.h"
	
#define MT6816_Mode_PWM		(0x01)	//MT6816������PWMģʽ		
#define Sensor_Mode_ABZ		(0x02)	//������ABZģʽ		
#define MT6816_Mode_SPI		(0x03)	//MT6816������SPIģʽ		
//GPIO��(tim.c�е���)
#define ABZ_A_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()	//PC6
#define ABZ_A_GPIO_Port					(GPIOC)
#define ABZ_A_Pin 								(GPIO_PIN_6)
#define ABZ_B_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()	//PC7
#define ABZ_B_GPIO_Port					(GPIOC)
#define ABZ_B_Pin 								(GPIO_PIN_7)
#define GPIO_CH1_AFx_TIMx                   GPIO_AF2_TIM3//���ù��ܣ�����������ֻ��CH1��CH2
#define GPIO_CH2_AFx_TIMx                   GPIO_AF2_TIM3

#define Sensor_Mode		Sensor_Mode_ABZ

//�ṹ��
typedef struct{
	uint16_t	MechAngle;	//ABZ��ȡ��������,��еλ��0-3999
//	uint16_t	OffsetAngle;		//ƫ���е�Ƕ�
	uint16_t	ElecAngle;		//��Ƕ�0~79
	uint16_t	angle;				//ABZ����ĽǶ�0-2pi

}Sensor_ABZ_Signal_Typedef;

typedef struct{
	uint16_t	angle_data;				//�Ƕ�����
	uint16_t	rectify_angle;		//У׼�ĽǶ�����
	bool			rectify_valid;		//У׼������Ч��־
}Sensor_Typedef;

extern Sensor_Typedef	Encoder;
extern Sensor_ABZ_Signal_Typedef	Encoder_abz;

//
void Sensor_Init(void);							//Sensor��ʼ��
void Sensor_Get_AngleData(void);			//Sensor��ȡ�Ƕ�����
void Sensor_ABZ_Signal_Init(void);			//Sensor_ABZ�ɼ���ʼ��
void Sensor_ABZ_ZPulse_Callback(void);	//Sensor_ABZ�ɼ�Z�����жϻص�
void Sensor_ABZ_Get_AngleData(void);		//Sensor_ABZ��ȡ�Ƕ�����
	

	
	
	#ifdef __cplusplus
}
#endif
	 
#endif
