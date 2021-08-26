#ifndef INST_REG_H
#define INST_REG_H
#include "systemc.h"
SC_MODULE(IR)
{
	sc_in<sc_bv<24> > irin;
	sc_out<sc_bv<24> > irout;
	
	void ir_thread(void);
	
	SC_CTOR(IR)
	{	
		SC_THREAD(ir_thread);
		sensitive<<irin;
	}

};
#endif
