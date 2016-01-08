/*********************************************************************************************
 *  SLS USB Mass Storage Class Driver
 *
 *  Copyright (C) 2011 SLS, All Rights Reserved.
 *
 *  History:
 *      v1.0.0  : September 18, 14  - Initial release with SDCard as a Mass Storage medium
 *
 *********************************************************************************************/
#ifndef _USB_MASS_STORAGE_H
#define _USB_MASS_STORAGE_H

#include "mem_interface_switch.h"
#include "sls_avalon_usb20.h"

/* Structure define the Command block wrapper for USB Mass Storage
 *
 */

//#pragma pack(1)

typedef struct _CBW
{
    volatile unsigned int  signature;
    volatile unsigned int  dCBWDataTransferLength;
    unsigned char bmCBWFlags;
    unsigned char bCBWLUN;
    unsigned char bCBWCBLength;
    unsigned char CBWCB[16];
    unsigned char dcBWTag[4];

}CBW,*PCBW;

typedef struct _CSW
{
  unsigned int  dCSWSignature;
  unsigned int  dCSWTag;
  unsigned int  dCSWDataResidue;
  unsigned char bCSWStatus;
}CSW,*PCSW;

#define VALID           1
#define NOT_VALID       0
#define CBW_SIGNATURE   0x43425355
#define CBW_LENGTH    31
#define CSW_LENGTH    13


//Command Block status value
#define CSW_COMMAND_PASSED  0x00
#define CSW_COMMAND_FAILED  0x01
#define CSW_PHASE_ERROR     0x02


/* Global variables */
extern CBW m_cbw;
extern CSW m_csw;

/*
   Function Name        : MassStorage_Main
   Input parameter      : -
   Output parameter     : -
   Function Description : This function handle main loop of USb Mass Storage protocol (Command/Data/Status stage)

 */
extern void MassStorage_Main(SD_INFO *, struct dev *pUsb20srDev);
/*
   Function Name        : CommandTransport()
   Input parameter      : -
   Output parameter     :  -
   Function Description : This function manage the first packet command block wrapper sent by
                          the Host.
                          First read the fixed length(31 data for Command Block Wrapper)data
   						  from usb device,decode it and fill appropriate fields of the CBW.

 */
extern int CommandTransport(struct dev *pUsb20srDev);

/*
   Function Name        : Data_Out()
   Input parameter      : PCBW
   Output parameter     :  -
   Function Description : This function receive the data from usb device(Host to Device).
                          Call the scsi to ata translation function to process
                          the CBWCB field of CBW. which return the command in the
                          translated form(ATA).
                          Call Compact flash function to configure the CF.
						  Call write function of CF to Write the data to CF.

 */

extern void Data_Out(SD_INFO *PMemInterfaceInfo,struct dev *pUsb20srDev);

/*
   Function Name        : Data_In();
   Input parameter      : -
   Output parameter     :  -
   Function Description : This function receive the data from usb device(Device to Host).
                          Call the scsi to ata translation function to process
                          the CBWCB field of CBW. which return the commands in the
                          translated form(ATA).
          						    Call Compact flash function to configure the CF.
					           	    Call read function of CF to read the data to CF.


 */
extern void Data_In(SD_INFO *PMemInterfaceInfo,struct dev *pUsb20srDev);

/*
   Function Name        : StatusTransport();
   Input parameter      : CBW
   Output parameter     :  -
   Function Description : This function has two stage
                          first is to receive the command from usb device(from Host) and
                          second send the status data to usb device(to Host).

 */
extern void StatusTransport(SD_INFO *PMemInterfaceInfo,struct dev *pUsb20srDev);

#endif
