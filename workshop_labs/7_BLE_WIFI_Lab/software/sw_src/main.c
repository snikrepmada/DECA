/******************************************************************************
 * NAME:         main.c
 *
 * DESCRIPTION:  Main program.
 *
 * NOTES:
 *   Performs system initialization and main loop processing.
 *
 * REFERENCES:
 *   None.
 *
 * HISTORY:
 *   2015/5/2:  AB - Initial version, supporting Rev B
 *   2015/5/9:  TD - Modified to support Rev B and Rev C boards
 ******************************************************************************/

#define _MAIN_C
#define DECA_REVB 1
/******************************************************************************
 * INCLUDE FILES
 ******************************************************************************/

#include <io.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/alt_stdio.h>
#include <sys/alt_irq.h>

#include "altera_avalon_pio_regs.h"
#include "altera_avalon_spi_regs.h"

#include "system.h"
#include "drivers/i2c.h"
#include "drivers/spi.h"

#include "devices/hdc1000.h"
#include "devices/lis332ar.h"
#include "devices/lis2dh12.h"

#include "simplelink/include/simplelink.h"
#include "simplelink/source/protocol.h"



/******************************************************************************
 * DEFINES
 ******************************************************************************/
#define SUCCESS         0
#define MAX_SSID_LEN    32
#define MAX_PASSKEY_LEN 32
#define BAUD_RATE       115200

#define PING_INTERVAL        1000
#define PING_SIZE            20
#define PING_REQUEST_TIMEOUT 3000
#define PING_ATTEMPT         3

#define SL_STOP_TIMEOUT        					0xFF


#define SET_STATUS_BIT(status_variable, bit)    status_variable |= (1<<(bit))
#define CLR_STATUS_BIT(status_variable, bit)    status_variable &= ~(1<<(bit))
#define GET_STATUS_BIT(status_variable, bit)    (0 != (status_variable & (1<<(bit))))

#define IS_CONNECTED(status_variable)           GET_STATUS_BIT(status_variable, \
                                                               STATUS_BIT_CONNECTION)
#define IS_IP_ACQUIRED(status_variable)          GET_STATUS_BIT(status_variable, \
                                                               STATUS_BIT_IP_ACQUIRED)
#define IS_PING_DONE(status_variable)           GET_STATUS_BIT(status_variable, \
                                                               STATUS_BIT_PING_DONE)
#define IS_IP_LEASED(status_variable)           GET_STATUS_BIT(status_variable, \
                                                               STATUS_BIT_IP_LEASED)
#define IS_STA_CONNECTED(status_variable)       GET_STATUS_BIT(status_variable, \
                                                               STATUS_BIT_STA_CONNECTED)

#define ASSERT_ON_ERROR(error_code) \
            {\
                /* Handling the error-codes is specifc to the application */ \
                if (error_code < 0) return error_code; \
                /* else, continue w/ execution */ \
            }

#define pal_Memset(x,y,z)   memset((void *)x,y,z)
#define pal_Memcpy(x,y,z)   memcpy((void *)x, (const void *)y, z)
#define pal_Memcmp(x,y,z)   memcmp((const void *)x, (const void *)y, z)
#define pal_Strlen(x)       strlen((const char *)x)
#define pal_Strcmp(x,y)     strcmp((const char *)x, (const char *)y)
#define pal_Strcpy(x,y)     strcpy((char *)x, (const char *)y)
#define pal_Strstr(x,y)     strstr((const char *)x, (const char *)y)
#define pal_Strncmp(x,y,z)  strncmp((const char *)x, (const char *)y, z)
#define pal_Strcat(x,y)     strcat((char *)x, (const char *)y)

#define LOOP_FOREVER() \
            {\
                while(1); \
            }

/******************************************************************************
 * TYPEDEFS
 ******************************************************************************/
typedef enum{
    STATUS_BIT_CONNECTION =  0, /* If this bit is:
                                 *      1 in a 'status_variable', the device is connected to the AP
                                 *      0 in a 'status_variable', the device is not connected to the AP
                                 */

    STATUS_BIT_IP_ACQUIRED,       /* If this bit is:
                                  *      1 in a 'status_variable', the device has acquired an IP
                                  *      0 in a 'status_variable', the device has not acquired an IP
                                  */

    STATUS_BIT_PING_DONE,        /* If this bit is:
                                  *      1 in a 'status_variable', the device has completed the ping operation
                                  *      0 in a 'status_variable', the device has not completed the ping operation
                                  */

    STATUS_BIT_IP_LEASED,        /* If this bit is:
                                  *      1 in a 'status_variable', the device has a client connected to it
                                  *      and the IP has been leased
                                  *      0 in a 'status_variable', the device has no clients connected to it
                                  */
    STATUS_BIT_STA_CONNECTED     /* If this bit is:
                                  *      1 in a 'status_variable', a station has connected to the device
                                  *      and the IP has been leased
                                  *      0 in a 'status_variable', the station couldn't connect to the device
                                  */
}e_StatusBits;

typedef enum{
    DEVICE_NOT_IN_STATION_MODE = -0x7D0,        /* Choosing this number to avoid overlap w/ host-driver's error codes */

    STATUS_CODE_MAX = -0xBB8
}e_AppStatusCodes;

typedef struct{
    _u8 SSID[MAX_SSID_LEN];
    _i32 encryption;
    _u8 password[MAX_PASSKEY_LEN];
}UserInfo;


/******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************/
_u8 g_Status = 0;
_u32 g_PingPacketsRecv = 0;
_u32 sta_IP = 0;

_u8 g_auth_name[MAX_AUTH_NAME_LEN+1];
_u8 g_auth_password[MAX_AUTH_PASSWORD_LEN+1];
_u8 g_auth_realm[MAX_AUTH_REALM_LEN+1];

_u8 g_domain_name[MAX_DOMAIN_NAME_LEN];
_u8 g_device_urn[MAX_DEVICE_URN_LEN];

_u8 POST_token[] = "__SL_P_L.D";
_u8 GET_token[]  = "__SL_G_LED";
_u8 GET_TEMP_token[]  = "__SL_G_TEM";
_u8 GET_HUMID_token[]  = "__SL_G_HUM";
_u8 GET_XAXIS_token[]  = "__SL_G_XAX";
_u8 GET_YAXIS_token[]  = "__SL_G_YAX";
_u8 GET_ZAXIS_token[]  = "__SL_G_ZAX";

/******************************************************************************
 * PROTOTYPES
 ******************************************************************************/
