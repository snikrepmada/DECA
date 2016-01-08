/******************************************************************************
 * NAME:         adcMAX10.h
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

#ifndef HDC1000_H_
#define HDC1000_H_

/******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/

#include "alt_types.h"


/******************************************************************************
 * FUNCTION PROTOTYPES
 ******************************************************************************/

void hdc1000Init (void);
void hdc1000Read (alt_u16 *temperature, alt_u16 *humidity);

#endif /* HDC1000_H_ */
