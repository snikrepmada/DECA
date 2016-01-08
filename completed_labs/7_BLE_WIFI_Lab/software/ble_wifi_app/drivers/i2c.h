/******************************************************************************
 * NAME:         i2c.h
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

#ifndef _I2C_H_
#define _I2C_H_

/******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/

#include "alt_types.h"


/******************************************************************************
 * FUNCTION PROTOTYPES
 ******************************************************************************/
void   i2cSelect (alt_u32 scl, alt_u32 sda);

void   i2cRead   (alt_u8 inst, alt_u8 devAddr, alt_u8 *dPtr, alt_u8 len);
void   i2cReadNoAddress (alt_u8 inst, alt_u8 *dPtr, alt_u8 len);
alt_u8 i2cWrite  (alt_u8 inst, alt_u8 devAddr, alt_u8 *dPtr, alt_u8 len);

#endif /* _I2C_H_ */
