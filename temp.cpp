#include "temp.h"
void TEMP_REG :: temp_thread(void)
{
	sc_int<8> temp_data;
	sc_int<1> tempsignal;
	while(true)
	{
		tempsignal=temp_sig.read();
		if(tempsignal==1)
		alu_in.write(tempsignal);
		else
		wait();
	}
}
