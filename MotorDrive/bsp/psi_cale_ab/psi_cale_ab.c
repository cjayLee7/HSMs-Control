#include "psi_cale_ab.h"
#include "sensors\Sensors.h"
#include "foc_math\foc_math.h"
#include "foc_it\foc_it.h"
#include "control_config\control_config.h"
#include "parameter\parameter.h"

extern uint16_t ADC_ConvertedValue[ADC_CHANNEL_NUMBER];

extern uint32_t ADC_ConvertedValueLocal[ADC_CHANNEL_NUMBER];
extern est_speed_typedef est_speed;
extern int32_t ADC_offset[3];

extern motor_parameter_typedef P_motor1;
extern control_parameter_typedef P_control1;

volatile vary_parameter_typedef vary={0};

bool u_cov=false;
bool psi_cov=false;

//Torque control loop
void second_loop(void)
{
/********Motion trajectory 1******************/
    
    vary.acc_d=vary.acc_d+vary.a_acc_d/((float)P_control1.fs_2); //acc=-300t+60

    vary.omega_d=vary.omega_d+(vary.acc_d+vary.acc_d_l)/(2*(float)P_control1.fs_2);
    vary.acc_d_l=vary.acc_d;

    vary.theta_d_l=vary.theta_d;
    vary.theta_d=vary.theta_d+(vary.omega_d+vary.omega_d_l)/(2*(float)P_control1.fs_2);
    vary.omega_d_l=vary.omega_d;
    
    
    if((vary.acc_d<=0)&&(vary.acc_flag==false))
    {
        vary.a_acc_d=0;
        vary.acc_d=0;
        vary.theta_acc =vary.theta_d-vary.theta_pin;
        vary.acc_flag=true;
    }
    if(vary.theta_d>=(vary.theta_pin+vary.distance-vary.theta_acc))
    {
        vary.a_acc_d=-100.0f;
    }
    if(vary.omega_d<=0)
    {
        vary.a_acc_d=0;
        vary.acc_d=0;
        vary.omega_d=0;
    }
    //new move
    if(vary.new_move==true)
    {
        vary.a_acc_d=-100.0f;
        vary.acc_d=20.0f;
        vary.acc_d_l=20.0f;
        vary.theta_acc=0;
//        vary.distance=1.34f;
        vary.theta_pin=vary.theta_d;
        vary.acc_flag=false;
        vary.new_move=false;
    }
/*******************************************/


/******************Motion trajectory 2***************
    vary.omega_d=vary.omega_d+(vary.acc_d+vary.acc_d_l)/(2*(float)P_control1.fs_2);
    vary.acc_d_l=vary.acc_d;
    vary.theta_d_l=vary.theta_d;
    vary.theta_d=vary.theta_d+(vary.omega_d+vary.omega_d_l)/(2*(float)P_control1.fs_2);
    vary.omega_d_l=vary.omega_d;

    if((vary.omega_d>=vary.speed)&&(vary.acc_d>0))
    {
        vary.a_acc_d=vary.acc_d;
        vary.acc_d=0;
        vary.acc_d_l=0;
        vary.theta_pin=vary.theta_d;
    }
    if(((vary.theta_d-vary.theta_pin)>10)&&(vary.acc_d==0))
    {
        vary.acc_d=-vary.a_acc_d;
    }
     if((vary.omega_d<=0)&&(vary.acc_d<0))
    {
        vary.acc_d=0;
        vary.acc_d_l=0;
        vary.omega_d=0;
        vary.omega_d_l=0;
    }
     if(vary.new_move==true)
    {
        vary.acc_d_l=0;
        vary.acc_d=0;
        vary.omega_d_l=0;
        vary.omega_d=0;
        vary.new_move=false;
    }

*****************************************/

/******************Motion trajectory 3***************
    vary.omega_d=vary.speed;
    vary.theta_d_l=vary.theta_d;
    vary.theta_d=vary.theta_d+(vary.omega_d+vary.omega_d_l)/(2*(float)P_control1.fs_2);
    vary.omega_d_l=vary.omega_d;
*****************************************/

	vary.theta=(float)est_speed.real_location/4000.0f;//1=1r
	vary.omega=est_speed.speed;
	vary.theta_e=vary.theta_d-vary.theta;
    vary.theta_e_out=vary.theta_d_l-vary.theta;
    vary.omega_e= vary.omega_d_l-vary.omega;
    
//k1=300;k2=0.025
    vary.omega_s=vary.omega_d+P_control1.k1*vary.theta_e;
    float d_omega_s=(vary.omega_s-vary.omega_s_l)*P_control1.fs_2;
    vary.tau_d=P_control1.k2*(vary.omega_s-vary.omega)+vary.theta_e+P_motor1.B*vary.omega+P_motor1.J*d_omega_s;
    vary.tau_d=vary.tau_d*6.2832f;
    vary.omega_s_l=vary.omega_s;
    vary.valid_tau_d=true;
/***************************************************/
}

