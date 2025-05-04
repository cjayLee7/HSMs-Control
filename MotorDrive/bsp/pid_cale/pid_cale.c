#include "foc_it\foc_it.h"
#include "pid_cale.h"
PID_typedef pid_speed;
PID_typedef pid_current_id;
PID_typedef pid_current_iq;

void pid_calculation(PID_typedef *pid)
{
	pid->error_last=pid->error;
	pid->error=pid->Ref-pid->Fbk;
  // 比例的部分
  // u_p  = P *e(k)
	pid->op=pid->kp * pid->error;
  // 积分部分的Tustin变换
  // u_ik = u_ik_1  + I*Ts/2*(ek + ek_1)
	pid->oi=(int32_t)(pid->oi + pid->ki *(pid->error +pid->error_last)/(2*pid->fs));
  // 限制输出电压q
  pid->oi = _constrain(pid->oi, -pid->limit, pid->limit);
  // 离散的推导
  // u_dk = D(ek - ek_1)/Ts
	pid->od=(int32_t)(pid->kd *(pid->error + pid->error_last)*pid->fs);
  // 求和所有的分量
	pid->out=pid->op + pid->oi + pid->od;
  // 限制输出变量
  pid->out = _constrain(pid->out, -pid->limit, pid->limit);

  // 通过提高输出来限制加速度
//  float output_rate = (output - output_prev)/Ts;
//  if (output_rate > output_ramp)
//    output = output_prev + output_ramp*Ts;
//  else if (output_rate < -output_ramp)
//      output = output_prev - output_ramp*Ts;

  // 为下一浏览存储
//  integral_prev = integral;
//  output_prev = output;
//  error_prev = error;
//  timestamp_prev = timestamp_now;
//  return pid_speed.out;

}
//输出为iq_Ref，与电流相对应，4096为1A，
void pid_speed_init(void)
{
  pid_speed.Ref=0; //目标转速  4r/s
  pid_speed.Fbk=0;   			 
	pid_speed.kp=0;
	pid_speed.ki=0;
	pid_speed.kd=0;		
	pid_speed.error=0;
	pid_speed.error_last=0;	//误差记录
  pid_speed.op=0;
	pid_speed.oi=0;
	pid_speed.od=0;							
	pid_speed.limit=40000;//4096;						//限制输出 4096=1A
	pid_speed.out=0;										//输出
	pid_speed.fs=1250;       //=1/Ts=500,Ts=0.002
}
//输出为U_d和U_q,用于反park变换，输出电压与Period值相比，占空比
void pid_current_init(void)
{
  pid_current_id.Ref=0;   
  pid_current_id.Fbk=0;   			 
	pid_current_id.kp=0;//FOC:0
	pid_current_id.ki=150;//FOC:100
	pid_current_id.kd=0;		
	pid_current_id.error=0;
	pid_current_id.error_last=0;	//误差记录
  pid_current_id.op=0;
	pid_current_id.oi=0;
	pid_current_id.od=0;							//输出
	pid_current_id.limit=20*1024;						//限制 100%占空比
	pid_current_id.out=0;										//输出
	pid_current_id.fs=25000;       //=1/Ts=12500,Ts=0.000080
	
	pid_current_iq.Ref=0;  
  pid_current_iq.Fbk=0;   			 
	pid_current_iq.kp=0;//0
	pid_current_iq.ki=150;//100
	pid_current_iq.kd=0;		
	pid_current_iq.error=0;
	pid_current_iq.error_last=0;	//误差记录
  pid_current_iq.op=0;
	pid_current_iq.oi=0;
	pid_current_iq.od=0;							
	pid_current_iq.limit=20*1024;						//限制
	pid_current_iq.out=0;										//输出
	pid_current_iq.fs=25000;       //=1/Ts=12500,Ts=0.000080

}
