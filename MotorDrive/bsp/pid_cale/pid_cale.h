#ifndef PID_CALE_H
#define PID_CALE_H

#include ".\loop\loop_port.h"


typedef struct {
	     int32_t  Ref;   
			 int32_t  Fbk;   			 
			int32_t	kp, ki, kd;		
			
			int32_t		error, error_last;	
			int32_t		op, oi, od;							
			int32_t		limit;						
			int32_t		out;										
			int32_t		fs;       
	   }PID_typedef;


void pid_calculation(PID_typedef *);

void pid_speed_init(void);
void pid_current_init(void);

#endif
