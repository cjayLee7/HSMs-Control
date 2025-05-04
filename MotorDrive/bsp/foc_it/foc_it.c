#include "foc_it.h"
#include "adc.h"
#include "usart.h"

#include "key\bsp_key.h" 
#include "sensors\Sensors.h"
#include "control_config\control_config.h"

#include "pid_cale\pid_cale.h"
#include "foc_cale\foc_cale.h"
#include "foc_math\foc_math.h"
#include "psi_cale_ab\psi_cale_ab.h"

#include "hw_pwm\hw_pwm.h"
//loop�������
extern TIM_HandleTypeDef htim1;//����ʱ���ź�
extern bool foc_start;
uint32_t time_loop1 = 0;
uint32_t time_loop2 = 0;
uint32_t count_a=0;
uint32_t over_current = 0;

extern Spwm_typedef spwm;

//PID+foc�㷨
extern PID_typedef pid_speed;
extern park_typedef P_park;
extern Invpark_typedef P_Invpark;
extern PID_typedef pid_current_id;
extern PID_typedef pid_current_iq;
//uint16_t Run_mode=2;

//psi�㷨
#include "parameter\parameter.h"
extern vary_parameter_typedef vary;
extern motor_parameter_typedef P_motor1;
extern control_parameter_typedef P_control1;

//dpsi X FOC
extern park_typedef_f current_park;
extern park_typedef_f dpsi_park;
extern Invpark_typedef_f U_Invpark;
extern Invpark_typedef_f I_Invpark;
extern park_typedef_f U_park;


est_speed_typedef est_speed={0,0,0,0,0,0,0,0};


//ADC
extern int32_t ADC_offset[3];
extern uint16_t ADC_ConvertedValue[ADC_CHANNEL_NUMBER];
extern uint32_t ADC_ConvertedValueLocal[ADC_CHANNEL_NUMBER];
int32_t ADC_value_3[ADC_CHANNEL_NUMBER][COVER_BUFFER_SIZE]={0};//��iͨ���ĵ�j������
int32_t ADC_max[ADC_CHANNEL_NUMBER][2]={0};
int32_t ADC_min[ADC_CHANNEL_NUMBER][2]={4096};
int32_t ADC_sum_i[ADC_CHANNEL_NUMBER]={0};
__IO uint32_t DMA_Transfer_Complete_Count=0;
__IO uint8_t  finish_flag=0;
__IO uint8_t  finish_convert=1;
//UART
extern uint8_t RxBuffer[1];//���ڽ��ջ���
extern uint16_t RxLine;//ָ���
extern uint8_t DataBuff[200];//ָ������

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
 //����
    for(uint8_t x=0;x<ADC_CHANNEL_NUMBER;x++)
    {
        ADC_value_3[x][DMA_Transfer_Complete_Count]=(uint32_t)ADC_ConvertedValue[x];
    }
    DMA_Transfer_Complete_Count++;
    if(DMA_Transfer_Complete_Count==COVER_BUFFER_SIZE)
    {
        DMA_Transfer_Complete_Count=0;
        finish_flag=1;
    }

    if(finish_flag==1)
    {
        //�˲�
        for(int i=0; i<ADC_CHANNEL_NUMBER; i++)
        {
             ADC_max[i][0]=ADC_value_3[i][1];//���ֵ
//             ADC_max[i][1]=0;//�δ�ֵ
             ADC_min[i][0]=ADC_value_3[i][1];//��Сֵ
//             ADC_min[i][1]=4096;//��Сֵ
            for(int j=1; j<COVER_BUFFER_SIZE; j++)//�ɼ��ĵ�һ����������
            {
                ADC_sum_i[i]=ADC_value_3[i][j]+ADC_sum_i[i];//�󼸴β����ĺ�
                
                if(ADC_value_3[i][j] > ADC_max[i][0])//ѡȡ����Լ��ڶ����ֵ
                {
//                    ADC_max[i][1]= ADC_max[i][0];
                    ADC_max[i][0]= ADC_value_3[i][j];
                } 
//                else if(ADC_value_3[i][j] > ADC_max[i][1])
//                {
//                    ADC_max[i][1]= ADC_value_3[i][j];
//                }
                
                if(ADC_value_3[i][j] < ADC_min[i][0]) //ѡȡ��С�Լ��ڶ�С��ֵ
                {
//                    ADC_min[i][1]=ADC_min[i][0];
                    ADC_min[i][0]=ADC_value_3[i][j];
                }
//                else if(ADC_value_3[i][j] < ADC_min[i][1])
//                {
//                    ADC_min[i][1]=ADC_value_3[i][j];
//                }
            }
        }
        
        for(int j=0;j<ADC_CHANNEL_NUMBER;j++)
		{
            //��ȥ�������ֵ����Сֵ��Ȼ��ȡƽ��;������Ϊ3.3Vʱ��ADת�����Ϊ4096
			ADC_ConvertedValueLocal[j] =(ADC_sum_i[j]-ADC_max[j][0]-ADC_min[j][0])/(COVER_BUFFER_SIZE-3);
            ADC_sum_i[j]=0;
		}
        finish_flag=0;
        //������ֵת��������ʵ�ʵ���ֵ���������ֵ�Ƚϵõ�ת����ϵ
        vary.ia=(float)((int32_t)ADC_ConvertedValueLocal[0]-ADC_offset[0])*17.8378f/4096;  //������ɼ�,����Ӳ���˷Ź�ʽ
        vary.ib=(float)((int32_t)ADC_ConvertedValueLocal[1]-ADC_offset[1])*17.8378f/4096;  //������ɼ�
        vary.vbus=24.0f;  //ĸ�ߵ�ѹ,ĸ�ߵ�ѹ�ɼ�������Ӳ����·����
        //��ͨ�˲�
//        vary.ia=vary.ia*P_control1.Wc+vary.ia_l* (1-P_control1.Wc);
//        vary.ib=vary.ib*P_control1.Wc+vary.ib_l* (1-P_control1.Wc);
//        vary.ia_l=vary.ia;
//        vary.ib_l=vary.ib;
        //��������
        if((vary.ia>1.8f)||(vary.ib>1.8f )||(vary.ia<-1.8f)||(vary.ib<-1.8f ))
        {
            if(foc_start==true)
            {
                over_current++;
                if( over_current==P_control1.fs_1/2)//����0.5s��ͣ��
                {
                    over_current=0;
                    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);//led2
                    foc_start=false;
                    Out_AM_CLOSE();
                    Out_BM_CLOSE();
                }
            }else
            {
                over_current++;
                if( over_current==P_control1.fs_1)//����0.5s��ͣ��
                {
                    over_current=0;
//                    Out_AM_CLOSE();
//                    Out_BM_CLOSE();
                }
            }
        }else
        over_current=0;
        //������ѭ��
        main_loop();
    }
    
}


