/*********************************************************************************************
 *  SLS SD Host Controller Driver
 *
 *  Copyright (C) 2008  SLS, All Rights Reserved.
 *
 *  History:
 *      v1.0.0  : Nov 08   - SLS: SDHC IP - Core v2.3
 *      v2.0.0  : Jan 09   - SLS: SDHC IP - Core v2.4 and Quartus II 8.1
 *      v3.0.0  : April    - SLS: - Updated as per SDHC IP - Core v2.5
 *                                - Added speed selection API to select SD Card speed.
 *                                - Added and changed some APIs. So,user can also develop
 *									his own stack on top SLS IP.
 *      v3.0.1  : April 13 - SLS: - Added SDIO support
 *								  - Divided whole driver into two file.
 *      v3.0.2  : April 22, 2011  - Fixed block number issue when Block size is changed.
 *      v4.0.0  : August 16,2014  - Added eMMC support
 *********************************************************************************************/

#include <alt_types.h>

#ifndef __SLS_AVALON_SD_HOST_REGS_H__
#define __SLS_AVALON_SD_HOST_REGS_H__

/* IDE Slave I/O RD/WR/ADDR macros */
#define IORD_SLS_AVALON_SD_HOST_COMMAND_ARG(base)               IORD(base, 0)
#define IOWR_SLS_AVALON_SD_HOST_COMMAND_ARG(base,data)          IOWR(base, 0,data)

#define IORD_SLS_AVALON_SD_HOST_COMMAND_CNT(base)               IORD(base, 1)
#define IOWR_SLS_AVALON_SD_HOST_COMMAND_CNT(base, data)         IOWR(base, 1, data)

#define IORD_SLS_AVALON_SD_HOST_CONTROL(base)                   IORD(base, 2)
#define IOWR_SLS_AVALON_SD_HOST_CONTROL(base, data)             IOWR(base, 2, data)

#define IORD_SLS_AVALON_SD_HOST_BLOCK_LENGTH(base)              IORD(base, 3)
#define IOWR_SLS_AVALON_SD_HOST_BLOCK_LENGTH(base, data)        IOWR(base, 3, data)

#define IORD_SLS_AVALON_SD_HOST_DMA_LENGTH(base)                IORD(base, 4)
#define IOWR_SLS_AVALON_SD_HOST_DMA_LENGTH(base, data)          IOWR(base, 4, data)

#define IORD_SLS_AVALON_SD_HOST_DMA_ADDR(base)                  IORD(base, 5)
#define IOWR_SLS_AVALON_SD_HOST_DMA_ADDR(base, data)            IOWR(base, 5, data)

#define IORD_SLS_AVALON_SD_HOST_INT_CNTR(base)                  IORD(base, 6)
#define IOWR_SLS_AVALON_SD_HOST_INT_CNTR(base, data)            IOWR(base, 6, data)

#define IORD_SLS_AVALON_SD_HOST_STATUS(base)                    IORD(base, 7)
#define IOWR_SLS_AVALON_SD_HOST_STATUS(base, data)              IOWR(base, 7, data)

#define IOWR_SLS_AVALON_SD_HOST_TX_DATA_TIMEOUT(base, data)     IOWR(base, 8, data)
#define IORD_SLS_AVALON_SD_HOST_INT_SOURCE(base)                IORD(base, 0x8)

#define IOWR_SLS_AVALON_SD_HOST_RX_DATA_TIMEOUT(base, data)     IOWR(base, 9, data)

#define IOWR_SLS_AVALON_SD_HOST_CMD_DATA_TIMEOUT(base, data)    IOWR(base, 0xa, data)

#define IORD_SLS_AVALON_SD_HOST_RESPONSE1(base)                 IORD(base, 0xb)

#define IORD_SLS_AVALON_SD_HOST_RESPONSE2(base)                 IORD(base, 0xc)

#define IORD_SLS_AVALON_SD_HOST_RESPONSE3(base)                 IORD(base, 0xd)

#define IORD_SLS_AVALON_SD_HOST_RESPONSE4(base)                 IORD(base, 0xe)

#define IORD_SLS_AVALON_SD_HOST_RESPONSE5(base)                 IORD(base, 0xf)

//#define SD_EMMC_VOLTAGE_SWITCH

