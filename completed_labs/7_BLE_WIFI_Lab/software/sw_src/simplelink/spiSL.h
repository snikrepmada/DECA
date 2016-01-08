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

#ifndef _SPISL_H
#define _SPISL_H


/**********************************************************************
 * INCLUDE FILES
 **********************************************************************/

#include <stdint.h>


/**********************************************************************
 * TYPEDEFS
 **********************************************************************/
typedef int* spiSL_Handle;


/**********************************************************************
 * FUNCTION PROTOTYPES
 **********************************************************************/
spiSL_Handle spiSL_Open  (char *ifName, unsigned long flags);
int 		 spiSL_Close (spiSL_Handle hdl);
int 		 spiSL_Read  (spiSL_Handle hdl, unsigned char *pBuff, int len);
int 		 spiSL_Write (spiSL_Handle hdl, unsigned char *pBuff, int len);

#endif  // _SPISL_H
