#include "register.h"
//template <int 32>
void REGISTER :: reg_thread(void)
{
	sc_uint<8> data;
	data=indata.read();
	if(ctrlsig.read()==1)
	outdata.write(data);

}
/*
void dummy_register (void)
{
	REGISTER<32> TempRegister32("Temp32");
	REGISTER<4> TempRegister4("Temp4");
}*/