/* Command Control Register */
#define SLS_AVALON_SD_HOST_COMMAND_CNT_TX_EN                    (0x1)
#define SLS_AVALON_SD_HOST_COMMAND_CNT_RX_EN                    (0x2)
#define SLS_AVALON_SD_HOST_COMMAND_CNT_CMD_EN                   (0x4)
#define SLS_AVALON_SD_HOST_COMMAND_EMMC_IRQ_ABORT               (0x8)
#define SLS_AVALON_SD_HOST_COMMAND_DMA_WR_START                 (0x20)
#define SLS_AVALON_SD_HOST_COMMAND_DMA_RD_START                 (0x40)
#define SLS_AVALON_SD_HOST_COMMAND_EMMC_RST_START               (0x80)
#define SLS_AVALON_SD_HOST_COMMAND_EMMC_BOOT_START              (0x100)
#define SLS_AVALON_SD_HOST_COMMAND_EMMC_RESP_EN                 (0x200)
#define SLS_AVALON_SD_HOST_COMMAND_CNT_INDEX(index)             (((index)& 0x3F)<< 10)
#define SLS_AVALON_SD_HOST_COMMAND_CMD_TYPE(index)              (((index)& 0x7) << 16)
#define SLS_AVALON_SD_HOST_COMMAND_CNT_RESP_TYPE(response)      ((response & 0x7)<<19)   //KA

/* IP Control Register */
#define SLS_AVALON_SD_HOST_CONTROL_PRESCALE(prescale)           (prescale & 0xFF)
#define SLS_AVALON_SD_HOST_CONTROL_SD_BUS(bus)                  ((bus & 0x1)<<8)
#define SLS_AVALON_SD_HOST_CONTROL_EMMC_BUS(bus)                ((bus & 0x1)<<11) //KA
#define SLS_AVALON_SD_HOST_CONTROL_DMA_EN                       (0x200)
#define SLS_AVALON_SD_HOST_CONTROL_SOFT_RESET                   (0x4000)
#define SLS_AVALON_SD_HOST_CONTROL_CORE_EN                      (0x8000)
#define SLS_AVALON_SD_HOST_CONTROL_DDR_MODE(ddr_mode)           ((ddr_mode & 0x1) << 10)



/* Interrupt Control Register */
#define SLS_AVALON_SD_HOST_INT_CNT_TX_COMPLETE_MASK             (0x1)
#define SLS_AVALON_SD_HOST_INT_CNT_RX_COMPLETE_MASK             (0x2)
#define SLS_AVALON_SD_HOST_INT_CNT_CMD_COMPLETE_MASK            (0x4)
#define SLS_AVALON_SD_HOST_INT_CNT_TX_CRC_ERR_MASK              (0x8)
#define SLS_AVALON_SD_HOST_INT_CNT_RX_CRC_ERR_MASK              (0x10)
#define SLS_AVALON_SD_HOST_INT_CNT_CMD_RESP_CRC_ERR_MASK        (0x20)
#define SLS_AVALON_SD_HOST_INT_CNT_TX_TIMEOUT_MASK              (0x40)
#define SLS_AVALON_SD_HOST_INT_CNT_RX_TIMEOUT_MASK              (0x80)
#define SLS_AVALON_SD_HOST_INT_CNT_CMD_TIMEOUT_MASK             (0x100)
#define SLS_AVALON_SD_HOST_INT_CNT_DMA_COMPLETE_MASK            (0x200)
#define SLS_AVALON_SD_HOST_INT_CNT_CARD_INSERT_MASK             (0x400)
#define SLS_AVALON_SD_HOST_INT_CNT_GLOBAL_INT_MASK              (0x800)
#define SLS_AVALON_SD_HOST_INT_CNT_INT_CLEAR                    (0x1000)

/* Interrupt Source Register */
#define SLS_AVALON_SD_HOST_INT_TX_COMPLETE                      (0x1)
#define SLS_AVALON_SD_HOST_INT_RX_COMPLETE                      (0x2)
#define SLS_AVALON_SD_HOST_INT_CMD_COMPLETE                     (0x4)
#define SLS_AVALON_SD_HOST_INT_TX_CRC_ERR                       (0x8)
#define SLS_AVALON_SD_HOST_INT_RX_CRC_ERR                       (0x10)
#define SLS_AVALON_SD_HOST_INT_CMD_RESP_CRC_ERR                 (0x20)
#define SLS_AVALON_SD_HOST_INT_TX_TIMEOUT                       (0x40)
#define SLS_AVALON_SD_HOST_INT_RX_TIMEOUT                       (0x80)
#define SLS_AVALON_SD_HOST_INT_CMD_TIMEOUT                      (0x100)
#define SLS_AVALON_SD_HOST_INT_DMA_COMPLETE                     (0x200)
#define SLS_AVALON_SD_HOST_INT_CARD_INSERT                      (0x400)

