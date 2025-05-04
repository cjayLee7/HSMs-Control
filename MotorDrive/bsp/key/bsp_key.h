#ifndef __BSP_KEY_H__
#define	__BSP_KEY_H__

#ifdef __cplusplus
extern "C" {
#endif
#include ".\loop\loop_port.h"

//���Ŷ���
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

 /** �������±��ú�
	* ��������Ϊ�ߵ�ƽ������ KEY_ON=1�� KEY_OFF=0
	* ����������Ϊ�͵�ƽ���Ѻ����ó�KEY_ON=0 ��KEY_OFF=1 ����
	*/
#define KEY_ON	1
#define KEY_OFF	0

/*******************************************************/
//��������
#define Button_Quan		5		//����֧������
#define Button_1			1		//�������
#define Button_2  		2		//�������
#define Button_3			3		//�������
#define Button_4  		4		//�������
#define Button_5			5		//�������

//ʶ������
#define Button_Shake_Time	20		//msȥ��ʱ��
#define Button_Long_Time	1000	//ms��������ʱ��

typedef enum{
	//����״̬
	Button_Bit_Up = 0,			//״̬_����
	Button_Bit_Shake,				//״̬_����
	Button_Bit_Press,				//״̬_����
	Button_Bit_Long,				//״̬_����
	//����״̬
	Button_Bit_Drop,				//����_����
	Button_Bit_Rise,				//����_����
	Button_Bit_LongDrop,		//����_��������
	Button_Bit_LongRise,		//����_��������
}Button_State_Typedef;

typedef struct{
	//����
	bool									level;		//����ˮƽ
	Button_State_Typedef	state;		//����״̬
	uint32_t							time_ms;	//����ʱ��
}Button_Typedef;

void Button_Init(void);								//������ʼ��
void Button_Scan_ms(uint32_t _time);	//��ʱɨ��
Button_State_Typedef Button_Inquice_State(uint16_t button_num);		//��ȡ����״̬




void Key_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
void LED_GPIO_Config(void);

#ifdef __cplusplus
}
#endif
#endif /* __LED_H */

