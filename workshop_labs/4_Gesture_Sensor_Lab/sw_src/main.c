// Arrow DECA Si1143 Gesture Sensor Lab
// 03/28/2015
// Copyright (C) 2015 Arrow Electronics Inc
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#include <string.h>
#include <stdio.h>
#include "alt_stdio.h"
#include "terasic_includes.h"
#include "mem_verify.h"
#include "../lab_work_bsp/system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_irq.h"
#include "Bridge_code.h"
#include "i2c_opencores.h"
#include "Si114x_functions.h"

#include <sys/time.h>

// function declarations
int DECA_si1143_irq_pop(HANDLE si114x_handle, SI114X_IRQ_SAMPLE *samples);
static gesture_t ProcessSi1143Samples(SI114X_IRQ_SAMPLE *samples);
 
int main()
{
	// variable declarations
	int usr_sel;
	int s16_current = 0x0bbb;
	int s16_tasklist = -1;
	int s16_measrate = 0x84;
	int gest_cnt = 0;
	s16 SI114x_ret_val = -1;
	u8 SI114x_write_val;
	u8 SI114x_ret_val_array[8];
	u8* SI114x_ptr = &SI114x_ret_val_array;

	// data structure declarations
	SI114X_IRQ_SAMPLE  samples;
	gesture_t  gest = NONE;
	HANDLE si114x_handle;
	si114x_handle = 0;

	// main program
	printf("\nGesture Sensor program starting... Please wait...\n\n");
	
	// initializing the I2C bus @ addr = I2C_OPENCORES_0_BASE
	printf("Initializing I2C bus...\n");
	I2C_init(I2C_OPENCORES_0_BASE, (alt_32) 50000000, (alt_32) 200000);
	
	// reset the Si1143 Gesture IC
	printf("Resetting Si1143 Gesture Sensor...\n");
	SI114x_ret_val = Si114xReset(si114x_handle);
	if ( SI114x_ret_val != 0 )	// if reset is successful...
	{
		printf("Si1143 Reset completed successfully!\n");
		
		// set IR LED current values to a default level
		printf("Setting LED current values...\n");
		u8 i21, i3;
		i21 = 0xbb; // current = LEDI_202;
		i3  = 0x0b;
		SI114x_ret_val+=Si114xWriteToRegister(si114x_handle, REG_PS_LED21, i21);
		SI114x_ret_val+=Si114xWriteToRegister(si114x_handle, REG_PS_LED3 , i3);
	}
	else	// if reset fails, exit
	{
		printf("Si1143 Reset failed... Exiting...\n");
		return -1;
	}
	// gesture recognition loop
	printf("Entering main loop...\n Loop exits after 32 gestures are recognized.\n");
	// have Si1143 measure all three proximity channels, the visual channel, and the IR channel
	s16_tasklist = PS1_TASK + PS2_TASK + PS3_TASK + ALS_VIS_TASK + ALS_IR_TASK;
	SI114x_ret_val+=Si114xParamSet(si114x_handle, PARAM_CH_LIST, s16_tasklist);

	while ( gest_cnt <= 32 ){
		// make measurement
		SI114x_ret_val = Si114xPsAlsForce(si114x_handle);
		//usleep(10000);	// uncomment if you need a pause in measurements
		if ( SI114x_ret_val > 0 ){	// if measurement is successful...
			// retrieve data from sensor and put it in struct "samples"
			DECA_si1143_irq_pop(si114x_handle, &samples);
			// process data in gesture algorithm
			gest = ProcessSi1143Samples(&samples);
			
			// report the gesture and increment counter
			if ( gest != NONE ) gest_cnt++;
			if ( gest == UP ) printf("UP swipe detected!\n");
			if ( gest == DOWN ) printf("DOWN swipe detected!\n");
			if ( gest == LEFT ) printf("LEFT swipe detected!\n");
			if ( gest == RIGHT ) printf("RIGHT swipe detected!\n");
			if ( gest == TAP ) printf("TAP detected!\n");
		}
		else printf("Unable to force measurement...\n");
	}

	return 0;
}

/**************************************************************************//**
 * @brief
  *  retrieves measurement data from the Si1143 Gesture IC
  *  Should be called with after every measurement
 * @param[in] HANDLE, samples
 *	 board handle
 *   New sample data received from the sensor.
 * @return
 *   returns a positive number if successful, 0 otherwise
 *****************************************************************************/