#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
static void slInterrupt(void* context);
#else
static void slInterrupt(void* context, alt_u32 id);
#endif

static _i32 configureSimpleLinkToDefaultState(_i8 *);
static _i32 initializeAppVariables();

static _i32 set_authentication_check (_u8 enable);
static _i32 get_auth_name (_u8 *auth_name);
static _i32 get_auth_password (_u8 *auth_password);
static _i32 get_auth_realm (_u8 *auth_realm);
static _i32 get_device_urn (_u8 *device_urn);
static _i32 get_domain_name (_u8 *domain_name);

static _i32 configureSimpleLinkToDefaultState(_i8 *pConfig)
{
    SlVersionFull   ver = {0};
    _WlanRxFilterOperationCommandBuff_t  RxFilterIdMask = {0};

    _u8           val = 1;
    _u8           configOpt = 0;
    _u8           configLen = 0;
    _u8           power = 0;

    _i32          retVal = -1;
    _i32          mode = -1;

    mode = sl_Start(0, pConfig, 0);
    ASSERT_ON_ERROR(mode);

        /* If the device is not in station-mode, try configuring it in station-mode */
    if (ROLE_STA != mode)
    {
        if (ROLE_AP == mode)
        {
            /* If the device is in AP mode, we need to wait for this event before doing anything */
            while(!IS_IP_ACQUIRED(g_Status));
        }

        /* Switch to STA role and restart */
        retVal = sl_WlanSetMode(ROLE_STA);
        ASSERT_ON_ERROR(retVal);

        retVal = sl_Stop(SL_STOP_TIMEOUT);
        ASSERT_ON_ERROR(retVal);

        retVal = sl_Start(0, pConfig, 0);
        ASSERT_ON_ERROR(retVal);

        /* Check if the device is in station again */
        if (ROLE_STA != retVal)
        {
            /* We don't want to proceed if the device is not coming up in station-mode */
            ASSERT_ON_ERROR(DEVICE_NOT_IN_STATION_MODE);
        }
    }

    /* Get the device's version-information */
    configOpt = SL_DEVICE_GENERAL_VERSION;
    configLen = sizeof(ver);
    retVal = sl_DevGet(SL_DEVICE_GENERAL_CONFIGURATION, &configOpt, &configLen, (_u8 *)(&ver));
    ASSERT_ON_ERROR(retVal);

    printf("Host Driver Version: %s\n",SL_DRIVER_VERSION);
    printf("Build Version %d.%d.%d.%d.31.%d.%d.%d.%d.%d.%d.%d.%d\n",
                        ver.NwpVersion[0],ver.NwpVersion[1],ver.NwpVersion[2],ver.NwpVersion[3],
                        ver.ChipFwAndPhyVersion.FwVersion[0],ver.ChipFwAndPhyVersion.FwVersion[1],
                        ver.ChipFwAndPhyVersion.FwVersion[2],ver.ChipFwAndPhyVersion.FwVersion[3],
                        ver.ChipFwAndPhyVersion.PhyVersion[0],ver.ChipFwAndPhyVersion.PhyVersion[1],
                        ver.ChipFwAndPhyVersion.PhyVersion[2],ver.ChipFwAndPhyVersion.PhyVersion[3]);

    /* Set connection policy to Auto + SmartConfig (Device's default connection policy) */
    retVal = sl_WlanPolicySet(SL_POLICY_CONNECTION, SL_CONNECTION_POLICY(1, 0, 0, 0, 1), NULL, 0);
    //ASSERT_ON_ERROR(retVal);

    /* Remove all profiles */
    retVal = sl_WlanProfileDel(0xFF);
    //ASSERT_ON_ERROR(retVal);

    /*
     * Device in station-mode. Disconnect previous connection if any
     * The function returns 0 if 'Disconnected done', negative number if already disconnected
     * Wait for 'disconnection' event if 0 is returned, Ignore other return-codes
     */
    retVal = sl_WlanDisconnect();
    if(0 == retVal)
    {
        /* Wait */
        while(IS_CONNECTED(g_Status));
    }

    /* Enable DHCP client*/
    retVal = sl_NetCfgSet(SL_IPV4_STA_P2P_CL_DHCP_ENABLE,1,1,&val);
    ASSERT_ON_ERROR(retVal);

    /* Disable scan */
    configOpt = SL_SCAN_POLICY(0);
    retVal = sl_WlanPolicySet(SL_POLICY_SCAN , configOpt, NULL, 0);
//    ASSERT_ON_ERROR(retVal);

    /* Set Tx power level for station mode
       Number between 0-15, as dB offset from max power - 0 will set maximum power */
    power = 0;
    retVal = sl_WlanSet(SL_WLAN_CFG_GENERAL_PARAM_ID, WLAN_GENERAL_PARAM_OPT_STA_TX_POWER, 1, (_u8 *)&power);
    ASSERT_ON_ERROR(retVal);

    /* Set PM policy to normal */
    retVal = sl_WlanPolicySet(SL_POLICY_PM , SL_NORMAL_POLICY, NULL, 0);
    //ASSERT_ON_ERROR(retVal);

    /* Unregister mDNS services */
    retVal = sl_NetAppMDNSUnRegisterService(0, 0);
    ASSERT_ON_ERROR(retVal);

    /* Remove  all 64 filters (8*8) */
    memset(RxFilterIdMask.FilterIdMask, 0xFF, 8);
    retVal = sl_WlanRxFilterSet(SL_REMOVE_RX_FILTER, (_u8 *)&RxFilterIdMask,
                       sizeof(_WlanRxFilterOperationCommandBuff_t));
    ASSERT_ON_ERROR(retVal);

    retVal = sl_Stop(SL_STOP_TIMEOUT);
    ASSERT_ON_ERROR(retVal);

    retVal = initializeAppVariables();
    ASSERT_ON_ERROR(retVal);

    return retVal; /* Success */
}

/*!
    \brief This function initializes the application variables

    \param[in]  None

    \return     0 on success, negative error-code on error
*/
static _i32 initializeAppVariables()
{
    g_Status = 0;
    g_PingPacketsRecv = 0;
    sta_IP = 0;

    return SUCCESS;
}

static _i16 GetUserNum()
{
    _i32   flag = 0;
    _i8    input[20] = {'\0'};
    _i16   value = -1;

    while (!flag)
    {
        if(scanf("%s",input,sizeof(input)) != 0)
        {
            value = atoi((const char *)input);
            if (value > 0 && value < 5 )
            {
                flag = 1;
            }
            else
            {
                printf("Invalid entry. Please try again:\n");
            }
        }
    }

    return value;
}

