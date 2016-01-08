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
 *  Change History :
 *  (v1.2.2)             1> Added SLS_AVALON_USB20_EP_IMS_STATUS_ISO_PKT_LOSS_MSK &
 *                          SLS_AVALON_USB20_EP_IMS_STATUS_ISO_PKT_LOSS_OFST macros
 *                       2> Changed SLS_AVALON_USB20_EP_IMS_INT_ALL_STATUS_ERR_MASK's value
 *                          to 0x000000A7 from 0x00000027
 *                       3> Changed SLS_AVALON_USB20_EP_IMS_INT_STATUS_MSK's value
 *                          to 0x000000FF from 0x0000007F
 *                       4> Added SLS_AVALON_USB20_LOW_SPEED_MODE macro
 *
 *********************************************************************************************/

#ifndef __SLS_AVALON_USB20_REGS_H
#define __SLS_AVALON_USB20_REGS_H

#include "io.h"
#include "HwInterface.h"

#define IORD_SLS_AVALON_USB20_CSR(base)             IORD(base, 4)
#define IOWR_SLS_AVALON_USB20_CSR(base, data)       IOWR(base, 4, data)

#define SLS_USB20_CSR_SP_MODE_MSK                   (0x01)
#define SLS_USB20_CSR_SP_MODE_OFST                  (0)
#define SLS_USB20_CSR_INF_SPEED_MODE_MSK            (0x02)
#define SLS_USB20_CSR_INF_SPEED_OFST                (1)
#define SLS_USB20_CSR_INF_STATUS_MSK                (0x04)
#define SLS_USB20_CSR_INF_STATUS_OFST               (2)
#define SLS_USB20_CSR_UTMI_LN_STATE_MODE_MSK        (0x18)
#define SLS_USB20_CSR_UTMI_LN_STATE_OFST            (3)

#define SLS_AVALON_USB20_FULL_SPEED_MODE            (0)
#define SLS_AVALON_USB20_HIGH_SPEED_MODE            (1)
#define SLS_AVALON_USB20_LOW_SPEED_MODE             (2)

#define IORD_SLS_AVALON_USB20_FA(base)              IORD(base, 1)
#define IOWR_SLS_AVALON_USB20_FA(base, data)        IOWR(base, 1, data)

#define IORD_SLS_AVALON_USB20_INT_MSK(base)         IORD(base, 2)
#define IOWR_SLS_AVALON_USB20_INT_MSK(base, data)   IOWR(base, 2, data)

#define IORD_SLS_AVALON_USB20_SETUP_PCKT_REG1_MSK(base)         IORD(base, 12)
#define IOWR_SLS_AVALON_USB20_SETUP_PCKT_REG1_MSK(base, data)   IOWR(base, 12, data)

#define IORD_SLS_AVALON_USB20_SETUP_PCKT_REG2_MSK(base)         IORD(base, 13)
#define IOWR_SLS_AVALON_USB20_SETUP_PCKT_REG2_MSK(base, data)   IOWR(base, 13, data)

#define SLS_AVALON_USB20_INT_MSK_INT_A              (0x03FF)

#define IORD_SLS_AVALON_USB20_INT_SRC(base)         IORD(base, 3)
#define IOWR_SLS_AVALON_USB20_INT_SRC(base, data)   IOWR(base, 3, data)

