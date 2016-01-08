/******************************************************************************
 * NAME:         hdc1000.c
 *
 * DESCRIPTION:  Low power, high accuracy digital humidity and temperature
 * 				 sensor.
 *
 * NOTES:
 *
 *
 * REFERENCES:
 *   None.
 *
 * HISTORY:
 *   2015/5/2:  Initial version
 ******************************************************************************/

/******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/

#include <io.h>
#include "system.h"
#include "../drivers/i2c.h"
#include "hdc1000.h"

#if 1

/******************************************************************************
 * DEFINES
 ******************************************************************************/

#define HDC1000_WTR						0x0
#define HDC1000_RDR						0x1

#define HDC1000_ADDR_BASE				0x80
#define HDC1000_ADDR_WTR				(HDC1000_ADDR_BASE | HDC1000_WTR)
#define HDC1000_ADDR_RDR				(HDC1000_ADDR_BASE | HDC1000_RDR)


#define HDC1000_TRIGGERG_ADDR			0x00
#define HDC1000_TEMPERATURE_ADDR		0x00
#define HDC1000_HUMIDITY_ADDR			0x01
#define HDC1000_CONFIG_ADDR				0x02
#define HDC1000_ID0_ADDR				0xFB
#define HDC1000_ID1_ADDR				0xFC
#define HDC1000_ID2_ADDR				0xFD
#define HDC1000_MANUID_ADDR				0xFE
#define HDC1000_DEVICEID_ADDR			0xFF


// Bits 15-8, Configuration Register
#define HDC1000_SOFTRESET				0x80
#define HDC1000_NORMOP					0x00
#define HDC1000_HEAT_EN					0x20
#define HDC1000_HEAT_OFF				0x00
#define HDC1000_BOTH_ACQUIRE			0x10
#define HDC1000_SINGLE_ACQUIRE			0x00
#define HDC1000_BSTAT_OVER28			0x08
#define HDC1000_BSTAT_UNDER28			0x00
#define HDC1000_TRES_11BIT				0x04
#define HDC1000_TRES_14BIT				0x00
#define HDC1000_HRES_8BIT				0x02
#define HDC1000_HRES_11BIT				0x01
#define HDC1000_HRES_14BIT				0x00



/******************************************************************************
 * FUNCTION:	hdc1000Init
 *
 * DESCRIPTION:
 *
 * INPUTS:
 *   None.
 *
 * RETURNS:
 *   None.
 *
 * NOTES:
 *   None.
 ******************************************************************************/
void hdc1000Init (void)
{
	alt_u8 dataWrite[2];


	/********************************************
	 * Set SDA/SCL for device
	 ********************************************/
	i2cSelect(RH_TEMP_SCL_BASE, RH_TEMP_SDA_BASE);

	/********************************************
	 * Set acquisition for temperature and
	 * humidity.  Set resolution.
	 ********************************************/
	dataWrite[0] = (HDC1000_BOTH_ACQUIRE | HDC1000_TRES_14BIT | HDC1000_HRES_14BIT); //0x10
	dataWrite[1] = 0x00; //Reserved, must be 0
	i2cWrite(HDC1000_ADDR_WTR, HDC1000_CONFIG_ADDR, dataWrite, 2);
}


/******************************************************************************
 * FUNCTION:	hdc1000Read
 *
 * DESCRIPTION:
 *
 * INPUTS:
 *   None.
 *
 * RETURNS:
 *   None.
 *
 * NOTES:
 *   None.
 ******************************************************************************/
void hdc1000Read (alt_u16 *temperature, alt_u16 *humidity)
{
	alt_u8 drdyn;
	alt_u8 dataRead[4];
	alt_u8 dataWrite[2];


	/********************************************
	 * Set SDA/SCL for device
	 ********************************************/
	i2cSelect(RH_TEMP_SCL_BASE, RH_TEMP_SDA_BASE);

#if 0
	/********************************************
	 * Set acquisition for temperature and
	 * humidity.  Set resolution.
	 ********************************************/
	dataWrite[0] = (HDC1000_BOTH_ACQUIRE | HDC1000_TRES_14BIT | HDC1000_HRES_14BIT); //0x10
	dataWrite[1] = 0x00; //Reserved, must be 0
	i2cWrite(HDC1000_ADDR_WTR, HDC1000_CONFIG_ADDR, dataWrite, 2);
#endif

	/********************************************
	 * Trigger measurements
	 ********************************************/
	i2cWrite(HDC1000_ADDR_WTR, HDC1000_TRIGGERG_ADDR, 0, 0);

	/********************************************
	 * Wait for complete
	 ********************************************/
	do
	{
		drdyn = IORD(RH_TEMP_DRDY_BASE, 0);
	} while(drdyn);

	/********************************************
	 * Read Data
	 ********************************************/
	i2cReadNoAddress(HDC1000_ADDR_RDR, dataRead, 4);

	*temperature = ((dataRead[0] << 8) | dataRead[1]);
	*humidity = ((dataRead[2] << 8) | dataRead[3]);

	//*temperature = (((dataRead[0] << 8) | dataRead[1]) / 65536) * 165 - 40;
	//*humidity = (((dataRead[0] << 8) | dataRead[1]) / 65536);
}

#endif
