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
#include "altera_avalon_pio_regs.h"
#include "hdc1000.h"

#define HDC1000_I2C_ADDR 0x40


int main()
{

  alt_u16 temperature;
  alt_u16 humidity;
  alt_u16 tlow, thigh, hlow, hhigh;
  alt_u32 serial_no_high, serial_no_mid, serial_no_lo;

  double fTemp;
  double fHumidity;

  printf("Testing the HDC1000 via I2C...\n\n");

  //Initialize I2C master controller at 100kHz, 50MHz Cpu clock.
  I2C_init(RH_TEMP_I2C_BASE,ALT_CPU_CPU_FREQ,100000);

  /***********************************************************************
   * read the HDC1000_MFR_ID (0xFE) - expected readback value: 0x5449    *
   ***********************************************************************/

   // Write address that is to be read from
 	  I2C_start(RH_TEMP_I2C_BASE,HDC1000_I2C_ADDR,0);
 	  I2C_write(RH_TEMP_I2C_BASE,HDC1000_MFR_ID,0); // where FAMILY_ID is the offset to the family id

 	  // Set the start bit for a read command
 	  I2C_start(RH_TEMP_I2C_BASE,HDC1000_I2C_ADDR,1);
 	  printf("HDC1000_MFR_ID: \t0x%02X%02X \n",I2C_read(RH_TEMP_I2C_BASE,0),I2C_read(RH_TEMP_I2C_BASE,1));

  /***********************************************************************
   * read the HDC1000_DEVICE_ID (0xFF) - expected readback value: 0x1000 *
   ***********************************************************************/

  // Write address that is to be read from
	  I2C_start(RH_TEMP_I2C_BASE,HDC1000_I2C_ADDR,0);
	  I2C_write(RH_TEMP_I2C_BASE,HDC1000_DEVICE_ID,0); // where FAMILY_ID is the offset to the family id

	  // Set the start bit for a read command
	  I2C_start(RH_TEMP_I2C_BASE,HDC1000_I2C_ADDR,1);
	  printf("HDC1000_DEVICE_ID: \t0x%02X%02X \n\n",I2C_read(RH_TEMP_I2C_BASE,0),I2C_read(RH_TEMP_I2C_BASE,1));


  /***********************************************************************
   * read the HDC1000 Unique ID Serial Number
   ***********************************************************************/

  // Write address that is to be read from
	  I2C_start(RH_TEMP_I2C_BASE,HDC1000_I2C_ADDR,0);
	  I2C_write(RH_TEMP_I2C_BASE,HDC1000_REG_HI_SERIAL,0); // where FAMILY_ID is the offset to the family id

	  // Set the start bit for a read command
	  I2C_start(RH_TEMP_I2C_BASE,HDC1000_I2C_ADDR,1);
	  serial_no_high = I2C_read(RH_TEMP_I2C_BASE,0);
	  serial_no_high = serial_no_high<<8 | I2C_read(RH_TEMP_I2C_BASE,1);

  // Write address that is to be read from
	  I2C_start(RH_TEMP_I2C_BASE,HDC1000_I2C_ADDR,0);
	  I2C_write(RH_TEMP_I2C_BASE,HDC1000_REG_MID_SERIAL,0); // where FAMILY_ID is the offset to the family id

	  // Set the start bit for a read command
	  I2C_start(RH_TEMP_I2C_BASE,HDC1000_I2C_ADDR,1);
	  serial_no_mid  = I2C_read(RH_TEMP_I2C_BASE,0);
	  serial_no_mid  = serial_no_mid<<8 | I2C_read(RH_TEMP_I2C_BASE,1);

  // Write address that is to be read from
	  I2C_start(RH_TEMP_I2C_BASE,HDC1000_I2C_ADDR,0);
	  I2C_write(RH_TEMP_I2C_BASE,HDC1000_REG_LO_SERIAL,0); // where FAMILY_ID is the offset to the family id

	  // Set the start bit for a read command
	  I2C_start(RH_TEMP_I2C_BASE,HDC1000_I2C_ADDR,1);
	  serial_no_lo   = I2C_read(RH_TEMP_I2C_BASE,1);

	  printf("HDC1000 Serial No: \t0x%04X%04X%02X \n\n",serial_no_high,serial_no_mid,serial_no_lo);

  /************************************************************************************************
   * Configure the HDC1000, ensure bit 12 is set; High byte is transferred first then the low byte
   ************************************************************************************************/
	  I2C_start(RH_TEMP_I2C_BASE,HDC1000_I2C_ADDR,0);
	  I2C_write(RH_TEMP_I2C_BASE,HDC1000_REG_CONFIG,0);
	  I2C_write(RH_TEMP_I2C_BASE,0x10,0);	// 0x10 is BIT(12), the mode bit
	  I2C_write(RH_TEMP_I2C_BASE,0x00,1);

  /*************************************************************************************
   * Read the temperature and the humidity words consecutively						   *
   *************************************************************************************/
	  printf("Beginning Temperature and Humidity Capture\n");

  	  I2C_start(RH_TEMP_I2C_BASE,HDC1000_I2C_ADDR,0);
  	  I2C_write(RH_TEMP_I2C_BASE,HDC1000_REG_TEMP,0);
  	  I2C_write(RH_TEMP_I2C_BASE,HDC1000_REG_TEMP,0); // writing 0 to reg temp register to initiate sample


  	  printf("Waiting for Temperature and Humidity Capture Complete\n\n");

	  //wait for data ready, poll the drdyn pin
	  while(IORD_ALTERA_AVALON_PIO_DATA(RH_TEMP_DRDYN_BASE)!=0);

	  // Set the start bit for a read command
	  I2C_start(RH_TEMP_I2C_BASE,HDC1000_I2C_ADDR,1);
	  // temperature data
	  thigh = I2C_read(RH_TEMP_I2C_BASE,0); // MS Byte first
	  tlow = I2C_read(RH_TEMP_I2C_BASE,0);
	  // followed by humidity data
	  hhigh = I2C_read(RH_TEMP_I2C_BASE,0);
	  hlow = I2C_read(RH_TEMP_I2C_BASE,1);

	  temperature = thigh<<8|tlow;
	  humidity = hhigh<<8|hlow;

	  printf("Raw Temperature: \t%d\n",temperature);
	  printf("Raw Humidity: \t%d\n",humidity);


	  fTemp = (double)(((temperature/65535.0L)*165.0L)-40.0L);
	  fHumidity = (double)(humidity/65535.0L*100.0L);
	  printf("Actual Temperature: \t%.2f degC\n",fTemp);
	  printf("Actual Humidity: \t%.2f%% RH\n",fHumidity);


  return;

}