#define SLS_AVALON_USB20_INT_SRC_EP0_MSK            (0x01)
#define SLS_AVALON_USB20_INT_SRC_EP0_OFST           (0)
#define SLS_AVALON_USB20_INT_SRC_EP1_MSK            (0x02)
#define SLS_AVALON_USB20_INT_SRC_EP1_OFST           (1)
#define SLS_AVALON_USB20_INT_SRC_EP2_MSK            (0x04)
#define SLS_AVALON_USB20_INT_SRC_EP2_OFST           (2)
#define SLS_AVALON_USB20_INT_SRC_EP3_MSK            (0x08)
#define SLS_AVALON_USB20_INT_SRC_EP3_OFST           (3)
#define SLS_AVALON_USB20_INT_SRC_EP4_MSK            (0x10)
#define SLS_AVALON_USB20_INT_SRC_EP4_OFST           (4)
#define SLS_AVALON_USB20_INT_SRC_EP5_MSK            (0x20)
#define SLS_AVALON_USB20_INT_SRC_EP5_OFST           (5)
#define SLS_AVALON_USB20_INT_SRC_EP6_MSK            (0x40)
#define SLS_AVALON_USB20_INT_SRC_EP6_OFST           (6)
#define SLS_AVALON_USB20_INT_SRC_EP7_MSK            (0x80)
#define SLS_AVALON_USB20_INT_SRC_EP7_OFST           (7)
#define SLS_AVALON_USB20_INT_SRC_EP8_MSK			(0x100)
#define SLS_AVALON_USB20_INT_SRC_EP8_OFST			(8)
#define SLS_AVALON_USB20_INT_SRC_EP9_MSK			(0x200)
#define SLS_AVALON_USB20_INT_SRC_EP9_OFST			(9)
#define SLS_AVALON_USB20_INT_SRC_EP10_MSK			(0x400)
#define SLS_AVALON_USB20_INT_SRC_EP10_OFST			(10)
#define SLS_AVALON_USB20_INT_SRC_EP11_MSK			(0x800)
#define SLS_AVALON_USB20_INT_SRC_EP11_OFST			(11)
#define SLS_AVALON_USB20_INT_SRC_EP12_MSK			(0x1000)
#define SLS_AVALON_USB20_INT_SRC_EP12_OFST			(12)
#define SLS_AVALON_USB20_INT_SRC_EP13_MSK			(0x2000)
#define SLS_AVALON_USB20_INT_SRC_EP13_OFST			(13)
#define SLS_AVALON_USB20_INT_SRC_EP14_MSK			(0x4000)
#define SLS_AVALON_USB20_INT_SRC_EP14_OFST			(14)
#define SLS_AVALON_USB20_INT_SRC_EP15_MSK			(0x8000)
#define SLS_AVALON_USB20_INT_SRC_EP15_OFST			(15)

#define SLS_AVALON_USB20_INT_SRC_BAD_TCKN_MSK        (0x00100000)
#define SLS_AVALON_USB20_INT_SRC_BAD_TCKN_OFST       (20)
#define SLS_AVALON_USB20_INT_SRC_PID_ERR_MSK         (0x00200000)
#define SLS_AVALON_USB20_INT_SRC_PID_ERR_OFST        (21)
#define SLS_AVALON_USB20_INT_SRC_NO_EP_MSK           (0x00400000)
#define SLS_AVALON_USB20_INT_SRC_NO_EP_OFST          (22)
#define SLS_AVALON_USB20_INT_SRC_SUSPEND_MSK         (0x00800000)
#define SLS_AVALON_USB20_INT_SRC_SUSPEND_OFST        (23)
#define SLS_AVALON_USB20_INT_SRC_RESUME_MSK          (0x01000000)
#define SLS_AVALON_USB20_INT_SRC_RESUME_OFST         (24)
#define SLS_AVALON_USB20_INT_SRC_ATTACHED_MSK        (0x02000000)
#define SLS_AVALON_USB20_INT_SRC_ATTACHED_OFST       (25)
#define SLS_AVALON_USB20_INT_SRC_DETACHED_MSK        (0x04000000)
#define SLS_AVALON_USB20_INT_SRC_DETACHED_OFST       (26)
#define SLS_AVALON_USB20_INT_SRC_UTMI_RX_ERR_MSK     (0x08000000)
#define SLS_AVALON_USB20_INT_SRC_UTMI_RX_ERR_OFST    (27)
#define SLS_AVALON_USB20_INT_SRC_USB_RESET_MSK       (0x10000000)
#define SLS_AVALON_USB20_INT_SRC_USB_RESET_OFST      (28)
#define SLS_AVALON_USB20_INT_SRC_USB_SP_NG_DONE_MSK  (0x20000000)
#define SLS_AVALON_USB20_INT_SRC_USB_SP_NG_DONE_OFST (29)

#define IORD_SLS_AVALON_USB20_FRM_NAT(base)         IORD(base, 5)
#define IOWR_SLS_AVALON_USB20_FRM_NAT(base, data)   IOWR(base, 5, data)