static UserInfo GetUserInput()
{
    UserInfo UserFunction;
    _i32   eflag = -1;
    _i32   wepflag = -1;
    _i32   length = -1;

    printf("Please input the SSID name for AP mode: \n");
    //scanf("%[^\n]s",UserFunction.SSID,MAX_SSID_LEN);
    //fgets(UserFunction.SSID,MAX_SSID_LEN,stdin);
    strcpy(UserFunction.SSID, "DallasLogicWIFI"); // fixed SSID name can be entered here.

    printf("Encryption Types for AP mode:\n");
    printf("1:  Open\n");
    printf("2:  WEP\n");
    printf("3:  WPA\n");
    printf("Please enter the corresponding number for the encryption type: \n");
    //UserFunction.encryption = GetUserNum();
    UserFunction.encryption = 1;

    if (UserFunction.encryption != 1)
    {
        printf ("Please enter the password for AP mode: \n");
        scanf("%s",UserFunction.password,MAX_PASSKEY_LEN);
    }

    return UserFunction;
}

static _i32 ConfigureAPmode(UserInfo UserParams)
{
    _i32 retVal = -1;
    _u8 val = SL_SEC_TYPE_OPEN;

    /* Configure the SSID of the CC3100 */
    retVal = sl_WlanSet(SL_WLAN_CFG_AP_ID, WLAN_AP_OPT_SSID,
               strlen((const char *)UserParams.SSID),
               UserParams.SSID);
    ASSERT_ON_ERROR(retVal);

    /* Configure the Security parameter in the AP mode */
    switch(UserParams.encryption)
    {
        case 1:
        {
            val = SL_SEC_TYPE_OPEN;
            retVal = sl_WlanSet(SL_WLAN_CFG_AP_ID,
                       WLAN_AP_OPT_SECURITY_TYPE,
                       1, &val);
            ASSERT_ON_ERROR(retVal);
        }
        break;

        case 2:
        {
            val = SL_SEC_TYPE_WEP;
            retVal = sl_WlanSet(SL_WLAN_CFG_AP_ID,
                       WLAN_AP_OPT_SECURITY_TYPE,
                       1, &val);
            ASSERT_ON_ERROR(retVal);

            retVal = sl_WlanSet(SL_WLAN_CFG_AP_ID,
                       WLAN_AP_OPT_PASSWORD,
                       strlen((const char *)UserParams.password),
                       UserParams.password);
            ASSERT_ON_ERROR(retVal);
        }
        break;

        case 3:
        {
            val = SL_SEC_TYPE_WPA;
            retVal = sl_WlanSet(SL_WLAN_CFG_AP_ID,
                       WLAN_AP_OPT_SECURITY_TYPE,
                       1, &val);
            ASSERT_ON_ERROR(retVal);

            retVal = sl_WlanSet(SL_WLAN_CFG_AP_ID,
                       WLAN_AP_OPT_PASSWORD,
                       strlen((const char *)UserParams.password),
                       UserParams.password);
            ASSERT_ON_ERROR(retVal);
        }
        break;
    }

    return SUCCESS;
}

void SimpleLinkGeneralEventHandler(SlDeviceEvent_t *pDevEvent)
{
    /*
     * Most of the general errors are not FATAL are are to be handled
     * appropriately by the application
     */
    printf(" [GENERAL EVENT] \r\n");
}

void SimpleLinkWlanEventHandler(SlWlanEvent_t *pWlanEvent)
{
	if(pWlanEvent == NULL)
	        printf(" [WLAN EVENT] NULL Pointer Error \n\r");

	     switch(pWlanEvent->Event)
	    {
	        case SL_WLAN_CONNECT_EVENT:
	        {
	            SET_STATUS_BIT(g_Status, STATUS_BIT_CONNECTION);

	            /*
	             * Information about the connected AP (like name, MAC etc) will be
	             * available in 'slWlanConnectAsyncResponse_t' - Applications
	             * can use it if required
	             *
	             * slWlanConnectAsyncResponse_t *pEventData = NULL;
	             * pEventData = &pWlanEvent->EventData.STAandP2PModeWlanConnected;
	             *
	             */
	        }
	        break;

	        case SL_WLAN_DISCONNECT_EVENT:
	        {
	            slWlanConnectAsyncResponse_t*  pEventData = NULL;

	            CLR_STATUS_BIT(g_Status, STATUS_BIT_CONNECTION);
	            CLR_STATUS_BIT(g_Status, STATUS_BIT_IP_ACQUIRED);

	            pEventData = &pWlanEvent->EventData.STAandP2PModeDisconnected;

	            /* If the user has initiated 'Disconnect' request, 'reason_code' is SL_USER_INITIATED_DISCONNECTION */
	            if(SL_USER_INITIATED_DISCONNECTION == pEventData->reason_code)
	            {
	                printf(" Device disconnected from the AP on application's request \r\n");
	            }
	            else
	            {
	                printf(" Device disconnected from the AP on an ERROR..!! \r\n");
	            }
	        }
	        break;

	        case SL_WLAN_STA_CONNECTED_EVENT:
	        {
	            SET_STATUS_BIT(g_Status, STATUS_BIT_STA_CONNECTED);
	        }
	        break;

	        case SL_WLAN_STA_DISCONNECTED_EVENT:
	        {
	            CLR_STATUS_BIT(g_Status, STATUS_BIT_STA_CONNECTED);
	            CLR_STATUS_BIT(g_Status, STATUS_BIT_IP_LEASED);
	        }
	        break;

	        default:
	        {
	            printf(" [WLAN EVENT] Unexpected event \r\n");
	        }
	        break;
	     }
}

void SimpleLinkNetAppEventHandler(SlNetAppEvent_t *pNetAppEvent)
{
    if(pNetAppEvent == NULL)
        printf(" [NETAPP EVENT] NULL Pointer Error \n\r");

    switch(pNetAppEvent->Event)
    {
        case SL_NETAPP_IPV4_IPACQUIRED_EVENT:
        {
        	printf(" [NETAPP EVENT] IP Acquire \n\r");
            SlIpV4AcquiredAsync_t *pEventData = NULL;

            SET_STATUS_BIT(g_Status, STATUS_BIT_IP_ACQUIRED);

            pEventData = &pNetAppEvent->EventData.ipAcquiredV4;
        }
        break;

        case SL_NETAPP_IP_LEASED_EVENT:
        {
        	printf(" [NETAPP EVENT] Lease Aquire \n\r");
            sta_IP = pNetAppEvent->EventData.ipLeased.ip_address;
            SET_STATUS_BIT(g_Status, STATUS_BIT_IP_LEASED);
        }
        break;

        default:
        {
            printf(" [NETAPP EVENT] Unexpected event \r\n");
        }
        break;
    }
}


