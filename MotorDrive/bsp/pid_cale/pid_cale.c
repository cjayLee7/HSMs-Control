#include "foc_it\foc_it.h"
#include "pid_cale.h"
PID_typedef pid_speed;
PID_typedef pid_current_id;
PID_typedef pid_current_iq;

void pid_calculation(PID_typedef *pid)
{
	pid->error_last=pid->error;
	pid->error=pid->Ref-pid->Fbk;
  // u_p  = P *e(k)
	pid->op=pid->kp * pid->error;
  // u_ik = u_ik_1  + I*Ts/2*(ek + ek_1)
	pid->oi=(int32_t)(pid->oi + pid->ki *(pid->error +pid->error_last)/(2*pid->fs));
  	pid->oi = _constrain(pid->oi, -pid->limit, pid->limit);
  // u_dk = D(ek - ek_1)/Ts
	pid->od=(int32_t)(pid->kd *(pid->error + pid->error_last)*pid->fs);

	pid->out=pid->op + pid->oi + pid->od;
  	pid->out = _constrain(pid->out, -pid->limit, pid->limit);
}
//speed PID
void pid_speed_init(void)
{
  pid_speed.Ref=0;
  pid_speed.Fbk=0;   			 
	pid_speed.kp=0;
	pid_speed.ki=0;
	pid_speed.kd=0;		
	pid_speed.error=0;
	pid_speed.error_last=0;	
  pid_speed.op=0;
	pid_speed.oi=0;
	pid_speed.od=0;							
	pid_speed.limit=40000;					
	pid_speed.out=0;										
	pid_speed.fs=1250;      
}
//current PID
void pid_current_init(void)
{
  pid_current_id.Ref=0;   
  pid_current_id.Fbk=0;   			 
	pid_current_id.kp=0;
	pid_current_id.ki=150;
	pid_current_id.kd=0;		
	pid_current_id.error=0;
	pid_current_id.error_last=0;	
  pid_current_id.op=0;
	pid_current_id.oi=0;
	pid_current_id.od=0;							
	pid_current_id.limit=20*1024;						
	pid_current_id.out=0;										
	pid_current_id.fs=25000;       
	
	pid_current_iq.Ref=0;  
  pid_current_iq.Fbk=0;   			 
	pid_current_iq.kp=0;
	pid_current_iq.ki=150;
	pid_current_iq.kd=0;		
	pid_current_iq.error=0;
	pid_current_iq.error_last=0;	
  pid_current_iq.op=0;
	pid_current_iq.oi=0;
	pid_current_iq.od=0;							
	pid_current_iq.limit=20*1024;						
	pid_current_iq.out=0;										
	pid_current_iq.fs=25000;       

}
