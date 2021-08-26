#ifndef INTERSPLITTER_H
#define INTERSPLITTER_H
#include "systemc.h"
SC_MODULE(INTERSPLITTER)
{
	sc_in<sc_bv<24> > inst_in;
	sc_out<sc_bv<8> > byte1,byte2,byte3;		//for  3 byte instruction
	sc_out<sc_bv<2> > 2bits;				//for 1 byte instruction
	sc_out<sc_bv<3> > 3bit_1,3bit_2;
	sc_out<sc_bv<5> > 5bits;
	
	void intersplitter_thread(void);
	
	SC_CTOR(INTERSPLITTER){
			SC_THREAD(intersplitter_thread);
			sensitive<<inst_in;
	
	}
};
#endif