void SimpleLinkHttpServerCallback(SlHttpServerEvent_t *pEvent,
                                  SlHttpServerResponse_t *pResponse)
{
	static alt_u16 x_axis = 0x1111,
			y_axis = 0x2222,
			z_axis = 0x3333;
	static alt_u16 temperature = 0x4444,
			humidity = 0x5555;
	int tempCorrection = 0;
	char reply_buffer [50];
	int  replySz;

	printf(" [HTTP EVENT] event \r\n");

	if(pEvent == NULL || pResponse == NULL)
		printf(" [HTTP EVENT] NULL Pointer Error \n\r");

	    switch (pEvent->Event)
	    {
	        case SL_NETAPP_HTTPGETTOKENVALUE_EVENT:
	        {
	            _u8 status = 0;
	            _u8 *ptr = 0;

	            ptr = pResponse->ResponseData.token_value.data;
	            pResponse->ResponseData.token_value.len = 0;
	            if(pal_Memcmp(pEvent->EventData.httpTokenName.data, GET_token,
	                                         pal_Strlen(GET_token)) == 0)
	            {
	            	printf("LED event \n\r");

	            	status = IORD (BLUE_LEDS_BASE, 0);

	                pal_Memcpy(ptr, "LED0_", pal_Strlen("LED0_"));
	                ptr += 5;
	                pResponse->ResponseData.token_value.len += 5;
	                if(status & 0x01)
	                {
	                    pal_Memcpy(ptr, "OFF", pal_Strlen("OFF"));
	                    ptr += 3;
	                    pResponse->ResponseData.token_value.len += 3;
	                }
	                else
	                {
	                    pal_Memcpy(ptr, "ON", pal_Strlen("ON"));
	                    ptr += 2;
	                    pResponse->ResponseData.token_value.len += 2;

	                }

	                pal_Memcpy(ptr, "LED1_", pal_Strlen("LED1_"));
	                ptr += 5;
	                pResponse->ResponseData.token_value.len += 5;
	                if(status & 0x02)
	                {
	                    pal_Memcpy(ptr, "OFF", pal_Strlen("OFF"));
	                    ptr += 3;
	                    pResponse->ResponseData.token_value.len += 3;
	                }
	                else
	                {
	                    pal_Memcpy(ptr, "ON", pal_Strlen("ON"));
	                    ptr += 2;
	                    pResponse->ResponseData.token_value.len += 2;

	                }

	                pal_Memcpy(ptr,",LED2_", pal_Strlen(",LED2_"));
	                ptr += 6;
	                pResponse->ResponseData.token_value.len += 6;
	                if(status & 0x04)
	                {
	                    pal_Memcpy(ptr, "OFF", pal_Strlen("OFF"));
	                    ptr += 3;
	                    pResponse->ResponseData.token_value.len += 3;
	                }
	                else
	                {
	                    pal_Memcpy(ptr, "ON", pal_Strlen("ON"));
	                    ptr += 2;
	                    pResponse->ResponseData.token_value.len += 2;

	                }

	                pal_Memcpy(ptr, "LED3_", pal_Strlen("LED3_"));
	                ptr += 5;
	                pResponse->ResponseData.token_value.len += 5;
	                if(status & 0x08)
	                {
	                    pal_Memcpy(ptr, "OFF", pal_Strlen("OFF"));
	                    ptr += 3;
	                    pResponse->ResponseData.token_value.len += 3;
	                }
	                else
	                {
	                    pal_Memcpy(ptr, "ON", pal_Strlen("ON"));
	                    ptr += 2;
	                    pResponse->ResponseData.token_value.len += 2;
	                }

	                pal_Memcpy(ptr, "LED4_", pal_Strlen("LED4_"));
	                ptr += 5;
	                pResponse->ResponseData.token_value.len += 5;
	                if(status & 0x10)
	                {
	                    pal_Memcpy(ptr, "OFF", pal_Strlen("OFF"));
	                    ptr += 3;
	                    pResponse->ResponseData.token_value.len += 3;
	                }
	                else
	                {
	                    pal_Memcpy(ptr, "ON", pal_Strlen("ON"));
	                    ptr += 2;
	                    pResponse->ResponseData.token_value.len += 2;
	                }
	                pal_Memcpy(ptr, "LED5_", pal_Strlen("LED5_"));
	                ptr += 5;
	                pResponse->ResponseData.token_value.len += 5;
	                if(status & 0x20)
	                {
	                    pal_Memcpy(ptr, "OFF", pal_Strlen("OFF"));
	                    ptr += 3;
	                    pResponse->ResponseData.token_value.len += 3;
	                }
	                else
	                {
	                    pal_Memcpy(ptr, "ON", pal_Strlen("ON"));
	                    ptr += 2;
	                    pResponse->ResponseData.token_value.len += 2;
	                }

	                pal_Memcpy(ptr, "LED6_", pal_Strlen("LED6_"));
	                ptr += 5;
	                pResponse->ResponseData.token_value.len += 5;
	                if(status & 0x40)
	                {
	                    pal_Memcpy(ptr, "OFF", pal_Strlen("OFF"));
	                    ptr += 3;
	                    pResponse->ResponseData.token_value.len += 3;
	                }
	                else
	                {
	                    pal_Memcpy(ptr, "ON", pal_Strlen("ON"));
	                    ptr += 2;
	                    pResponse->ResponseData.token_value.len += 2;
	                }
	                pal_Memcpy(ptr, "LED7_", pal_Strlen("LED7_"));
	                ptr += 5;
	                pResponse->ResponseData.token_value.len += 5;
	                if(status & 0x80)
	                {
	                    pal_Memcpy(ptr, "OFF", pal_Strlen("OFF"));
	                    ptr += 3;
	                    pResponse->ResponseData.token_value.len += 3;
	                }
	                else
	                {
	                    pal_Memcpy(ptr, "ON", pal_Strlen("ON"));
	                    ptr += 2;
	                    pResponse->ResponseData.token_value.len += 2;

	                }
	                *ptr = '\0';
	            }

	            if(pal_Memcmp(pEvent->EventData.httpTokenName.data, GET_TEMP_token,
	            	           pal_Strlen(GET_TEMP_token)) == 0)
	            {
	        		//lis332arRead(&x_axis, &y_axis, &z_axis);
	        		hdc1000Read(&temperature, &humidity);
	        		tempCorrection = temperature - 31755;

	        		replySz = sprintf(ptr, "TEMP_%d", tempCorrection);
	        		pResponse->ResponseData.token_value.len += replySz;

	            	//pal_Memcpy(ptr, "TEMP_", pal_Strlen("TEMP_"));
	            	//ptr += 5;
	            	//pResponse->ResponseData.token_value.len += 5;
	            }

	            if(pal_Memcmp(pEvent->EventData.httpTokenName.data, GET_HUMID_token,
	            	           pal_Strlen(GET_HUMID_token)) == 0)
	            {
	            	//hdc1000Read(&temperature, &humidity);

	        		replySz = sprintf(ptr, "HUMI_%d", humidity);
	        		pResponse->ResponseData.token_value.len += replySz;

	            	//pal_Memcpy(ptr, "HUMI_", pal_Strlen("HUMI_"));
	            	//ptr += 5;
	            	//pResponse->ResponseData.token_value.len += 5;
	            }

	            if(pal_Memcmp(pEvent->EventData.httpTokenName.data, GET_XAXIS_token,
	            	           pal_Strlen(GET_XAXIS_token)) == 0)
	            {
	            	if(IORD_ALTERA_AVALON_PIO_DATA(DECA_REV_PIO_BASE) == DECA_REVB)
	            		lis332arRead(&x_axis, &y_axis, &z_axis); // REV_B
	            	else
	            	{
	            		initLIS2DH12();
	            		lis2dh12Read(&x_axis, &y_axis, &z_axis); // REV_C
	            	}

	        		replySz = sprintf(ptr, "XAXI_%d", x_axis);
	        		pResponse->ResponseData.token_value.len += replySz;

	            	//pal_Memcpy(ptr, "XAXI_", pal_Strlen("XAXI_"));
	            	//ptr += 5;
	            	//pResponse->ResponseData.token_value.len += 5;
	            }

	            if(pal_Memcmp(pEvent->EventData.httpTokenName.data, GET_YAXIS_token,
	            	           pal_Strlen(GET_YAXIS_token)) == 0)
	            {
	            	//lis332arRead(&x_axis, &y_axis, &z_axis);

	        		replySz = sprintf(ptr, "YAXI_%d", y_axis);
	        		pResponse->ResponseData.token_value.len += replySz;

	            	//pal_Memcpy(ptr, "YAXI_", pal_Strlen("YAXI_"));
	            	//ptr += 5;
	            	//pResponse->ResponseData.token_value.len += 5;
	            }

	            if(pal_Memcmp(pEvent->EventData.httpTokenName.data, GET_ZAXIS_token,
	            	           pal_Strlen(GET_ZAXIS_token)) == 0)
	            {
	            	//lis332arRead(&x_axis, &y_axis, &z_axis);

	        		replySz = sprintf(ptr, "ZAXI_%d", z_axis);
	        		pResponse->ResponseData.token_value.len += replySz;

	            	//pal_Memcpy(ptr, "ZAXI_", pal_Strlen("ZAXI_"));
	            	//ptr += 5;
	            	//pResponse->ResponseData.token_value.len += 5;
	            }

	        }
	        break;

	        case SL_NETAPP_HTTPPOSTTOKENVALUE_EVENT:
	        {
	        	 _u8 led_state;
	            _u8 led = 0;
	            _u8 *ptr = pEvent->EventData.httpPostData.token_name.data;

	            if(pal_Memcmp(ptr, POST_token, pal_Strlen(POST_token)) == 0)
	            {
	                ptr = pEvent->EventData.httpPostData.token_value.data;
	                if(pal_Memcmp(ptr, "LED", 3) != 0)
	                    break;

	                ptr += 3;
	                led = *ptr;
	                ptr += 2;
	                led_state = IORD(BLUE_LEDS_BASE, 0);
	                if(led == '0')
	                {
	                    if(pal_Memcmp(ptr, "ON", 2) == 0)
	                    {
	                        IOWR(BLUE_LEDS_BASE, 0, led_state & 0xfe);
	                    }
	                    else
	                    {
	                    	IOWR(BLUE_LEDS_BASE, 0, led_state | 0x1);
	                    }
	                }
	                else if(led == '1')
	                {
	                    if(pal_Memcmp(ptr, "ON", 2) == 0)
	                    {
	                        IOWR(BLUE_LEDS_BASE, 0, led_state & 0xfd);
	                    }
	                    else
	                    {
	                    	IOWR(BLUE_LEDS_BASE, 0, led_state | 0x2);
	                    }
	                }
	                else if(led == '2')
	                {
	                    if(pal_Memcmp(ptr, "ON", 2) == 0)
	                    {
	                        IOWR(BLUE_LEDS_BASE, 0, led_state & 0xfb);
	                    }
	                    else
	                    {
	                    	IOWR(BLUE_LEDS_BASE, 0, led_state | 0x4);
	                    }
	                }
	                else if(led == '3')
	                {
	                    if(pal_Memcmp(ptr, "ON", 2) == 0)
	                    {
	                        IOWR(BLUE_LEDS_BASE, 0, led_state & 0xf7);
	                    }
	                    else
	                    {
	                    	IOWR(BLUE_LEDS_BASE, 0, led_state | 0x8);
	                    }
	                }
	                else if(led == '4')
	                {
	                    if(pal_Memcmp(ptr, "ON", 2) == 0)
	                    {
	                        IOWR(BLUE_LEDS_BASE, 0, led_state & 0xef);
	                    }
	                    else
	                    {
	                    	IOWR(BLUE_LEDS_BASE, 0, led_state | 0x10);
	                    }
	                }
	                else if(led == '5')
	                {
	                    if(pal_Memcmp(ptr, "ON", 2) == 0)
	                    {
	                        IOWR(BLUE_LEDS_BASE, 0, led_state & 0xdf);
	                    }
	                    else
	                    {
	                    	IOWR(BLUE_LEDS_BASE, 0, led_state | 0x20);
	                    }
	                }
	                else if(led == '6')
	                {
	                    if(pal_Memcmp(ptr, "ON", 2) == 0)
	                    {
	                        IOWR(BLUE_LEDS_BASE, 0, led_state & 0xbf);
	                    }
	                    else
	                    {
	                    	IOWR(BLUE_LEDS_BASE, 0, led_state | 0x40);
	                    }
	                }
	                else if(led == '7')
	                {
	                    if(pal_Memcmp(ptr, "ON", 2) == 0)
	                    {
	                        IOWR(BLUE_LEDS_BASE, 0, led_state & 0x7f);
	                    }
	                    else
	                    {
	                    	IOWR(BLUE_LEDS_BASE, 0, led_state | 0x80);
	                    }
	                }
	            }
	        }
	        break;

	        default:
	        break;
	    }
}