#define SLS_AVALON_USB20_FRM_NAT_LST_SOF_TIME_MSK       (0xFFF)
#define SLS_AVALON_USB20_FRM_NAT_LST_SOF_TIME_OFST      (0)
#define SLS_AVALON_USB20_FRM_NAT_FRM_NO_MSK       		(0x7FF0000)
#define SLS_AVALON_USB20_FRM_NAT_FRM_NO_OFST      		(16)
#define SLS_AVALON_USB20_FRM_NAT_NO_CURNT_MCRFRM_MSK    (0xF0000000)
#define SLS_AVALON_USB20_FRM_NAT_NO_CURNT_MCRFRM_OFST   (28)

#define IORD_SLS_AVALON_USB20_UTMI_VEND(base)       IORD(base, 5)
#define IOWR_SLS_AVALON_USB20_UTMI_VEND(base, data) IOWR(base, 5, data)

#define IORD_SLS_AVALON_USB20_EP0_CSR(base)         IORD(base, 16)
#define IOWR_SLS_AVALON_USB20_EP0_CSR(base, data)   IOWR(base, 16, data)

#define IORD_SLS_AVALON_USB20_EP0_INT(base)         IORD(base, 17)
#define IOWR_SLS_AVALON_USB20_EP0_INT(base, data)   IOWR(base, 17, data)

#define IORD_SLS_AVALON_USB20_EP0_BUF0(base)        IORD(base, 18)
#define IOWR_SLS_AVALON_USB20_EP0_BUF0(base, data)  IOWR(base, 18, data)

#define IORD_SLS_AVALON_USB20_EP0_BUF1(base)        IORD(base, 19)
#define IOWR_SLS_AVALON_USB20_EP0_BUF1(base, data)  IOWR(base, 19, data)

#define IORD_SLS_AVALON_USB20_EP1_CSR(base)         IORD(base, 20)
#define IOWR_SLS_AVALON_USB20_EP1_CSR(base, data)   IOWR(base, 20, data)

#define IORD_SLS_AVALON_USB20_EP1_INT(base)         IORD(base, 21)
#define IOWR_SLS_AVALON_USB20_EP1_INT(base, data)   IOWR(base, 21, data)

#define IORD_SLS_AVALON_USB20_EP1_BUF0(base)        IORD(base, 22)
#define IOWR_SLS_AVALON_USB20_EP1_BUF0(base, data)  IOWR(base, 22, data)

#define IORD_SLS_AVALON_USB20_EP1_BUF1(base)        IORD(base, 23)
#define IOWR_SLS_AVALON_USB20_EP1_BUF1(base, data)  IOWR(base, 23, data)

#define IORD_SLS_AVALON_USB20_EP2_CSR(base)         IORD(base, 24)
#define IOWR_SLS_AVALON_USB20_EP2_CSR(base, data)   IOWR(base, 24, data)

#define IORD_SLS_AVALON_USB20_EP2_INT(base)         IORD(base, 25)
#define IOWR_SLS_AVALON_USB20_EP2_INT(base, data)   IOWR(base, 25, data)

#define IORD_SLS_AVALON_USB20_EP2_BUF0(base)        IORD(base, 26)
#define IOWR_SLS_AVALON_USB20_EP2_BUF0(base, data)  IOWR(base, 26, data)

#define IORD_SLS_AVALON_USB20_EP2_BUF1(base)        IORD(base, 27)
#define IOWR_SLS_AVALON_USB20_EP2_BUF1(base, data)  IOWR(base, 27, data)

#define IORD_SLS_AVALON_USB20_EP3_CSR(base)         IORD(base, 28)
#define IOWR_SLS_AVALON_USB20_EP3_CSR(base, data)   IOWR(base, 28, data)

#define IORD_SLS_AVALON_USB20_EP3_INT(base)         IORD(base, 29)
#define IOWR_SLS_AVALON_USB20_EP3_INT(base, data)   IOWR(base, 29, data)

#define IORD_SLS_AVALON_USB20_EP3_BUF0(base)        IORD(base, 30)
#define IOWR_SLS_AVALON_USB20_EP3_BUF0(base, data)  IOWR(base, 30, data)

#define IORD_SLS_AVALON_USB20_EP3_BUF1(base)        IORD(base, 31)
#define IOWR_SLS_AVALON_USB20_EP3_BUF1(base, data)  IOWR(base, 31, data)

#define SLS_AVALON_USB20_CNCT_OFST						(0x1FC)
#define SLS_AVALON_USB20_CNCT_VAL						(0x01)
#define SLS_AVALON_USB20_DSCNCT_VAL                     (0x00)

