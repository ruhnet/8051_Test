#define delay_ms(x)  __mydelay_loop_((long) x*80)
//79.681 would be correct
#define delay_us(x)  __mydelay_loop_((long) x)  
//actually 12.55uS Temic 80c31 11.0592MHz

//extern void __delay_loop_(signed long);
void __mydelay_loop_(signed long);

void __mydelay_loop_(signed long val)
{
	    for(;val;val--);
}



