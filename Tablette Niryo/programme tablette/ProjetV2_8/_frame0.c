#include "hmiworks.h"
BYTE ladder_main(BYTE);

int g_hmi_CurrentFrame = 0;
static int s_hmi_tcp_inited = 0;

const char *g_FrameNames[] = 
{
  "Statut",
  "Connexion",
  "Clavier",
  "Trajectoire",
  "Menu",
  "Statistic",
  "StatisticMoteurs",
};

const int g_FrameCount = (sizeof(g_FrameNames)/sizeof(char *));

#define MAGIC_NUM_TO_CON		472882027


void hmi_CheckModbus()
{
}

void _tpd_tcp_initial()
{
   if ( !lwIPLocalIPAddrGet() ) return;


   s_hmi_tcp_inited = 1;
}

volatile unsigned long g_TimerTicksCount = 0;
unsigned long g_ulTickTmrEvtTrig = 0;


void hmi_TimerTrigger()
{
  g_TimerTicksCount++;
  
  if (table_init_flag && (g_TimerTicksCount%(100/10)) == 0)
  { g_ulTickTmrEvtTrig = g_TimerTicksCount;
    HMI_REQUEST_LADDER_PROCESS();}
  
  if ( s_hmi_tcp_inited ) {
     if ((g_TimerTicksCount%50) == 0) hmi_CheckModbus();
  } else if ( g_TimerTicksCount > 80 )
     _tpd_tcp_initial();
  
  switch(g_hmi_CurrentFrame) {
    case 1: {
     TimerUpdate(&Timer8, 10);
     TimerUpdate(&Timer10, 10);
     TimerUpdate(&Timer29, 10);
    break;
    }
    case 2: {
     TimerUpdate(&Timer15, 10);
    break;
    }
    case 3: {
    break;
    }
    case 4: {
     TimerUpdate(&Timer135, 10);
     TimerUpdate(&Timer139, 10);
     TimerUpdate(&Timer206, 10);
    break;
    }
    case 5: {
     TimerUpdate(&Timer145, 10);
    break;
    }
    case 6: {
     TimerUpdate(&Timer115, 10);
     TimerUpdate(&Timer146, 10);
    break;
    }
    case 7: {
     TimerUpdate(&Timer182, 10);
     TimerUpdate(&Timer183, 10);
    break;
    }
  }
}

void hmi_FreeCurrentFrame()
{
  switch (g_hmi_CurrentFrame)
  {
	case 1: hmi_FreeFrameWidgets1(); break;
	case 2: hmi_FreeFrameWidgets2(); break;
	case 3: hmi_FreeFrameWidgets3(); break;
	case 4: hmi_FreeFrameWidgets4(); break;
	case 5: hmi_FreeFrameWidgets5(); break;
	case 6: hmi_FreeFrameWidgets6(); break;
	case 7: hmi_FreeFrameWidgets7(); break;
  }
}

void hmi_GetActiveFrame(char* str, unsigned int len)
{
 int FNLen = strlen(g_FrameNames[g_hmi_CurrentFrame-1]) +1;
 if(len >= FNLen)
 memcpy(str, g_FrameNames[g_hmi_CurrentFrame-1], FNLen);
}

const char* hmi_GetCurrentFrameName()
{ return g_FrameNames[g_hmi_CurrentFrame-1];}

void hmi_GotoFrame(int nFrame)
{
  HMI_NEW_FRAME();
  switch(nFrame)
  {
	case 1: hmi_Statut(); break;
	case 2: hmi_Connexion(); break;
	case 3: hmi_Clavier(); break;
	case 4: hmi_Trajectoire(); break;
	case 5: hmi_Menu(); break;
	case 6: hmi_Statistic(); break;
	case 7: hmi_StatisticMoteurs(); break;
  }

  WidgetMessageQueueClear();
  HMI_REDRAW();
}

int hmi_IndexOfFrame(const char *frame_name)
{
   int i;
   for (i=0; i<g_FrameCount; i++)
      if (strcmp(frame_name, g_FrameNames[i]) == 0) return i+1;
   return 0;
}


void hmi_GotoFrameByName(const char *frame_name)
{
   hmi_GotoFrame(hmi_IndexOfFrame(frame_name));
}

long hmi_Ladder_Process(tWidget *pWidget, unsigned long ulMessage,
                     unsigned long ulParam1, unsigned long ulParam2)

{
  ladder_main(1);
  passDataThruBindingOnChange();
  default_output(1);
  return 1;
}


BYTE hmi_MtmReconnectState(BYTE en, tHandle mtconn, tModbusTCPDevice* mtmdev)
{
  mtmdev->preerrsta = mtmdev->errsta;
  switch (hmi_TCPState(mtconn))
  {
  default:
  case STATE_TCP_IDLE:
    mtmdev->errsta = 1;
    break;
  case STATE_TCP_LISTEN:
    mtmdev->errsta = 1;
    break;
  case STATE_TCP_CONNECTING:
    if(g_ulTickTmrEvtTrig%(500/10) == 0){
    if (mtmdev->preerrsta == 2)
    mtmdev->errsta = 3;
    else if (mtmdev->preerrsta == 3)
    mtmdev->errsta = 2;
    else 
    {
    mtmdev->errsta = 2;
    mtmdev->preerrsta = 2;
    }
    } break;
  case STATE_TCP_CONNECTED:
    if (en > 0)
    mtmdev->errsta = 1;
    else
    mtmdev->errsta = 0;
    break;
    }
  return mtmdev->errsta;
}

void hmi_IOScan_Process(void)
{
  default_input(1);
}

void hmi_frame0()
{
  tContext sContext;
  
  RegisterNullWidgetMsgProc(hmi_Ladder_Process);
  
  hmi_grlib_init(HMI_GRLIB_INIT_BASIC);
  GrContextInit(&sContext, HMI_DISPLAY_DRIVER_PTR);
  hmi_GotoFrame(2);
  GrFlush(&sContext);
}
