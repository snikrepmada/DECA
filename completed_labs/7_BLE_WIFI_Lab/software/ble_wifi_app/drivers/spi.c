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
#include "altera_avalon_spi.h"
#include "altera_avalon_spi_regs.h"
#include "altera_avalon_pio_regs.h"

#include "spi.h"


/******************************************************************************
 * DEFINES
 ******************************************************************************/

#define NUM_INSTANCES           SPI_NUM_DEVICES


/******************************************************************************
 * TYPEDEFS
 ******************************************************************************/

typedef struct
{
	uint32_t	base;
	uint32_t 	sSelect;
	uint32_t	flags;
	uint32_t	numReadBytes;
	uint32_t	pioDirBase;
} DEVICE_INFO;


/******************************************************************************
 * CONSTANTS
 ******************************************************************************/

static const DEVICE_INFO deviceInfo [] =
{
	/* SPI_DEVICE_CC3100)		==> */  { CC3100_SPI_BASE,  	0, 0, 1, 0 },
	/* SPI_DEVICE_CC2650)		==> */  { CC2650_SPI_BASE,  	0, 0, 1, 0 },
};


/******************************************************************************
 * FUNCTION:     spiTransfer
 *
 * DESCRIPTION:  Perform SPI data write with specified SPI device.
 *
 * INPUTS:
 *   - deviceId :  uniquely identifies SPI device to transfer data to/from
 *   - outPtr   :  pointer to data to write to SPI device
 *   - inPtr    :  pointer to memory to hold data read from SPI device
 *   - numBytes :  number of bytes to transfer
 *
 * RETURNS:
 *   - outPtr   :  data read from device
 *
 * NOTES:
 *   For write-only devices, inPtr may be set to NULL.  For read-only
 *   devices, outPtr must point to valid memory as the driver will
 *   still use it - the simplest solution is to set outPtr = inPtr
 *   for read-only devices.
 *
 *   The macros spiRead() and spiWrite() in spi.h hide these details
 *   from the caller.
 ******************************************************************************/
void spiTransfer (SPI_DEVICE deviceId,
                  void       *outPtr,
                  int32_t    outBytes,
                  void       *inPtr,
                  int32_t    inBytes)
{
	const DEVICE_INFO *devPtr;
	devPtr      = &deviceInfo [deviceId];


	alt_avalon_spi_command(devPtr->base, devPtr->sSelect,
			outBytes, outPtr, inBytes, inPtr, devPtr->flags);
}


/******************************************************************************
 * FUNCTION:     spiBiRead
 *
 * DESCRIPTION:  Perform SPI data Read with specified SPI device.  This
 * 	 is for SPI devices that share SDO for read and write. PIO is used to
 * 	 change the SDO to tri-state.  This allows the slave device to drive
 * 	 data.
 *
 * INPUTS:
 *   - deviceId :  uniquely identifies SPI device to transfer data to/from
 *   - outPtr   :  pointer to data to write to SPI device
 *   - inPtr    :  pointer to memory to hold data read from SPI device
 *   - numBytes :  number of bytes to transfer
 *
 * RETURNS:
 *   - outPtr   :  data read from device
 *
 * NOTES:
 *   This is only for devices that are bi-direction SDO.
 ******************************************************************************/
void spiBiRead (SPI_DEVICE deviceId,
				void       *outPtr,
				void       *inPtr,
				int32_t    numBytes)
{
	const	DEVICE_INFO *devPtr = &deviceInfo [deviceId];
	int32_t				numWriteBytes;
	uint8_t				*bufInPtr,
						*bufOutPtr;



	IOWR_ALTERA_AVALON_PIO_DATA(devPtr->pioDirBase, 1);

	/********************************************
	* Number of write bytes
	********************************************/
	numWriteBytes = numBytes;// - devPtr->numReadBytes;

	/********************************************
	* Start
	********************************************/
	alt_avalon_spi_command(devPtr->base, devPtr->sSelect,
			numWriteBytes, outPtr, 0, NULL, ALT_AVALON_SPI_COMMAND_MERGE);

	/********************************************
	* Manually changing SDO to input with PIO.
	********************************************/
	IOWR_ALTERA_AVALON_PIO_DATA(devPtr->pioDirBase, 0);

	/********************************************
	* Finish read with
	********************************************/
	bufInPtr = inPtr;// + numWriteBytes;
	bufOutPtr = outPtr;// + numWriteBytes;

	alt_avalon_spi_command(devPtr->base, devPtr->sSelect,
			0, bufOutPtr, devPtr->numReadBytes, bufInPtr, devPtr->flags);

	/********************************************
	* De-assert SO
	********************************************/
	IOWR_ALTERA_AVALON_SPI_CONTROL(devPtr->base, 0);

	/********************************************
	* Manually changing SDO back to output with PIO.
	********************************************/
	IOWR_ALTERA_AVALON_PIO_DATA(devPtr->pioDirBase, 1);
}


/******************************************************************************
 * FUNCTION:     spiInit
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
 *   Initialize all SPI controllers which are connected to the
 *   NIOS processor.  Note that this function initializes the
 *   SPI controllers, not devices connected to the SPI controllers.
 ******************************************************************************/
void spiInit (void)
{
}