/* Status Register */
#define SLS_AVALON_SD_HOST_STATUS_TX_COMPLETE                   (0x1)
#define SLS_AVALON_SD_HOST_STATUS_RX_COMPLETE                   (0x2)
#define SLS_AVALON_SD_HOST_STATUS_CMD_COMPLETE                  (0x4)
#define SLS_AVALON_SD_HOST_STATUS_TX_CRC_ERR                    (0x8)
#define SLS_AVALON_SD_HOST_STATUS_RX_CRC_ERR                    (0x10)
#define SLS_AVALON_SD_HOST_STATUS_CMD_RESP_CRC_ERR              (0x20)
#define SLS_AVALON_SD_HOST_STATUS_TX_TIMEOUT                    (0x40)
#define SLS_AVALON_SD_HOST_STATUS_RX_TIMEOUT                    (0x80)
#define SLS_AVALON_SD_HOST_STATUS_CMD_TIMEOUT                   (0x100)
#define SLS_AVALON_SD_HOST_STATUS_DMA_COMPLETE                  (0x200)
#define SLS_AVALON_SD_HOST_STATUS_RX_FIFO_FULL                  (0x400)
#define SLS_AVALON_SD_HOST_STATUS_RX_FIFO_EMPTY                 (0x800)
#define SLS_AVALON_SD_HOST_STATUS_TX_FIFO_FULL                  (0x1000)
#define SLS_AVALON_SD_HOST_STATUS_TX_FIFO_EMPTY                 (0x2000)
#define SLS_AVALON_SD_HOST_STATUS_CARD_INSERT                   (0x4000)
#define SLS_AVALON_SD_HOST_STATUS_WRITE_PROTECT                 (0x8000)
#define SLS_AVALON_SD_HOST_STATUS_CARD_BUSY                     (0x10000)

/* System Specific Information */
#define SLS_SD_HOST_BUS_1BIT_BUS                                0
#define SLS_SD_HOST_BUS_4BIT_BUS                                1
#define SLS_EMMC_HOST_BUS_8BIT_BUS                              2  //KA
#define SLS_EMMC_HOST_BUS_4BIT_DDR_BUS                          3  //KA
#define SLS_EMMC_HOST_BUS_8BIT_DDR_BUS                          4  //KA

#define SLS_SD_HOST_RX_TIMEOUT_INIT                             (0xFFFF)
#define SLS_SD_HOST_TX_TIMEOUT_INIT                             (0xFFFF)
#define SLS_SD_HOST_CMD_TIMEOUT_INIT                            (0xFFFF)

#define SLS_SD_HOST_RX_TIMEOUT                                  (0xFFFFFF0)
#define SLS_SD_HOST_TX_TIMEOUT                                  (0xFFFFF0)
#define SLS_SD_HOST_CMD_TIMEOUT                                 (0xFFFFF0)

#define SLS_SD_NOT_PRESENT                                      0
#define SLS_SD_IS_PRESENT                                       1

#define SLS_SD_IS_NOT_WRITEPROTECED                             0
#define SLS_SD_IS_WRITEPROTECED                                 1

#define SLS_SD_READ_DIS                                         0
#define SLS_SD_READ_EN                                          1

#define SUCCESS                                                 0

#define SLS_PRINTF_ALL_MESSAGE                                  0
#define SLS_PRINTF_ERROR_MESSAGE                                1
#define SLS_PRINTF_NO_MESSAGE                                   2

/*Error code*/
#define E_FAIL                                                  -10

#define E_CMD                                                   -13
#define E_NO_SUPPORT                                            -15

#define E_CMD_CRC_ERROR                                         -16
#define E_CMD_RESPONSE_TIMEOUT                                  -17

#define E_WRITE_CRC_ERROR                                       -18
#define E_WRITE_TIMEOUT                                         -19

#define E_READ_CRC_ERROR                                        -20
#define E_READ_TIMEOUT                                          -21

#define CARD_TYPE_SD     0   /* SD card     */
#define CARD_TYPE_SDIO   1   /* SDIO card   */
#define CARD_TYPE_COMBO  2   /* COMBO card  */
#define CARD_TYPE_EMMC   3   /*  EMMC       */

