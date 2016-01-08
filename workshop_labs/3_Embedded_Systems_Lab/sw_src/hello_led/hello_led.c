/*
 * hello_led.c
 * This program uses the system timer to strobe two leds back and forth
 *
 */

#include <stdio.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_alarm.h"



//GLOBAL variable
int alarm_rang=0;
static alt_u8 alarm_counter = 0;

alt_u32 my_alarm_callback (void* context)
{
	// set the alarm_rang flag every 1 second
	if((alarm_counter++)%1==0)
		alarm_rang=1;
	return alt_ticks_per_second(); // return value is the time when the next alarm will occur
}

alt_u32 led_strobe_callback (void* context)
{
	alarm_rang=1;
	return alt_ticks_per_second()/4; // return value is the time when the next alarm will occur (1/4 second)
}

int main()
{
  static alt_alarm alarm;

  alt_u8 led_strobe=0;
  alt_u8 LED_DIRECTION;



  printf("Hello from hello_led!\n");


  /*******************************************************
   * Strobe leds        							     *
   *******************************************************/

	  //IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE,0x00);

	  alt_alarm_start (&alarm,  alt_ticks_per_second(),  led_strobe_callback, NULL);

	  led_strobe=0xFF;
	  LED_DIRECTION=1;
	  while(1)
	  {
		  alarm_rang=0;
		  while(alarm_rang==0);

		  if(LED_DIRECTION==1) // shift right
			  if(led_strobe > 3)   	IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE,led_strobe>>=1);
			  else LED_DIRECTION = 0; // shift left

		  else
			  if(led_strobe < 16) IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE,led_strobe<<=1);
			  else LED_DIRECTION = 1; // shift right
	  }


  return 0;
}
