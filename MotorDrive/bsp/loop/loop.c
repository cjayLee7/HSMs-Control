//Oneself
#include "loop.h"



//Base_Drivers
#include "loop_port.h"
#include "sensors\Sensors.h"
#include "pid_cale/pid_cale.h"
#include "hw_pwm/hw_pwm.h"

//Control
#include "control_config\control_config.h"

#include "psi_cale_ab\psi_cale_ab.h"
#include "foc_it\foc_it.h"
//Debug
#include "key\bsp_key.h" 
#include "test\test.h"

#include "parameter\parameter.h"
#include "pid_cale\pid_cale.h"
#include "psi_cale_ab\psi_cale_ab.h"

bool foc_start=false;
uint32_t time_1ms_count = 0;
//uint32_t major_cycle_count = 0;
static uint32_t time_second_1ms = 0;
static uint32_t time_second_10ms = 0;
static uint32_t time_second_20ms = 0;
static uint32_t time_second_50ms = 0;
static uint32_t time_second_100ms = 0;

extern uint32_t ADC_ConvertedValueLocal[ADC_CHANNEL_NUMBER];

extern uint16_t ADC_ConvertedValue[ADC_CHANNEL_NUMBER];
extern int32_t ADC_offset[3];

extern vary_parameter_typedef vary;
extern PID_typedef pid_current_id;
extern PID_typedef pid_current_iq;
extern PID_typedef pid_speed;
extern est_speed_typedef est_speed;

extern uint32_t count_a;
/**
* @brief ��ʱ��10msִ��
*/
void time_second_10ms_serve(void)
{

     if( foc_start==true)
    {
      
        float buffer[140]={vary.theta_d_l,vary.theta,vary.omega_d_l,vary.omega,vary.a_acc_d,vary.acc_d,vary.ia_d_l,vary.ib_d_l,
                        vary.iq,vary.id,vary.acc_time,vary.dcc_time,vary.omega_e,vary.theta_e_out};
        Serial_DMA_Float(buffer,14);//number��Ϊ���ݸ���
    }

}

/**
* @brief ��ʱ��20msִ��
*/
void time_second_20ms_serve(void)
{
	//����(50Hzˢ����)
    Button_Scan_ms(20);
//    test4();
    Button_Stop();

}

/**
* @brief ��ʱ��50msִ��
*/
void time_second_50ms_serve(void)
{

}

/**
* @brief ��ʱ��100msִ��
*/
void time_second_100ms_serve(void)
{
    if( foc_start==true)
    {
        printf("%d\n",count_a);
//        float a= (float)count_a;
//        float buffer[15]={a,};
//        Serial_DMA_Float(buffer,1);
    }
}
	
/**
* @brief ��ʱ��ѭ��ִ��
**/
void time_second_run(void)
{
//    if(time_second_10ms)		{time_second_10ms--;		time_second_10ms_serve();		}
//	if(time_second_20ms)		{time_second_20ms--;		time_second_20ms_serve();		}
//	if(time_second_50ms)		{time_second_50ms--;		time_second_50ms_serve();		}
//if(time_second_100ms)		{time_second_100ms--;		time_second_100ms_serve();	}
}

/**
* @brief ��ʱ��1msʱ��
**/
void loop_second_base_1ms(void)
{
	time_1ms_count++;
	time_second_1ms++;
	if(!(time_second_1ms % 10))		{time_second_10ms++;time_second_10ms_serve();		}
	if(!(time_second_1ms % 20))		{time_second_20ms++;time_second_20ms_serve();		}
	if(!(time_second_1ms % 50))		{time_second_50ms++; 		}
	if(!(time_second_1ms % 500))	{time_second_100ms++;		}
	if(!(time_second_1ms % 1000))	{time_second_1ms = 0;		}
}

/**
* This is Main LOOP
*/
void loop(void)
{
	
    Button_Init();//������ʼ��
	LED_GPIO_Config();//LED��ʼ��
	
	//���йؼ������ʼ��ǰ�ȴ���Դ�ȶ�
	HAL_Delay(1000);
	
	//���������ʼ��
	MX_USART1_UART_Init();//��ʼ�����ڲ����ô����ж����ȼ�
	MX_ADC1_Init();//ADC+DMA��ʼ��
	HAL_Delay(500);
	Sensor_Init();//��������ʼ��
    MX_TIM8_Init();//��ʱ��8��ʼ��
    Hbrige_GPIO_Config();//H�ſ����źų�ʼ��
    
    psi_control_Init();//psi��������������ʼ��
    pid_current_init();//PID��������������ʼ��
    pid_speed_init();
    HAL_Delay(1000);
    
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
    Out_AP_CLOSE();
    Out_BP_CLOSE();
    HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&ADC_ConvertedValue,ADC_CHANNEL_NUMBER);//��ʼ�ж�
    Offset_CurrentReading(); // ���ϵ�����£�����������ƫִ��ѹ
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_Delay(200);
//    resistance_test(); //��������



	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET);//led2��
	Out_AM_CLOSE();
	Out_BM_CLOSE();
    HAL_Delay(500);
    Out_PWM_AP(336-1);
//    Out_PWM_BM(1000);
    HAL_Delay(1000);
//    Out_PWM_BM(400);
    Out_AP_CLOSE();

	__HAL_TIM_SET_COUNTER(&ABZ_Get_HTIM, 0);

	HAL_Delay(500);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);//led2��
    //����λ���Բ������и�ֵ�󣬽����㷨�ж�
    
//FOR Circulation
	for(;;)
		{

		}
}