#define SD_VDD_165_195 0x00000080  /* VDD voltage 1.65 - 1.95 */
#define SD_VDD_20_21   0x00000100  /* VDD voltage 2.0 ~ 2.1 */
#define SD_VDD_21_22   0x00000200  /* VDD voltage 2.1 ~ 2.2 */
#define SD_VDD_22_23   0x00000400  /* VDD voltage 2.2 ~ 2.3 */
#define SD_VDD_23_24   0x00000800  /* VDD voltage 2.3 ~ 2.4 */
#define SD_VDD_24_25   0x00001000  /* VDD voltage 2.4 ~ 2.5 */
#define SD_VDD_25_26   0x00002000  /* VDD voltage 2.5 ~ 2.6 */
#define SD_VDD_26_27   0x00004000  /* VDD voltage 2.6 ~ 2.7 */
#define SD_VDD_27_28   0x00008000  /* VDD voltage 2.7 ~ 2.8 */
#define SD_VDD_28_29   0x00010000  /* VDD voltage 2.8 ~ 2.9 */
#define SD_VDD_29_30   0x00020000  /* VDD voltage 2.9 ~ 3.0 */
#define SD_VDD_30_31   0x00040000  /* VDD voltage 3.0 ~ 3.1 */
#define SD_VDD_31_32   0x00080000  /* VDD voltage 3.1 ~ 3.2 */
#define SD_VDD_32_33   0x00100000  /* VDD voltage 3.2 ~ 3.3 */
#define SD_VDD_33_34   0x00200000  /* VDD voltage 3.3 ~ 3.4 */
#define SD_VDD_34_35   0x00400000  /* VDD voltage 3.4 ~ 3.5 */
#define SD_VDD_35_36   0x00800000  /* VDD voltage 3.5 ~ 3.6 */

#define SLS_SD_VDD_SUPPORT  ( SD_VDD_27_28 | SD_VDD_28_29 | SD_VDD_29_30 |      \
                              SD_VDD_30_31 | SD_VDD_31_32 | SD_VDD_32_33 |      \
                              SD_VDD_33_34 | SD_VDD_34_35 | SD_VDD_35_36 )

/* SD IP Response type */
#define SLS_SD_HOST_NO_RESPONSE            0
#define SLS_SD_HOST_48B_RESPONSE           1   /* R1 , R3(OCR) ,R6,R7 */
#define SLS_SD_HOST_136B_RESPONSE          2   /* R2(CSD,CID) */
#define SLS_SD_EMMC_HOST_48B_BUSY_RESPONSE 3   /*R1b KA*/
#define SLS_EMMC_HOST_DAT0_RESPONSE        4   //KA - Used in eMMC alternative boot operation mode.

/* Standard SD commands (4.1)           type  argument     response */

/* class 1 */
#define SD_GO_IDLE_STATE         0   /* bc                          */
#define SD_SEND_OP_COND          1   /* bcr  [31:0] OCR         R3  */
#define SD_ALL_SEND_CID          2   /* bcr                     R2  */
#define SD_SET_RELATIVE_ADDR     3   /* ac   [31:16] RCA        R1  */
#define SD_SET_DSR               4   /* bc   [31:16] RCA            */

#define SD_SWITCH                6   /* ac   [31:0] See below   R1b */
#define SD_SELECT_CARD           7   /* ac   [31:16] RCA        R1  */
#define SD_SEND_EXT_CSD          8   /* ad                      R7  */
#define SD_SEND_CSD              9   /* ac   [31:16] RCA        R2  */
#define SD_SEND_CID             10   /* ac   [31:16] RCA        R2  */
#define SD_READ_DAT_UNTIL_STOP  11   /* adtc [31:0] dadr        R1  */
#define SD_STOP_TRANSMISSION    12   /* ac                      R1b */
#define SD_SEND_STATUS          13   /* ac   [31:16] RCA        R1  */
#define SD_GO_INACTIVE_STATE    15   /* ac   [31:16] RCA            */
#define SD_SPI_READ_OCR         58   /* spi                  spi_R3 */
#define SD_SPI_CRC_ON_OFF       59   /* spi  [0:0] flag      spi_R1 */
#define SD_VOLTAGE_SWITCH       11   /* spi  [0:0] flag      spi_R1 */

