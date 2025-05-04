#ifndef PID_CALE_H
#define PID_CALE_H

#include ".\loop\loop_port.h"


typedef struct {
	     int32_t  Ref;   // 给定参数
			 int32_t  Fbk;   // 反馈参数 			 
			int32_t	kp, ki, kd;		//参数
			//控制参数
			int32_t		error, error_last;	//误差记录
			int32_t		op, oi, od;							//输出
			int32_t		limit;						//限制
			int32_t		out;										//输出
			int32_t		fs;       //=1/Ts
	   }PID_typedef;


void pid_calculation(PID_typedef *);//借鉴simple_foc

void pid_speed_init(void);
void pid_current_init(void);

#endif
