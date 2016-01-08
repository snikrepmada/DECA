/*********************************************************************************************
 *  SLS USB20SR Device Controller Driver
 *
 *  Copyright (C) 2011 SLS, All Rights Reserved.
 *
 *  History:
 *      v1.0.0  : September 09  - SLS : USB20SR IP - Core v1.0
 *      v1.1.1  : October 10    - SLS : USB20SR IP - Core v1.1
 *      v1.2.2  : July 11       - SLS : USB20SR IP - Core v1.2
 *      v1.2.3  : December 12   - SLS : USB20SR IP - Core v1.2
 *      v1.3.4  : December 12   - SLS : USB20SR IP - Core v1.3
 *
 *  Change History :
 *  (v1.2.2)        1> Added conf_desc_ls_ for Low Speed configuration of device
 *                     (For the support of Low Speed, contact support@slscorp.com)
 *                  2> Corrected str_desc_indexes_ array values
 *  (v1.2.3)        1> volatile const unsigned char str_desc_indexes_[] is changed to
 *					   volatile unsigned int str_desc_indexes_[] to support higher range of string
 *  					descriptor idnex.
 *********************************************************************************************/

#ifndef SLS_USB_H_
#define SLS_USB_H_

#include "sls_avalon_usb20_descriptors.h"

/******************************************************************************
 * If user wants to add/remove endpoint then below all arrays will be changed.
 * User needs to take care that all configuration related with speed(HS/FS/LS)
 * must be initialized properly before enumeration starts.
 * Refer USB2.0 specification (Chapter 9) for more details.
 ******************************************************************************/

/* Number of available endpoints for enumeration.
 * According to this, provide a value of endpoint CSR, IMS and BUFFER registers' value from sls_ep_configuration.h file.*/
#define NUM_ENDPOINTS   2
#define USB_EP0_MAX_PACKETSIZE 64

// To convert word to individual char
#define WORD_TO_CHAR(data) data&0x000000FF,(data>>8)0x000000FF,(data>>16)0x000000FF,(data>>24)&0x000000FF

// To convert short integer to individual char
#define SHORT_TO_CHAR(data) (data&0x000000FF),(data>>8)&0x000000FF

#define DEV_VID (0x1772)
#define DEV_PID (0x0002)

/* USB Standard Device Descriptor */
volatile unsigned char device_desc_[] = {
	USB_DEVICE_DESC_SIZE,                      /* bLength */
	USB_DEVICE_DESCRIPTOR_TYPE,                /* bDescriptorType */
	SHORT_TO_CHAR(0x0110), /* 2.00 */          /* bcdUSB */
	0x00,                                      /* bDeviceClass */
	0x00,                                      /* bDeviceSubClass */
	0x00,                                      /* bDeviceProtocol */
	USB_EP0_MAX_PACKETSIZE,                    /* bMaxPacketSize0 */
	SHORT_TO_CHAR(DEV_VID),                    /* idVendor */
	SHORT_TO_CHAR(DEV_PID),                    /* idProduct */
	SHORT_TO_CHAR(0x0010), /* 0.10 */          /* bcdDevice */
	0x01,                                      /* iManufacturer */
	0x02,                                      /* iProduct */
	0x03,                                      /* iSerialNumber */
	0x01                                       /* bNumConfigurations */
};

