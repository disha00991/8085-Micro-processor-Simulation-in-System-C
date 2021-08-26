#ifndef ram_H_INCLUDED
#define ram_H_INCLUDED

#include "mips.h"

SC_MODULE(ram) {
	sc_in< sc_bv<16> > address;
	sc_out< sc_bv<16> > d_read;
	sc_in< sc_bv<16> > d_write;
	sc_in< sc_bv<0x1> > w;
	sc_in< sc_bv<0x1> > r;
	sc_in< bool > clk;

	sc_bv<8>* ramfile;

	void ram_thread(void);
	void ram_init(const char *filename);
	void ram_dump(const char *filename);

	SC_CTOR(ram) {
		SC_THREAD(ram_thread);
		sensitive << clk;
		sensitive << address;
		sensitive << d_write;
		sensitive << w;
		sensitive << r;

		ramfile = new sc_bv<8> [ramSIZE];

	};
};

#endif
