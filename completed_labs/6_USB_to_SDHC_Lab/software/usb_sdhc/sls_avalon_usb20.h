/****************************************************************************************************************************************************
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
 *  (v1.1.1)            1>	Added ifConfigured and SetRemoteWakeUp functions
 *			           	2>	Changed data type "unsigned int" to "int" of bi_ready and bo_ready
 *							variables of in_ep_s & out_ep_s structures respectively
 *	(v1.2.2)			1>	Added structure instances of __USB_CONTROL_REQUEST and
 *							__CONTROL_REQUEST_STATUS structures in sls_avalon_usb20sr_dev
 *						2>	Added RWakeup_SelfPowered and UDSC's members(udsc_name, udsc_irq & udsc_base)
 *						3>	Added macro of ISO_PKT_LOSS as 0x00000080
 *						4>	Changed macro value of UTMI_RX_ERROR from 0x00000080 to 0x00008000
 *						5>	Modified data type of name, dma_name, udsc_name in sls_avalon_usb20sr_dev(unsigned char* to char*)
 *						6>	Added ENUM_DONE & Device_CS members in sls_avalon_usb20sr_dev
 *						7>	Changed ZERO_LENGTH_PACKET macro's value from 0x00000008 to 0x00
 *						8>	Changed EP_TYPE_MASK macro's value to 0xC0000000 from 0x80000000
 *						9>	Added IN_EP_TYPE, OUT_EP_TYPE & CONTROL_EP_TYPE macros
 *                      10> Added Low Speed parameters in sls_avalon_usb20sr_dev, in_ep_s & out_ep_s structures
 *                      11> Changed function declarations of usb_initialize_descriptor & usb_ep_config for adding Low Speed parameters
 *                      12> Added macros of IN_EP_TYPE, OUT_EP_TYPE & CONTROL_EP_TYPE
 *                      13> Added CONTROL TRANSFER macros
 *  (v1.2.3)            1>  Added flag DEBUG_ENABLE, to enable or disable print messages of the setup packets.
 *                      2>  unsigned char *str_desc_indexes_ is changed to unsigned int *str_desc_indexes_ in the usb_initialize_descriptor()
 *							to support higher range of string descriptor.
 *						3>  volatile unsigned char *str_desc_indexes is changed to volatile unsigned int *str_desc_indexes in typedef struct dev.
 *  (v1.3.4)            1> Added argument *class_spec_desc_req_isr in usb20sr_config() function. It is a call back function. If any class
 *						   specific descriptor request event occurs, HAL driver calls this function and user can pass own descriptor.
 *						2> Added call back function in void(*class_spec_desc_req_isr)() in sls_avalon_usb20sr_dev.
 * 						3> Added function HandleClassSpecificDescriptorRequests () to handle Class Specific descriptor Request from the Host.
 *
 ****************************************************************************************************************************************************/

#ifndef _SLS_AVALON_USB_20_H__
#define _SLS_AVALON_USB_20_H__

#include "sls_avalon_usb20_dev.h"
#include "sls_avalon_usb20_regs.h"
#include "sls_avalon_usb20_descriptors.h"

#define DEBUG_ENABLE 0

#define _DMA_USE 1
#if _DMA_USE > 0
	#define DMA_USE
	#include "altera_avalon_dma_regs.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
#define USB_IF_NUM          4
#define USB_EP_NUM          16

//CONTROL TRANSFER MACROs
/*****************************/
#define SETUP_STAGE_OVER  0x00
#define DATA_STAGE_OVER   0x01
#define STATUS_STAGE_OVER 0x02
/*---------------------------*/
#define SETUP_HANDSHAKE   0x02
#define SETUP_IN_OUT      0x01
#define SETUP_OUT_IN      0x00
/*****************************/

#define ZERO_LENGTH_PACKET           (0x00)
#define REQUEST_TO_DEVICE            0
#define REQUEST_TO_INTERFACE         1
#define REQUEST_TO_ENDPOINT          2
#define DEFAULT_STATE                0
#define ADDRESS_STATE                1
#define CONFIGURATION_STATE          2

