#include "ctrlunit.h"
void CTRL_UNIT :: ctrl_thread(void)
{
	sc_uint<5> alu_op;
	sc_uint<3> msb,lsb;
	sc_uint<4> state;

	while (true) {
		// Read the input
		alu_op = c5bits.read();
		msb=c3bit_1.read();
		lsb=c3bit_2.read();
		state = State.read();

		// Determine output
		switch (state) {
			case 0:						// 4-T States for fetch
			case 1:
			case 2:
			case 3:
			s0.write(1);
			s1.write(1);
			rd.write(0);
			wr.write(1);
			alusig.write(0);
			accsig.write(0);
			tempsig.write(0);
			flagsig.write(0);
			irsig.write(1);
			regsig.write(0);
			inspsig.write(1);
			NextState.write(0x1);
			break;

			case 4:						// 3-T States for read
			case 5:
			case 6:
			s0.write(0);
			s1.write(1);
			rd.write(1);
			wr.write(0);
			if(alu_op==16)
			alusig.write(0);
			else if(alu_op==18)
			alusig.write(1);
			if(lsb==7)
			accsig.write(1);
			if(msb==0)
			tempsig.write(1);
			flagsig.write(1);
			irsig.write(0);
			regsig.write(1);
			inspsig.write(0);
			NextState.write(0x1);
			break;

			case 7:						// 3-T States for write
			case 8:
			case 9:
			s0.write(1);
			s1.write(0);
			rd.write(1);
			wr.write(0);
			alusig.write(0);
			accsig.write(0);
			tempsig.write(0);
			flagsig.write(0);
			irsig.write(0);
			regsig.write(1);
			inspsig.write(0);
			NextState.write(0x1);
			break;

			default:						//machine idle
			break;
		}

		// wait for new event
		wait(); 
	}
}