/* USB Configuration Descriptor */
/* All Descriptors (Configuration, Interface, Endpoint */
volatile const unsigned char conf_desc_hs_[] = {
	/* Configuration 1 */
	USB_CONFIGUARTION_DESC_SIZE,              /* bLength */
	USB_CONFIGURATION_DESCRIPTOR_TYPE,        /* bDescriptorType */
	SHORT_TO_CHAR((
	USB_CONFIGUARTION_DESC_SIZE +
	USB_INTERFACE_DESC_SIZE     +
	NUM_ENDPOINTS * USB_ENDPOINT_DESC_SIZE))
	,
	0x01,                                     /* bNumInterfaces */
	0x01,                                     /* bConfigurationValue */
	0x04,                                     /* iConfiguration */
	USB_CONFIG_BUS_POWERED                    /* bmAttributes */
	/* | USB_CONFIG_REMOTE_WAKEUP */,
	0x32,          							  /* bMaxPower */
	/* Interface 0, Alternate Setting 0, Class Code Unknown */
	USB_INTERFACE_DESC_SIZE,                  /* bLength */
	USB_INTERFACE_DESCRIPTOR_TYPE,            /* bDescriptorType */
	0x00,                                     /* bInterfaceNumber */
	0x00,                                     /* bAlternateSetting */
	NUM_ENDPOINTS,                            /* bNumEndpoints */
	0x08,                                     /* bInterfaceClass, USB_CLASS_VENDOR_SPECIFIC */
	0x06,                                     /* bInterfaceSubClass, USB_SUBCLASS_CODE_UNKNOWN */
	0x50,                                     /* bInterfaceProtocol, USB_PROTOCOL_CODE_UNKNOWN */
	0x05,                                     /* iInterface, STR_INDEX_INTERFACE */
	/* Endpoint, EP1 Bulk In */
	USB_ENDPOINT_DESC_SIZE,                   /* bLength */
	USB_ENDPOINT_DESCRIPTOR_TYPE,             /* bDescriptorType */
	0x81,                                     /* bEndpointAddress */
	USB_ENDPOINT_TYPE_BULK,                   /* bmAttributes */
	SHORT_TO_CHAR(0x200),                     /* wMaxPacketSize */
	0x01,          /* 32ms */                 /* bInterval */
	/* Endpoint, EP2 Bulk Out */
	USB_ENDPOINT_DESC_SIZE,                   /* bLength */
	USB_ENDPOINT_DESCRIPTOR_TYPE,             /* bDescriptorType */
	0x02,                                     /* bEndpointAddress */
	USB_ENDPOINT_TYPE_BULK,                   /* bmAttributes */
	SHORT_TO_CHAR(0x0200),                    /* wMaxPacketSize */
	0x01,          /* 32ms */                 /* bInterval */
};

volatile const unsigned char conf_desc_fs_[] = {
	/* Configuration 1 */
	USB_CONFIGUARTION_DESC_SIZE,              /* bLength */
	USB_CONFIGURATION_DESCRIPTOR_TYPE,        /* bDescriptorType */

	SHORT_TO_CHAR((
	USB_CONFIGUARTION_DESC_SIZE +
	USB_INTERFACE_DESC_SIZE     +
	NUM_ENDPOINTS * USB_ENDPOINT_DESC_SIZE))
	,                                         /* wTotalLength */
	0x01,                                     /* bNumInterfaces */
	0x01,                                     /* bConfigurationValue */
	0x04,                                     /* iConfiguration */
	USB_CONFIG_BUS_POWERED                    /* bmAttributes */
	/* | USB_CONFIG_REMOTE_WAKEUP */,
	0x32,                                     /* bMaxPower */
	/* Interface 0, Alternate Setting 0, Class Code Unknown */
	USB_INTERFACE_DESC_SIZE,                  /* bLength */
	USB_INTERFACE_DESCRIPTOR_TYPE,            /* bDescriptorType */
	0x00,                                     /* bInterfaceNumber */
	0x00,                                     /* bAlternateSetting */
	NUM_ENDPOINTS,                            /* bNumEndpoints */
	0x08,                                     /* bInterfaceClass, USB_CLASS_VENDOR_SPECIFIC */
	0x06,                                     /* bInterfaceSubClass, USB_SUBCLASS_CODE_UNKNOWN */
	0x50,                                     /* bInterfaceProtocol, USB_PROTOCOL_CODE_UNKNOWN */
	0x05,                                     /* iInterface, STR_INDEX_INTERFACE */
	/* Endpoint, EP1 Bulk In */
	USB_ENDPOINT_DESC_SIZE,                   /* bLength */
	USB_ENDPOINT_DESCRIPTOR_TYPE,             /* bDescriptorType */
	0x81,                                     /* bEndpointAddress */
	USB_ENDPOINT_TYPE_BULK,                   /* bmAttributes */
	SHORT_TO_CHAR(0x0040),                    /* wMaxPacketSize */
	0x01,          /* 32ms */                 /* bInterval */
	/* Endpoint, EP2 Bulk Out */
	USB_ENDPOINT_DESC_SIZE,                   /* bLength */
	USB_ENDPOINT_DESCRIPTOR_TYPE,             /* bDescriptorType */
	0x02,                                     /* bEndpointAddress */
	USB_ENDPOINT_TYPE_BULK,                   /* bmAttributes */
	SHORT_TO_CHAR(0x0040),                    /* wMaxPacketSize */
	0x01,                                     /* 32ms */
};

