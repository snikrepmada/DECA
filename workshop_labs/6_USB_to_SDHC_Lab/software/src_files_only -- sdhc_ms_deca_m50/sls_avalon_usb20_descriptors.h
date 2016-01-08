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
 *  (v1.3.4)      	    1> Added report_descriptor macro
 *
 *********************************************************************************************/

#ifndef  __USB20_DEVICE_DESCRITOR_DEFINES_H
#define  __USB20_DEVICE_DESCRITOR_DEFINES_H

/* USB Descriptor Types */
#define USB_DEVICE_DESCRIPTOR_TYPE             1
#define USB_CONFIGURATION_DESCRIPTOR_TYPE      2
#define USB_STRING_DESCRIPTOR_TYPE             3
#define USB_INTERFACE_DESCRIPTOR_TYPE          4
#define USB_ENDPOINT_DESCRIPTOR_TYPE           5
#define USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE   6
#define USB_OTHER_SPEED_CONFIG_DESCRIPTOR_TYPE 7
#define USB_INTERFACE_POWER_DESCRIPTOR_TYPE    8

/* USB Device Classes */
#define USB_DEVICE_CLASS_RESERVED              0x00
#define USB_DEVICE_CLASS_AUDIO                 0x01
#define USB_DEVICE_CLASS_COMMUNICATIONS        0x02
#define USB_DEVICE_CLASS_HUMAN_INTERFACE       0x03
#define USB_DEVICE_CLASS_MONITOR               0x04
#define USB_DEVICE_CLASS_PHYSICAL_INTERFACE    0x05
#define USB_DEVICE_CLASS_POWER                 0x06
#define USB_DEVICE_CLASS_PRINTER               0x07
#define USB_DEVICE_CLASS_STORAGE               0x08
#define USB_DEVICE_CLASS_HUB                   0x09
#define USB_DEVICE_CLASS_VENDOR_SPECIFIC       0xFF

/* bmAttributes in Endpoint Descriptor */
#define USB_ENDPOINT_TYPE_MASK                 0x03
#define USB_ENDPOINT_TYPE_CONTROL              0x00
#define USB_ENDPOINT_TYPE_ISOCHRONOUS          0x01
#define USB_ENDPOINT_TYPE_BULK                 0x02
#define USB_ENDPOINT_TYPE_INTERRUPT            0x03
#define USB_ENDPOINT_SYNC_MASK                 0x0C
#define USB_ENDPOINT_SYNC_NO_SYNCHRONIZATION   0x00
#define USB_ENDPOINT_SYNC_ASYNCHRONOUS         0x04
#define USB_ENDPOINT_SYNC_ADAPTIVE             0x08
#define USB_ENDPOINT_SYNC_SYNCHRONOUS          0x0C
#define USB_ENDPOINT_USAGE_MASK                0x30
#define USB_ENDPOINT_USAGE_DATA                0x00
#define USB_ENDPOINT_USAGE_FEEDBACK            0x10
#define USB_ENDPOINT_USAGE_IMPLICIT_FEEDBACK   0x20
#define USB_ENDPOINT_USAGE_RESERVED            0x30

/* bmAttributes in Configuration Descriptor */
#define USB_CONFIG_POWERED_MASK                0xC0
#define USB_CONFIG_BUS_POWERED                 0x80
#define USB_CONFIG_SELF_POWERED                0x40
#define USB_CONFIG_REMOTE_WAKEUP               0x20

/************* 11 Standard request For Control Transfer ***************/
#define device_id             0x01
#define get_status            0x00
#define clear_feature         0x01
#define set_feature           0x03
#define set_address           0x05
#define get_descriptor        0x06
#define set_descriptor        0x07
#define get_configuration     0x08
#define set_configuration     0x09
#define get_interface         0x0A
#define set_interface         0x0B
#define sync_frame            0x0C

/**********************************************************************/
#define report_descriptor	            0x22  //HID

#define device_qualifier                0x06
#define other_speed_configuration       0x07

