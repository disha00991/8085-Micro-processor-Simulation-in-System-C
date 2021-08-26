#ifndef DATABUS_H
#define DATABUS_H
#include "systemc.h"
SC_MODULE(IDB)
{
	sc_inout<sc_bv<8> > acc_inout;
	sc_out<sc_bv<8> > temp_out;
	sc_in<sc_bv<8> > alu_in;
	sc_out<sc_bv<24> > ir_out;
	sc_inout<sc_bv<8> > reg_inout;
	sc_in<sc_bv<8> > databuff;
	sc_in<sc_bv<1> >s0,s1;
	sc_in<sc_bv<24> >mdr_in;
	
	void idb_thread(void);
	
	SC_CTOR(IDB)
	{
		SC_THREAD(idb_thread);
		sensitive<<acc_inout<<alu_in<<reg_inout<<databuff<<s0<<s1;
	}
};
#endif
