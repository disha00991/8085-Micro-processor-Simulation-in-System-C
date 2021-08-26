#ifndef TEMP_REG_H
#define TEMP_REG_H
#include "systemc.h"
SC_MODULE(TEMP_REG)
{
	sc_in<sc_bv<8> > idb_out;
	sc_in<sc_bv<1> > temp_sig;
	sc_out<sc_bv<8> > alu_in;
	
	void temp_thread(void);
	
	SC_CTOR(TEMP_REG)
	{	
		SC_THREAD(temp_thread);
		sensitive<<idb_out<<temp_sig;
	}
};
#endif
