
#ifndef __MEM_SWITCH
#define __MEM_SWITCH

//#pragma pack(1)

#define BYTE     unsigned volatile char
#define UINT16   unsigned volatile int
#define UINT32   unsigned volatile long

#define TRANSFER_SIZE          SIZE_OF_BUFF * 1024

#define SIZE_OF_BUFF           32          // 1k to 512k

typedef struct SD_CARD_INFO
{
  unsigned int      total_blocks;               //Total number of blocks inside SD
  unsigned int      total_size;                 //Total size of SD Memory
  unsigned int      Block_size;                 //Total size of one SD Block
  unsigned int      LBA;                        //Store Logical Block Address issue by the HOST
//  unsigned char     tempData[524288];           //Buffer for internal Operation
  unsigned char     tempData[TRANSFER_SIZE];           //Buffer for internal Operation
  void              *bufr_addr;
  unsigned int      error;
}SD_INFO;

#endif