#define SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_MSK            (0x7FF)
#define SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_OFST           (0)
#define SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_0_MSK          (0x00)
#define SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_8_MSK          (0x08)
#define SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_24_MSK         (0x18)
#define SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_64_MSK         (0x40)
#define SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_128_MSK        (0x80)
#define SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_130_MSK        (0x82)
#define SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_256_MSK 		 (0x100)
#define SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_512_MSK		 (0x200)
#define SLS_AVALON_USB20_EP_CSR_MAX_PL_SZ_1024_MSK		 (0x400)

#define SLS_AVALON_USB20_EP_CSR_TR_FR_MSK                (0x1800)
#define SLS_AVALON_USB20_EP_CSR_TR_FR_OFST               (11)
#define SLS_AVALON_USB20_EP_CSR_TR_FR_0_MSK              (0x0000)
#define SLS_AVALON_USB20_EP_CSR_TR_FR_1_MSK              (0x0800)
#define SLS_AVALON_USB20_EP_CSR_TR_FR_2_MSK              (0x1000)
#define SLS_AVALON_USB20_EP_CSR_TR_FR_3_MSK              (0x1800)

#define SLS_AVALON_USB20_EP_CSR_OTS_STOP_MSK             (0x2000)
#define SLS_AVALON_USB20_EP_CSR_OTS_STOP_OFST            (13)
#define SLS_AVALON_USB20_EP_CSR_DMAEN_MSK                (0x8000)
#define SLS_AVALON_USB20_EP_CSR_DMAEN_OFST               (15)
#define SLS_AVALON_USB20_EP_CSR_SML_OK_MSK             	 (0x10000)
#define SLS_AVALON_USB20_EP_CSR_SML_OK_OFST              (16)
#define SLS_AVALON_USB20_EP_CSR_LRG_OK_MSK               (0x20000)
#define SLS_AVALON_USB20_EP_CSR_LRG_OK_OFST              (17)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_MSK                (0x3C0000)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_OFST               (18)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_0_MSK              (0x000000)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_1_MSK              (0x040000)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_2_MSK              (0x080000)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_3_MSK              (0x0C0000)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_4_MSK              (0x100000)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_5_MSK              (0x140000)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_6_MSK              (0x180000)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_7_MSK              (0x1C0000)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_8_MSK              (0x200000)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_9_MSK              (0x240000)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_10_MSK             (0x280000)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_11_MSK             (0x2C0000)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_12_MSK             (0x300000)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_13_MSK             (0x340000)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_14_MSK             (0x380000)
#define SLS_AVALON_USB20_EP_CSR_EP_NO_15_MSK             (0x3C0000)
#define SLS_AVALON_USB20_EP_CSR_EP_DIS_MSK               (0xC00000)
#define SLS_AVALON_USB20_EP_CSR_ALL_EP_MSK               (0x0000FFFE)
#define SLS_AVALON_USB20_EP_CSR_EP_DIS_OFST              (22)
#define SLS_AVALON_USB20_EP_CSR_EP_DIS_NORMAL_MSK        (0x000000)
#define SLS_AVALON_USB20_EP_CSR_EP_DIS_ING_TRF_MSK       (0x400000)
#define SLS_AVALON_USB20_EP_CSR_EP_DIS__HLT_ST_MSK       (0x800000)
#define SLS_AVALON_USB20_EP_CSR_TR_TYPE_MSK              (0x3000000)
#define SLS_AVALON_USB20_EP_CSR_TR_TYPE_OFST             (24)
#define SLS_AVALON_USB20_EP_CSR_TR_TYPE_INTERRUPT_MSK    (0x0000000)
#define SLS_AVALON_USB20_EP_CSR_TR_TYPE_ISO_MSK          (0x1000000)
#define SLS_AVALON_USB20_EP_CSR_TR_TYPE_BULK_MSK         (0x2000000)
#define SLS_AVALON_USB20_EP_CSR_TR_TYPE_CONTROL_MSK      (0x3000000)
#define SLS_AVALON_USB20_EP_CSR_EP_TYPE_MSK              (0xC000000)
#define SLS_AVALON_USB20_EP_CSR_EP_TYPE_OFST             (26)
#define SLS_AVALON_USB20_EP_CSR_EP_TYPE_CONTROL_MSK      (0x0000000)
#define SLS_AVALON_USB20_EP_CSR_EP_TYPE_IN_MSK           (0x4000000)
#define SLS_AVALON_USB20_EP_CSR_EP_TYPE_OUT_MSK          (0x8000000)
#define SLS_AVALON_USB20_EP_CSR_UC_DPD_MSK               (0x30000000)
#define SLS_AVALON_USB20_EP_CSR_UC_DPD_OFST              (28)
#define SLS_AVALON_USB20_EP_CSR_UC_DPD_DATA0_MSK         (0x00000000)
#define SLS_AVALON_USB20_EP_CSR_UC_DPD_DATA1_MSK         (0x10000000)
#define SLS_AVALON_USB20_EP_CSR_UC_BSEL_MSK              (0xC0000000)
#define SLS_AVALON_USB20_EP_CSR_UC_BSEL_OFST             (30)

