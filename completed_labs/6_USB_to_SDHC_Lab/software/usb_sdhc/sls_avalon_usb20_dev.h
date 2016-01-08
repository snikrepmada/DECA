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
 *********************************************************************************************/

//#pragma pack(1)

typedef struct Usb_Control_Request
{
    struct bmrequesttype
    {
        unsigned char Recepient     :5;
        unsigned char RequestType   :2;
        unsigned char Direction     :1;

    }bmRequestType;
    unsigned char bRequest;
    union windex
    {
        unsigned short int  Value;
        unsigned char       Byte[2];

    }wIndex;
    union wvalue
    {
        unsigned short int  Value;
        unsigned char       Byte[2];

    }wValue;
    unsigned short int wLength;

}__attribute__ ((packed,aligned(1))) __USB_CONTROL_REQUEST ;

/********************************************************************************************

usb_ctrlep_req 		: indicating pointer to control request structure

currentStage		: indicating current control request is in which stage
					  0-Setup 		Stage
					  1-Data  		Stage
					  2-Handshake 	Stage

isThereDataStage	: indicating whether there is a data transfer stage between
					  setup stage and handshake stage
					  0-OUT (control write)
					  1-IN  (control read)
					  2-No Data Stage (Direct Handshake stage Needed)

PDataStageData		: indicating pointer to data came in data stage of control request

PHandshakeStageData	: indicating pointer to data came in Handshake stage of control Request

********************************************************************************************/

typedef struct Control_Request_Status __CONTROL_REQUEST_STATUS;

struct Control_Request_Status
{
	volatile unsigned char 	*PHandshakeStageData;
    volatile unsigned char 	*PDataStageData;
    unsigned int 			currentStage;
    unsigned int 			isThereDataStage;
	unsigned int 			sizeOfDataStageData;
	unsigned int 			sizeOfHandshakeStageData;
    __USB_CONTROL_REQUEST 	*PUsbCtrlReq;
};
