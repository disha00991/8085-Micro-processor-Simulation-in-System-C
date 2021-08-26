#ifndef PROGRAMCOUNTER_INC
#define PROGRAMCOUNTER_INC
#include "systemc.h"
SC_MODULE(pcw)
{
    sc_in<sc_int<16> > P;
    sc_out<sc_int<16> > P1;
    sc_in<char> ctrl1;
    //sc_in<bool> clk;
    void pcw_thread(void);
    
    SC_CTOR(pcw)
    {
        SC_THREAD(pcw_thread);
        sensitive<<P;
        sensitive<<ctrl1;
        //sensitive<<clk.pos();
    }
};
#endif