int DECA_si1143_irq_pop(HANDLE si114x_handle, SI114X_IRQ_SAMPLE *samples) {

	s16 SI114x_ret_val = -1;
	u8 SI114x_ret_val_array[16];
	u8 *SI114x_ptr = (u8*) &SI114x_ret_val_array;
	struct timeval timestmp;
	gettimeofday( &timestmp, NULL );

	// block read to get measurement values
	SI114x_ret_val = Si114xBlockRead(si114x_handle, REG_IRQ_STATUS, 0xD, SI114x_ptr );
	
	// put measurements in the samples data structure and add a timestamp for the algorithm
	samples->irqstat = SI114x_ret_val_array[0];
	samples->vis = ( ( (u16)SI114x_ret_val_array[2] << 8 ) | SI114x_ret_val_array[1] );
	samples->ir = ( ( (u16)SI114x_ret_val_array[4] << 8 ) | SI114x_ret_val_array[3] );
	samples->ps1 = ( ( (u16)SI114x_ret_val_array[6] << 8 ) | SI114x_ret_val_array[5] );
	samples->ps2 = ( ( (u16)SI114x_ret_val_array[8] << 8 ) | SI114x_ret_val_array[7] );
	samples->ps3 = ( ( (u16)SI114x_ret_val_array[10] << 8 ) | SI114x_ret_val_array[9] );
	samples->aux = ( ( (u16)SI114x_ret_val_array[12] << 8 ) | SI114x_ret_val_array[11] );
	samples->timestamp = (u32)( timestmp.tv_usec + ( 1000000 * timestmp.tv_sec ) );

	// uncomment these lines to see raw data values
	//printf("Time: %s\n", ctime( &timestmp ) );
	//printf("PS1 Data: %x\n", samples->ps1 );
	//printf("PS2 Data: %x\n", samples->ps2 );
	//printf("PS3 Data: %x\n", samples->ps3 );
	//printf("IR Data: %x\n", samples->ir );
	//printf("VIS Data: %x\n", samples->vis );

	return SI114x_ret_val;
}

/**************************************************************************//**
 * @brief
  *  Implements the algorithm for detecting gestures on the sensor STK.
  *  Should be called with new sample data every time an interrupt is
  *  received.
 * @param[in] samples
 *   New sample data received from the sensor.
 * @return
 *   Returns the type of gesture detected (as defined by gesture_t).
 *****************************************************************************/
