/******************************************************************************
 * NAME:         lis2dh12.c
 *
 * DESCRIPTION:  MEMS 3-axix, 2g digital-output accelerometer.
 *
 * NOTES:
 *	 This is a simple driver to read the g_sensor data
 *
 * REFERENCES:
 *   None
 *
 * HISTORY:
 *   2015/5/10:  Initial version
 ******************************************************************************/

/******************************************************************************
 * INCLUDE FILES, only if they haven't already been included
 ******************************************************************************/
#ifndef __ALTERA_AVALON_SPI_REGS_H__
  #include "altera_avalon_spi_regs.h"
#endif

#ifndef __ALT_AVALON_SPI_H__
  #include "altera_avalon_spi.h"
#endif

#ifndef __SYSTEM_H_
  #include "system.h"
#endif

#include "lis2dh12.h"

#define DEVICE_ID_REG	0x0F 		// returns 0x33 when read
//-WRITE/READ-
#define TEMP_CFG_REG 	0x1F
#define CTRL_REG1   	0x20
#define CTRL_REG4   	0x23
#define STATUS_REG      0x27
//-READ-
#define OUT_TEMP_L 	    0x0C
#define OUT_TEMP_H 	    0x0D
#define OUT_X_L 	    0x28
#define OUT_X_H  	    0x29
#define OUT_Y_L         0x2A
#define OUT_Y_H         0x2B
#define OUT_Z_L         0x2C
#define OUT_Z_H         0x2D

//Register Configuration
#define TEMP_CFG_REG_value   0xC0    // Temperature sensor (T) enable
#define CTRL_REG1_value      0x97    // X/Y/Z-axis enable,HR mode (1.344 kHz);High-resolution mode(12-bit data output),12mg/digit
#define CTRL_REG4_value      0xB8    // output registers not updated until MSB and LSB have been read,data LSb at lower address,+-16g,High resolution mode,4-wire SPI interface


alt_u8 reg_addr[2]= {0x20,0x23};
alt_u16 wdata[2]  = {0x2097,0x23b8};
alt_u16 rdata[6]  = {0xa800,0xa900,0xAA00,0xAB00,0xAC00,0xAD00};


int initLIS2DH12(void)
{
	int i;
	alt_u16  reg_read=0xA000;
	alt_u16   reg_data[2];


	IOWR_ALTERA_AVALON_SPI_CONTROL(SPI_GSENSOR_BASE,0x00);          //Initialize the spi control reg
	IOWR_ALTERA_AVALON_SPI_TXDATA(SPI_GSENSOR_BASE, 0x2097);		//setup data rate and enable x,y,z axes
	usleep(100*2000);
	IOWR_ALTERA_AVALON_SPI_TXDATA(SPI_GSENSOR_BASE, 0x23b8);		//full scale, high resolution
	usleep(100*2000);

	// Read the Device ID register
	IOWR_ALTERA_AVALON_SPI_TXDATA(SPI_GSENSOR_BASE, (0x8F00)); // setup address to read from (0x0F), MSbit is R/Wn
	usleep(100*2000);
	if((IORD_ALTERA_AVALON_SPI_RXDATA(SPI_GSENSOR_BASE))!=0x33)   // verify the device id matches (0x33)
		return -1;

	return 1; // success
}

void lis2dh12Read(alt_u16 *data_x, alt_u16 *data_y, alt_u16 *data_z)
{
	int i;
	alt_u8   data[6];


	  for(i=0;i<6;i++){
		  IOWR_ALTERA_AVALON_SPI_TXDATA(SPI_GSENSOR_BASE, rdata[i]);
		  usleep(100*200);
		  data[i] = IORD_ALTERA_AVALON_SPI_RXDATA(SPI_GSENSOR_BASE);
	   }

	  //raw data values
	  *data_x = ((data[1]<<8)|data[0]);
	  *data_y = ((data[3]<<8)|data[2]);
	  *data_z = ((data[5]<<8)|data[4]);


	  // actual g values, unused:
	  // x = (float)(data_x/16.0)*12.0;
	  // y = (float)(data_y/16.0)*12.0;
	  // z = (float)(data_z/16.0)*12.0;
}
