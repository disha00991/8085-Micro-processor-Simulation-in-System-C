#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H
#include "systemc.h"
SC_MODULE(ACCUMULATOR){

	sc_inout<sc_bv<8> >data_bus;
	sc_in<sc_bv<1> >ctrl_sig;
	sc_out<sc_bv<8> >value_to_alu;
	
	void acc_thread(void);
	
	SC_CTOR(ACCUMULATOR){
		SC_THREAD(acc_thread);
		sensitive<<data_bus<<ctrl_sig;
	}
};
#endif