#define DEVICE_STATUS_REMOTE_WAKEUP_BUS_POWERED_00_VALUE    0x0000
#define DEVICE_STATUS_REMOTE_WAKEUP_SELF_POWERED_01_VALUE   0x0001
#define DEVICE_STATUS_REMOTE_WAKEUP_BUS_POWERED_10_VALUE    0x0002
#define DEVICE_STATUS_REMOTE_WAKEUP_SELF_POWERED_11_VALUE   0x0003

// To decode the direction of transfer from
#define USB20_PACKET_IN_TRANSFER_DIRECTION(pckt) ((pckt & 0x00000080) >> 7)

// To decode the type of transfer
#define USB20_PACKET_IN_TYPE(pckt)               ((pckt & 0x00000060) >> 5)

// To decode the endpoint number
#define USB20_PACKET_IN_RECIPIENT(pckt)          (pckt & 0x0000001F)

// To get bReqquest(1-byte)
#define UBS20_BREQUEST(data)           			 ((data & 0x0000FF00) >> 8)

// To decode wValue(2-bytes)
#define UBS20_WVALUE(data)             			 ((data & 0xFFFF0000) >> 16)

// To decode wIndex(2-bytes)
#define USB20_WINDEX(data)             			 (data & 0x0000FFFF)

// To decode wLnegth(2-bytes)
#define USB20_WLENGTH(data)            			 ((data & 0xFFFF0000) >> 16)

// To decode Descripto_Type(1-bytes)
#define USB20_DESCRIPTOR_TYPE(data)    			 ((data & 0x0000FF00) >> 8)

// To decode Descriptor_Value(1-bytes)
#define USB20_DESCRIPTOR_VALUE(data)   			 (data & 0x000000FF)

// Device's states
enum state
{
	NONE, RESET, ADDRESS, CONFIGURE, SUSPEND, RESUME
};

/******************************************
 * DMA control registers' values
 *****************************************/
#define DMA_CONTROL_REG_VAL_WORD         (0x0000008C)
#define DMA_STATUS_REG_VAL               (0x00000002)
#define DMA_CONTROL_REG_VAL_BYTE         (0x00000089)
#define DMA_CONTROL_REG_CLEAR            (0x00000000)
#define DMA_DATA_SIZE_NOT_DIVISIBLE_BY_4 (0x00000003)

/***********************************************
 * Events for USB as well as errors that can be
 * generated on any Endpoint.
 ***********************************************/
#define ERROR_CODE_MASK                         0x001F8FFF
#define EP_NO_FROM_GENERATED_ERROR_MASK         0xCF000000
#define EP_TYPE_MASK                            0xC0000000
#define EP_NO_MASK								0x0F000000
#define TIME_OUT_ERROR                          0x00000001
#define BAD_PCK_ERROR                           0x00000002
#define UNEXPTED_PID_ERROR                      0x00000004
#define PID_SEQ_ERROR                           0x00000020
#define BAD_TCKN_ERROR                          0x00000100
#define PID_ERROR                               0x00000200
#define NO_EP_ERROR                             0x00000400
#define UTMI_RX_ERROR                           0x00008000
#define USB_RESET                               0x00010000
#define USB_SUSPEND                             0x00020000
#define USB_RESUME                              0x00040000
#define USB_ATTACHED                            0x00080000
#define USB_DETACHED                            0x00100000
#define SECCUSSFUL_EP_CONF_DONE                 0x00000000
#define EP_NUMBER_EXCEED_LIMIT                  0x00001000
#define NO_EP_TYPE_SUPPORTED_EXCEPT_BULK        0x00002000
#define UNDIFINE_ERROR                          0x00004000
#define ISO_PKT_LOSS                          	0x00000080
#define IN_EP_TYPE								1
#define OUT_EP_TYPE								2
#define CONTROL_EP_TYPE							3
#define MAXIMUM_ENDPOINT_NO 					15

