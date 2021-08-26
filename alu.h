#ifndef ALU_H
#define ALU_H
#include "systemc.h"
SC_MODULE(ALU)
{
	sc_in<sc_bv<8> > acc_in,temp_in;
	sc_in<sc_bv<1> > ctrl_in;
	sc_out<sc_bv<1> > carry,parity,aux_carry,zero,sign;
	sc_out<sc_bv<8> > result;
	
	unsigned int i,count_parity;
	void alu_thread(void);
	void add(void);
	void sub(void);
	
	sc_uint<8> A,B;
	sc_int<8> res;
	sc_uint<5> res1,res2;
	sc_uint<1> control;
	sc_uint<1> c,ac,p,z,s;
	sc_uint<4> a2,a1,b2,b1;
	
	SC_CTOR(ALU)
	{
		count_parity=0;
		SC_THREAD(alu_thread);
		sensitive<<acc_in<<temp_in<<ctrl_in;
	}
};
#endif
