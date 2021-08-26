#include "MDR.h"
void MDR :: mdr_thread(void)
{ 
	sc_int<24> inst;
	
	while(true)
	{
		inst=mdrin.read();	
		mdrout.write(inst);
		wait();
	}
}
