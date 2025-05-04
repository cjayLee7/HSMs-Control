#ifndef FOC_CALE_H
#define FOC_CALE_H

#include ".\loop\loop_port.h"
typedef struct {  
	        int32_t  I_Alpha;  	//  ���ྲֹ����ϵ Alpha �����
		 		  int32_t  I_Beta;	 	//  ���ྲֹ����ϵ Beta �����
		 	 	  int32_t  Angle;		//  ��Ƕ�0---79����0---180�� 
		 	 	  int32_t  I_Ds;			//  ���������ת����ϵ�µ�d�����
		 	 	  int32_t  I_Qs;			//  ���������ת����ϵ�µ�q�����
		 	 	  int32_t  Sine;    //  ���Ҳ�����0---4096  0��1 
		 	 	  int32_t  Cosine;  //  ���Ҳ�����0---4096  0��1
	   }park_typedef;

typedef struct {  
	        int32_t  U_Alpha;  	//  ���ྲֹ����ϵ Alpha ���ѹ
		 		  int32_t  U_Beta;	 	//  ���ྲֹ����ϵ Beta ���ѹ
		 	 	  int32_t  Angle;		//  ��Ƕ�0---79����0---180�� 
		 	 	  int32_t  U_Ds;			//  ���������ת����ϵ�µ�d���ѹ
		 	 	  int32_t  U_Qs;			//  ���������ת����ϵ�µ�q���ѹ
		 	 	  int32_t  Sine;    //  ���Ҳ�����0---4096  0��1 
		 	 	  int32_t  Cosine;  //  ���Ҳ�����0---4096  0��1
	   }Invpark_typedef;

       
/***********�����Ͷ���**********/
typedef struct {  
                  float  Alpha;  	//  ���ྲֹ����ϵ Alpha �����
		 		  float  Beta;	 	//  ���ྲֹ����ϵ Beta �����
		 	 	  float  Ds;			//  ���������ת����ϵ�µ�d�����
		 	 	  float  Qs;			//  ���������ת����ϵ�µ�q�����
		 	 	  float  Sine;    //  ���Ҳ��� 
		 	 	  float  Cosine;  //  ���Ҳ���
	   }park_typedef_f;

typedef struct {  
                  float  U_Alpha;  	//  ���ྲֹ����ϵ Alpha ���ѹ
		 		  float  U_Beta;	 	//  ���ྲֹ����ϵ Beta ���ѹ
		 	 	  float  U_Ds;			//  ���������ת����ϵ�µ�d���ѹ
		 	 	  float  U_Qs;			//  ���������ת����ϵ�µ�q���ѹ
		 	 	  float  Sine;    //  ���Ҳ���
		 	 	  float  Cosine;  //  ���Ҳ���
	   }Invpark_typedef_f;

void  PARK_Cale(park_typedef *);
void  IPARK_Cale(Invpark_typedef *);
void  PARK_Cale_f(park_typedef_f *);
void  IPARK_Cale_f(Invpark_typedef_f *);
#endif
