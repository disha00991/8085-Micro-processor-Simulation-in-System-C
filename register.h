#ifndef REG_H
#define REG_H
#include "systemc.h"
SC_MODULE(REGISTER)
{
	sc_in<sc_bv<8> > indata;       //data input
	sc_in<sc_bv<1> > ctrlsig;	//write control signal
	sc_out<sc_bv<8> > outdata;	//data output
	sc_in<bool> clk;	
	
	void reg_thread(void);
	
	SC_CTOR(REGISTER)
	{
		SC_THREAD(reg_thread);
		sensitive<<clk.pos();
	}

};
#endif
