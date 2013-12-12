#include <16F877A.h>
#device adc=10
#include <math.h>
#include <stdlib.h>
#use delay(clock=4000000)
#fuses XT,NOWDT,NOPROTECT,PUT,NOLVP,NOBROWNOUT
#use rs232(baud=9600, bits=8, parity=N, xmit=PIN_C6, rcv=PIN_C7)


#use standard_io(c)
#use standard_io(d)
#use standard_io(b)

float sensor1 = 0, sensor2 = 0, distance = 0, velocity = 0, measurement = 0;
int pulses = 0, timer0_interrupts = 0, beacons = 0;
int8 B=0x00;
char c;
#byte portB=0x06

#int_rda
void isr_rda()
{
  while(kbhit())
  {
     c=getc();
  }
  if (c=='d')
  {
    printf("%2.2f,%d,%2.2f",velocity,beacons,distance);
  }
}

#int_RB
void RB_isr(void) //función de interrupción 
{ 
  B=portB;
  if ((B & 0x10)== (0x10))
  {
	if (beacons == 4)
	{
	  beacons = 1;
	}
    else
	{
	  beacons++;
	}
    B=0x00;
  } 
} 

#INT_EXT
void isr_rb(void)
{ 
  pulses++;
} 

#INT_timer0
void timer0_isr()
{
  set_timer0(0x06);
  timer0_interrupts++;
  if(timer0_interrupts == 250)
  {
    timer0_interrupts=0;
    velocity = pulses*0.56;
    distance+=velocity;
	pulses=0;
  }
}

void adc_setup()
{
  setup_adc(ADC_CLOCK_INTERNAL);
  setup_adc_ports(ALL_ANALOG);
}

void external_interrupts_setup()
{
  enable_interrupts(INT_EXT);
}

void timer0_interrupts_setup()
{
  enable_interrupts(INT_timer0);
  setup_timer_0(RTCC_INTERNAL|RTCC_DIV_16);
}

int read_sensor(int channel)
{
  set_adc_channel(channel);  
  delay_ms(3);
  measurement = read_adc();
  return measurement;
}

void main()
{
  adc_setup();
  enable_interrupts(INT_RB);
  enable_interrupts(int_rda);
  external_interrupts_setup();
  timer0_interrupts_setup();
  enable_interrupts(GLOBAL);
  
  setup_CCP1(ccp_pwm);
  setup_timer_2(T2_DIV_BY_4, 249, 1);
  
  set_pwm1_duty(800);

  //printf("inicio");

  while(true)
  {    
    sensor1 = read_sensor(0);
    sensor2 = read_sensor(1);

    if ((sensor1>200)&&(sensor2>200))  
	{
	  output_low(PIN_B1);
	  output_low(PIN_B2);
	}
    else if ((sensor1<200)&&(sensor2>200))
	{
      output_high(PIN_B2);
      output_low(PIN_B1);
    }
    else if ((sensor1>200)&&(sensor2<200)) 
    {
      output_high(PIN_B1);
      output_low(PIN_B2);
    }
  }
}