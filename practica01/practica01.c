/// Librería del pic
#include <16F887> 

/// Configuración del adc a resulción de 10bits         
#device adc=10  

/// Se configurar el valor del delay con el del clock
#use delay(clock=4000000)

/// 
#fuses XT,NOWDT,NOPROTECT,NOLVP,PUT
#include <MATH.H>

/// Se configuran los grupos de pines RA,RC para entrada/salida
#use standard_io(a)
#use standard_io(c)

/// Variable enteera para las lecturas
int read;

void main()
{
	/// Se configura el reloj interno que trabaja todo el tiempo
	setup_adc(ADC_CLOCK_INTERNAL);

	/// Se configuran los pines con AN# para entradas anaogas
	setup_adc_ports(ALL_ANALOG);

	/// Se especifica el canal de entrada AN0
	setup_adc_channel(0);

	do
	{
		set_adc_channel(0);
		delay_ms(10);
		read = read_adc();
		delay_ms(10);
		
		if(read > 40)
		{
			output_high(PIC_C0);
		}
		else
		{
			output_low(PIC_C0);
		}

		set_adc_channel(1);
		delay_ms(10);
		read = read_adc();
		delay_ms(10);
		
		if(read > 40)
		{
			output_high(PIC_C1);
		}
		else
		{
			output_low(PIC_C1);
		}
		
		set_adc_channel(0)
		delay_ms(10)	
	}
	while (true)

}