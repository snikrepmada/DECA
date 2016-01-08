#include "stdio.h"
#include "system.h"
#include "sls_avalon_usb20.h"
#include "sls_usb.h"
#include "sls_ep_configuration.h"
#include "USBMassStore.h"
#include "SD_Interface.h"
#include "mem_interface_switch.h"

/**************************************************************
 * Set DMA_FLAG as 1 to use DMA
 * Set DMA_FLAG as 0 to use UDSC(USB Data Streamer Controller)
 * NOTE : For support of UDSC, contact http://www.slscorp.com
 **************************************************************/
#define DMA_FLAG    1  /*1 -> DMA & 0 -> UDSC*/

unsigned char DataToBeSent = 0x00;

void usb20sr_error_event(int event);

sls_avalon_usb20sr_dev *pUsb20srDev;
sls_avalon_usb20sr_dev usb20srdev;

void configure_usb20sr(sls_avalon_usb20sr_dev *pUsb20srDev)
{
	usb_initialize_descriptor(pUsb20srDev,(unsigned char*)device_desc_,
										  (unsigned char*)conf_desc_hs_,
										  (unsigned char*)conf_desc_fs_,
										  (unsigned char*)conf_desc_ls_,
										  sizeof(conf_desc_hs_),
										  sizeof(conf_desc_fs_),
										  sizeof(conf_desc_ls_),
										  (unsigned int*)str_desc_indexes_,
										  (unsigned char*)str_desc_,
										  sizeof(str_desc_indexes_),
										  (unsigned char*)device_quali_desc_,
										  (unsigned char*)other_speed_conf_desc_hs_,
										  (unsigned char*)other_speed_conf_desc_fs_);

	usb_ep_config(      pUsb20srDev,    SUPPORTED_CONF,     supported_ep_,      ep_ip_csr_hs_,      ep_ip_csr_fs_,		ep_ip_csr_ls_,
						ep_buf0_sz_hs_, ep_buf1_sz_hs_,     ep_buf0_sz_fs_,     ep_buf1_sz_fs_, 	ep_buf0_sz_ls_, 	ep_buf1_sz_ls_,
						ep_ip_int_hs,	ep_ip_int_fs,		ep_ip_int_ls     );
	
    //Use DMA/UDSC's BASE, IRQ & NAME from system.h file
	dma_config(pUsb20srDev, DMA_0_BASE, DMA_0_IRQ, DMA_0_NAME, DMA_FLAG);		     //set DMA_FLAG as 1 while using DMA
	//dma_config(pUsb20srDev, UDSC_0_BASE, UDSC_0_IRQ, UDSC_0_NAME, DMA_FLAG);	 //set DMA_FLAG as 0 while using UDSC

	usb20_event_isr(pUsb20srDev, USB_Attached_Event, USB_Detached_Event, USB_Reset_Event, USB_Resume_Event, USB_Suspend_Event, USB_WakeUpCfg_Event);

	if(usb20sr_config(pUsb20srDev, USB20SR_BASE, USB20SR_IRQ, USB20SR_NAME, usb20sr_error_event, HandleClassSpecificControlRequests, HandleClassSpecificDescriptorRequests))
	{}
}

int main()
{
   	pUsb20srDev = &usb20srdev;

	configure_usb20sr(pUsb20srDev);

	usb20sr_disconnect(pUsb20srDev);

	//usb20sr_set_dev_speed(pUsb20srDev, 0);     //Connect device in the full speed(0)/high speed(1) mode

	usb20sr_connect(pUsb20srDev);

    printf("Connect USB Device..! \n");
	while(!(ifConfigured(pUsb20srDev)));//Check whether device is Configured or not
	printf("Device Configured \n");

	SD_INFO MemInterfaceInfo = {0};
    InitSD((SD_INFO *)&MemInterfaceInfo);
    
    MassStorage_Main((SD_INFO *)&MemInterfaceInfo, pUsb20srDev);

    return 0;
}

void USB_Attached_Event(sls_avalon_usb20sr_dev *usb20dev)
{
    printf("\nAttEvent\n");
}

void USB_Detached_Event(sls_avalon_usb20sr_dev *usb20dev)
{
    printf("\nDetaEvent\n");
}

void USB_Reset_Event(sls_avalon_usb20sr_dev *usb20dev)
{
    printf("\nResetEvent\n");
}

void USB_Resume_Event(sls_avalon_usb20sr_dev *usb20dev)
{
    printf("\nResume\n");
}

void USB_Suspend_Event(sls_avalon_usb20sr_dev *usb20dev)
{
    printf("\nSuspend\n");
}

