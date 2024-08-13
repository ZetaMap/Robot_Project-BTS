#define HMI_WDT_ENABLE 4000
#define HMI_WDT_TIMEOUT 4000
#define HMI_WDT_CLEAR 1000
#define HMI_WDT_MTCP_TIMEOUT 60000
#define HMI_WDT_MTCPS_TIMEOUT 60000
#define HMI_STARTUP_LED 1
#define HMI_STARTUP_BEEP 0
#define HMI_STARTUP_DELAY 100
#define HMI_BEEP_FREQ 800
#define HMI_BEEP_MS 100
#define HMI_LCD_AUTO_OFF 60
#define HMI_LCD_ON_BEEP 0
#define HMI_LCD_OFF_BEEP 0
#define HMI_LCD_BRIGHTNESS 180
#define HMI_TOUCH_BEEP 0
#define HMI_TCP_TIMEOUT_BEEP 0
#define HMI_NTP_ENABLE 0
#define HMI_NTP_ADDR "time.stdtime.gov.tw"
#define HMI_NTP_FREQ 15000
#define HMI_NTP_ZONE 100000
#define HMI_USER_FLASH 0


#include "hmiworks.h"

#define TICKS_PER_SECOND 100
#define MS_PER_TICK      (1000 / TICKS_PER_SECOND)
#define APPLICATION_TITLE "TouchPAD-ICPDAS"

#define USE_DHCP                 0

extern volatile unsigned char g_ucLCDIdleUserCallbackStatus;   // 0 = nothing, 1=Idle callback, 2 = wake up callback
extern PFN_VOIDCALLBACK pfnLCDIdleUserCallback; 
extern PFN_VOIDCALLBACK pfnLCDWakeupUserCallback;

static volatile tBoolean g_bFirmwareUpdate = false;
static unsigned long g_ulLastClearWatchdog = 0;
static unsigned long g_ulLastHSCallback = 0;
extern volatile bool hmi_gbUSBUpdateSignalled;

void SysTickIntHandler(void)
{
   lwIPTimer(1000 / TICKS_PER_SECOND);
   hmi_TimerTrigger();
   AudioHandler();
}

void SoftwareUpdateRequestCallback(void)
{
   if (GetRotaryID() == 0) 
      g_bFirmwareUpdate = true;
}

