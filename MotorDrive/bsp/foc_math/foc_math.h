#ifndef FOC_MATH_H
#define FOC_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


#define sin_pi_d2_dpix			500	
#define sin_pi_d2_dpiybit		12		
extern const int16_t sin_pi[sin_pi_d2_dpix+1 ];

float SquareRootFloat(float);
	
	
	
	
#ifdef __cplusplus
}
#endif

#endif
