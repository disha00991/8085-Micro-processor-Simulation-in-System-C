#ifndef MEM_DATA_REG_H
#define MEM_DATA_REG_H
#include "systemc.h"
SC_MODULE(MDR)
{
	sc_in<sc_bv<24> > mdrin;
	sc_out<sc_bv<24> > mdrout;
	
	void mdr_thread(void);
	
	SC_CTOR(MDR)
	{	
		SC_THREAD(mdr_thread);
		sensitive<<mdrin;
	}

};
#endif