void main_loop(void)//��ѭ��
{
	if(foc_start==true)
	{
        count_a++;
        if(count_a==P_control1.fs_1)
        {
            HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_6);
            count_a=0;
        }
        
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);//led2

        //�������ٻ�
        Sensor_ABZ_Get_AngleData();
        int32_t sub_data;
        //��ȡ��Ȧλ��
        est_speed.real_lap_location_last = est_speed.real_lap_location;
        est_speed.real_lap_location = Encoder_abz.MechAngle;//0~3999��2pi�������ƣ�=4000
        sub_data = est_speed.real_lap_location - est_speed.real_lap_location_last;
        if(sub_data > (Move_Pulse_NUM >> 1))
            sub_data -= Move_Pulse_NUM;
        else if(sub_data < -(Move_Pulse_NUM >> 1))
            sub_data += Move_Pulse_NUM;
        //��ȡ��λ��
        est_speed.real_location += sub_data;
        
        time_loop2++;
        if(time_loop2==10)
        {
         //λ�ø���
            time_loop2=0;
            Calculate_Speed();
            est_speed.real_location_last = est_speed.real_location;
            second_loop();
            vary.theta=(float)est_speed.real_location/4000.0f;
            vary.omega=est_speed.speed;
        }

        current_loop();

		//�����ѹ���
		//tim8,spwm
		spwm.A_Alpha=vary.ua_out;
		spwm.B_Beta=vary.ub_out;
        _abs(spwm.A_Alpha);
        _abs(spwm.B_Beta);
		_constrain(spwm.A_Alpha, 0 , vary.vbus);
		_constrain(spwm.B_Beta,0 , vary.vbus);
        //ע�ⱻ������Ϊ��
        if(vary.vbus<1)
        {
            foc_start=false;
        }else
        {
            spwm.A_duty=(uint32_t)(spwm.A_Alpha*1680/vary.vbus);
            spwm.B_duty=(uint32_t)(spwm.B_Beta*1680/vary.vbus);
        }
		if(vary.ua_out > 0)         Out_PWM_AP(spwm.A_duty);
		else if(vary.ua_out < 0)    Out_PWM_AM(spwm.A_duty);
		else                        Out_AP_CLOSE();
		if(vary.ub_out > 0)         Out_PWM_BP(spwm.B_duty);
		else if(vary.ub_out< 0)     Out_PWM_BM(spwm.B_duty);
		else                        Out_BP_CLOSE();
        
	}

}

//����ͣ��
void Button_Stop(void)
{
    if( Button_Inquice_State(Button_1) == Button_Bit_Drop  )
	{
        //ͣ������
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);//led2
        vary.ua_out=0;
        vary.ub_out=0;
        foc_start=false;
        Out_AM_CLOSE();
        Out_BM_CLOSE();

	}
}