void SimpleLinkPingReport(SlPingReport_t *pPingReport)
{

}


void SimpleLinkSockEventHandler(SlSockEvent_t *pSock)
{
	if(pSock == NULL)
	        printf(" [SOCK EVENT] NULL Pointer Error \n\r");

	    switch( pSock->Event )
	    {
	        case SL_SOCKET_TX_FAILED_EVENT:
	        {
	            /*
	            * TX Failed
	            *
	            * Information about the socket descriptor and status will be
	            * available in 'SlSockEventData_t' - Applications can use it if
	            * required
	            *
	            * SlSockEventData_t *pEventData = NULL;
	            * pEventData = & pSock->EventData;
	            */
	            switch( pSock->EventData.status )
	            {
	                case SL_ECLOSE:
	                  /*
	                   * Close Socket operation:- Failed to transmit all the
	                   * queued packets.
	                   */
	                    printf(" [SOCK EVENT] Failed to transmit packets \r\n");
	                break;
	                default:
	                    printf(" [SOCK EVENT] Unexpected event \r\n");
	                break;
	            }
	        }
	        break;

	        default:
	            printf(" [SOCK EVENT] Unexpected event \r\n");
	        break;
	    }
}

/******************************************************************************
 * FUNCTION:     main
 *
 * DESCRIPTION:  Main program.
 *
 * INPUTS:
 *   None.
 *
 * RETURNS:
 *   None.
 *
 * NOTES:
 *   None.
 ******************************************************************************/
