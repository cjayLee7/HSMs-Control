#ifndef FOC_IT_H
#define FOC_IT_H

#include ".\loop\loop_port.h"

#define _constrain(a, b, c) ((a<b)?(a=b):(a>c)?(a=c):a)
#define _abs(a) ((a<0)?(a=-a):a)


typedef struct{
	int32_t		real_lap_location;			
	int32_t		real_lap_location_last;		
	int32_t		real_location;						
	int32_t		real_location_last;				
	int32_t		est_speed_mut;						
	int32_t		est_speed;								
	float speed;												
    float speed_l;
	int32_t		est_location;							
}est_speed_typedef;



void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef*);
void main_loop(void);
void Button_Stop(void);
//void TIM_Update_Callback(void);
void Calculate_Speed(void);
void Calculate_park(void);
void Calculate_Invpark(void);
void resistance_test(void);
void sin_cos(void);


void current_loop(void);

#endif
