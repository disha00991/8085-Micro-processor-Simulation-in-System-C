#include "Intersplitter.h"
void INTERSPLITTER::intersplitter_thread(void){
	sc_uint<24> instr;
	sc_uint<8> byt1,byt2,byt3;
	sc_uint<2> 2bit;
	sc_uint<3> 3bt_1,3bt_2;
	sc_uint<5> 5bit;
	
	instr=inst_in.read();
	byt1=instr.range(23,16);
	byt2=instr.range(15,8);
	byt3=instr.range(7,0);
	2bit=instr.range(7,6);
	3bt_1=instr.range(5,3);
	3bt_2=instr.range(2,0);
	5bit=instr.range(7,3);
	byte1.write(byt1);
	byte2.write(byt2);
	byte3.write(byt3);
	2bits.write(2bit);	
	3bit_1.write(3bt_1);
	3bit_2.write(3bt_2);
	5bits.write(5bit);
	
}
