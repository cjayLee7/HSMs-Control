#ifndef FOC_CALE_H
#define FOC_CALE_H

#include ".\loop\loop_port.h"
typedef struct {  
	        int32_t  I_Alpha;  	
		 		  int32_t  I_Beta;	 	
		 	 	  int32_t  Angle;		// Electric Angle:0~79 
		 	 	  int32_t  I_Ds;			
		 	 	  int32_t  I_Qs;			
		 	 	  int32_t  Sine;    //  0~4096, 0~1 
		 	 	  int32_t  Cosine;  // 0~4096,0~1
	   }park_typedef;

typedef struct {  
	        int32_t  U_Alpha;  
		 		  int32_t  U_Beta;	 	
		 	 	  int32_t  Angle;		// Electric Angle:0~79  
		 	 	  int32_t  U_Ds;			
		 	 	  int32_t  U_Qs;			
		 	 	  int32_t  Sine;    
		 	 	  int32_t  Cosine;  
	   }Invpark_typedef;

       
/***********Floating-point type definition**********/
typedef struct {  
                  float  Alpha;  	
		 		  float  Beta;	 	
		 	 	  float  Ds;			
		 	 	  float  Qs;			
		 	 	  float  Sine;    
		 	 	  float  Cosine;  
	   }park_typedef_f;

typedef struct {  
                  float  U_Alpha;  	
		 		  float  U_Beta;	 	
		 	 	  float  U_Ds;			
		 	 	  float  U_Qs;			
		 	 	  float  Sine;    
		 	 	  float  Cosine;  
	   }Invpark_typedef_f;

void  PARK_Cale(park_typedef *);
void  IPARK_Cale(Invpark_typedef *);
void  PARK_Cale_f(park_typedef_f *);
void  IPARK_Cale_f(Invpark_typedef_f *);
#endif
