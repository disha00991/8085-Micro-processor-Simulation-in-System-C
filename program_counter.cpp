#include "program_counter.h"
void pcw::pcw_thread(void)
{
    sc_int<16> p;
    
    char x;
    
    while(true)
    {
        p=P.read();
        x=ctrl1.read();
        if(x=='m')// move instruction mov a,b one byte instruction
        {
            p=p+1;
        }
        else if(x=='a') //add instuction 1 byte instruction
        {
            p=p+1;
        }
        else if(x=='s') // subtract instruction 1 byte instruction
        {
            p=p+1;
        }
        else if(x=='b') //branch instruction  3 byte instruction
        {
            p=p+3;
        }
        else if(x=='o')// or instruction
        {
            p=p+1;
        }
        else if(x=='d')//and
        {
            p=p+1;
        }
        else if(x=='i')//increment instruction
        {
            p=p+1;
        }
        else if(x=='z')//decrement instruction
        {
            p=p+1;
        }
        P1.write(p);
        wait();    
    }
}
