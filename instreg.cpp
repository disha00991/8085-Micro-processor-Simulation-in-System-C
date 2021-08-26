#include "instreg.h"
void IR :: ir_thread(void)
{ 
	sc_uint<24> instir;
	
	while(true)
	{
		instir=irin.read();	
		irout.write(instir);
		wait();
	}
}