volatile const unsigned char conf_desc_ls_[] = {
	/* Configuration 1 */
	USB_CONFIGUARTION_DESC_SIZE,              /* bLength */
	USB_CONFIGURATION_DESCRIPTOR_TYPE,        /* bDescriptorType */
	SHORT_TO_CHAR((
	USB_CONFIGUARTION_DESC_SIZE +
	USB_INTERFACE_DESC_SIZE		+
	NUM_ENDPOINTS * USB_ENDPOINT_DESC_SIZE))
	,                                         /* wTotalLength */
	0x01,                                     /* bNumInterfaces */
	0x01,                                     /* bConfigurationValue */
	0x04,                                     /* iConfiguration */
	USB_CONFIG_BUS_POWERED                    /* bmAttributes */
	/* | USB_CONFIG_REMOTE_WAKEUP */,
	0x32,                                     /* bMaxPower */
	/* Interface 0, Alternate Setting 0, Class Code Unknown */
	USB_INTERFACE_DESC_SIZE,                  /* bLength */
	USB_INTERFACE_DESCRIPTOR_TYPE,            /* bDescriptorType */
	0x00,                                     /* bInterfaceNumber */
	0x00,                                     /* bAlternateSetting */
	NUM_ENDPOINTS,                            /* bNumEndpoints */
	0xFF,                                     /* bInterfaceClass, USB_CLASS_VENDOR_SPECIFIC */
	0x00,                                     /* bInterfaceSubClass, USB_SUBCLASS_CODE_UNKNOWN */
	0xFF,                                     /* bInterfaceProtocol, USB_PROTOCOL_CODE_UNKNOWN */
	0x05,                                     /* iInterface, STR_INDEX_INTERFACE */
	/* Endpoint, EP1 Interrupt In */
	USB_ENDPOINT_DESC_SIZE,                   /* bLength */
	USB_ENDPOINT_DESCRIPTOR_TYPE,             /* bDescriptorType */
	0x81,                                     /* bEndpointAddress */
	USB_ENDPOINT_TYPE_INTERRUPT,              /* bmAttributes */
	SHORT_TO_CHAR(0x0008),                    /* wMaxPacketSize */
	0x01,          /* 32ms */                 /* bInterval */
	/* Endpoint, EP2 Interrupt Out */
	USB_ENDPOINT_DESC_SIZE,                   /* bLength */
	USB_ENDPOINT_DESCRIPTOR_TYPE,             /* bDescriptorType */
	0x02,                                     /* bEndpointAddress */
	USB_ENDPOINT_TYPE_INTERRUPT,              /* bmAttributes */
	SHORT_TO_CHAR(0x0008),                    /* wMaxPacketSize */
	0x01,          /* 32ms */                 /* bInterval */
};

/* USB String Descriptor (optional) */
volatile unsigned int str_desc_indexes_[6] ={0x00, 0x04, 0x0C, 0x1A, 0x34, 0x44};