#define SLS_AVALON_USB20_EP_CSR_UC_BSEL_BUF0_MSK         (0x00000000)
#define SLS_AVALON_USB20_EP_CSR_UC_BSEL_BUF1_MSK         (0x40000000)

#define SLS_AVALON_USB20_EP_IMS_STATUS_TIME_OUT_MSK                 (0x01)
#define SLS_AVALON_USB20_EP_IMS_STATUS_TIME_OUT_OFST		    	(0)
#define SLS_AVALON_USB20_EP_IMS_STATUS_BAD_PCK_MSK                  (0x02)
#define SLS_AVALON_USB20_EP_IMS_STATUS_BAD_PCK_OFST			        (1)
#define SLS_AVALON_USB20_EP_IMS_STATUS_UNSPRTED_PID_MSK             (0x04)
#define SLS_AVALON_USB20_EP_IMS_STATUS_UNSPRTED_PID_OFST	    	(2)
#define SLS_AVALON_USB20_EP_IMS_STATUS_BUF0_FE_MSK                  (0x00000008)
#define SLS_AVALON_USB20_EP_IMS_STATUS_BUF0_FE_OFST			        (3)
#define SLS_AVALON_USB20_EP_IMS_STATUS_BUF1_FE_MSK                  (0x00000010)
#define SLS_AVALON_USB20_EP_IMS_STATUS_BUF1_FE_OFST			        (4)
#define SLS_AVALON_USB20_EP_IMS_STATUS_PID_SEQ_ERR_MSK              (0x20)
#define SLS_AVALON_USB20_EP_IMS_STATUS_PID_SEQ_ERR_OFST			    (5)
#define SLS_AVALON_USB20_EP_IMS_STATUS_ISO_PKT_LOSS_MSK             (0x80)
#define SLS_AVALON_USB20_EP_IMS_STATUS_ISO_PKT_LOSS_OFST			(7)
#define SLS_AVALON_USB20_EP_IMS_STATUS_OUT_PCK_SMALL_M_P_SIZE_MSK   (0x40)
#define SLS_AVALON_USB20_EP_IMS_STATUS_OUT_PCK_SMALL_M_P_SIZE_OFST	(6)
#define SLS_AVALON_USB20_EP_IMS_INT_A_ERR_ENABLE_MSK                (0x37000000)
#define SLS_AVALON_USB20_EP_IMS_INT_A_ENABLE_MSK                    (0x3F000000)
#define SLS_AVALON_USB20_EP_IMS_INT_A_DISABLE_MSK                   (0x00000000)
#define SLS_AVALON_USB20_EP_IMS_INT_A_ENABLE_OFST		    	    (24)
#define SLS_AVALON_USB20_EP_IMS_INT_B_ENABLE_MSK                    (0x003F0000)
#define SLS_AVALON_USB20_EP_IMS_INT_B_ENABLE_OFST		    	    (16)
#define SLS_AVALON_USB20_EP_IMS_INT_STATUS_MSK                      (0x000000FF)
#define SLS_AVALON_USB20_EP_IMS_INT_STATUS_OFST                     (0)
#define SLS_AVALON_USB20_EP_IMS_INT_SETUP_PACKET_RECV_MASK          (0x00000040)
#define SLS_AVALON_USB20_EP_IMS_INT_STATUSPACKET_RECV_OFST          (6)
#define SLS_AVALON_USB20_EP_IMS_INT_ALL_ENABLE_ERR_MASK             (0x17000000)
#define SLS_AVALON_USB20_EP_IMS_INT_ALL_STATUS_ERR_MASK             (0x000000A7)
#define SLS_TEST_MODE_REG                                           (0x20)
#define SLS_TEST_MODE_VALUE                                         (0x02)
#define SLS_TEST_MODE_SET_MASK                                      (0x10)
#define SLS_TEST_MODE_SET_OFFSET                                    (5)
#define SLS_TEST_MODE_TEST_J_MASK                                   (0x01)
#define SLS_TEST_MODE_TEST_J_OFFSET                                 (1)
#define SLS_TEST_MODE_TEST_K_MASK                                   (0x02)
#define SLS_TEST_MODE_TEST_K_OFFSET                                 (2)
#define SLS_TEST_MODE_TEST_SE0_NAK_MASK                             (0x04)
#define SLS_TEST_MODE_TEST_SE0_NAK_OFFSET                           (3)
#define SLS_TEST_MODE_TEST_PACKET_MASK                              (0x08)
#define SLS_TEST_MODE_TEST_PACKET_OFFSET                            (4)

