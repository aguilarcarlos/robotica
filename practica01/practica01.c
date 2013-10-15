/// Librería del pic con .h
#include <16f877a.h>

/// Configuración del adc a resulción de 10bits         
#device adc=10  

/// Se configurar el valor del delay con el del clock
#use delay(clock=4000000)

/// Desactivación de fuses o activación 
#fuses XT,NOWDT,NOPROTECT,NOLVP,PUT

/// Se configuran los grupos de pines RA,RC para entrada/salida
#use fast_io(a)
#use fast_io(b)

/// Variable enteera para las lecturas
float data;

void main()
{
	/// Configura los puertos como entrada o salida
	set_tris_a(1);
	set_tris_b(0);
	
	/// Se configura el reloj interno que trabaja todo el tiempo
	setup_adc(ADC_CLOCK_INTERNAL);

	/// Se configuran los pines con AN# para entradas anaogas
	setup_adc_ports(ALL_ANALOG);

	/// Se configura el canal de entrada AN0
	// set_adc_channel(1);

	do{
		/// Se configura el canal de entrada AN0
		set_adc_channel(0);

		///Retardo de 10 milisegundos
		delay_ms(10);

		/// int read se llena con lo que lee en el adc
		data = read_adc();
		
		///Retardo
		delay_ms(10);
		
		/// Condicional para activar los LED's
		if(data > 300)
		{
			output_high(PIN_B1);
		}
		else
		{
			output_low(PIN_B1);
		}
		
		/// Configuración del el canal de entrada AN1
		set_adc_channel(1);
		
		delay_ms(10);
		
		data = read_adc();
		
		delay_ms(10);
		
		/// Condicional para activar los LED's
		if(data > 300)
		{
			output_high(PIN_B2);
		}
		else
		{
			output_low(PIN_B2);
		}
		
		delay_ms(10);
			
	} while(true);
}