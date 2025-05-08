#ifndef HW_PWM_H
#define HW_PWM_H

#include ".\loop\loop_port.h"


typedef struct {  
                  float  A_Alpha;  	
		 		  float  B_Beta;	 	
		 	 	  uint32_t  A_duty;		// CCR value,1680-1
		 	 	  uint32_t  B_duty;	  
	   }Spwm_typedef;

void Hbrige_GPIO_Config(void);
void Out_AP_CLOSE(void);
void Out_AM_CLOSE(void);
void Out_BP_CLOSE(void);
void Out_BM_CLOSE(void);
void Out_PWM_AP(uint32_t);
void Out_PWM_AM(uint32_t);
void Out_PWM_BP(uint32_t);
void Out_PWM_BM(uint32_t);
#endif