int main (int argc, char* argv[], char* envp[])
{

	adc_stop(ADC_SEQUENCER_CSR_BASE);
	adc_interrupt_disable(ADC_SAMPLE_STORE_CSR_BASE);

	_i32 retVal = -1;
	_i8  *pConfig = NULL;

	alt_u16 x_axis,
			y_axis,
			z_axis;
	alt_u16 temperature,
			humidity;
	alt_u8  data[2];

	 SlPingStartCommand_t PingParams;
	    SlPingReport_t Report;
	    UserInfo User;

	    _u32 IpAddr = 0;
	    _u32 Mask = 0;
	    _u32 Gw = 0;
	    _u32 Dns = 0;
	    _u8  IsDhcp = 0;

	    _i32 Status = -1;
	    _i32 mode = ROLE_STA;

	/********************************************
	 * Initialize device
	 ********************************************/
	IOWR (BLUE_LEDS_BASE, 0, 0xff);
	lis332arInit();
	hdc1000Init();
	IOWR(CC3100_CTRL_PIO_BASE, 0, 0);
	usleep(1);
	//IOWR(SYS_RST_OUT_BASE, 0, 0);
	usleep(1);
	//IOWR(SYS_RST_OUT_BASE, 0, 1);

	IOWR(SYS_RST_OUT_N_BASE, 0, 0);
	usleep(1);

	/********************************************
	 * Setup Interrupt
	 ********************************************/
	IOWR(CC2650_IRQ_PIO_BASE, 0, 0x00);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(CC2650_IRQ_PIO_BASE, 0xFF);
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(CC2650_IRQ_PIO_BASE,  0xFF);

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
	alt_ic_isr_register (CC2650_IRQ_PIO_IRQ_INTERRUPT_CONTROLLER_ID,
			CC2650_IRQ_PIO_IRQ,
						 slInterrupt,
						 (void *)CC2650_IRQ_PIO_BASE,
						 (void *)0);
#else
	alt_irq_register (CC2650_CTRL_PIO_IRQ, CC2650_CTRL_PIO_BASE, slInterrupt);
#endif


	//IOWR(X_PIO_IRQ_BASE, 3, 0xff);
	alt_ic_irq_enable(CC2650_IRQ_PIO_IRQ_INTERRUPT_CONTROLLER_ID,
			CC2650_IRQ_PIO_IRQ);

	//IOWR(SYS_RST_OUT_N_BASE, 0, 0);
	//usleep(1);
	IOWR(SYS_RST_OUT_N_BASE, 0, 1);

#if 1
	retVal = configureSimpleLinkToDefaultState(pConfig);

	if(retVal < 0)
	    {
	        printf(" Failed to configure the device in its default state, Error code: %ld\r\n",retVal);
	        LOOP_FOREVER();
	    }

	    printf("Device is configured in default state \r\n");

	    /*
	     * Asumption is that the device is configured in station mode already
	     * and it is in its default state
	     */

	    /* Initializing the CC3100 device */
	    mode = sl_Start(0, pConfig, 0);
	    if (ROLE_AP == mode)
	    {
	        /* If some other application has configured the device in AP mode,
	           then we need to wait for this event */
	        while(!IS_IP_ACQUIRED(g_Status))
	            ;
	    }
	    else
	    {
	        /* Configure CC3100 to start in AP mode */
	        retVal = sl_WlanSetMode(ROLE_AP);
	        if(retVal < 0)
	            LOOP_FOREVER();

	        retVal = sl_Stop(SL_STOP_TIMEOUT);
	        if(retVal < 0)
	            LOOP_FOREVER();
	        mode = sl_Start(0, pConfig, 0);
	        if (ROLE_AP == mode)
	        {
	            /* If the device is in AP mode, we need to wait for this event before doing anything */
	            while(!IS_IP_ACQUIRED(g_Status))
	                ;
	        }
	        else
	        {
	            printf(" Device couldn't be configured in AP mode \n\r");
	            LOOP_FOREVER();
	        }
	    }

	    User = GetUserInput();

	    retVal = ConfigureAPmode(User);
	    if(retVal < 0)
	    {
	        printf(" Failed to set AP mode configuration, Error code: %ld\r\n",retVal);
	        LOOP_FOREVER();
	    }
	    printf("Configured CC3100 in AP mode, Restarting CC3100 in AP mode\n");

	    /* Restart the CC3100 */
	    retVal = sl_Stop(SL_STOP_TIMEOUT);
	    if(retVal < 0)
	        LOOP_FOREVER();

	    g_Status = 0;

	    mode  = sl_Start(0, pConfig, 0);
	    if (ROLE_AP == mode)
	    {
	        /* If the device is in AP mode, we need to wait for this event before doing anything */
	        while(!IS_IP_ACQUIRED(g_Status))
	            ;
	    }
	    else
	    {
	        printf(" Device couldn't come-up in AP mode \r\n");
	        LOOP_FOREVER();
	    }

	    printf("Connect client to AP %s\n",User.SSID);

	    while((!IS_IP_LEASED(g_Status)) || (!IS_STA_CONNECTED(g_Status))) { _SlNonOsMainLoopTask(); }


	    printf("Client connected \n");

	    /* Enable the HTTP Authentication */
	    retVal = set_authentication_check(FALSE);
	    if(retVal < 0)
	        LOOP_FOREVER();
#if 0
	    /* Get authentication parameters */
	    retVal = get_auth_name(g_auth_name);
	    if(retVal < 0)
	        LOOP_FOREVER();

	    retVal = get_auth_password(g_auth_password);
	    if(retVal < 0)
	        LOOP_FOREVER();

	    retVal = get_auth_realm(g_auth_realm);
	    if(retVal < 0)
	        LOOP_FOREVER();

	    printf((_u8 *)"\r\n Authentication parameters: ");
	    printf((_u8 *)"\r\n Name = ");
	    printf(g_auth_name);
	    printf((_u8 *)"\r\n Password = ");
	    printf(g_auth_password);
	    printf((_u8 *)"\r\n Realm = ");
	    printf(g_auth_realm);
#endif
	    /* Get the domain name */
	     retVal = get_domain_name(g_domain_name);
	     if(retVal < 0)
	         LOOP_FOREVER();

	     printf((_u8 *)"\r\n\r\n Domain name = ");
	     printf(g_domain_name);

	     /* Get URN */
	     retVal = get_device_urn(g_device_urn);
	     if(retVal < 0)
	         LOOP_FOREVER();

	     printf((_u8 *)"\r\n Device URN = ");
	     printf(g_device_urn);
	     printf((_u8 *)"\r\n");
#endif

	/********************************************
	 * Perform system processing.
	 ********************************************/
	while (1)
	{
		_SlNonOsMainLoopTask();

		//lis332arRead(&x_axis, &y_axis, &z_axis);
		//hdc1000Read(&temperature, &humidity);
#if 0
		data[0] = 0xFF;
		data[1] = 0xBB;
		spiWrite(SPI_DEVICE_CC3100, data, 2);

		data[0] = 0xAA;
		data[1] = 0x11;
		spiWrite(SPI_DEVICE_CC2650, data, 2);
#endif
	}

	return 0;
}



