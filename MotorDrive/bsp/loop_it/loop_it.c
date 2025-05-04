#include ".\loop\loop_port.h"
#include "sensors\Sensors.h"
#include "test\test.h"
#include "loop\loop.h"

uint8_t lit_1ms_divider = 0;			//��ʱ�ӷ�Ƶ��(1ms)
uint8_t lit_20ms_divider = 0;
struct Loop_IT_Typedef{
	//�жϼ�����
	uint32_t	systick_count;
	uint32_t	exti7_count;
	uint32_t	time3_count;
	uint32_t	dma1_ch4_count;
	uint32_t	dma1_ch5_count;
	uint32_t	uart1_count;
}loop_it;


void SysTick_Handler(void)
{

//	loop_it.systick_count++;
		//1ms��Ƶ
		lit_1ms_divider++;
//        lit_20ms_divider++;
		if(lit_1ms_divider >= 20){
			lit_1ms_divider  = 0;
			loop_second_base_1ms();		//��ʱ��1msʱ��
			HAL_IncTick();	//�ṩHAL���1ms�жϵ���,ά��HAL_Delay�ȳ�ʱ��������Чִ��
		}
        
//        if(lit_20ms_divider >= 400){
//            lit_20ms_divider  = 0;
//            time_second_20ms_serve();
//        }

}

