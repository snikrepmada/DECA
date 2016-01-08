/*
 * MBR3102 cap touch reference code.
 *
 */



#include <stdio.h>
#include "system.h"
#include <alt_types.h>
#include "sys/alt_alarm.h"
#include "i2c_opencores_regs.h"
#include "i2c_opencores.h"
#include "MBR3102.h"
#include "MBR3102_2Button_rev1.h"
#include "MBR3102_1Button_1Prox_rev1.h"
#include "altera_avalon_pio_regs.h"

#define TWO_BUTTON
#define MBR3102_ADDR 0x37

int alarm_counter=0;
int alarm_rang=0;



int main()
{
  alt_u8 write_return_value;
  alt_u16 n;
  alt_u8 cmd[16];
  alt_u16 proximity_value;
  unsigned char *pConfig;

#ifdef TWO_BUTTON
  pConfig = CY8CMBR3102_configuration_2BUTTON;
#else // ONE_BUTTON__ONE_PROXIMITY
  pConfig = CY8CMBR3102_configuration_1B_1P;
#endif

  printf("Testing the Cypress MBR3102 via I2C...\n\n");

  //http://www.alteraforum.com/forum/showthread.php?t=38962
  //Initialize I2C master controller at 100kHz, 50MHz Cpu clock.
  I2C_init(CAPSENSE_I2C_BASE,ALT_CPU_CPU_FREQ,100000);

 /***********************************************************
  * read the FAMILY_ID - expected readback value dec: 154   *
  ***********************************************************/

  // Write address that is to be read from
  // the while loop is necessary because the MBR3102 will NACK the first three tries before sending ACK
  do
  {
	  I2C_start(CAPSENSE_I2C_BASE,MBR3102_ADDR,0);
	  write_return_value=I2C_write(CAPSENSE_I2C_BASE,FAMILY_ID,0); // where FAMILY_ID is the offset to the family id
  }
  while (write_return_value!=0);

  // Set the start bit for a read command
  I2C_start(CAPSENSE_I2C_BASE,MBR3102_ADDR,1);
  printf("FAMILY_ID: %d \n",I2C_read(CAPSENSE_I2C_BASE,1)); // the one in this function call terminates the I2C transaction (vs leaving it open)

  /*****************************************************************
   *next step, concatenate two 8-bit reads into one 16-bit read    *
   *****************************************************************/
  do
  {
	  I2C_start(CAPSENSE_I2C_BASE,MBR3102_ADDR,0);
	  write_return_value=I2C_write(CAPSENSE_I2C_BASE,DEVICE_ID,0); // where DEVICE_ID is the offset to the device id
  }
  while (write_return_value!=0);


  // Set the start bit for a read command
  I2C_start(CAPSENSE_I2C_BASE,MBR3102_ADDR,1);
  printf("DEVICE_ID: %d\n",I2C_read(CAPSENSE_I2C_BASE,0)+I2C_read(CAPSENSE_I2C_BASE,1)*0x100); // multiply-add was done to shift the upper byte

  /***********************************************************
   * read the DEVICE_REV								     *
   ***********************************************************/

   // Write address that is to be read from
   // the while loop is necessary because the MBR3102 will NACK the first three tries before sending ACK
   do
   {
 	  I2C_start(CAPSENSE_I2C_BASE,MBR3102_ADDR,0);
 	  write_return_value=I2C_write(CAPSENSE_I2C_BASE,DEVICE_REV,0); // where FAMILY_ID is the offset to the family id
   }
   while (write_return_value!=0);

   // Set the start bit for a read command
   I2C_start(CAPSENSE_I2C_BASE,MBR3102_ADDR,1);
   printf("DEVICE_REV: %d \n",I2C_read(CAPSENSE_I2C_BASE,1)); // the one in this function call terminates the I2C transaction (vs leaving it open)

   /*****************************************************************************
    * write the new 128-byte value to configure the MBR for button or proximity *
    *****************************************************************************/
   do
   {
 	  I2C_start(CAPSENSE_I2C_BASE,MBR3102_ADDR,0);
 	  write_return_value=I2C_write(CAPSENSE_I2C_BASE,0x00,0); // start write at offset 0x00
   }
   while (write_return_value!=0);


   // Set the start bit for a write command
   I2C_start(CAPSENSE_I2C_BASE,MBR3102_ADDR,0);
   for(n=0;n<127;n++)
	   I2C_write(CAPSENSE_I2C_BASE,pConfig[n],0);
   I2C_write(CAPSENSE_I2C_BASE,pConfig[n],1);

   printf("Done writing to MBR3102\n\nPress a button!\n");

// setup an interrupt to avoid polling
   while(1) {
	   // read the BUTTON_STAT register
	   do
	   {
		  I2C_start(CAPSENSE_I2C_BASE,MBR3102_ADDR,0);
		  write_return_value=I2C_write(CAPSENSE_I2C_BASE,BUTTON_STAT,0); // where FAMILY_ID is the offset to the family id
	   }
	   while (write_return_value!=0);

	   // Set the start bit for a read command
	   I2C_start(CAPSENSE_I2C_BASE,MBR3102_ADDR,1);
	   IOWR_ALTERA_AVALON_PIO_DATA(CAP_PB_PIO_BASE,I2C_read(CAPSENSE_I2C_BASE,1)); // the one in this function call terminates the I2C transaction (vs leaving it open)

   	}

}