/*!
    \brief Set the HTTP port

    This function can be used to change the default port (80) for HTTP request

    \param[in]      num- contains the port number to be set

    \return         None

    \note

    \warning
*/
_i32 set_port_number(_u16 num)
{
    _NetAppHttpServerGetSet_port_num_t port_num;
    _i32 status = -1;

    port_num.port_number = num;

    /*Need to restart the server in order for the new port number configuration
     *to take place */
    status = sl_NetAppStop(SL_NET_APP_HTTP_SERVER_ID);
    ASSERT_ON_ERROR(status);

    status  = sl_NetAppSet (SL_NET_APP_HTTP_SERVER_ID, NETAPP_SET_GET_HTTP_OPT_PORT_NUMBER,
                  sizeof(_NetAppHttpServerGetSet_port_num_t), (_u8 *)&port_num);
    ASSERT_ON_ERROR(status);

    status = sl_NetAppStart(SL_NET_APP_HTTP_SERVER_ID);
    ASSERT_ON_ERROR(status);

    return SUCCESS;
}

/*!
    \brief Enable/Disable the authentication check for http server,
           By default authentication is disabled.

    \param[in]      enable - false to disable and true to enable the authentication

    \return         None

    \note

    \warning
*/
static _i32 set_authentication_check (_u8 enable)
{
    _NetAppHttpServerGetSet_auth_enable_t auth_enable;
    _i32 status = -1;

    auth_enable.auth_enable = enable;
    status = sl_NetAppSet(SL_NET_APP_HTTP_SERVER_ID, NETAPP_SET_GET_HTTP_OPT_AUTH_CHECK,
                 sizeof(_NetAppHttpServerGetSet_auth_enable_t), (_u8 *)&auth_enable);
    ASSERT_ON_ERROR(status);

    return SUCCESS;
}

/*!
    \brief Get the authentication user name

    \param[in]      auth_name - Pointer to the string to store authentication
                    name

    \return         None

    \note

    \warning
*/
static _i32 get_auth_name (_u8 *auth_name)
{
    _u8 len = MAX_AUTH_NAME_LEN;
    _i32 status = -1;

    status = sl_NetAppGet(SL_NET_APP_HTTP_SERVER_ID, NETAPP_SET_GET_HTTP_OPT_AUTH_NAME,
                 &len, (_u8 *) auth_name);
    ASSERT_ON_ERROR(status);

    auth_name[len] = '\0';

    return SUCCESS;
}

/*!
    \brief Get the authentication password

    \param[in]      auth_password - Pointer to the string to store
                    authentication password

    \return         None

    \note

    \warning
*/
static _i32 get_auth_password (_u8 *auth_password)
{
    _u8 len = MAX_AUTH_PASSWORD_LEN;
    _i32 status = -1;

    status = sl_NetAppGet(SL_NET_APP_HTTP_SERVER_ID, NETAPP_SET_GET_HTTP_OPT_AUTH_PASSWORD,
                                                &len, (_u8 *) auth_password);
    ASSERT_ON_ERROR(status);

    auth_password[len] = '\0';

    return SUCCESS;
}

/*!
    \brief Get the authentication realm

    \param[in]      auth_realm - Pointer to the string to store authentication
                    realm

    \return         None

    \note

    \warning
*/
static _i32 get_auth_realm (_u8 *auth_realm)
{
    _u8 len = MAX_AUTH_REALM_LEN;
    _i32 status = -1;

    status = sl_NetAppGet(SL_NET_APP_HTTP_SERVER_ID, NETAPP_SET_GET_HTTP_OPT_AUTH_REALM,
                 &len, (_u8 *) auth_realm);
    ASSERT_ON_ERROR(status);

    auth_realm[len] = '\0';

    return SUCCESS;
}

