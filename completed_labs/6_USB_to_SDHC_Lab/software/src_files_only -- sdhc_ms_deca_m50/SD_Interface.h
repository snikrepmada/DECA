#ifndef __SD_INTERFACE_H__
#define __SD_INTERFACE_H__

#include "mem_interface_switch.h"

#include "system.h"
#include "sys/alt_flash.h"
#include "sys/alt_flash_dev.h"
#include "sys/alt_flash_types.h"

#define USB_STORAGE_DEV_SEC_SIZE (512)
#define USB_SEC_2_SDCARD_SEC_MAP (1)

int InitSD(SD_INFO *PMemInterfaceInfo);
BYTE SD_card_init(SD_INFO *PMemInterfaceInfo);
int sd_write(unsigned int block_no,unsigned int no_of_block,unsigned char *ptr);
int sd_read(unsigned int block_no,unsigned int no_of_block,unsigned char *ptr);

#endif // __SD_INTERFACE_H__
