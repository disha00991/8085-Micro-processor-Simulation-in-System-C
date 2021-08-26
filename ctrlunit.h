#ifndef CONTROL_H
#define CONTROL_H
#include "systemc.h"
SC_MODULE(CTRL_UNIT)
{
	sc_in<sc_bv<8> > cbyte1,cbyte2,cbyte3;
	sc_in< sc_bv<4> > State;	// Present State
	sc_in<sc_bv<2> > c2bits;
	sc_in<sc_bv<3> > c3bit_1,c3bit_2;
	sc_in<sc_bv<5> > c5bits;
	sc_out<sc_bv<1> > alusig,accsig,tempsig,s0,s1,rd,wr,flagsig,irsig,regsig,inspsig;
	sc_out< sc_bv<4> > NextState;	// Next State
	
	void ctrl_thread(void);
	
	SC_CTOR(CTRL_UNIT)
	{
		SC_THREAD(ctrl_thread);
		REGISTER<4> stateregister("StateRegister");
		CTRLLOGIC ctrllogic("CtrlLogic");

		// Signals
		sc_signal< sc_bv<4> > bus_next_state;
		sc_signal< sc_bv<4> > bus_present_state;

		// Connections
		stateregister.in(bus_next_state);
		stateregister.out(bus_present_state);
		//stateregister.w((sc_bv<1>)clk);
		stateregister.clk(clk);
		sensitive<<cbyte1<<c2bits<<State<<NextState;
	}
};
#endif
