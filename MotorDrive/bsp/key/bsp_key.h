#ifndef __BSP_KEY_H__
#define	__BSP_KEY_H__

#ifdef __cplusplus
extern "C" {
#endif
#include ".\loop\loop_port.h"

//引脚定义
/*******************************************************/
#define KEY1_PIN                  GPIO_PIN_0                 
#define KEY1_GPIO_PORT            GPIOE                      
#define KEY1_GPIO_CLK_ENABLE()    __GPIOE_CLK_ENABLE()

#define KEY2_PIN                  GPIO_PIN_1                 
#define KEY2_GPIO_PORT            GPIOE                      
#define KEY2_GPIO_CLK_ENABLE()    __GPIOE_CLK_ENABLE()

#define KEY3_PIN                  GPIO_PIN_2                 
#define KEY3_GPIO_PORT            GPIOE                      
#define KEY3_GPIO_CLK_ENABLE()    __GPIOE_CLK_ENABLE()

#define KEY4_PIN                  GPIO_PIN_3                 
#define KEY4_GPIO_PORT            GPIOE                      
#define KEY4_GPIO_CLK_ENABLE()    __GPIOE_CLK_ENABLE()

#define KEY5_PIN                  GPIO_PIN_4                 
#define KEY5_GPIO_PORT            GPIOE                      
#define KEY5_GPIO_CLK_ENABLE()    __GPIOE_CLK_ENABLE()
/*******************************************************/

 /** 按键按下标置宏
	* 按键按下为高电平，设置 KEY_ON=1， KEY_OFF=0
	* 若按键按下为低电平，把宏设置成KEY_ON=0 ，KEY_OFF=1 即可
	*/
#define KEY_ON	1
#define KEY_OFF	0

/*******************************************************/
//工程配置
#define Button_Quan		5		//按键支持数量
#define Button_1			1		//按键编号
#define Button_2  		2		//按键编号
#define Button_3			3		//按键编号
#define Button_4  		4		//按键编号
#define Button_5			5		//按键编号

//识别配置
#define Button_Shake_Time	20		//ms去抖时间
#define Button_Long_Time	1000	//ms长按触发时间

typedef enum{
	//保持状态
	Button_Bit_Up = 0,			//状态_弹起
	Button_Bit_Shake,				//状态_抖动
	Button_Bit_Press,				//状态_按下
	Button_Bit_Long,				//状态_长按
	//边沿状态
	Button_Bit_Drop,				//边沿_按下
	Button_Bit_Rise,				//边沿_弹起
	Button_Bit_LongDrop,		//边沿_长按按下
	Button_Bit_LongRise,		//边沿_长按弹起
}Button_State_Typedef;

typedef struct{
	//数据
	bool									level;		//按键水平
	Button_State_Typedef	state;		//按键状态
	uint32_t							time_ms;	//按下时间
}Button_Typedef;

void Button_Init(void);								//按键初始化
void Button_Scan_ms(uint32_t _time);	//定时扫描
Button_State_Typedef Button_Inquice_State(uint16_t button_num);		//获取按键状态




void Key_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
void LED_GPIO_Config(void);

#ifdef __cplusplus
}
#endif
#endif /* __LED_H */

