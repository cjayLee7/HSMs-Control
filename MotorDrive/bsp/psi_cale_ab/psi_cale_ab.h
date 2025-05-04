#ifndef PSI_CONTROL_AB_H
#define PSI_CONTROL_AB_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include ".\loop\loop_port.h"	
	
//中间变量	 
typedef struct { 
				
            float  a_acc_d;   //加加速度值
		    float  a_acc_d_l;
            float  a_m;
            float  acc_time;//被除数，不能为0
            float  dcc_time;
    
            float  acc_d;   //加速度值
			float  acc_d_l;
            float  omega_d;   //速度值
		    float  omega_d_l; 
			float  theta_d;   //位置值
            float  theta_d_l;
            float  theta_e;
            float  theta_e_l;
            float  theta_e_out;//位置误差输出
            float  theta_oi;
    
            bool   dcc_flag; //减速判断
            bool   new_move; //新的一次移动
            bool   acc_flag;  //记录加速距离后弹出
            float  theta_pin; //记录上次运动后位置
            float  theta_acc; //加速阶段位移圈速
            float  speed;   //速度模式时目标速度
            float  distance;    //位置模式时目标位置

            float  omega_s;   //omega_*
			float  omega_s_l;   //omega_*_last 用于求*的导数
		    float  theta;   //theta
            float  omega;   //omega
            float  omega_e;
            float  omega_e_l;
            float  omega_oi;
            
            float  omega_x;
            
		    float  tau_d;  

			float  d_psi_a_l;   //psi_a_last的导数 用于积分
			float  d_psi_a;   //psi_a的导数
		    float  psi_a;   //psi_a
		    float  psi_a_l;   

			float  d_psi_b_l;   //psi_b_last的导数 用于积分
			float  d_psi_b;   //psi_b的导数
            float  psi_b;   //psi_b
            float  psi_b_l;   

            float  dpsi_Sine;
            float  dpsi_Cosine;
            float  current_fw;
            float  dpsi_s;   
            float  psi_s;
            
            float Sine;
            float Cosine;
            int32_t pin;
            
            float  ia;   //ia
            float  ia_l;
			float  ia_d;   //ia_d
            float  ia_d_l;
			float  ia_oi;	//ia的积分输出项
			float  ia_oi_l;	//ia的上一步积分输出项
			float  ia_e;	//ia的误差值
			float  ia_e_l;	//ia的上一步误差值
            float  ia_od;//微分输出项
			float  ud;	//ud输出项
			float  ua_out;	//ua输出项
            float  um;   //m轴电压
            float  um_l;
            
            float  ib;   //ib
            float  ib_l;
			float  ib_d;   //ib_d
            float  ib_d_l;
			float  ib_oi;	//ib的积分输出项
			float  ib_oi_l;	//ib的上一步积分输出项
			float  ib_e;	//ib的误差值
			float  ib_e_l;	//ib的上一步误差值
            float  ib_od;//微分输出项
			float  uq;	//uq输出项
			float  ub_out;	//ua输出项
            float  ut;   //t轴电压
            float  ut_l;
            
            float  u_sum;
            float  u_e;
            float  u_e_l;
            float  u_oi;
            float  u_oi_l;
            
            float  iq;
            float  id;
            float  iq_d;
            float  id_d;
            float power;
            float power_l;

			 float vbus;//实时母线电压
			 bool valid_i_d;
             bool valid_u_d;
             bool valid_tau_d;
             bool valid_FWC;
             bool model_change;
	   }vary_parameter_typedef;

void second_loop(void);
void vary_parameter_init(void);
void psi_control_Init(void);



		 
#ifdef __cplusplus
}
#endif

#endif
