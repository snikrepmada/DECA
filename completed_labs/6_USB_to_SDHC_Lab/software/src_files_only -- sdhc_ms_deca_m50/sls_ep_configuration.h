/***********************************************************************************************
 *  SLS USB20SR Device Controller Driver
 *
 *  Copyright (C) 2015 SLS, All Rights Reserved.
 *
 *  History:
 *      v1.0.0  : September 09  - SLS : USB20SR IP - Core v1.0
 *      v1.1.1  : October 10	- SLS : USB20SR IP - Core v1.1
 *      v1.2.2  : July 11       - SLS : USB20SR IP - Core v1.2
 *      v1.2.3  : December 12   - SLS : USB20SR IP - Core v1.2
 *      v1.3.4  : December 12   - SLS : USB20SR IP - Core v1.3
 *      v1.3.5  : November 14   - SLS : USB20SR IP - Core v1.3
 *      v1.4.5  : January 15    - SLS : USB20SR IP - Core v1.4
 *
 *  Change History :
 *  (v1.1.1)            1>	Changed Endpoint type from ISO to BULK and Endpoint size from 0xC8
 *			           		to 0x200 in ep_ip_csr_hs_ array's first index
 *	(v1.2.2)			1>	Added Low Speed arrays with Low Speed endpoint configuration values
 *							(For the support of Low Speed, contact support@slscorp.com)
 *
 ***********************************************************************************************/

#ifndef  SLS_EP_CONFIGURATION_H_
#define  SLS_EP_CONFIGURATION_H_

#include "sls_avalon_usb20_regs.h"

#define SUPPORTED_CONF 1
#define MAXIMUM_EP_NO  15

/*************************************************************************************************************************************************************************
 * For supported_ep_[]'s value, upper 2 bytes are for IN endpoints and lower 2 bytes are for OUT endpoints.
 *
 * Example1: If 1st endpoint is IN endpoint with 0x81 address then enable 17th number of bit as 1 because 0x81 & 0x0F = 0x01
 *           If 2nd endpoint is OUT endpoint with 0x02 address then enable 2nd number of bit as 1 because 0x02 & 0x0F = 0x02
 *           So the final configuration will be 0x00010002
 * Example2: If 1st endpoint is IN endpoint with 0x81 address then enable 17th number of bit as 1 because 0x81 & 0x0F = 0x01
 *           If 2nd endpoint is OUT endpoint with 0x02 address then enable 2nd number of bit as 1 because 0x02 & 0x0F = 0x02
 *           If 3rd endpoint is OUT endpoint with 0x04 address then enable 4th number of bit as 1 because 0x04 & 0x0F = 0x04
 *           So the final configuration will be 0x0001000A = (0x00010000)|(0x0000000A)
 *
 * <---------------IN Endpoints------------------->|<---------------OUT Endpoints------------------> Set bit 1 according to endpoint number
 *  32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01  Bits number are defined with endpoints (address & 0x0F) respectively
 *  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
 * |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
 *  -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
 *
 * If any user wants to add/remove endpoint(s) then below all array(s) will be changed according to the index of endpoint(s) respectively.
 * For an example, if endpoint address is 0x84 then it's index in array will be 4th(Starting from 1st position).
 * User must have to take care about addressing of endpoint. None of the index should overlapped.
 * If user takes 0x81 as IN endpoint then he/she can't take 0x01 as OUT endpoint.
 *************************************************************************************************************************************************************************/
unsigned const int supported_ep_[] = {
                                     	0x00010002
                                     };