void sin_cos(void)
{
    int32_t Angle;
    int32_t Sine=0;
    int32_t Cosine=1;
    Angle= Encoder_abz.ElecAngle+vary.pin;//0~79,0~2pi
    if(Angle>79 )
        Angle=Angle-79;
    if(Angle<0 )
        Angle=Angle+79;
    

    if(Angle<40){		//0~pi
        if(Angle<20)		//0~pi/2
        {
            Sine=sin_pi[(Angle)* 25];	// 500/20=25
            Cosine=sin_pi[(20-Angle)*25];
        }
        else		//pi/2~pi
        {
            Sine=sin_pi[(40-Angle)* 25];
            Cosine=-sin_pi[(Angle-20)*25];
        }
    }
    else {			//pi~2pi
        if(Angle<60)		//pi~3pi/2
        {
            Sine=-sin_pi[(Angle-40)* 25];
            Cosine=-sin_pi[(60-Angle)*25];
        }
        else		//3pi/2~2pi
        {
            Sine=-sin_pi[(80-Angle)* 25];
            Cosine=sin_pi[(Angle-60)*25];
        }
    }
    vary.Sine=(float)Sine/4096.0f;
    vary.Cosine=(float)Cosine/4096.0f;

}

void Calculate_Speed(void)
{
//	est_speed.est_speed_mut += (	((est_speed.real_location - est_speed.real_location_last) * P_control1.fs_2)// 1/0.8ms
//								+ ((int32_t)(est_speed.est_speed  << 5) - (int32_t)(est_speed.est_speed)));
//	est_speed.est_speed      = (est_speed.est_speed_mut >> 5);  // pulse/s,1r=4000pulse
//	est_speed.est_speed_mut  = ((est_speed.est_speed_mut) - ((est_speed.est_speed << 5)));	//(ȡ��)(��0ȡ��)(��������λ)
//	est_speed.speed=(float)(est_speed.est_speed+1)/4000;   // r/s
    est_speed.est_speed=(est_speed.real_location - est_speed.real_location_last) * P_control1.fs_2;
    est_speed.speed=(float)(est_speed.est_speed+1)/4000.0f;   //1r/s
    est_speed.speed=P_control1.Ws*est_speed.speed+(1-P_control1.Ws)*est_speed.speed_l;
    est_speed.speed_l= est_speed.speed;
}


void Calculate_park(void)
{
		P_park.Angle=Encoder_abz.ElecAngle;//0~79,0~2pi
		if(P_park.Angle<40){		//0~pi
			if(P_park.Angle<20)		//0~pi/2
			{
				P_park.Sine=sin_pi[(P_park.Angle)* 25];	// 500/20=25
				P_park.Cosine=sin_pi[(20-P_park.Angle)*25];
			}
			else		//pi/2~pi
			{
				P_park.Sine=sin_pi[(40-P_park.Angle)* 25];
				P_park.Cosine=-sin_pi[(P_park.Angle-20)*25];
			}
		}
		else {			//pi~2pi
			if(P_park.Angle<60)		//pi~3pi/2
			{
				P_park.Sine=-sin_pi[(P_park.Angle-40)* 25];
				P_park.Cosine=-sin_pi[(60-P_park.Angle)*25];
			}
			else		//3pi/2~2pi
			{
				P_park.Sine=-sin_pi[(80-P_park.Angle)* 25];
				P_park.Cosine=sin_pi[(P_park.Angle-60)*25];
			}
		}
		PARK_Cale(&P_park);
}


void Calculate_Invpark(void)
{
	P_Invpark.Angle=P_park.Angle;
	P_Invpark.Sine=P_park.Sine;
	P_Invpark.Cosine=P_park.Cosine;
//	Invpark_typedef *ipark;
//	ipark=&P_Invpark;
	IPARK_Cale(&P_Invpark);
}


