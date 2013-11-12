#include <16f877a.h>
#fuses XT,NOWDT, PUT, NOWRT
#use delay(clock=4000000)
#include <lcd.c>
#include <STDIO.H>
int32 pulsos;
float distancia;

#use fast_io(B)
#INT_EXT

//Interrupción externa        
ext_isr()
{
	if ((input(PIN_B0)==1)&(input(PIN_B1)==0))
    {
    	pulsos = pulsos+1;	
    }
    
    if ((input(PIN_B0)==1)&(input(PIN_B1)==1))
    {
    	pulsos = pulsos-1;
    }
    
	distancia = pulsos * 0.65;
	
    lcd_gotoxy(1,1);
    printf(lcd_putc,"Pulsos=%Ld \n",pulsos); 
    printf(lcd_putc,"Dist=%Lf cm",distancia);
}
    
void main() {
   //Inicializo la variable pulsos en el codigo principal
   pulsos = 0;
   
   // Activar puerto B como entrada
   set_tris_B(0x01); 
   
   port_b_pullups(TRUE);
   enable_interrupts(int_ext);
   ext_int_edge(L_to_H);
   enable_interrupts(GLOBAL);
   lcd_init(); //Esta es la primera instrucción para inicializar el lcd
   
   while(TRUE) 
   {
	   
   }
}
    
         
