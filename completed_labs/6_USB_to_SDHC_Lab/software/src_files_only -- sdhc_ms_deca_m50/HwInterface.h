/*********************************************************************************************
 *  SLS USB20SR Device Controller Driver
 *
 *  Copyright (C) 2015 SLS, All Rights Reserved.
 *
 *  History:
 *      v1.0.0  : September 09  - SLS : USB20SR IP - Core v1.0
 *      v1.1.1  : October 10    - SLS : USB20SR IP - Core v1.1
 *      v1.2.2  : July 11       - SLS : USB20SR IP - Core v1.2
 *      v1.2.3  : December 12   - SLS : USB20SR IP - Core v1.2
 *      v1.3.4  : December 12   - SLS : USB20SR IP - Core v1.3
 *      v1.3.5  : November 14   - SLS : USB20SR IP - Core v1.3
 *      v1.4.5  : January 15    - SLS : USB20SR IP - Core v1.4
 *
 *********************************************************************************************/

#ifndef HWINTERFACE_H_
#define HWINTERFACE_H_

//Parent Bus IO ( Host Controller's parent bus IO )

#define __IO_CALC_ADDRESS_NATIVE(BASE, REGNUM) \
  ((void *)(((alt_u8*)BASE) + ((REGNUM) * (SYSTEM_BUS_WIDTH/8))))

#define IORD(BASE, REGNUM) \
  __builtin_ldwio (__IO_CALC_ADDRESS_NATIVE ((BASE), (REGNUM)))
#define IOWR(BASE, REGNUM, DATA) \
  __builtin_stwio (__IO_CALC_ADDRESS_NATIVE ((BASE), (REGNUM)), (DATA))

#define PARENT_BUS_IORD_8(CSAddr,Offset)        IORD_8DIRECT(CSAddr,Offset)

#define PARENT_BUS_IOWR_8(CSAddr,Offset,data)   IOWR_8DIRECT(CSAddr,Offset,data)

#define PARENT_BUS_IORD_16(CSAddr,Offset)       IORD_16DIRECT(CSAddr,Offset)

#define PARENT_BUS_IOWR_16(CSAddr,Offset,data)  IOWR_16DIRECT(CSAddr,Offset,data)

#define PARENT_BUS_IORD_32(CSAddr,Offset)       IORD_32DIRECT(CSAddr,Offset)

#define PARENT_BUS_IOWR_32(CSAddr,Offset,data)  IOWR_32DIRECT(CSAddr,Offset,data)

#endif /*HWINTERFACE_H_*/
