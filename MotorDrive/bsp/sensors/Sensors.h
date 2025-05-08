#ifndef SENSORS_H
#define SENSORS_H

#ifdef __cplusplus
extern "C" {
#endif

	
#include ".\loop\loop_port.h"
	
#define MT6816_Mode_PWM		(0x01)			
#define Sensor_Mode_ABZ		(0x02)	//ABZ Mode	
#define MT6816_Mode_SPI		(0x03)		

#define ABZ_A_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()	//PC6
#define ABZ_A_GPIO_Port					(GPIOC)
#define ABZ_A_Pin 								(GPIO_PIN_6)
#define ABZ_B_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()	//PC7
#define ABZ_B_GPIO_Port					(GPIOC)
#define ABZ_B_Pin 								(GPIO_PIN_7)
#define GPIO_CH1_AFx_TIMx                   GPIO_AF2_TIM3/
#define GPIO_CH2_AFx_TIMx                   GPIO_AF2_TIM3

#define Sensor_Mode		Sensor_Mode_ABZ


typedef struct{
	uint16_t	MechAngle;			
	uint16_t	ElecAngle;		
	uint16_t	angle;		

}Sensor_ABZ_Signal_Typedef;

typedef struct{
	uint16_t	angle_data;				
	uint16_t	rectify_angle;		
	bool			rectify_valid;		
}Sensor_Typedef;

extern Sensor_Typedef	Encoder;
extern Sensor_ABZ_Signal_Typedef	Encoder_abz;

//
void Sensor_Init(void);							
void Sensor_Get_AngleData(void);			
void Sensor_ABZ_Signal_Init(void);			
void Sensor_ABZ_ZPulse_Callback(void);	
void Sensor_ABZ_Get_AngleData(void);		
	

	
	
	#ifdef __cplusplus
}
#endif
	 
#endif
