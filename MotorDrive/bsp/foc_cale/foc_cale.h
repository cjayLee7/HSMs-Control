#ifndef FOC_CALE_H
#define FOC_CALE_H

#include ".\loop\loop_port.h"
typedef struct {  
	        int32_t  I_Alpha;  	//  二相静止坐标系 Alpha 轴电流
		 		  int32_t  I_Beta;	 	//  二相静止坐标系 Beta 轴电流
		 	 	  int32_t  Angle;		//  电角度0---79即是0---180度 
		 	 	  int32_t  I_Ds;			//  电机二相旋转坐标系下的d轴电流
		 	 	  int32_t  I_Qs;			//  电机二相旋转坐标系下的q轴电流
		 	 	  int32_t  Sine;    //  正弦参数，0---4096  0到1 
		 	 	  int32_t  Cosine;  //  余弦参数，0---4096  0到1
	   }park_typedef;

typedef struct {  
	        int32_t  U_Alpha;  	//  二相静止坐标系 Alpha 轴电压
		 		  int32_t  U_Beta;	 	//  二相静止坐标系 Beta 轴电压
		 	 	  int32_t  Angle;		//  电角度0---79即是0---180度 
		 	 	  int32_t  U_Ds;			//  电机二相旋转坐标系下的d轴电压
		 	 	  int32_t  U_Qs;			//  电机二相旋转坐标系下的q轴电压
		 	 	  int32_t  Sine;    //  正弦参数，0---4096  0到1 
		 	 	  int32_t  Cosine;  //  余弦参数，0---4096  0到1
	   }Invpark_typedef;

       
/***********浮点型定义**********/
typedef struct {  
                  float  Alpha;  	//  二相静止坐标系 Alpha 轴电流
		 		  float  Beta;	 	//  二相静止坐标系 Beta 轴电流
		 	 	  float  Ds;			//  电机二相旋转坐标系下的d轴电流
		 	 	  float  Qs;			//  电机二相旋转坐标系下的q轴电流
		 	 	  float  Sine;    //  正弦参数 
		 	 	  float  Cosine;  //  余弦参数
	   }park_typedef_f;

typedef struct {  
                  float  U_Alpha;  	//  二相静止坐标系 Alpha 轴电压
		 		  float  U_Beta;	 	//  二相静止坐标系 Beta 轴电压
		 	 	  float  U_Ds;			//  电机二相旋转坐标系下的d轴电压
		 	 	  float  U_Qs;			//  电机二相旋转坐标系下的q轴电压
		 	 	  float  Sine;    //  正弦参数
		 	 	  float  Cosine;  //  余弦参数
	   }Invpark_typedef_f;

void  PARK_Cale(park_typedef *);
void  IPARK_Cale(Invpark_typedef *);
void  PARK_Cale_f(park_typedef_f *);
void  IPARK_Cale_f(Invpark_typedef_f *);
#endif
