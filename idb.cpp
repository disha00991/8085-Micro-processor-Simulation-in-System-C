#include "idb.h"
void IDB :: idb_thread(void)
{
	while(true)
	 {
	 	wait();
	 	if(s0.read()==1 && s1.read()==1)		//fetch
	 	 ir_out.write(mdr_in.read());
	 	else if(s0.read()==1 && s1.read()==0)	//read
	 	 temp_out.write(reg_inout.read());
	 	else if(s0.read()==0 && s1.read()==1)	//write
	 	 {
	 	 	reg_inout.write(alu_in.read());
	 	 }	
	 	else if(s0.read()==0 && s1.read()==0)	//halt
	 	 wait();
	 }
}
