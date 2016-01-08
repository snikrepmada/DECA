/******************************************************************************
 * NAME:         lis322ar.c
 *
 * DESCRIPTION:  MEMS 3-axix, 2g analog-output accelerometer.
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
#include <unistd.h>

#include "altera_avalon_pio_regs.h"
#include "system.h"
#include "lis332ar.h"

#if 1

/******************************************************************************
 * FUNCTION:	lis332arInit
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
void lis332arInit (void)
{
	/********************************************
	 * Start Sequencer
	 ********************************************/
	IOWR(ADC_SEQUENCER_CSR_BASE, 0, 0);
	usleep(10);
	IOWR(ADC_SEQUENCER_CSR_BASE, 0, 1);

	/********************************************
	 * Enable accelerometer
	 ********************************************/
	IOWR_ALTERA_AVALON_PIO_DATA(G_SENSOR_PIO_BASE, 0x0);
}

/******************************************************************************
 * FUNCTION:	lis332arRead
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
void lis332arRead (alt_u16 *x, alt_u16 *y, alt_u16 *z)
{
	/********************************************
	 * Read Sequence 0, 1, 2
	 ********************************************/
	*x = IORD(ADC_SAMPLE_STORE_CSR_BASE, 0);
	*y = IORD(ADC_SAMPLE_STORE_CSR_BASE, 1);
	*z = IORD(ADC_SAMPLE_STORE_CSR_BASE, 2);

	//alt_printf("%x %x %x\n", *x, *y, *z);
	usleep(3);
}

#endif
