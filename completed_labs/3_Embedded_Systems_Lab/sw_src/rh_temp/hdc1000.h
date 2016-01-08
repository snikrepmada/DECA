/*
 * hdc1000.h
 *
 *  Created on: Feb 21, 2015
 *      Author: a05450
 */

#ifndef HDC1000_H_
#define HDC1000_H_

#define HDC1000_REG_TEMP 			0x00
#define HDC1000_REG_HUMIDITY	 	0x01
#define HDC1000_REG_CONFIG			0x02

//40-bit unique serial number for each HDC1000
#define HDC1000_REG_HI_SERIAL		0xFB
#define HDC1000_REG_MID_SERIAL 		0xFC
#define HDC1000_REG_LO_SERIAL 		0xFD
#define HDC1000_MFR_ID 				0xFE
#define HDC1000_DEVICE_ID 			0xFF

#define HDC1000_EXPECTED_MFR_ID		0x5449
#define HDC1000_EXPECTED_DEVICE_ID	0x1000

//Config/Status bit definition
#define BIT(n)						(1 << (n))

#define HDC1000_BIT_RST				BIT(15)
#define HDC1000_BIT_RESERVED_14		BIT(14)
#define HDC1000_BIT_HEAT			BIT(13)
#define HDC1000_BIT_MODE			BIT(12)
#define HDC1000_BIT_BTST			BIT(11)
#define HDC1000_BIT_TRES			BIT(10)
#define HDC1000_BIT_HRES_MSBIT		BIT(9)
#define HDC1000_BIT_HRES_LSBIT		BIT(8)
//the rest of the bus is reserved 	BIT[7:0]


//bit 12 = 00001000_00000000 = 0x0800



#endif /* HDC1000_H_ */
