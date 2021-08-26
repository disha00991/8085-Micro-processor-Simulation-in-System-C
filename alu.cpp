#include "alu.h"
void ALU :: alu_thread(void)
{
	
	while(true)
	{
		control=ctrl_in.read();
		A=acc_in.read();
		B=temp_in.read();
		a2=A.range(7,4);
		a1=A.range(3,0);
		b2=B.range(7,4);
		b1=B.range(3,0);
		switch(control)
		{
			case 0:
				add();
				s=1;		
				break;
			case 1:
				sub();
				if(A<B)		//sign flag
				s=1;
				else
				s=0;
				break;
		}
		
		res.range(3,0)=res1%16;
		res.range(7,4)=res2%16;
		
		for(i=0;i<8;i++)			//parity flag
			if(res.range(i,i)==1)
			  count_parity++; 
			  
		if(count_parity%2==0)
			p=1;
		else
			p=0;
			
		if(res==0)				//zero flag
			z=1;
		else
			z=0;
		
		carry.write(c);			//sending values to flag register
		aux_carry.write(ac);
		parity.write(p);
		zero.write(z);
		sign.write(s);
		
		result.write(res);				  
		wait();
	}
}

void ALU ::add(void)
{
	res1=a1+b1;
	ac=res1/16;				
	res2=a2+b2+ac;
	c=res2/16;
}

void ALU ::sub(void)
{
	if(a1>b1)
	{
	 	res1=a1-b1;
	 	ac=0;
	}
	else
	 {
	  	res1=a1+16-b1;
	  	ac=1;
	 } 
	 
	if(a2>b2)
	{
	 	res2=a2-ac-b2;
	 	c=0;
	}
	else
	{
	 	res2=a2+16-ac-b2;
	 	c=1;
	} 
}












