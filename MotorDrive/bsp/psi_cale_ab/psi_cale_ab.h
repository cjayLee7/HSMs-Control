#ifndef PSI_CONTROL_AB_H
#define PSI_CONTROL_AB_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include ".\loop\loop_port.h"	
	
//�м����	 
typedef struct { 
				
            float  a_acc_d;   //�Ӽ��ٶ�ֵ
		    float  a_acc_d_l;
            float  a_m;
            float  acc_time;//������������Ϊ0
            float  dcc_time;
    
            float  acc_d;   //���ٶ�ֵ
			float  acc_d_l;
            float  omega_d;   //�ٶ�ֵ
		    float  omega_d_l; 
			float  theta_d;   //λ��ֵ
            float  theta_d_l;
            float  theta_e;
            float  theta_e_l;
            float  theta_e_out;//λ��������
            float  theta_oi;
    
            bool   dcc_flag; //�����ж�
            bool   new_move; //�µ�һ���ƶ�
            bool   acc_flag;  //��¼���پ���󵯳�
            float  theta_pin; //��¼�ϴ��˶���λ��
            float  theta_acc; //���ٽ׶�λ��Ȧ��
            float  speed;   //�ٶ�ģʽʱĿ���ٶ�
            float  distance;    //λ��ģʽʱĿ��λ��

            float  omega_s;   //omega_*
			float  omega_s_l;   //omega_*_last ������*�ĵ���
		    float  theta;   //theta
            float  omega;   //omega
            float  omega_e;
            float  omega_e_l;
            float  omega_oi;
            
            float  omega_x;
            
		    float  tau_d;  

			float  d_psi_a_l;   //psi_a_last�ĵ��� ���ڻ���
			float  d_psi_a;   //psi_a�ĵ���
		    float  psi_a;   //psi_a
		    float  psi_a_l;   

			float  d_psi_b_l;   //psi_b_last�ĵ��� ���ڻ���
			float  d_psi_b;   //psi_b�ĵ���
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
			float  ia_oi;	//ia�Ļ��������
			float  ia_oi_l;	//ia����һ�����������
			float  ia_e;	//ia�����ֵ
			float  ia_e_l;	//ia����һ�����ֵ
            float  ia_od;//΢�������
			float  ud;	//ud�����
			float  ua_out;	//ua�����
            float  um;   //m���ѹ
            float  um_l;
            
            float  ib;   //ib
            float  ib_l;
			float  ib_d;   //ib_d
            float  ib_d_l;
			float  ib_oi;	//ib�Ļ��������
			float  ib_oi_l;	//ib����һ�����������
			float  ib_e;	//ib�����ֵ
			float  ib_e_l;	//ib����һ�����ֵ
            float  ib_od;//΢�������
			float  uq;	//uq�����
			float  ub_out;	//ua�����
            float  ut;   //t���ѹ
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

			 float vbus;//ʵʱĸ�ߵ�ѹ
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