static gesture_t ProcessSi1143Samples(SI114X_IRQ_SAMPLE *samples)
{
  u16        ps[3];

  static u32 ps_entry_time[3] = { 0, 0, 0 };
  static u32 ps_exit_time[3]  = { 0, 0, 0 };

  static u8  ps_state[3] = { 0, 0, 0 };

  u8         array_counter;
  u32 diff_x ;
  u32 diff_y1 ;
  u32 diff_y2 ;
  u32 ps_time[3] ;
  u32 ps_avg;
  gesture_t  ret = NONE;  /*gesture result return value */
  /*save new samples into ps array */
  ps[0] = samples->ps1;
  ps[1] = samples->ps2;
  ps[2] = samples->ps3;

  /* Check state of all three measurements */
  for (array_counter = 0; array_counter < 3; array_counter++)
  {
    /* If measurement higher than the ps_threshold value, */
    /*   record the time of entry and change the state to look for the exit time */
    if (ps[array_counter] >= PS_THRESHOLD)
    {
      if (ps_state[array_counter] == 0)
      {
        ps_state[array_counter]      = 1;
        ps_entry_time[array_counter] = samples->timestamp;
      }
    }
    else
    {
      if (ps_state[array_counter] == 1)
      {
        ps_state[array_counter]     = 0;
        ps_exit_time[array_counter] = samples->timestamp;
      }
    }
  }

  /* If there is no object in front of the board, look at history to see if a gesture occured */
  if ((ps[0] < PS_THRESHOLD) && (ps[1] < PS_THRESHOLD) && (ps[2] < PS_THRESHOLD))
  {
    /* If the ps_max values are high enough and there exit entry and exit times, */
    /*   then begin processing gestures */
    if ((ps_entry_time[0] != 0) && (ps_entry_time[1] != 0) && (ps_entry_time[2] != 0)
        && (ps_exit_time[0] != 0) && (ps_exit_time[1] != 0) && (ps_exit_time[2] != 0))
    {
      /* Make sure no timestamps overflowed, indicated possibility if any of them are close to overflowing */
      if ((ps_exit_time[0] > 0xFC000000L) || (ps_exit_time[1] > 0xFC000000L) || (ps_exit_time[2] > 0xFC000000L)
          || (ps_entry_time[0] > 0xFC000000L) || (ps_entry_time[1] > 0xFC000000L) || (ps_entry_time[2] > 0xFC000000L))
      {         /* If any of them are close to overflowing, overflow them all so they all have the same reference */
        ps_exit_time[0] += 0x1FFFFFFFL;
        ps_exit_time[1] += 0x1FFFFFFFL;
        ps_exit_time[2] += 0x1FFFFFFFL;

        ps_entry_time[0] += 0x1FFFFFFFL;
        ps_entry_time[1] += 0x1FFFFFFFL;
        ps_entry_time[2] += 0x1FFFFFFFL;
      }

      /* Calculate the midpoint (between entry and exit times) of each waveform */
      /*  the order of these midpoints helps determine the gesture */
      ps_time[0] = (ps_exit_time[0] - ps_entry_time[0]) / 2;
      ps_time[0] = ps_time[0] + ps_entry_time[0];

      ps_time[1] = (ps_exit_time[1] - ps_entry_time[1]) / 2;
      ps_time[1] = ps_time[1] + ps_entry_time[1];

      ps_time[2] = (ps_exit_time[2] - ps_entry_time[2]) / 2;
      ps_time[2] = ps_time[2] + ps_entry_time[2];

      /* The diff_x and diff_y values help determine a gesture by comparing the */
      /*  LED measurements that are on a single axis */
      if (ps_time[1] > ps_time[2])
      {
        diff_x = ps_time[1] - ps_time[2];
      }
      else
      {
        diff_x = ps_time[2] - ps_time[1];
      }
      if( ps_time[0] > ps_time[1] )
      {
        diff_y1 = ps_time[0] - ps_time[1];
      }
	  else
      {
        diff_y1 = ps_time[1] - ps_time[0];
      }

      if( ps_time[0] > ps_time[2] )
      {
        diff_y2 = ps_time[0] - ps_time[2];
      }
	  else
      {
        diff_y2 = ps_time[2] - ps_time[0];
      }


      /* Take the average of all three midpoints to make a comparison point for each midpoint */
      ps_avg = (u32) ps_time[0] + (u32) ps_time[1] + (u32) ps_time[2];
      ps_avg = ps_avg / 3;

      if ((ps_exit_time[0] - ps_entry_time[0]) > 10 || (ps_exit_time[1] - ps_entry_time[1]) > 10 || (ps_exit_time[2] - ps_entry_time[2]) > 10)
      {
        if( ( (ps_time[0] < ps_time[1]) &&  (diff_y1 > diff_x) ) || ( (ps_time[0] <= ps_time[2]) && (diff_y2 > diff_x) ) )
        {           /* An up gesture occured if the bottom LED had its midpoint first */
          ret = UP;
        }
        else if  ( ( (ps_time[0] < ps_time[1]) &&  (diff_y1 > diff_x) ) || ( (ps_time[0] > ps_time[2]) && (diff_y2 > diff_x) ) )
        {           /* A down gesture occured if the bottom LED had its midpoint last */
          ret = DOWN;
        }
        else if((ps_time[0] < ps_time[1]) && (ps_time[2] < ps_time[1]) && (diff_x > ((diff_y1+diff_y2)/2)))
        {           /* A left gesture occured if the left LED had its midpoint last */
          ret = LEFT;
        }
        else if( (ps_time[0] < ps_time[2]) && (ps_time[1] < ps_time[2])  && (diff_x > ((diff_y1+diff_y2)/2)))
        {           /* A right gesture occured if the right LED had midpoint later than the right LED */
          ret = RIGHT;
        }
      }
    }
    for (array_counter = 0; array_counter < 3; array_counter++)
    {
      ps_exit_time[array_counter]  = 0;
      ps_entry_time[array_counter] = 0;
    }
  }

  return ret;
}
