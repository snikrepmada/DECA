/*
 * main.c
 *  version 2
 *
 */

#include <stdio.h>
#include "alt_types.h"
#include "system.h"
//#include "altera_adc.h"
#include "altera_modular_adc.h"
#include "altera_modular_adc_sample_store_regs.h"
#include "altera_modular_adc_sequencer_regs.h"
#include "altera_avalon_pio_regs.h"

#include "sys/alt_irq.h"
#include "sys/alt_alarm.h"

int main()
{
  printf("adc_example.c\n\n");
  //*
  int i;
  int loop_count;
  int led_output;
  float scale_factor;
  int line_in_binned;

  alt_u32 *adc_data;
  alt_u32 line_in_data;


  printf("************ System Information ************\n");
  printf("ADC_SAMPLE_STORE_CSR_BASE:    0x%08X\n",ADC_SAMPLE_STORE_CSR_BASE);
  printf("ADC_SEQUENCER_CSR_BASE:       0x%08X\n",ADC_SEQUENCER_CSR_BASE);
  printf("Number of Slots in Sequencer: %d\n\n",ADC_SEQUENCER_CSR_CSD_LENGTH);
  printf("Sequencer Slot 0: %s\n",ADC_SAMPLE_STORE_CSR_CSD_SLOT_0);
  printf("Sequencer Slot 1: %s\n",ADC_SAMPLE_STORE_CSR_CSD_SLOT_1);
  printf("Sequencer Slot 2: %s\n",ADC_SAMPLE_STORE_CSR_CSD_SLOT_2);
  printf("Sequencer Slot 3: %s\n\n",ADC_SAMPLE_STORE_CSR_CSD_SLOT_3);
  printf("********************************************\n\n");


  printf("*** Configure and start the ADC sequencer ***\n\n");
  adc_stop(ADC_SEQUENCER_CSR_BASE);							// ADC must be stopped to change the mode

  adc_interrupt_disable(ADC_SEQUENCER_CSR_BASE);			// Disable interrupts.
  adc_clear_interrupt_status(ADC_SEQUENCER_CSR_BASE);
  adc_set_mode_run_continuously(ADC_SEQUENCER_CSR_BASE);
  adc_start(ADC_SEQUENCER_CSR_BASE);						// Start the sequencer

  printf("*** Running ***\n\n");
  for(loop_count=1;loop_count<100000; loop_count++)
	  {
	  alt_adc_word_read(ADC_SAMPLE_STORE_CSR_BASE, adc_data, ADC_SEQUENCER_CSR_CSD_LENGTH);
	  line_in_data = adc_data[1];  // Line in is CH 5, and in the sequencer, Slot 1 is CH5

	  //printf("Line IN Data: 0x%04X\n",line_in_data);

	  scale_factor = ( (float)8 / ( (float)4096 - (float)1600 ) );	 // create the scaling factor (8 LEDS, 12 bit range, minus ~1V offset)
	  line_in_binned = (unsigned int)(scale_factor * (float)line_in_data);		 // Scale the data and convert to integer.  This is the 'bin' of the current volume

	  // Now we know which LED bin should be on.  Turn all the LEDs on below that value
      led_output = 0;
      for(i = 0; i < line_in_binned; i ++)
      {
    	  led_output = led_output << 1;
    	  led_output = led_output | 1;
      }

      // Output the result to the LEDs
	  IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE,led_output);

}

  printf("*** Stopping the ADC sequencer ***\n\n");
  adc_stop(ADC_SEQUENCER_CSR_BASE);

  // Turn the LEDs off
  IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE,0xff);

  printf("Done\n");

  return 0;
  //*/
}