unsigned int ep_ip_csr_hs_[SUPPORTED_CONF][MAXIMUM_EP_NO] = {
									{
										SLS_AVALON_USB20_EP_CSR_EP_TYPE_IN_MSK | SLS_AVALON_USB20_EP_CSR_TR_TYPE_BULK_MSK | SLS_AVALON_USB20_EP_CSR_EP_DIS_NORMAL_MSK | SLS_AVALON_USB20_EP_CSR_EP_NO_1_MSK | SLS_AVALON_USB20_EP_CSR_SML_OK_MSK | SLS_AVALON_USB20_EP_CSR_TR_FR_1_MSK | SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_512_MSK,
										SLS_AVALON_USB20_EP_CSR_EP_TYPE_OUT_MSK | SLS_AVALON_USB20_EP_CSR_TR_TYPE_BULK_MSK | SLS_AVALON_USB20_EP_CSR_EP_DIS_NORMAL_MSK | SLS_AVALON_USB20_EP_CSR_EP_NO_2_MSK | SLS_AVALON_USB20_EP_CSR_SML_OK_MSK | SLS_AVALON_USB20_EP_CSR_TR_FR_1_MSK | SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_512_MSK,
										0,0,0,0,0,0,0,0,0,0,0,0,0
									}
};

unsigned int ep_ip_csr_fs_[SUPPORTED_CONF][MAXIMUM_EP_NO] = {
									{
										SLS_AVALON_USB20_EP_CSR_EP_TYPE_IN_MSK | SLS_AVALON_USB20_EP_CSR_TR_TYPE_BULK_MSK | SLS_AVALON_USB20_EP_CSR_EP_DIS_NORMAL_MSK | SLS_AVALON_USB20_EP_CSR_EP_NO_1_MSK | SLS_AVALON_USB20_EP_CSR_SML_OK_MSK | SLS_AVALON_USB20_EP_CSR_TR_FR_1_MSK | SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_64_MSK,
										SLS_AVALON_USB20_EP_CSR_EP_TYPE_OUT_MSK | SLS_AVALON_USB20_EP_CSR_TR_TYPE_BULK_MSK | SLS_AVALON_USB20_EP_CSR_EP_DIS_NORMAL_MSK | SLS_AVALON_USB20_EP_CSR_EP_NO_2_MSK | SLS_AVALON_USB20_EP_CSR_SML_OK_MSK | SLS_AVALON_USB20_EP_CSR_TR_FR_1_MSK | SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_64_MSK,
										0,0,0,0,0,0,0,0,0,0,0,0,0
									}
};

unsigned int ep_ip_csr_ls_[SUPPORTED_CONF][MAXIMUM_EP_NO] = {
									{
										SLS_AVALON_USB20_EP_CSR_EP_TYPE_IN_MSK | SLS_AVALON_USB20_EP_CSR_TR_TYPE_INTERRUPT_MSK | SLS_AVALON_USB20_EP_CSR_EP_DIS_NORMAL_MSK | SLS_AVALON_USB20_EP_CSR_EP_NO_1_MSK | SLS_AVALON_USB20_EP_CSR_SML_OK_MSK | SLS_AVALON_USB20_EP_CSR_TR_FR_1_MSK | SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_8_MSK,
										SLS_AVALON_USB20_EP_CSR_EP_TYPE_OUT_MSK | SLS_AVALON_USB20_EP_CSR_TR_TYPE_INTERRUPT_MSK | SLS_AVALON_USB20_EP_CSR_EP_DIS_NORMAL_MSK | SLS_AVALON_USB20_EP_CSR_EP_NO_2_MSK | SLS_AVALON_USB20_EP_CSR_SML_OK_MSK | SLS_AVALON_USB20_EP_CSR_TR_FR_1_MSK | SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_8_MSK,
										0,0,0,0,0,0,0,0,0,0,0,0,0
									}
};

unsigned int ep_buf0_sz_hs_[SUPPORTED_CONF][MAXIMUM_EP_NO] = {
                                    {
                                        (SLS_AVALON_USB20_EP_BUF_USED_MSK | (0x0200 << SLS_AVALON_USB20_EP_BUF_SZ_OFST) | 0x00000100),
                                        ((0x0200 << SLS_AVALON_USB20_EP_BUF_SZ_OFST) | 0x00000100),
                                        0,0,0,0,0,0,0,0,0,0,0,0,0
                                    }
};