void psi_control_Init(void)
{
    P_motor_init();
    P_control_init();
    vary_parameter_init();
}

//Variable initialization
void vary_parameter_init(void)
{
        vary.a_acc_d=20.0f;  //acc=-100t+20  
		vary.a_acc_d_l=0;
        vary.a_m=0;
        vary.acc_time=1.0f;
        vary.dcc_time=1.0f;
    
        vary.acc_d=20.0f;   
		vary.acc_d_l=20.0f;
        vary.omega_d=0;   
		vary.omega_d_l=0; 
		vary.theta_d=0;   
        vary.theta_d_l=0;
        vary.theta_e=0;
        vary.theta_e_l=0;
        vary.theta_e_out=0;
        vary.theta_oi=0;
    
        vary.dcc_flag=false;
        vary.new_move=false;
        vary.acc_flag=false;
        vary.theta_pin=0; 
        vary.theta_acc=0; 
        vary.speed=0;
        vary.distance=1.34f;

    
		vary.omega_s=0;   //omega_*
		vary.omega_s_l=0;   
	
		vary.tau_d=0.3f;   
		vary.theta=0;   
        vary.omega=0;   
        vary.omega_e=0;
        vary.omega_e_l=0;
        vary.omega_oi=0;
        
        vary.omega_x=0;
		vary.d_psi_a_l=0; 
		vary.d_psi_a=0;
		vary.psi_a=P_motor1.Fm;
        vary.psi_a_l=P_motor1.Fm;
		vary.d_psi_b_l=0; 
		vary.d_psi_b=0;
	    vary.psi_b=0;  
        vary.psi_b_l=0;
        
        vary.dpsi_Sine=1;
        vary.dpsi_Cosine=0;
        vary.current_fw=0;
        vary.dpsi_s=1;
        vary.psi_s=1;
        
        vary.Sine=0;
        vary.Cosine=0;
        vary.pin=0;
        
	    vary.ia=0;  
        vary.ia_l=0;
		vary.ia_d=0;   
        vary.ia_d_l=0;
		vary.ia_oi=0;	
		vary.ia_oi_l=0;	
		vary.ia_e=0;	
		vary.ia_e_l=0;	
        vary.ia_od=0;
		vary.ud=0;	
        vary.ua_out=0;	
        vary.um=0;
        vary.um_l=0;
        
	    vary.ib=0;   
        vary.ib_l=0;
		vary.ib_d=0;   
		vary.ib_oi=0;	
		vary.ib_oi_l=0;	
		vary.ib_e=0;	
		vary.ib_e_l=0;	
        vary.ib_od=0;
		vary.uq=0;	
        vary.ub_out=0;
        vary.ut=0;
        vary.ut_l=0;
        
        vary.u_sum=0;
        vary.u_e=0;
        vary.u_e_l=0;
        vary.u_oi=0;
        vary.u_oi_l=0;
        
        vary.iq=0;
        vary.id=0;
        vary.iq_d=0;
        vary.id_d=0;
        
        vary.power=0;
        vary.power_l=0;
        
		vary.vbus=24.0f;
		vary.valid_i_d=false;
        vary.valid_u_d=false;
        vary.valid_tau_d =false;
        vary.valid_FWC=false;
        vary.model_change=false;
}