int main(void)
{
   unsigned char pucMACAddr[6];

   hmi_DeviceInit(0x703);
   hmi_MACAddrInit(pucMACAddr);

   I2CM_Driver_Init();
   int yy, mm, dd, hh, nn, ss; 
   hmi_GetDateTime(&yy, &mm, &dd, &hh, &nn, &ss); 
	ss += (nn << 6) + (hh << 11);
	ss ^= *(unsigned int*)(pucMACAddr +2);
   srand( ss );
	
   //uart_Init();
   
   if ( HMI_STARTUP_DELAY )
      hmi_DelayUS( HMI_STARTUP_DELAY * 1000);  

   hmi_WdtEnable( 5000 );

   hmi_TCPInit();
   hmi_TCPTimeoutBeep( HMI_TCP_TIMEOUT_BEEP );
	  
#if USE_DHCP == 1
   lwIPInit(pucMACAddr, 0, 0, 0, IPADDR_USE_DHCP);
#elif USE_DHCP == 0
   #define DEFAULT_IPADDR          	IPADDR(192,168,1,19)
   #define DEFAULT_GATEWAY_ADDR    	IPADDR(192,168,1,1)
   #define DEFAULT_NET_MASK        	IPADDR(255,255,255,0)
   lwIPInit(pucMACAddr, DEFAULT_IPADDR, DEFAULT_NET_MASK, DEFAULT_GATEWAY_ADDR, IPADDR_USE_STATIC);
#elif USE_DHCP == 2
   do {
      unsigned long ulParams[4];
      hmi_NetworkParamsGet(ulParams, ulParams +1, ulParams +2, ulParams +3);
      if ( ulParams[0] == 1 ) // DHCP enabled
         lwIPInit(pucMACAddr, 0, 0, 0, IPADDR_USE_DHCP);
      else
         lwIPInit(pucMACAddr, ulParams[1], ulParams[2], ulParams[3], IPADDR_USE_STATIC);   
   } while (0);   
#endif

   hmi_WdtClear();  // Don't reboot
       
   LocatorInit();
   LocatorMACAddrSet(pucMACAddr);
   LocatorAppTitleSet(APPLICATION_TITLE);
   SoftwareUpdateInit(SoftwareUpdateRequestCallback);
   
   BuzzerInit();
    
   hmi_WdtClear();  // Don't reboot

   HMI_INIT(O_LANDSCAPE);
   hmi_BacklightSet( HMI_LCD_BRIGHTNESS );
   hmi_SetLED( HMI_STARTUP_LED );

   hmi_ConfigBeep(HMI_BEEP_FREQ, HMI_BEEP_MS);
   if ( HMI_STARTUP_BEEP )
      hmi_Beep();
        
   TouchScreenInit();
   TouchScreenCallbackSet(WidgetPointerMessage);

   if ( HMI_TOUCH_BEEP )
      hmi_TurnTouchBeep(1);
       
   if ( HMI_LCD_AUTO_OFF ) 
   {
      hmi_LCDIdleSetTimeout( HMI_LCD_AUTO_OFF * 1000 );
      hmi_LCDIdleSetBeep(HMI_LCD_OFF_BEEP, HMI_LCD_ON_BEEP);
   }

   if ( HMI_WDT_ENABLE )
   {
	   g_ulLastClearWatchdog = hmi_GetTickCount();
      hmi_WdtEnable( HMI_WDT_TIMEOUT );	 
   }
   else
	   hmi_WdtEnable( 0 );   
   
   if ( HMI_NTP_ENABLE )
   {
	   SNTP_UpdateRTC(HMI_NTP_ADDR, HMI_NTP_ZONE, HMI_NTP_FREQ);
   }	  
   
   hmi_UserFlashConfig(HMI_USER_FLASH);
   
   hmi_frame0();
	WidgetMessageQueueProcess(); // Show initial screen
   
   while(!g_bFirmwareUpdate)
   {
		if ( hmi_gbUSBUpdateSignalled )
			break;
		
#if HMI_NTP_ENABLE 
      SNTP_Process();
#endif		
	  
	   hmi_IOScan_Process();
      WidgetMessageQueueProcess();
	  
      if (g_TimerTicksCount != g_ulLastHSCallback) // every 10 ms (may be more)
      {
         // Process High Speed Callback Functions at 10 ms
         hmi_ProcessHSCallback();
         g_ulLastHSCallback = g_TimerTicksCount; 
			
         hmi_GTimerProcess();
			hmi_TCPProcessMessages();
			
#if HMI_WDT_ENABLE 
			if ( g_TimerTicksCount - g_ulLastClearWatchdog > (HMI_WDT_CLEAR / 10) )
			{
				g_ulLastClearWatchdog = g_TimerTicksCount;
				hmi_WdtClear();  // Don't reboot
			}
#endif
			
#if (HMI_WDT_MTCP_TIMEOUT > 10000) || (HMI_WDT_MTCPS_TIMEOUT > 10000)
			static unsigned long sLastTicks1s = 0;
			if ( g_TimerTicksCount - sLastTicks1s > 300 ) // 3000 ms / 10 ms
			{
  #if (HMI_WDT_MTCP_TIMEOUT > 10000) 
				// Check Modbus TCP Master WDT timeout when setting larger then 10 seconds.
				mtm_CheckWDT( HMI_WDT_MTCP_TIMEOUT / 10 ); // based on 10 ms.
  #endif				
  #if (HMI_WDT_MTCPS_TIMEOUT > 10000) 
				// Check Modbus TCP Slave WDT timeout when setting larger then 10 seconds.
				mts_CheckWDT( HMI_WDT_MTCPS_TIMEOUT / 10 ); // based on 10 ms.
  #endif			
				sLastTicks1s = g_TimerTicksCount;
			}
#endif
      }
	  
      // callback for LCD idle or wake up
      if ( 1 == g_ucLCDIdleUserCallbackStatus && pfnLCDIdleUserCallback )
      {
         g_ucLCDIdleUserCallbackStatus = 0;
         pfnLCDIdleUserCallback();
      }
      else if ( 2 == g_ucLCDIdleUserCallbackStatus && pfnLCDWakeupUserCallback )
      {
         g_ucLCDIdleUserCallbackStatus = 0;
         pfnLCDWakeupUserCallback();
      }
   }

   if ( HMI_WDT_ENABLE )  // Disable Watchdog when firmware update. 
      hmi_WdtEnable( 0 );

	if ( hmi_gbUSBUpdateSignalled )
		hmi_dfu_update();
	else
      SoftwareUpdateBegin();
	
   while(1) { }
}



