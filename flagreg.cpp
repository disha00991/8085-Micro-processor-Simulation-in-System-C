#include "flagreg.h"
void FLAGREG::flag_method(void){
	sc_uint<1>flag_var[8];
	
	for(i=0;i<8;i++)
	{
	if(i!=2 && i!=4 && i!=6)
	{
	  if((flag[i].read())==1)
	    flag_var[i]=1;
	  else
	    flag_var[i]=0;  
	 }   
	}
	flag_var[2]=0;
	flag_var[4]=0;
	flag_var[6]=0;
}