/* class 2 */
#define SD_SET_BLOCKLEN         16   /* ac   [31:0] block len   R1  */
#define SD_READ_SINGLE_BLOCK    17   /* adtc [31:0] data addr   R1  */
#define SD_READ_MULTIPLE_BLOCK  18   /* adtc [31:0] data addr   R1  */

/* class 3 */
#define SD_WRITE_DAT_UNTIL_STOP 20   /* adtc [31:0] data addr   R1  */

/* class 4 */
#define SD_SET_BLOCK_COUNT      23   /* adtc [31:0] data addr   R1  */
#define SD_WRITE_BLOCK          24   /* adtc [31:0] data addr   R1  */
#define SD_WRITE_MULTIPLE_BLOCK 25   /* adtc                    R1  */
#define SD_PROGRAM_CID          26   /* adtc                    R1  */
#define SD_PROGRAM_CSD          27   /* adtc                    R1  */

/* class 6 */
#define SD_SET_WRITE_PROT       28   /* ac   [31:0] data addr   R1b */
#define SD_CLR_WRITE_PROT       29   /* ac   [31:0] data addr   R1b */
#define SD_SEND_WRITE_PROT      30   /* adtc [31:0] wpdata addr R1  */

/* class 5 */
#define SD_ERASE_GROUP_START    35   /* ac   [31:0] data addr   R1  */
#define SD_ERASE_GROUP_END      36   /* ac   [31:0] data addr   R1  */
#define SD_ERASE                38   /* ac                      R1b */

/* class 9 */
#define SD_FAST_IO              39   /* ac   <Complex>          R4  */
#define SD_GO_IRQ_STATE         40   /* bcr                     R5  */

/* class 7 */
#define SD_LOCK_UNLOCK          42   /* adtc                    R1b */

/* class 8 */
#define SD_APP_CMD              55   /* ac   [31:16] RCA        R1  */
#define SD_GEN_CMD              56   /* adtc [0] RD/WR          R1  */

/* Application commands */
#define SD_APP_SET_BUS_WIDTH     6   /* ac   [1:0] bus width    R1  */
#define SD_APP_SEND_NUM_WR_BLKS 22   /* adtc                    R1  */
#define SD_APP_OP_COND          41   /* bcr  [31:0] OCR         R3  */
#define SD_APP_SEND_SCR         51   /* adtc                    R1  */

/* SDIO card commands */
#define SD_GET_OCR_SDIO          5   /* bcr                     R2  */
#define IO_RD_WR_DIRECT         52   /*                         R5  */
#define IO_RD_WR_EXTENDED       53

#define SLS_EMMC_HIGH_VOLTAGE_ARG           0x40FF8000 //KA
#define SLS_EMMC_DUAL_VOLTAGE_ARG           0x40FF8080 //KA
#define SLS_EMMC_DUAL_VOLTAGE_RES           0xC0FF8080 //KA
#define SLS_EMMC_HIGH_VOLTAGE_RES           0xC0FF8000 //KA
#define OCR_BUSY                            0x80000000 //KA
#define HIGHSPEED_MODE                      0x03b90100 //KA
#define EMMC_4BIT_MODE                      0x03b70100 //KA
#define EMMC_8BIT_MODE                      0x03b70200 //KA
#define EMMC_4BIT_DDR_MODE                  0x03b70500 //KA
#define EMMC_8BIT_DDR_MODE                  0x03b70600 //KA
#define HIGH_SPEED_EMMC_26MHz               0          //KA
#define HIGH_SPEED_EMMC_52MHz               1          //KA
#define HIGH_SPEED_DDR_EMMC_52MHz_18V_OR_3V 2          //KA
#define HIGH_SPEED_DDR_EMMC_52MHz_12V       3          //KA
#define SPEC_VERSION_SUPPORT_HIGH_SPEED     4          //KA
#define BYTE_MODE                           0x00000000 //KA
#define SECTOR_MODE                         0x40000000 //KA

#define NORMAL_CMD                          0x0
#define SD_VOLTAGE_SWITCH_CMD               0x1
#define EMMC_SLEEP_AWAKE_CMD                0x2
#define EMMC_GO_IRQ_STATE_CMD               0x3


/*
 * SD_SWITCH argument format:
 *
 *      [31] Check (0) or switch (1)
 *      [30:24] Reserved (0)
 *      [23:20] Function group 6
 *      [19:16] Function group 5
 *      [15:12] Function group 4
 *      [11:8]  Function group 3
 *      [7:4]   Function group 2
 *      [3:0]   Function group 1
 */