/*!
    \brief Get the device URN

    \param[in]      device_urn - Pointer to the string to store device urn

    \return         None

    \note

    \warning
*/
static _i32 get_device_urn (_u8 *device_urn)
{
    _u8 len = MAX_DEVICE_URN_LEN;
    _i32 status = -1;

    status = sl_NetAppGet(SL_NET_APP_DEVICE_CONFIG_ID, NETAPP_SET_GET_DEV_CONF_OPT_DEVICE_URN,
                 &len, (_u8 *) device_urn);
    ASSERT_ON_ERROR(status);

    device_urn[len] = '\0';

    return SUCCESS;
}

/*!
    \brief Get the domain Name

    \param[in]      domain_name - Pointer to the string to store domain name

    \return         None

    \note

    \warning        Domain name is used only in AP mode.
*/
static _i32 get_domain_name (_u8 *domain_name)
{
    _u8 len = MAX_DOMAIN_NAME_LEN;
    _i32 status = -1;

    status = sl_NetAppGet(SL_NET_APP_DEVICE_CONFIG_ID, NETAPP_SET_GET_DEV_CONF_OPT_DOMAIN_NAME,
                 &len, (_u8 *)domain_name);
    ASSERT_ON_ERROR(status);

    domain_name[len] = '\0';

    return SUCCESS;
}

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
static void slInterrupt(void* context)
#else
static void slInterrupt(void* context, alt_u32 id)
#endif
{
	static alt_u16 x_axis,
			y_axis,
			z_axis;
	static alt_u16 temperature,
				  humidity;
	alt_u32		upperMac, lowerMac;

	unsigned int	pioData;
	static int 		count = 0;
	static int 		macData[10] = {0, 0, 0, 0, 0, 0, 0, 0};

	//printf("Interrupt!\n");

	/********************************************
	 * Acknowledge the interrupt
	 ********************************************/
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(CC2650_IRQ_PIO_BASE, 0xFF);

	//pioButtonFlag = 0;
	//*((int*)context) = 0;

	/********************************************
	 * Read Data & Write to Transfer Register
	 ********************************************/
#if 0
	if (count == 0)
	{
		//lis332arRead(&x_axis, &y_axis, &z_axis);
		//hdc1000Read(&temperature, &humidity);

		x_axis = 0x1188;
		y_axis = 0x2266;
		z_axis = 0x3311;
		temperature = 0x4499;
		humidity = 0x5577;

	}
#endif

	switch (count)
	{
		case 0:
			IOWR_ALTERA_AVALON_SPI_TXDATA(CC2650_SPI_BASE, (temperature >> 8) & 0xff);
			break;
		case 1:
			IOWR_ALTERA_AVALON_SPI_TXDATA(CC2650_SPI_BASE, temperature & 0xff);
			break;

		case 2:
			IOWR_ALTERA_AVALON_SPI_TXDATA(CC2650_SPI_BASE, (humidity >> 8) & 0xff);
			break;
		case 3:
			IOWR_ALTERA_AVALON_SPI_TXDATA(CC2650_SPI_BASE, humidity & 0xff);
			break;

		case 4:
			IOWR_ALTERA_AVALON_SPI_TXDATA(CC2650_SPI_BASE, (x_axis >> 8) & 0xff);
			break;
		case 5:
			IOWR_ALTERA_AVALON_SPI_TXDATA(CC2650_SPI_BASE, x_axis & 0xff);
			break;

		case 6:
			IOWR_ALTERA_AVALON_SPI_TXDATA(CC2650_SPI_BASE, (y_axis >> 8) & 0xff);
			break;
		case 7:
			IOWR_ALTERA_AVALON_SPI_TXDATA(CC2650_SPI_BASE, y_axis & 0xff);
			break;

		case 8:
			IOWR_ALTERA_AVALON_SPI_TXDATA(CC2650_SPI_BASE, (z_axis >> 8) & 0xff);
			break;
		case 9:
			IOWR_ALTERA_AVALON_SPI_TXDATA(CC2650_SPI_BASE, z_axis & 0xff);
			break;

		default:
			//hdc1000Read(&temperature, &humidity);
			//IOWR_ALTERA_AVALON_SPI_TXDATA(CC2650_SPI_BASE, temperature);
			break;
	}

	macData[count] = IORD_ALTERA_AVALON_SPI_RXDATA(CC2650_SPI_BASE);
	//printf(" %x: %x\n", count, macData[count]);

	if (count < 9)
	{
		count++;
	}
	else
	{
		// replaced the lis332arRead() to detect which DECA_REV is running
		// was:   lis332arRead(&x_axis, &y_axis, &z_axis);

		if(IORD_ALTERA_AVALON_PIO_DATA(DECA_REV_PIO_BASE) == DECA_REVB)
			lis332arRead(&x_axis, &y_axis, &z_axis); // REV_B
		else
		{
			initLIS2DH12();
			lis2dh12Read(&x_axis, &y_axis, &z_axis); // REV_C
		}



		hdc1000Read(&temperature, &humidity);
#if 0
		x_axis = 0x1122;
		y_axis = 0x3344;
		z_axis = 0x5566;
		temperature = 0x7788;
		humidity = 0x99aa;
#endif
		upperMac = (macData[7] << 24) | (macData[6] << 16) | (macData[5] << 8) | (macData[4]);
		lowerMac = (macData[3] << 24) | (macData[2] << 16) | (macData[1] << 8) | (macData[0]);

	    //printf(" %x: %x\n", upperMac, lowerMac);
		IOWR(CC2650_SSID_HIGH_BASE, 0,upperMac);
		IOWR(CC2650_SSID_LOW_BASE, 0,lowerMac);

		//printf(" %x: %x\n", temperature, humidity);
		//printf(" %x: %x: %x\n", x_axis, y_axis, z_axis);
		count = 0;

	}

	/********************************************
	 * Allow some time
	 ********************************************/
	//IORD_ALTERA_AVALON_PIO_EDGE_CAP(CC2650_CTRL_PIO_BASE);

	//pioData = IORD(CC2650_CTRL_PIO_BASE, 0);
	//usleep(2);

	//IOWR(CC2650_CTRL_PIO_BASE, 0, pioData);
	//count++;
	//printf(" %x\n", count);
}