#define USB_DEVICE_DESC_SIZE                  sizeof(DEVICE_DESCRIPTOR)
#define USB_DEVICE_QUALIFIER_DESC_SIZE        sizeof(DEVICE_QUALIFIER)
#define USB_CONFIGUARTION_DESC_SIZE           sizeof(CONFIG_DESCRIPTOR)
#define USB_INTERFACE_DESC_SIZE               sizeof(INTERFACE_DESCRIPTOR)
#define USB_ENDPOINT_DESC_SIZE                sizeof(ENDPOINT_DESCRIPTOR)
#define CONFIG_DESCRI_SIZE                    (0x09)

typedef struct Device_Descriptor
{
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned short bcdUSB;
	unsigned char  bDeviceClass;
	unsigned char  bDeviceSubClass;
	unsigned char  bDeviceProtocol;
	unsigned char  bMaxPacketSize;
	unsigned short idVendor;
	unsigned short idProduct;
	unsigned short bcdDevice;
	unsigned char  iManufacturer;
	unsigned char  iProduct;
	unsigned char  iSerialNumber;
	unsigned char  bNumConfiguration;

}__attribute__ ((packed,aligned(1)))  DEVICE_DESCRIPTOR,*PDEVICE_DESCRIPTOR;// 10 char 4 short = 18 total bytes ( 0x12 bytes )

typedef struct Configuration_Descriptor
{
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned short wTotalLength;
	unsigned char  bNumInterface;
	unsigned char  bConfigurationValue;
	unsigned char  iConfiguration;
	unsigned char  bmAttributes;
	unsigned char  MaxPower;

}__attribute__ ((packed,aligned(1))) CONFIG_DESCRIPTOR,*PCONFIG_DESCRIPTOR;// 7 char 1 short = 9 bytes total ( 0x09 bytes )

typedef struct Interface_Descriptor
{
	unsigned char bLength;
	unsigned char bDescriptorType;
	unsigned char InterafceNumber;
	unsigned char bAlternateSetting;
	unsigned char NumEndpoint;
	unsigned char bInterfaceClass;
	unsigned char bInterfaceSubClass;
	unsigned char bInterfaceProtocol;
	unsigned char iInterace;

}__attribute__ ((packed,aligned(1))) INTERFACE_DESCRIPTOR,*PINTERFACE_DESCRIPTOR;// 9 char 0 short = 9 bytes total ( 0x09 bytes )

typedef struct Endpoint_Descriptor
{
	unsigned char   bLength;
	unsigned char   bDecriptorType;
	unsigned char   bEndpointAddress;
	unsigned char   bmAttribute;
	unsigned short  wMaxPacketSize;
	unsigned char   bInterval;

}__attribute__ ((packed,aligned(1))) ENDPOINT_DESCRIPTOR,*PENDPOINT_DESCRIPTOR;// 5 char 1 short = 7 bytes total ( 0x07 bytes )

typedef struct String_Descreptor
{
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned int   bString/*[]*/;

}__attribute__ ((packed,aligned(1))) STRING_DESCRIPTOR;

#define USB_FEATURE_REMOTE_WAKEUP              1

typedef struct Device_Qualifier /* should be changed according to the current selected speed configuration */
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned short bcdUSB;
    unsigned char  bDeviceClass;
    unsigned char  bDeviceSubClass;
    unsigned char  bDeviceProtocol;
    unsigned char  bMaxPacketSize;
    unsigned char  bNumConfiguration;
    unsigned char  bReserved;

}__attribute__ ((packed,aligned(1)))  DEVICE_QUALIFIER,*PDEVICE_QUALIFIER;// 6 char 2 short = 10 bytes total ( 0x0A bytes )

typedef struct _USB_COMMON_DESCRIPTOR
{
	char  bLength;
	char  bDescriptorType;

}__attribute__ ((packed,aligned(1)))  USB_COMMON_DESCRIPTOR;

#endif
