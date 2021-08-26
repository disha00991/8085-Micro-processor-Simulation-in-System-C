#ifndef FLAGREG_H
#define FLAGREG_H
#include "systemc.h"
SC_MODULE(FLAGREG)
{
	sc_in<sc_bv<1> >flag[8];
	sc_in<sc_bv<1> >ctrlsig;
	
	unsigned int i;
	void flag_method(void);
	
	SC_CTOR(FLAGREG)
	{
	SC_METHOD(flag_method);
	sensitive<<flag[0]<<flag[1]<<flag[2]<<flag[3]<<flag[4]<<flag[5]<<flag[6]<<flag[7];
	}
};
#endif
