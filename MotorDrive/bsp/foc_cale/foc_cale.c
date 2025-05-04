#include "foc_cale.h"
#include "foc_math\foc_math.h"

park_typedef P_park={0,0,0,0,0,0,0};
Invpark_typedef P_Invpark={1,1,1,1,1,1,1};

park_typedef_f current_park={0,0,0,0,0,0};
park_typedef_f dpsi_park={0,0,0,0,0,0};
park_typedef_f U_park={0,0,0,0,0,0};
Invpark_typedef_f U_Invpark={1,1,1,1,1,1};
Invpark_typedef_f I_Invpark={1,1,1,1,1,1};

// Parking Id,Iq
// Id = Ialpha*cos+Ibeta*sin
// Iq = Ibeta*cos-Ialpha*sin
void  PARK_Cale(park_typedef *p)
{
	p->I_Ds = (p->I_Alpha * p->Cosine + p->I_Beta * p->Sine)>>sin_pi_d2_dpiybit;
  p->I_Qs = (p->I_Beta * p->Cosine - p->I_Alpha * p->Sine)>>sin_pi_d2_dpiybit;
}

//IParking Ia,Ib
// Ialpha = Id*cos-Iq*sin
// Ibeta = Iq*cos+Id*sin
void  IPARK_Cale(Invpark_typedef *p)    
{
	p->U_Alpha=(p->U_Ds * p->Cosine - p->U_Qs * p->Sine)>>sin_pi_d2_dpiybit;
	p->U_Beta =(p->U_Qs * p->Cosine + p->U_Ds * p->Sine)>>sin_pi_d2_dpiybit;
}


//¸¡µãÐÍpark/ipark

void  PARK_Cale_f(park_typedef_f *p)
{
	p->Ds = (p->Alpha * p->Cosine + p->Beta * p->Sine);
  p->Qs = (p->Beta * p->Cosine - p->Alpha * p->Sine);
}

void  IPARK_Cale_f(Invpark_typedef_f *p)    
{
	p->U_Alpha=(p->U_Ds * p->Cosine - p->U_Qs * p->Sine);
	p->U_Beta =(p->U_Qs * p->Cosine + p->U_Ds * p->Sine);
}

