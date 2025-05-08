#ifndef __BSP_KEY_H__
#define	__BSP_KEY_H__

#ifdef __cplusplus
extern "C" {
#endif
#include ".\loop\loop_port.h"

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

#define KEY_ON	1
#define KEY_OFF	0

/*******************************************************/

#define Button_Quan		5		//The number of keys
#define Button_1			1	//Key number
#define Button_2  		2		
#define Button_3			3		
#define Button_4  		4		
#define Button_5			5		

#define Button_Shake_Time	20		
#define Button_Long_Time	1000	

//Key status
typedef enum{
	Button_Bit_Up = 0,			
	Button_Bit_Shake,				
	Button_Bit_Press,				
	Button_Bit_Long,			
	Button_Bit_Drop,			
	Button_Bit_Rise,			
	Button_Bit_LongDrop,		
	Button_Bit_LongRise,		
}Button_State_Typedef;

typedef struct{

	bool									level;		
	Button_State_Typedef	state;		
	uint32_t							time_ms;	
}Button_Typedef;

void Button_Init(void);								
void Button_Scan_ms(uint32_t _time);	
Button_State_Typedef Button_Inquice_State(uint16_t button_num);		




void Key_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
void LED_GPIO_Config(void);

#ifdef __cplusplus
}
#endif
#endif /* __LED_H */

