#include <16f877a.h>
#fuses XT,NOWDT, PUT, NOWRT
#use delay(clock=4000000)
#include <lcd.c>
#include <STDIO.H>
int32 pulsos, velocidad,pulsos1;
float distancia;

#use fast_io(B)
#INT_EXT       
ext_isr()
{
	if ((input(PIN_B0)==1)&(input(PIN_B1)==0))
    {
    	pulsos = pulsos+1;
    	pulsos1 = pulsos1+1;	
    }
    
    if ((input(PIN_B0)==1)&(input(PIN_B1)==1))
    {
    	pulsos = pulsos-1;
    	pulsos1 = pulsos1+1;
    }
    
	distancia = pulsos * 0.65;	
}

int Contador = 250;

#INT_TIMER0
void interruption()
{
	set_timer0(6);
	Contador--;
	if(Contador == 0)
	{
		velocidad = pulsos1 * 0.65;
		lcd_gotoxy(1,1);
		printf(lcd_putc,"Pulsos=%Ld \n",pulsos); 
    	printf(lcd_putc,"V=%Ld cm/seg",velocidad);
		pulsos1 = 0;
		Contador = 250;
			
	}	
}
    
void main() {
   //Inicializo la variable pulsos en el codigo principal
   pulsos = 0;
   
   // Activar puerto B como entrada
   set_tris_B(0x01); 
   
   port_b_pullups(TRUE);
   enable_interrupts(int_ext);
   ext_int_edge(L_to_H);
   setup_counters(RTCC_INTERNAL,RTCC_DIV_16);
   set_timer0(6);
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   lcd_init(); //Esta es la primera instrucción para inicializar el lcd
   
   while(TRUE) 
   {
	   
   }
}
    
         
