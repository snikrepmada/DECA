/*********************************************************************************************
 *  SLS USB Mass Storage Class Driver
 *
 *  Copyright (C) 2011 SLS, All Rights Reserved.
 *
 *  History:
 *      v1.0.0  : September 18, 14  - Initial release with SDCard as a Mass Storage medium
 *
 *********************************************************************************************/
#ifndef _SCSI_TO_ATA_H
#define _SCSI_TO_ATA_H

#include "SD_interface.h"

/* SCSI operation commands */
#define REQUEST_SENSE                0X03
#define TEST_UNIT_READY              0X00
#define VERIFY                       0X2F
#define INQUIRY                      0X12
#define MODE_SELECT                  0X55
#define MODE_SENSE6                  0X1A
#define MODE_SENSE10                 0X5A
#define PREVENT_ALLOW_MEDIUM_REMOVAL 0X1E
#define READ                         0X28
#define READ_CAPACITY                0X25
#define WRITE                        0X2A
#define READ_FORMAT_CAPACITY         0x23
#define START_STOP_UNIT              0x1B

/* CFI_ATA(IDE) operation commands */
#define READ_SECTOR                  0X20
#define WRITE_SECTOR                 0X30

#define OPERATION_COMPLETED 1
#define OPERATION_NOT_COMPLETED 0
#define FALSE 0
#define TRUE  1

#define ZERO_LENGTH                   0x0
#define REQUEST_SENSE_DATA_SIZE        18
#define INQUIRY_DATA_SIZE              36
#define MODE_SENSE_DATA_SIZE            4
#define READ_CAPACITY_DATA_SIZE         8
#define READ_FORMAT_CAPACITY_DATA_SIZE 12

extern int SCSI_To_ATA_Translation(unsigned char *, int *, SD_INFO *);

#endif
