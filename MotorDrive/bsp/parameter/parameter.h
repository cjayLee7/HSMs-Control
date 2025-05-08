#ifndef PARAMETER_H
#define PARAMETER_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include ".\loop\loop_port.h"

typedef struct {
           float  Ra;   
           float  Rb;   
           float  B;  
           float  J;  
           float  L;                                                      
           float Fm;
           float Nr;
           }motor_parameter_typedef;

	 
typedef struct {
            float    kp;   
            float    ki;   
            float    kd;   

            float    k1;   
            float    k2;   
            float    k3;  
            float    k4;
            float    Wc;    
            float    Ws;    
            float    Wi;

		   int32_t  fs_1;   
		   int32_t  fs_2;   
	   }control_parameter_typedef;



void P_motor_init(void);
void P_control_init(void);
		 

		 
		 
#ifdef __cplusplus
}
#endif

#endif