/* Buffer offset in USB2.0 IP. To get exact address of buffer, add buffer offset to USB2.0 base */
#define SLS_AVALON_USB20_BUFFER_OFFSET                        		(0x00020000)

#define IORD_SLS_AVALON_USB20_EP_BUF_DATA(base,offset)              PARENT_BUS_IORD_32(base, (SLS_AVALON_USB20_BUFFER_OFFSET + offset))
#define IORD_8_SLS_AVALON_USB20_EP_BUF_DATA(base,offset)            PARENT_BUS_IORD_8(base, (SLS_AVALON_USB20_BUFFER_OFFSET + offset))
#define IOWR_SLS_AVALON_USB20_EP_BUF_DATA(base,offset,data)         PARENT_BUS_IOWR_32(base, (SLS_AVALON_USB20_BUFFER_OFFSET + offset), data)

#define SLS_AVALON_USB20_EP_BUF_PTR_MSK             (0x1FFFF)
#define SLS_AVALON_USB20_EP_BUF_PTR_OFST		    (0)
#define SLS_AVALON_USB20_EP_BUF_SZ_MSK              (0x7FFE0000)
#define SLS_AVALON_USB20_EP_BUF_SZ_OFST		    	(17)
#define SLS_AVALON_USB20_EP_BUF_USED_MSK            (0x80000000)
#define SLS_AVALON_USB20_EP_BUF_USED_OFST		    (31)
#define SLS_AVALON_USB20_EP_BUF_DISABLE             (0x7FFFFFFF)
#define SLS_AVALON_USB20_EP_BUF_WITHOUT_USED_MSK    (0x7FFF0000)

//Speed selection register value - bit value is 1(default value) if HS and bit value is 0 if FS
#define USBSR_SPEED_CONFIG_REG                      (0x1F8)
#define USBSR_HS_CONFIG                             (0x01)
#define USBSR_FS_CONFIG                             (0x00)
#define USBSR_NS_CONFIG                             -(0x01)   //NS = No speed selection means device not configured in any speed due to speed negotiation not done

//ULPI PHY chip register access
#define USBSR_PHY_CS                                (0x1F0)
#define USBSR_PHY_READ_ENABLE_OFST                  (25)
#define USBSR_PHY_READ_ENABLE_MSK                   (0x002000000)
#define USBSR_PHY_WRITE_ENABLE_OFST                 (24)
#define USBSR_PHY_WRITE_ENABLE_MSK                  (0x001000000)
#define USBSR_PHY_READ_DATA_OFST                    (16)
#define USBSR_PHY_READ_DATA_MSK                     (0x00FF0000)
#define USBSR_PHY_WRITE_DATA_OFST                   (8)
#define USBSR_PHY_WRITE_DATA_MSK                    (0x0000FF00)
#define USBSR_PHY_REG_ADDRESS_OFST                  (0)
#define USBSR_PHY_REG_ADDRESS_MSK                   (0x0000003F)

#define IORD_ULPI_PHY_REG(base)                     PARENT_BUS_IORD_32(base, 0x1F4)
#define IOWR_ULPI_PHY_REG(base,data)                PARENT_BUS_IOWR_32(base, 0x1F4)

#endif
