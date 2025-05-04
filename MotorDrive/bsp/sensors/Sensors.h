#ifndef SENSORS_H
#define SENSORS_H

#ifdef __cplusplus
extern "C" {
#endif

	
#include ".\loop\loop_port.h"
	
#define MT6816_Mode_PWM		(0x01)	//MT6816工作在PWM模式		
#define Sensor_Mode_ABZ		(0x02)	//工作在ABZ模式		
#define MT6816_Mode_SPI		(0x03)	//MT6816工作在SPI模式		
//GPIO定(tim.c中调用)
#define ABZ_A_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()	//PC6
#define ABZ_A_GPIO_Port					(GPIOC)
#define ABZ_A_Pin 								(GPIO_PIN_6)
#define ABZ_B_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOA_CLK_ENABLE()	//PC7
#define ABZ_B_GPIO_Port					(GPIOC)
#define ABZ_B_Pin 								(GPIO_PIN_7)
#define GPIO_CH1_AFx_TIMx                   GPIO_AF2_TIM3//复用功能，编码器功能只有CH1和CH2
#define GPIO_CH2_AFx_TIMx                   GPIO_AF2_TIM3

#define Sensor_Mode		Sensor_Mode_ABZ

//结构体
typedef struct{
	uint16_t	MechAngle;	//ABZ读取到的数据,机械位置0-3999
//	uint16_t	OffsetAngle;		//偏差机械角度
	uint16_t	ElecAngle;		//电角度0~79
	uint16_t	angle;				//ABZ输出的角度0-2pi

}Sensor_ABZ_Signal_Typedef;

typedef struct{
	uint16_t	angle_data;				//角度数据
	uint16_t	rectify_angle;		//校准的角度数据
	bool			rectify_valid;		//校准数据有效标志
}Sensor_Typedef;

extern Sensor_Typedef	Encoder;
extern Sensor_ABZ_Signal_Typedef	Encoder_abz;

//
void Sensor_Init(void);							//Sensor初始化
void Sensor_Get_AngleData(void);			//Sensor获取角度数据
void Sensor_ABZ_Signal_Init(void);			//Sensor_ABZ采集初始化
void Sensor_ABZ_ZPulse_Callback(void);	//Sensor_ABZ采集Z脉冲中断回调
void Sensor_ABZ_Get_AngleData(void);		//Sensor_ABZ获取角度数据
	

	
	
	#ifdef __cplusplus
}
#endif
	 
#endif
