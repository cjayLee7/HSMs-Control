#include "parameter.h"

motor_parameter_typedef P_motor1;
control_parameter_typedef P_control1;
//Motor parameter initialization
void P_motor_init(void)
{
	P_motor1.Ra=0.38f;
	P_motor1.Rb=0.38f;
	P_motor1.B=0.001f;
	P_motor1.J=0.000048f;
    P_motor1.L=0.00175f;
	P_motor1.Fm=0.015f;
	P_motor1.Nr=50;
}
//Initialization of control parameters
void P_control_init(void)
{
	P_control1.kp=0;
	P_control1.ki=1;
	P_control1.kd=0;
    
    P_control1.k1=300;
    P_control1.k2=0.025f;
    P_control1.k3=0.1f;
    P_control1.k4=20;
    P_control1.Wc=1.0f;
    P_control1.Ws=0.1f;
    P_control1.Wi=0.25f;
	P_control1.fs_1=35000;//Current loop frequency
	P_control1.fs_2=3500;//Torque control loop frequency

}
