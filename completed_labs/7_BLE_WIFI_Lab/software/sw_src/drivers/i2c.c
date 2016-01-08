/******************************************************************************
 * NAME:         i2c.c
 *
 * DESCRIPTION:
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

#include <sys/alt_stdio.h>
#include <io.h>

#include "system.h"
#include "i2c.h"


#define I2C_DATA_OFFSET_ADDR	0
#define I2C_DIR_OFFSET_ADDR		1

#define	I2C_HI					1
#define I2C_LO					0

#define I2C_INPUT				0
#define I2C_OUTPUT				1

/******************************************************************************
 * FUNCTION PROTOTYPES
 ******************************************************************************/

void 	i2cAck   		(void);
void 	i2cNAck  		(void);
void 	i2cStart 		(void);
void 	i2cStop  		(void);

alt_u8	i2cWrite8bit	(unsigned char val);
alt_u8	i2cRead8bit		(void);


/******************************************************************************
 * LOCAL VARIABLES
 ******************************************************************************/
static	alt_u32 sclBase = 0;
static  alt_u32 sdaBase = 0;


/******************************************************************************
 * FUNCTION:
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
void i2cAck (void)
{

	IOWR(sdaBase, 0, 0);
	usleep(1);

	IOWR(sclBase, 0, 1);
	usleep(1);

	IOWR(sclBase, 0, 0);
	usleep(1);

	IOWR(sdaBase, 0, 1);
	usleep(1);
}


/******************************************************************************
 * FUNCTION:
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
void i2cNAck (void)
{
	IOWR(sdaBase, 0, 1);
	usleep(1);

	IOWR(sclBase, 0, 1);
	usleep(1);

	IOWR(sclBase, 0, 0);
	usleep(1);

	IOWR(sdaBase, 0, 0);
	usleep(1);
}


/******************************************************************************
 * FUNCTION:	i2cSelect
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
void i2cSelect (alt_u32 scl, alt_u32 sda)
{
	sclBase = scl;
	sdaBase = sda;
}


/******************************************************************************
 * FUNCTION:	i2cStart
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
void i2cStart (void)
{
	IOWR(sdaBase, I2C_DIR_OFFSET_ADDR, I2C_OUTPUT);

	IOWR(sdaBase, 0, 1);
	usleep(1);

	IOWR(sclBase, 0, 1);
	usleep(1);

	IOWR(sdaBase, 0, 0);
	usleep(1);

	IOWR(sclBase, 0, 0);
	usleep(1);
}


/******************************************************************************
 * FUNCTION:	i2cStop
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
void i2cStop (void)
{
	IOWR(sdaBase, 0, 0);
	usleep(1);

	IOWR(sclBase, 0, 0);
	usleep(1);

	IOWR(sclBase, 0, 1);
	usleep(1);

	IOWR(sdaBase, 0, 1);
	usleep(1);
}


/******************************************************************************
 * FUNCTION:	i2cWrite8bit
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
alt_u8 i2cWrite8bit	(unsigned char val)
{
	alt_8  i;
	alt_u8 bAck;


	/********************************************
	 * Make sure SCL is low
	 ********************************************/
	IOWR(sclBase, 0, 0);
	usleep(1);

	/********************************************
	 * Clock out Data, MSB -> LSB
	 ********************************************/
	for ( i = 7; i >= 0; i--)
	{
		IOWR(sdaBase, 0, ((val >> i) & 1));
		usleep(1);

		IOWR(sclBase, 0, 1);
		usleep(1);

		IOWR(sclBase, 0, 0);
		usleep(1);
	}

	/********************************************
	 * Check Ack
	 ********************************************/
	IOWR(sdaBase, I2C_DIR_OFFSET_ADDR, I2C_INPUT);
	usleep(1);

	bAck = IORD(sdaBase, 0);

	IOWR(sclBase, 0, 1);
	usleep(1);

	IOWR(sclBase, 0, 0);
	usleep(1);

	IOWR(sdaBase, I2C_DIR_OFFSET_ADDR, I2C_OUTPUT);
	usleep(1);
	return (bAck & 1);
}


/******************************************************************************
 * FUNCTION:	i2cRead8bit
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
alt_u8 i2cRead8bit (void)
{
	alt_8  i;
	alt_u8 dbit, data = 0;

	for ( i = 0; i < 8; i++)
	{
		IOWR(sclBase, 0, 1);
		usleep(1);

		data = (data << 1);
		dbit = IORD(sdaBase, 0);
		data |= (dbit & 1);

		IOWR(sclBase, 0, 0);
		usleep(1);
	}

	return data;
}

/******************************************************************************
 * FUNCTION:	i2cWrite
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
alt_u8 i2cWrite (alt_u8 inst, alt_u8 devAddr, alt_u8 *dPtr, alt_u8 len)
{
	alt_8  i;

	i2cStart	 ();
	i2cWrite8bit (inst);
	i2cWrite8bit (devAddr);

	for (i = 0; i < len; i++)
	{
		i2cWrite8bit (*dPtr);
		dPtr++;
		//devAddr++;
	}
	i2cStop		 ();

	return 0;
}

/******************************************************************************
 * FUNCTION:	i2cRead
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
void i2cRead (alt_u8 inst, alt_u8 devAddr, alt_u8 *dPtr, alt_u8 len)
{
	alt_8  i;

	i2cStart	 ();
	i2cWrite8bit (inst);
	i2cWrite8bit (devAddr);
	i2cStart	 ();
	i2cWrite8bit (inst + 1);

	for (i = 0; i < len; i++)
	{
		*dPtr = i2cRead8bit();

		if (i < (len - 1))
			i2cAck();
		else
			i2cNAck();
	}

	i2cStop		 ();
}


/******************************************************************************
 * FUNCTION:	i2cReadNoAddress
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
void i2cReadNoAddress (alt_u8 inst, alt_u8 *dPtr, alt_u8 len)
{
	alt_8  i;

	i2cStart	 ();
	i2cWrite8bit (inst);

	for (i = 0; i < len; i++)
	{
		*dPtr = i2cRead8bit();

		if (i < (len - 1))
			i2cAck();
		else
			i2cNAck();

		dPtr++;
	}

	i2cStop		 ();
}