volatile const unsigned char str_desc_[] =
{
	/* Index 00 = 0x00 : LANGID Codes */
	0x04,                                     /* bLength */
	USB_STRING_DESCRIPTOR_TYPE,               /* bDescriptorType */
	SHORT_TO_CHAR(0x0409), /* US English */   /* wLANGID */

	/* Index 04 = 0x04 : Manufacturer */
	0x08,                                     /* bLength */
	USB_STRING_DESCRIPTOR_TYPE,               /* bDescriptorType */
	'S',0,
	'L',0,
	'S',0,

	/* Index 12 = 0x0C : Product */
	0x0E,                                     /* bLength */
	USB_STRING_DESCRIPTOR_TYPE,               /* bDescriptorType */
	'U',0,
	'S',0,
	'B',0,
	'2',0,
	'.',0,
	'0',0,

	/* Index 26 = 0x1A : Serial Number */
	0x1A,                                     /* bLength */
	USB_STRING_DESCRIPTOR_TYPE,               /* bDescriptorType */
	'0',0,
	'0',0,
	'0',0,
	'0',0,
	'0',0,
	'0',0,
	'0',0,
	'0',0,
	'0',0,
	'0',0,
	'0',0,
	'1',0,

	/* Index 52 = 0x34 : Configuration 1 */
	0x10,                                     /* bLength */
	USB_STRING_DESCRIPTOR_TYPE,               /* bDescriptorType */
	'C',0,
	'O',0,
	'N',0,
	'F',0,
	'I',0,
	'G',0,
	'1',0,

	/* Index 68 = 0x44 : Interface 0, Alternate Setting 0 */
	0x0C,                                     /* bLength */
	USB_STRING_DESCRIPTOR_TYPE,               /* bDescriptorType */
	'R',0,
	'D',0,
	'/',0,
	'W',0,
	'R',0,
};

volatile const unsigned char device_quali_desc_[]=
{
	USB_DEVICE_QUALIFIER_DESC_SIZE,            /* bLength */
	USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE,      /* bDescriptorType */
	SHORT_TO_CHAR(0x0200), /* 2.00 */          /* bcdUSB */
	0x08,                                      /* bDeviceClass */
	0x06,                                      /* bDeviceSubClass */
	0x50,                                      /* bDeviceProtocol */
	USB_EP0_MAX_PACKETSIZE,                    /* bMaxPacketSize0 */
	0x01,                                      /* bNumConfigurations */
	0x00                                       /* bReserved */
};

volatile const unsigned char other_speed_conf_desc_hs_[] = {
	/* Configuration 1 */
	USB_CONFIGUARTION_DESC_SIZE,              /* bLength */
	USB_OTHER_SPEED_CONFIG_DESCRIPTOR_TYPE,   /* bDescriptorType */
	SHORT_TO_CHAR((
	USB_CONFIGUARTION_DESC_SIZE +
	USB_INTERFACE_DESC_SIZE     +
	NUM_ENDPOINTS * USB_ENDPOINT_DESC_SIZE))
	,                                         /* wTotalLength */
	0x01,                                     /* bNumInterfaces */
	0x01,                                     /* bConfigurationValue */
	0x04,                                     /* iConfiguration */
	USB_CONFIG_BUS_POWERED                    /* bmAttributes */
	/* | USB_CONFIG_REMOTE_WAKEUP */,
	0x32,                                     /* bMaxPower */
	/* Interface 0, Alternate Setting 0, Class Code Unknown */
	USB_INTERFACE_DESC_SIZE,                  /* bLength */
	USB_INTERFACE_DESCRIPTOR_TYPE,            /* bDescriptorType */
	0x00,                                     /* bInterfaceNumber */
	0x00,                                     /* bAlternateSetting */
	NUM_ENDPOINTS,                            /* bNumEndpoints */
	0x08,                                     /* bInterfaceClass, USB_CLASS_VENDOR_SPECIFIC */
	0x06,                                     /* bInterfaceSubClass, USB_SUBCLASS_CODE_UNKNOWN */
	0x50,                                     /* bInterfaceProtocol, USB_PROTOCOL_CODE_UNKNOWN */
	0x05,                                     /* iInterface, STR_INDEX_INTERFACE */
	/* Endpoint, EP1 Bulk In */
	USB_ENDPOINT_DESC_SIZE,                   /* bLength */
	USB_ENDPOINT_DESCRIPTOR_TYPE,             /* bDescriptorType */
	0x81,                                     /* bEndpointAddress */
	USB_ENDPOINT_TYPE_BULK,                   /* bmAttributes */
	SHORT_TO_CHAR(0x0200),                    /* wMaxPacketSize */
	0x01,          /* 32ms */                 /* bInterval */
	/* Endpoint, EP2 Bulk Out */
	USB_ENDPOINT_DESC_SIZE,                   /* bLength */
	USB_ENDPOINT_DESCRIPTOR_TYPE,             /* bDescriptorType */
	0x02,                                     /* bEndpointAddress */
	USB_ENDPOINT_TYPE_BULK,                   /* bmAttributes */
	SHORT_TO_CHAR(0x0200),                    /* wMaxPacketSize */
	0x01,          /* 32ms */                 /* bInterval */
};