void USB_WakeUpCfg_Event(sls_avalon_usb20sr_dev *usb20dev, unsigned char cfg)
{
    //printf("\nWakeUpCfgEvent\n");
}
void USB_SOFRecved_Event(sls_avalon_usb20sr_dev *usb20dev)
{

}
void HandleClassSpecificDescriptorRequests(volatile __CONTROL_REQUEST_STATUS *CONTROL_REQUEST_STATUS,
										volatile unsigned int base, char stage)
{
//	printf("ep_sp_req\n");

	unsigned char Buffer[] = {
				0x05, 0x01, 0x09, 0x02,\
				0xa1, 0x01, 0x09, 0x01,\
				0xa1, 0x00, 0x05, 0x09,\
				0x19, 0x01, 0x29, 0x03,\
				0x15, 0x00, 0x25, 0x01,\
				0x95, 0x03, 0x75, 0x01,\
				0x81, 0x02, 0x75, 0x05,\
				0x95, 0x01, 0x81, 0x01,\
				0x05, 0x01, 0x09, 0x30,\
				0x09, 0x31, 0x15, 0x81,\
				0x25, 0x7f, 0x75, 0x08,\
				0x95, 0x02, 0x81, 0x06,\
				0xc0, 0xc0			};

	CONTROL_REQUEST_STATUS->sizeOfDataStageData = sizeof(Buffer);
	CONTROL_REQUEST_STATUS->PDataStageData = Buffer;

}
void HandleClassSpecificControlRequests(volatile __CONTROL_REQUEST_STATUS *PCtrlReqStatus,
										volatile unsigned int base, char stage)
{
    if(PCtrlReqStatus->PUsbCtrlReq->bmRequestType.RequestType == 0x01)
    {
        //if Class specific request is there
    
        //printf("Class Req\n");
        if(     (PCtrlReqStatus->PUsbCtrlReq->bRequest == 0xFE)                &&
            (PCtrlReqStatus->PUsbCtrlReq->bmRequestType.Direction == 1)    &&
            (PCtrlReqStatus->PUsbCtrlReq->bmRequestType.RequestType == 1)  &&
            (PCtrlReqStatus->PUsbCtrlReq->wIndex.Value == 0)               &&
            (PCtrlReqStatus->PUsbCtrlReq->wValue.Value == 0)               &&
            (PCtrlReqStatus->PUsbCtrlReq->wLength == 1)         )
        {
            //printf("GetMaxLUN\n");
            PCtrlReqStatus->sizeOfDataStageData = 1;
            PCtrlReqStatus->PDataStageData = &DataToBeSent;
        }
        else if(    (PCtrlReqStatus->PUsbCtrlReq->bRequest == 0xFF)                   &&
                    (PCtrlReqStatus->PUsbCtrlReq->bmRequestType.Direction == 0)       &&
                    (PCtrlReqStatus->PUsbCtrlReq->bmRequestType.RequestType == 1)     &&
                    (PCtrlReqStatus->PUsbCtrlReq->wIndex.Value == 0)                  &&
                    (PCtrlReqStatus->PUsbCtrlReq->wValue.Value == 0)                  &&
                    (PCtrlReqStatus->PUsbCtrlReq->wLength == 0))
        {
            int csr = IORD_32DIRECT(base, 0x50);
            IOWR_32DIRECT(base, 0x50, csr | 0x00800000);
			csr = IORD_32DIRECT(base, 0x60);
            IOWR_32DIRECT(base, 0x60, csr | 0x00800000);
        }
        else
        {
//            printf("Bad control request\n");
            int csr = IORD_32DIRECT(base, 0x40);
            IOWR_32DIRECT(base, 0x40, csr | 0x00800000);
        }
    }
}

#define PRINTF_USB_EVENT(str,...) printf(str,##__VA_ARGS__)

void usb20sr_error_event(int event)
{
	volatile int data = event & ERROR_CODE_MASK;

	if(event & EP_NO_FROM_GENERATED_ERROR_MASK)
	{
		if(((event & EP_TYPE_MASK) >> 30) == IN_EP_TYPE)
			PRINTF_USB_EVENT("IN ");
		else if(((event & EP_TYPE_MASK) >> 30) == OUT_EP_TYPE)
			PRINTF_USB_EVENT("OUT ");
		else if(((event & EP_TYPE_MASK) >> 30) == CONTROL_EP_TYPE)
			PRINTF_USB_EVENT("CONTROL ");

		PRINTF_USB_EVENT("Endpoint %d cause ", (event & EP_NO_MASK) >> 24);
	}
	else
		PRINTF_USB_EVENT("\nUSB cause ");

	if(data & TIME_OUT_ERROR)
		PRINTF_USB_EVENT("TIME_OUT_ERROR\n");

	if(data & BAD_PCK_ERROR)
		PRINTF_USB_EVENT("BAD_PCK_ERROR\n");

	if(data & UNEXPTED_PID_ERROR)
		PRINTF_USB_EVENT("UNEXPECTED_PID_ERROR\n");

	if(data & PID_SEQ_ERROR)
		PRINTF_USB_EVENT("PID_SEQ_ERROR\n");

	if(data & BAD_TCKN_ERROR)
		PRINTF_USB_EVENT("BAD_TCKN_ERROR\n");

	if(data & PID_ERROR)
		PRINTF_USB_EVENT("PID_ERROR\n");

	if(data & NO_EP_ERROR)
		PRINTF_USB_EVENT("NO_EP_ERROR\n");

	if(data & UTMI_RX_ERROR)
		PRINTF_USB_EVENT("UTMI_RX_ERROR\n");

	if(data & ISO_PKT_LOSS)
		PRINTF_USB_EVENT("ISO_PKT_LOSS\n");
}
