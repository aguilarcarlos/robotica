#include <16f877a.h>
#fuses XT,NOWDT,NOPROTECT,PUT
#use delay(clock=4000000)
#use fast_io(a)

int Contador = 250;

#INT_TIMER0
void interruption()
{
	set_timer0(6);
	Contador--;
	if(Contador == 0)
	{
		output_toggle(PIN_A0);
		Contador = 250;	
	}	
}

void main()
{
	set_tris_a(0xFE);
	output_low(PIN_A0);
	setup_counters(RTCC_INTERNAL,RTCC_DIV_16);
	set_timer0(6);
	enable_interrupts(GLOBAL);
	enable_interrupts(INT_TIMER0);
	do
	{
		
	}while(TRUE);		
}	