unsigned int ep_buf1_sz_hs_[SUPPORTED_CONF][MAXIMUM_EP_NO] = {
                                    {
                                        (SLS_AVALON_USB20_EP_BUF_USED_MSK | (0x0200 << SLS_AVALON_USB20_EP_BUF_SZ_OFST) | 0x00000300),
                                        ((0x0200 << SLS_AVALON_USB20_EP_BUF_SZ_OFST) | 0x00000300),
                                        0,0,0,0,0,0,0,0,0,0,0,0,0
                                    }
};

unsigned int ep_buf0_sz_fs_[SUPPORTED_CONF][MAXIMUM_EP_NO] = {
                                    {
                                        (SLS_AVALON_USB20_EP_BUF_USED_MSK | (0x0040 << SLS_AVALON_USB20_EP_BUF_SZ_OFST) | 0x00000100),
                                        ((0x0040 << SLS_AVALON_USB20_EP_BUF_SZ_OFST) | 0x00000100),
                                        0,0,0,0,0,0,0,0,0,0,0,0,0
                                    }
};

unsigned int ep_buf1_sz_fs_[SUPPORTED_CONF][MAXIMUM_EP_NO] = {
                                    {
                                        (SLS_AVALON_USB20_EP_BUF_USED_MSK|(0x0040 << SLS_AVALON_USB20_EP_BUF_SZ_OFST) | 0x00000300),
                                        ((0x0040 << SLS_AVALON_USB20_EP_BUF_SZ_OFST) | 0x00000300),
                                        0,0,0,0,0,0,0,0,0,0,0,0,0
                                    }
};

unsigned int ep_buf0_sz_ls_[SUPPORTED_CONF][MAXIMUM_EP_NO] = {
                                    {
                                        (SLS_AVALON_USB20_EP_BUF_USED_MSK | (0x08 << SLS_AVALON_USB20_EP_BUF_SZ_OFST) | 0x00000100),
                                        ((0x08 << SLS_AVALON_USB20_EP_BUF_SZ_OFST) | 0x00000100),
                                        0,0,0,0,0,0,0,0,0,0,0,0,0
                                    }
};

unsigned int ep_buf1_sz_ls_[SUPPORTED_CONF][MAXIMUM_EP_NO] = {
                                    {
                                        (SLS_AVALON_USB20_EP_BUF_USED_MSK | (0x08 << SLS_AVALON_USB20_EP_BUF_SZ_OFST) | 0x00000300),
                                        ((0x08 << SLS_AVALON_USB20_EP_BUF_SZ_OFST) | 0x00000300),
                                        0,0,0,0,0,0,0,0,0,0,0,0,0
                                    }
};

unsigned int ep_ip_int_hs[SUPPORTED_CONF][MAXIMUM_EP_NO] = {
                                    {
                                        SLS_AVALON_USB20_EP_IMS_INT_A_ERR_ENABLE_MSK,
                                        SLS_AVALON_USB20_EP_IMS_INT_A_ERR_ENABLE_MSK,
                                        0,0,0,0,0,0,0,0,0,0,0,0,0
                                    }
};

unsigned int ep_ip_int_fs[SUPPORTED_CONF][MAXIMUM_EP_NO] = {
                                    {
                                        SLS_AVALON_USB20_EP_IMS_INT_A_ERR_ENABLE_MSK,
                                        SLS_AVALON_USB20_EP_IMS_INT_A_ERR_ENABLE_MSK,
                                        0,0,0,0,0,0,0,0,0,0,0,0,0
                                    }
};

unsigned int ep_ip_int_ls[SUPPORTED_CONF][MAXIMUM_EP_NO] = {
                                    {
                                        SLS_AVALON_USB20_EP_IMS_INT_A_ERR_ENABLE_MSK,
                                        SLS_AVALON_USB20_EP_IMS_INT_A_ERR_ENABLE_MSK,
                                        0,0,0,0,0,0,0,0,0,0,0,0,0
                                    }
};

#endif /*SLS_EP_CONFIGURATION_H_*/
