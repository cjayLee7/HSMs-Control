#include ".\loop\loop_port.h"
#include "sensors\Sensors.h"
#include "test\test.h"
#include "loop\loop.h"

uint8_t lit_1ms_divider = 0;			//副时钟分频器(1ms)
uint8_t lit_20ms_divider = 0;
struct Loop_IT_Typedef{
	//中断计数器
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
		//1ms分频
		lit_1ms_divider++;
//        lit_20ms_divider++;
		if(lit_1ms_divider >= 20){
			lit_1ms_divider  = 0;
			loop_second_base_1ms();		//副时钟1ms时钟
			HAL_IncTick();	//提供HAL库的1ms中断调用,维持HAL_Delay等超时动作的有效执行
		}
        
//        if(lit_20ms_divider >= 400){
//            lit_20ms_divider  = 0;
//            time_second_20ms_serve();
//        }

}