volatile const unsigned char other_speed_conf_desc_fs_[] = {
	/* Configuration 1 */
	USB_CONFIGUARTION_DESC_SIZE,              /* bLength */
	USB_OTHER_SPEED_CONFIG_DESCRIPTOR_TYPE,   /* bDescriptorType */
	SHORT_TO_CHAR((
	USB_CONFIGUARTION_DESC_SIZE +
	USB_INTERFACE_DESC_SIZE     +
	NUM_ENDPOINTS * USB_ENDPOINT_DESC_SIZE))
	,                                         /* wTotalLength */
	0x01,                                     /* bNumInterfaces */
	0x01,                                     /* bConfigurationValue */
	0x04,                                     /* iConfiguration */
	USB_CONFIG_BUS_POWERED                    /* bmAttributes */
	/* | USB_CONFIG_REMOTE_WAKEUP */,
	0x32,          							  /* bMaxPower */
	/* Interface 0, Alternate Setting 0, Class Code Unknown */
	USB_INTERFACE_DESC_SIZE,                  /* bLength */
	USB_INTERFACE_DESCRIPTOR_TYPE,            /* bDescriptorType */
	0x00,                                     /* bInterfaceNumber */
	0x00,                                     /* bAlternateSetting */
	NUM_ENDPOINTS,                            /* bNumEndpoints */
	0x08,                                     /* bInterfaceClass, USB_CLASS_VENDOR_SPECIFIC */
	0x06,                                     /* bInterfaceSubClass, USB_SUBCLASS_CODE_UNKNOWN */
	0x50,                                     /* bInterfaceProtocol, USB_PROTOCOL_CODE_UNKNOWN */
	0x05,                                     /* iInterface, STR_INDEX_INTERFACE */
	/* Endpoint, EP1 Bulk In */
	USB_ENDPOINT_DESC_SIZE,                   /* bLength */
	USB_ENDPOINT_DESCRIPTOR_TYPE,             /* bDescriptorType */
	0x81,                                     /* bEndpointAddress */
	USB_ENDPOINT_TYPE_BULK,                   /* bmAttributes */
	SHORT_TO_CHAR(0x0040),                    /* wMaxPacketSize */
	0x01,          /* 32ms */                 /* bInterval */
	/* Endpoint, EP2 Bulk Out */
	USB_ENDPOINT_DESC_SIZE,                   /* bLength */
	USB_ENDPOINT_DESCRIPTOR_TYPE,             /* bDescriptorType */
	0x02,                                     /* bEndpointAddress */
	USB_ENDPOINT_TYPE_BULK,                   /* bmAttributes */
	SHORT_TO_CHAR(0x0040),                    /* wMaxPacketSize */
	0x01,          /* 32ms */                 /* bInterval */
};

#endif /*SLS_USB_H_*/
