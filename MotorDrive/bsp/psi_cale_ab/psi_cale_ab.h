#ifndef PSI_CONTROL_AB_H
#define PSI_CONTROL_AB_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include ".\loop\loop_port.h"	
	
//Variable typedef
typedef struct { 
				
            float  a_acc_d;   
		    float  a_acc_d_l;
            float  a_m;
            float  acc_time;
            float  dcc_time;
    
            float  acc_d;   
			float  acc_d_l;
            float  omega_d;   
		    float  omega_d_l; 
			float  theta_d;   
            float  theta_d_l;
            float  theta_e;
            float  theta_e_l;
            float  theta_e_out;
            float  theta_oi;
    
            bool   dcc_flag;
            bool   new_move; 
            bool   acc_flag;  
            float  theta_pin; 
            float  theta_acc; 
            float  speed;   
            float  distance;   
            float  omega_s;   //omega_*
			float  omega_s_l;   
		    float  theta;   
            float  omega;   
            float  omega_e;
            float  omega_e_l;
            float  omega_oi;
            
            float  omega_x;
            
		    float  tau_d;  

			float  d_psi_a_l;   
			float  d_psi_a;   
		    float  psi_a;  
		    float  psi_a_l;   

			float  d_psi_b_l;   
			float  d_psi_b;   
            float  psi_b;  
            float  psi_b_l;   

            float  dpsi_Sine;
            float  dpsi_Cosine;
            float  current_fw;
            float  dpsi_s;   
            float  psi_s;
            
            float Sine;
            float Cosine;
            int32_t pin;
            
            float  ia;   
            float  ia_l;
			float  ia_d;  
            float  ia_d_l;
			float  ia_oi;	
			float  ia_oi_l;	
			float  ia_e;	
			float  ia_e_l;	
            float  ia_od;
			float  ud;	
			float  ua_out;	
            float  um;   
            float  um_l;
            
            float  ib;  
            float  ib_l;
			float  ib_d;   
            float  ib_d_l;
			float  ib_oi;	
			float  ib_oi_l;	
			float  ib_e;	
			float  ib_e_l;	
            float  ib_od;
			float  uq;	
			float  ub_out;	
            float  ut;  
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

			 float vbus;
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