struct in_ep_s
{
	volatile unsigned int  ep_csr_in[MAXIMUM_ENDPOINT_NO + 1]; /* Store Endpoint CSR register configuration */
	volatile unsigned int  ep_int_in[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  ep_buf_size_hs_in[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  ep_buf_size_fs_in[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  ep_buf_size_ls_in[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  ep_buf_size_in[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  ep_buf0_sz_in[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  ep_buf1_sz_in[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  ep_buf0_start_in[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  ep_buf1_start_in[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned char ep_buf0_reg_in[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned char ep_buf1_reg_in[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  wr_nxtBuf[MAXIMUM_ENDPOINT_NO + 1];
	volatile int 		   bi_ready;
};

struct out_ep_s
{
	volatile unsigned int  ep_csr_out[MAXIMUM_ENDPOINT_NO + 1]; /* Store Endpoint CSR register configuration */
	volatile unsigned int  ep_int_out[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  ep_buf_size_hs_out[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  ep_buf_size_fs_out[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  ep_buf_size_ls_out[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  ep_buf_size_out[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  ep_buf0_sz_out[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  ep_buf1_sz_out[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  ep_buf0_start_out[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  ep_buf1_start_out[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned char ep_buf0_reg_out[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned char ep_buf1_reg_out[MAXIMUM_ENDPOINT_NO + 1];
	volatile unsigned int  rd_nxtBuf[MAXIMUM_ENDPOINT_NO + 1];
	volatile int 		   bo_ready;
};

typedef struct dev
{
	volatile unsigned char USB_DeviceAddress;
	volatile unsigned char epsize;
	volatile char 		   *name;
	volatile char 		   *dma_name;
	volatile unsigned char *device_desc;
	volatile unsigned char *conf_desc_hs;
	volatile unsigned char *conf_desc_fs;
	volatile unsigned char *conf_desc_ls;
	volatile unsigned int  *str_desc_indexes;
	volatile unsigned char *str_desc;
	volatile unsigned char *device_quali_desc;
	volatile unsigned char *other_speed_conf_desc_hs;
	volatile unsigned char *other_speed_conf_desc_fs;
	/***************************************
	 * FS/HS Notification. HS = 1, FS = 0
	 **************************************/
	volatile int 		  speed;
	volatile unsigned int irq;
	volatile unsigned int flag_start_rdwr;
	volatile enum state   device_state;
	volatile unsigned int data;
	volatile unsigned int dma_irq;
	volatile unsigned int udsc_base;
	volatile char 		  *udsc_name;
	volatile unsigned int udsc_irq;
	volatile unsigned int base;
	volatile unsigned int start_usb_address;
	volatile unsigned int dma_base;
	volatile unsigned int size_of_str_desc;
	volatile unsigned int supported_conf;
	volatile unsigned int *supported_ep;
	volatile unsigned int *ep_ip_csr_hs;
	volatile unsigned int *ep_ip_csr_fs;
	volatile unsigned int *ep_ip_csr_ls;
	volatile unsigned int *ep_buf0_sz_hs;
	volatile unsigned int *ep_buf1_sz_hs;
	volatile unsigned int *ep_buf0_sz_fs;
	volatile unsigned int *ep_buf1_sz_fs;
	volatile unsigned int *ep_buf0_sz_ls;
	volatile unsigned int *ep_buf1_sz_ls;
	volatile unsigned int *ep_ip_int_hs;
	volatile unsigned int *ep_ip_int_fs;
	volatile unsigned int *ep_ip_int_ls;
	volatile unsigned int USB_DeviceStatus;
	volatile unsigned int USB_Configuration;
	volatile unsigned int RWakeup_SelfPowered;
	volatile unsigned int USB_Interface;
	volatile unsigned int USB_Altsettings;
	volatile unsigned int USB_EndPointMask;
	volatile unsigned int USB_EndPointHalt;
	volatile unsigned int USB_NumInterfaces;
	volatile unsigned int size_conf_hs;
	volatile unsigned int size_conf_fs;
	volatile unsigned int size_conf_ls;
	volatile unsigned int test_mode_flag;
	volatile unsigned int reset;
	volatile unsigned int transfer_size;
	volatile unsigned char USB_AltSetting[USB_IF_NUM];
	void(*usb_attached_isr)(void*);
	void(*usb_detached_isr)(void*);
	void(*usb_reset_isr)(void*);
	void(*usb_resume_isr)(void*);
	void(*usb_suspend_isr)(void*);
	void(*usb_wakeupcfg_isr)(void *, int);
	void(*ep_error_code_isr)(int);
	void(*class_spec_isr)(__CONTROL_REQUEST_STATUS*, int, char);
	void(*class_spec_desc_req_isr)(__CONTROL_REQUEST_STATUS*, int, char);
	volatile __USB_CONTROL_REQUEST 		*PUsbCtrlSetupReq;
	volatile __CONTROL_REQUEST_STATUS 	*PCtrlReqStatus;
	struct in_ep_s 						in_ep;
	struct out_ep_s 					out_ep;
	volatile __USB_CONTROL_REQUEST 		UsbCtrlSetupReq;
	volatile __CONTROL_REQUEST_STATUS 	CtrlReqStatus;
	volatile unsigned char 				ENUM_DONE;
	volatile unsigned char 				Device_CS;
}sls_avalon_usb20sr_dev;

//USB parameter initialize functions
extern void usb_initialize_descriptor(sls_avalon_usb20sr_dev *usb20dev, unsigned char *device_desc_,
																		unsigned char *conf_desc_hs_,
																		unsigned char *conf_desc_fs_,
																		unsigned char *conf_desc_ls_,
																		unsigned int  size_of_conf_desc_hs_,
																		unsigned int  size_of_conf_desc_fs_,
																		unsigned int  size_of_conf_desc_ls_,
																		unsigned int  *str_desc_indexes_,
																		unsigned char *str_desc_,
																		unsigned int  str_index_size,
																		unsigned char *device_quali_desc_,
																		unsigned char *other_speed_conf_desc_hs_,
																		unsigned char *other_speed_conf_desc_fs_);

extern void usb_ep_config(sls_avalon_usb20sr_dev *usb20dev, 					unsigned const int supported_conf_,
						  unsigned const int supported_ep_[], 					unsigned int ep_ip_csr_hs_[][MAXIMUM_ENDPOINT_NO],
						  unsigned int ep_ip_csr_fs_[][MAXIMUM_ENDPOINT_NO], 	unsigned int ep_ip_csr_ls_[][MAXIMUM_ENDPOINT_NO],
						  unsigned int ep_buf0_sz_hs_[][MAXIMUM_ENDPOINT_NO],	unsigned int ep_buf1_sz_hs_[][MAXIMUM_ENDPOINT_NO],
						  unsigned int ep_buf0_sz_fs_[][MAXIMUM_ENDPOINT_NO],   unsigned int ep_buf1_sz_fs_[][MAXIMUM_ENDPOINT_NO],
						  unsigned int ep_buf0_sz_ls_[][MAXIMUM_ENDPOINT_NO],   unsigned int ep_buf1_sz_ls_[][MAXIMUM_ENDPOINT_NO],
						  unsigned int ep_ip_int_hs_[][MAXIMUM_ENDPOINT_NO],    unsigned int ep_ip_int_fs_[][MAXIMUM_ENDPOINT_NO],
						  unsigned int ep_ip_int_ls_[][MAXIMUM_ENDPOINT_NO]		);

extern int usb20sr_config(sls_avalon_usb20sr_dev *usb20dev, volatile int usb_base, volatile int usb_irq,
						  char *usb_name, void *usb20sr_error_event, void *class_spec_isr,void *class_spec_desc_req_isr);

extern void usb20sr_connect(sls_avalon_usb20sr_dev *usb20dev);
extern void usb20sr_disconnect(sls_avalon_usb20sr_dev *usb20dev);

//USB access functions
extern int usb20sr_check_bi_ready(sls_avalon_usb20sr_dev *usbdev, char ep_no);
extern int usb20sr_check_bo_ready(sls_avalon_usb20sr_dev *usbdev, char ep_no);
extern int usb20sr_without_dma_read(sls_avalon_usb20sr_dev *usb20dev, unsigned char ep_no, unsigned char *ptr, int size);
extern int usb20sr_without_dma_write(sls_avalon_usb20sr_dev *usb20dev, unsigned char ep_no, unsigned char *ptr, int size);

//DMA configuration & read/write functions
extern void dma_config(sls_avalon_usb20sr_dev *usb20dev, int dma_base, int dma_irq, char *dma_name, int dma_flag);
extern int usb20sr_with_dma_read(sls_avalon_usb20sr_dev *usb20dev, unsigned char ep_no,
								 unsigned char *ptr, int size, int dma_flag);
extern int usb20sr_with_dma_write(sls_avalon_usb20sr_dev *usb20dev, unsigned char ep_no,
							      unsigned char *ptr, int size, int dma_flag);

extern void slsmemcpy(int base, void *dest, void *src, volatile int ilength);

//Control endpoint related functions
extern void HandleClassSpecificControlRequests(volatile __CONTROL_REQUEST_STATUS *CONTROL_REQUEST_STATUS,
											   volatile unsigned int base, char stage);
extern void HandleClassSpecificDescriptorRequests(volatile __CONTROL_REQUEST_STATUS *CONTROL_REQUEST_STATUS,
											   volatile unsigned int base, char stage);
extern void USB_ClrStallEP(sls_avalon_usb20sr_dev *usb20dev, int ep);
extern void USB_SetStallEP(sls_avalon_usb20sr_dev *usb20dev, int ep);

//Event functions
extern void usb20_event_isr(sls_avalon_usb20sr_dev *usb20dev, void *usb_attached_Event, void *usb_detached_event,
							void *usb_reset_event, void *usb_resume_event, void *usb_suspend_event, void *usb_wakeupCfg);
extern void usb20sr_error_event(int event);
extern void USB_Attached_Event(sls_avalon_usb20sr_dev *usb20dev);
extern void USB_Detached_Event(sls_avalon_usb20sr_dev *usb20dev);
extern void USB_Reset_Event(sls_avalon_usb20sr_dev *usb20dev);
extern void USB_Resume_Event(sls_avalon_usb20sr_dev *usb20dev);
extern void USB_Suspend_Event(sls_avalon_usb20sr_dev *usb20dev);
extern void USB_WakeUpCfg_Event(sls_avalon_usb20sr_dev *usb20dev, unsigned char cfg);

//Some get methods
extern int get_current_config(sls_avalon_usb20sr_dev *usb20dev);
extern int get_current_interface(sls_avalon_usb20sr_dev *usb20dev);
extern int get_current_alt_settings(sls_avalon_usb20sr_dev *usb20dev);
extern int get_current_micro_frame_no(sls_avalon_usb20sr_dev *usb20dev);
extern int get_current_frame_no(sls_avalon_usb20sr_dev *usb20dev);
extern int get_sof_time(sls_avalon_usb20sr_dev *usb20dev);
extern int usb20sr_get_dev_speed(sls_avalon_usb20sr_dev*);

extern char ifConfigured(sls_avalon_usb20sr_dev *usb20dev);
extern void SetRemoteWakeUp(sls_avalon_usb20sr_dev *usb20dev);
extern void usb20sr_set_dev_speed(sls_avalon_usb20sr_dev *, int);

//PHY register function
extern void usb20sr_phy_register_enable(sls_avalon_usb20sr_dev *);
extern void usb20sr_phy_register_disable(sls_avalon_usb20sr_dev *);
extern void usb20sr_phy_register_write(sls_avalon_usb20sr_dev *, int, int);
extern void usb20sr_phy_register_read(sls_avalon_usb20sr_dev *, int, int*);
extern void usb20sr_set_low_power_mode(sls_avalon_usb20sr_dev*);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _SLS_AVALON_USB_20_H__ */