/*****************************SensorlessControl_ab******************/
void current_loop(void)
{
    float power_a=vary.ua_out*vary.ia;
    float power_b=vary.ub_out*vary.ib;
    _abs(power_a);
    _abs(power_b);

    vary.power=power_a+power_b;
    vary.power=0.05f*vary.power+0.95f*vary.power_l;
    vary.power_l=vary.power;
    
    vary.d_psi_a=vary.ua_out-vary.ia*P_motor1.Ra;
    vary.d_psi_b=vary.ub_out-vary.ib*P_motor1.Rb;
     // ������/theta_e
    vary.psi_a=vary.psi_a_l+(vary.d_psi_a+vary.d_psi_a_l)/((float)P_control1.fs_1*2);
    vary.psi_b=vary.psi_b_l+(vary.d_psi_b+vary.d_psi_b_l)/((float)P_control1.fs_1*2);
    vary.d_psi_a_l=vary.d_psi_a;
    vary.d_psi_b_l=vary.d_psi_b;

    vary.psi_s=vary.psi_a*vary.psi_a+vary.psi_b*vary.psi_b;
    if (vary.psi_s<0.00001f)
    {
        vary.ia_d=0;
        vary.ib_d=0;
    } else
    {
        tau_s=vary.tau_d/vary.psi_s/(float)P_motor1.Nr;
        vary.ia_d=-vary.psi_b*tau_s;//psi��׼ֵ��iadҲ�Ǳ�׼��λ������λ���㴦��
        vary.ib_d=vary.psi_a*tau_s;
        _constrain(vary.ia_d, -1.5f, 1.5f);//������1.5A
        _constrain(vary.ib_d, -1.5f, 1.5f);
    }

    //����PID
    vary.ia_e=vary.ia_d-vary.ia;
    vary.ia_oi=vary.ia_oi_l + (vary.ia_e +vary.ia_e_l)/(2*P_control1.fs_1);
    vary.ia_oi_l= vary.ia_oi;

    vary.ib_e=vary.ib_d-vary.ib;
    vary.ib_oi=vary.ib_oi_l + (vary.ib_e +vary.ib_e_l)/(2*P_control1.fs_1);
    vary.ib_oi_l= vary.ib_oi;
    
//        vary.ia_od=(vary.ia_e - vary.ia_e_l)*P_control1.fs_1;
//        vary.ib_od=(vary.ib_e - vary.ib_e_l)*P_control1.fs_1;

    vary.ib_e_l=vary.ib_e;
    vary.ia_e_l=vary.ia_e;
/******************************k=0.1**************************/
    vary.ua_out=vary.ia_d*P_motor1.Ra+P_control1.k3 * vary.ia_oi+dpsi_park.d_psi_a;//Ŀ���ѹ
    vary.ub_out=vary.ib_d*P_motor1.Rb+P_control1.k3 * vary.ib_oi+dpsi_park.d_psi_b;//Ŀ���ѹ

    _constrain(vary.ua_out,-vary.vbus+0.5f,vary.vbus-0.5f);
    _constrain(vary.ub_out,-vary.vbus+0.5f,vary.vbus-0.5f);

}


void resistance_test(void)
{
    uint16_t i=0;
    float sum[4]={0,0,0,0};
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET);//led2��
    //B��������
	Out_AM_CLOSE();
    Out_PWM_BP(336-1);//ͨ0.2����ѹ
    HAL_Delay(3000);
    for(i=0;i<8;i++)
    {
//        HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&ADC_ConvertedValue,ADC_CHANNEL_NUMBER);
//        HAL_Delay(10);//��MDA����ʱ��
//        vary.ib=(float)((int32_t)ADC_ConvertedValueLocal[1]-ADC_offset[1])*17.8378f/4096;
//        vary.vbus=24.0f;  //ĸ�ߵ�ѹ,ĸ�ߵ�ѹ�ɼ�������Ӳ����·����

        sum[1]=sum[1]+vary.vbus*0.2f/vary.ib;
        sum[3]=sum[3]+vary.ib;
         HAL_Delay(200);
    }
    Out_BM_CLOSE();
    HAL_Delay(500);
    //A��������
	Out_PWM_AP(336-1);//ͨ0.1��ѹ
//	Out_BM_CLOSE();
    HAL_Delay(3000);
    for(i=0;i<8;i++)
    {
//        HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&ADC_ConvertedValue,ADC_CHANNEL_NUMBER);
//        HAL_Delay(10);//��MDA����ʱ��
//        vary.ia=(float)((int32_t)ADC_ConvertedValueLocal[0]-ADC_offset[0])*17.8378f/4096;
//        vary.vbus=24.0f;  //ĸ�ߵ�ѹ,ĸ�ߵ�ѹ�ɼ�������Ӳ����·����

        sum[0]=sum[0]+vary.vbus*0.2f/vary.ia;
        sum[2]=sum[2]+vary.ia;
        HAL_Delay(200);
    }
    Out_AM_CLOSE();

    P_motor1.Ra=sum[0]/8;
    P_motor1.Rb=sum[1]/8;
    sum[3]=sum[3]/8;
    sum[2]=sum[2]/8;
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);//led2��
    float buffer[12]={P_motor1.Ra,P_motor1.Rb,sum[2],sum[3]};//���浥���ȸ������ݣ�Ҫ�ȴ�������ݸ�����1�����ں����֡β
    Serial_DMA_Float(buffer,4);
    HAL_Delay(200);
//    printf( "%f,%f,%f,%f\n",P_motor1.Ra,P_motor1.Rb,sum[2],sum[3]);
  }