struct sd_cid {
  unsigned int    manfid;
  char            prod_name[8];
  unsigned int    serial;
  unsigned short  oemid;
  unsigned short  year;
  unsigned char   hwrev;
  unsigned char   fwrev;
  unsigned char   month;
};

struct sd_csd {
  unsigned char   mmca_vsn;
  unsigned short  cmdclass;
  unsigned short  tacc_clks;
  unsigned int    tacc_ns;
  unsigned int    r2w_factor;
  unsigned int    max_dtr;
  unsigned int    read_blkbits;
  unsigned int    write_blkbits;
  unsigned int    capacity;
  unsigned int    read_partial:1,
                  read_misalign:1,
                  write_partial:1,
                  write_misalign:1;
};


/*
 * sd device
 */
struct sls_sd_card {

  unsigned int         base;
  unsigned int         irq;
  unsigned int         sd_present;      /* card type */
  unsigned int         wr_protect;      /* write protect */
  unsigned int         bus_width;       /* Bus widh type:1/4 bits */
  unsigned int         ocr_avail;
  unsigned int         rca;             /* relative card address of device */
  unsigned int         flag8;
  unsigned int         ccs;
  unsigned int         raw_cid[4];      /* raw card CID        */
  unsigned int         raw_csd[4];      /* raw card CSD        */
  struct sd_cid        cid;             /* card identification */
  struct sd_csd        csd;             /* card specific       */
  unsigned int         power_window;
  unsigned int         tx_time_out;
  unsigned int         rx_time_out;
  unsigned int         cmd_time_out;
  unsigned int         sdhc_clock;
  unsigned int         sdhc_rw_scale;
  unsigned int         card_type;       /* Type of Card */
  unsigned int         no_of_sdio_func; /* No of function if card type is sdio */
  unsigned int         s18a;            /* Card accept 1.8 voltage level */
  unsigned char        sdr_12;
  unsigned char        sdr_25;
  unsigned char        sdr_50;
  unsigned char        sdr_104;
  unsigned char        ddr_50;
  unsigned char        emmc_dual_volt;  //KA
  unsigned char        eMMC_8bit;       //KA
  unsigned char        speed_mode;      //KA
  unsigned char        ddr_en;          //KA
  unsigned char        ext_csd_rev;
};

/********Lower Layer API **********/
int sdhc_card_init(struct sls_sd_card *sd_info);
void sdhc_decode_cid(struct sls_sd_card *sd_info, struct sd_cid  *cid,unsigned int *resp );
int sdhc_decode_csd( struct sls_sd_card *sd_info, struct sd_csd  *csd, unsigned int *resp );
int emmc_decode_ext_csd( struct sls_sd_card *sd_info,struct sd_csd  *csd, unsigned char *read_buffer);
int sdhc_send_command(struct sls_sd_card *card,unsigned int command_arg, unsigned char res_type, unsigned int command_index,unsigned int rx_en,unsigned char cmd_type);
int sdhc_get_response(struct sls_sd_card *sd_info,void *p_buffer, unsigned int Size);
unsigned int sdhc_set_freq(struct sls_sd_card *sd_info, unsigned int frequency);
int sdhc_sd_write_protected(struct sls_sd_card *sd_info);
int sdhc_sd_present(struct sls_sd_card *sd_info);
int sdhc_sdio_write(struct sls_sd_card *sd_info,unsigned int arg,unsigned int index,
                   unsigned int blocks,unsigned int bytes,unsigned char res_type,unsigned char *write_buffer);
int sdhc_sdio_read(struct sls_sd_card *sd_info,unsigned int arg,unsigned int index,
                   unsigned int blocks,unsigned int bytes,unsigned char res_type,unsigned char *read_buffer);


/********Upper Layer API **********/
void sdhc_set_debug_level(unsigned int level);
int  sdhc_init(struct sls_sd_card *card,unsigned int base_addr,unsigned int irq);
int  sdhc_set_high_speed_mode(struct sls_sd_card *sd_info);
int  sdhc_mode_select(struct sls_sd_card *card,unsigned char mode);
int  sdhc_read(struct sls_sd_card *card,unsigned int start_block,unsigned int NoOfBlocks, unsigned char *read_buffer);
int  sdhc_write(struct sls_sd_card *card,unsigned int start_block,unsigned int NoOfBlocks,unsigned char *write_buffer);

#endif // __SLS_AVALON_SD_HOST_REGS_H__






