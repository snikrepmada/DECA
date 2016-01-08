//conversion between Si code and I2C


#ifndef _Bridge_code_H__
#define _Bridge_code_H__

#include "alt_types.h"
#include "../lab_work_bsp/system.h"


#define I2C_READ (alt_u32)(0x01)
#define I2C_WRITE (alt_u32)(0x00)

#define Si114x_7BitSLAVEADDRESS (0x00005A)

#define I2C_BASEADDRESS (I2C_OPENCORES_0_BASE)


struct SI114X_HANDLE_S
{
	alt_u32     I2C_BaseAddress;
	alt_u32     Si114x_7BitSlaveAddress;
};



#endif /* _Bridge_code_H__ */

