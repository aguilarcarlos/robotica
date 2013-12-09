#include <16F877a.H>
#device ADC=10
#include <stdlib.h>
#fuses XT, NOWDT, NOPROTECT, BROWNOUT, PUT, NOLVP
#use delay(clock=4000000)
#include <LCD.c>
#byte port_b=0x06

void main()
{

  float senir,senir2;
  setup_adc(ADC_CLOCK_INTERNAL);
  setup_adc_ports(ALL_ANALOG);
  lcd_init();

  output_high(pin_b0);
  output_low(pin_b1);

  set_tris_b(0x00);

  setup_ccp1(ccp_PWM);
  setup_ccp2(ccp_PWM);
  setup_timer_2(t2_div_By_1,249,1);

  output_high(pin_b2);
  output_low(pin_b3);
  set_pwm1_duty(900);
  set_pwm2_duty(600);

  while (true)
  {
    set_adc_channel(0);
    delay_ms(30);
    senir=read_adc();
    senir*=(float).004882;

    set_adc_channel(1);
    delay_ms(30);
   
    senir2 = read_adc();
    senir2 *= (float).004882;
   
    lcd_gotoxy(1,1);
    printf(lcd_putc,"%f",senir);
    lcd_gotoxy(1,2);
    printf(lcd_putc,"%f",senir2);

    if (senir2>=(3.1) && senir>(3.1))
    {
      output_low(pin_b2);
      output_low(pin_b4);
    }
    else
    {

      if (senir>=(3.1))
      {
        output_high(pin_b2);
        output_low(pin_b3);
      }
      else
      {
        output_low(pin_b2);
      }

      if (senir2>=(3.1))
      {
        output_low(pin_b2);
        output_high(pin_b4);
      }
      else
      {
        output_low(pin_b4);
      }
    }
  }
}
