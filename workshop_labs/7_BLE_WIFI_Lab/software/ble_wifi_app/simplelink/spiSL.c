/******************************************************************************
 * NAME:         spi.c
 *
 * DESCRIPTION:  SPI bus driver.
 *
 * NOTES:
 *   None.
 *
 * REFERENCES:
 *   None.
 *
 * HISTORY:
 *   2015/13/2:  Initial version
 ******************************************************************************/

/******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "system.h"
#include "../drivers/spi.h"

#include "boardSL.h"
#include "spiSL.h"


/******************************************************************************
 * DEFINES
 ******************************************************************************/
#define NONOS_RET_OK			1

/******************************************************************************
 * TYPEDEFS
 ******************************************************************************/


/******************************************************************************
 * CONSTANTS
 ******************************************************************************/


/******************************************************************************
 * FUNCTION:     spiSL_Open
 *
 * DESCRIPTION:  Initialize SPI controllers.
 *
 * INPUTS:
 *   None.
 *
 * RETURNS:
 *   None.
 *
 * NOTES:
 ******************************************************************************/
spiSL_Handle spiSL_Open  (char *ifName, unsigned long flags)
{
	// nHib release CC3100_CTRL_PIO_BASE
	//IOWR(CC3100_CTRL_PIO_BASE, 0, 1);

	return NONOS_RET_OK;
}


/******************************************************************************
 * FUNCTION:     spiSL_Close
 *
 * DESCRIPTION:  Initialize SPI controllers.
 *
 * INPUTS:
 *   None.
 *
 * RETURNS:
 *   None.
 *
 * NOTES:
 ******************************************************************************/
int spiSL_Close (spiSL_Handle hdl)
{

	return NONOS_RET_OK;
}


/******************************************************************************
 * FUNCTION:     spiSL_Read
 *
 * DESCRIPTION:  Initialize SPI controllers.
 *
 * INPUTS:
 *   None.
 *
 * RETURNS:
 *   None.
 *
 * NOTES:
 ******************************************************************************/
int spiSL_Read  (spiSL_Handle hdl, unsigned char *pBuff, int len)
{
	spiRead(SPI_DEVICE_CC3100, pBuff, 0, len);
	return len;

	//return NONOS_RET_OK;
}


/******************************************************************************
 * FUNCTION:     spiSL_Write
 *
 * DESCRIPTION:  Initialize SPI controllers.
 *
 * INPUTS:
 *   None.
 *
 * RETURNS:
 *   None.
 *
 * NOTES:
 ******************************************************************************/
int spiSL_Write (spiSL_Handle hdl, unsigned char *pBuff, int len)
{
	int iteration = len;


	while (iteration > 0)
	{
		//spiWrite(SPI_DEVICE_CC3100, pBuff, len);
		if (iteration > 4)
		{
			spiWrite(SPI_DEVICE_CC3100, pBuff, 4);
			pBuff += 4;
		}
		else
		{
			spiWrite(SPI_DEVICE_CC3100, pBuff, iteration);
		}

		iteration -= 4;
	}

	return len;
	//return NONOS_RET_OK;
}

