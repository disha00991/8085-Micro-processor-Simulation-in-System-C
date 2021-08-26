#include "accumulator.h"
void ACCUMULATOR::acc_thread(void){
	sc_uint<8> acc_data;
while (true)
{
	wait();
	if(ctrl_sig.read()==1)
		{
		 acc_data=data_bus.read();
		 value_to_alu.write(acc_data);
	 	}
	 else
	      data_bus.write(acc_data);	
 	}	 	
}
