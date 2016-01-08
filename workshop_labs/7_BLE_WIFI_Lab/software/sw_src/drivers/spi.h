/**********************************************************************
 * NAME:         spi.h
 *
 * DESCRIPTION:  Defines interface to SPI driver.
 *
 * NOTES:
 *   None.
 *
 * REFERENCES:
 *   None.
 *
 * HISTORY:
 *   2015/13/2:  Initial version
 **********************************************************************/

#ifndef _SPI_H
#define _SPI_H


/**********************************************************************
 * INCLUDE FILES
 **********************************************************************/

#include <stdint.h>


/**********************************************************************
 * MACROS
 **********************************************************************/

#define spiRead(dev, bufPtr, outBytes, inBytes) \
	spiTransfer (dev, bufPtr, outBytes, bufPtr, inBytes)

#define spiReadDuo(dev, outBufPtr, outBytes, inBufPtr, inBytes) \
	spiTransfer (dev, outBufPtr, outBytes, inBufPtr, inBytes)

#define spiWrite(dev, bufPtr, numBytes) \
	spiTransfer (dev, bufPtr, numBytes, NULL, 0)


/**********************************************************************
 * TYPEDEFS
 **********************************************************************/

typedef enum
{
	SPI_DEVICE_CC3100,
	SPI_DEVICE_CC2650,
	SPI_NUM_DEVICES
} SPI_DEVICE;


/**********************************************************************
 * FUNCTION PROTOTYPES
 **********************************************************************/

void spiInit     	(void);
void spiTransfer	(SPI_DEVICE device,
					 void       *outPtr,
					 int32_t    outBytes,
					 void       *inPtr,
					 int32_t    inBytes);
void spiBiRead		(SPI_DEVICE deviceId,
					 void       *outPtr,
					 void       *inPtr,
					 int32_t    numBytes );
#endif  // _SPI_H
