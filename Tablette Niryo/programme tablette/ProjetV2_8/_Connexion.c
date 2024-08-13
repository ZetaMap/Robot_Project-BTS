#include "hmiworks.h"
#pragma GCC diagnostic ignored "-Wunused-variable"

static tWidget *thisCanvas = (tWidget *)&CanvasConnexion;
static tContext globalContext;
static tContext *thisContext = &globalContext;

#pragma GCC diagnostic warning "-Wunused-variable"


static void hmi_ConnectWidgetVariable();
static void hmi_DisconnectWidgetVariable();
static const unsigned char * ImageArr_BitButton124[] = 
{
pucImage_BitButton124, 
pucImagePress_BitButton124
};

#include "__connexion.h"

TimerWidget(Timer15, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0, 32, 32,
  TS_STYLE_TIMER_ENABLED, 1000, 0, hmi_hmi_OnTimer15Execute);
Canvas(Label16, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 178, 318, 415, 85,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCmss20b, "Label16", 0, 0);
Canvas(Label106, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 323, 423, 139, 35,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCmss18, "Etat TCP :", 0, 0);
RectangularButton(BitButton124, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR,
  24, 422, 116, 22, PB_STYLE_FILL|PB_STYLE_IMG |PB_AOPT_VISIBLE|PB_AOPT_ENABLED, ClrSilver, ClrSilver, 0, ClrSilver,
  0, 0, ImageArr_BitButton124, 0, 0,
  hmi_hmi_OnBitButton124Click, hmi_OnBitButton124Release, 0, 0, 1, 2);


Canvas(CanvasConnexion, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0,
       800, 480, (CANVAS_STYLE_APP_DRAWN | CV_AOPT_VISIBLE), 0, 0, 0, 0, 0, 0, hmi_OnConnexion12Paint);

void hmi_renderConnexion12Vector(tContext *pContext, int ox, int oy) {
  GrContextFontSet(pContext, g_pFontCmss42b);
  hmi_SetForeground(pContext, 0x00FFFFFF);
  hmi_DrawString(pContext, "Attente de connexion", -1, ox+159, oy+178, 0);
}
void hmi_OnConnexion12Paint(tWidget *pWidget, tContext *pContext)
{
  hmi_SetForeground(pContext, 0x252525);
  hmi_FillRect(pContext, 0, 0, 800, 480);
  hmi_renderConnexion12Vector(pContext, 0, 0);
}

static void hmi_InitGlobalContext()
{
  GrContextInit(thisContext, thisCanvas->pDisplay);
  GrContextClipRegionSet(thisContext, &(thisCanvas->sPosition));
}
void hmi_InitFrameWidgets2()
{
  hmi_EnableDrawings(0);
  Connexion12OnCreate();
  WidgetAdd(WIDGET_ROOT, (tWidget *)(&CanvasConnexion));
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Timer15);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label16);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label106);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&BitButton124);
  hmi_InitGlobalContext();
  hmi_ConnectWidgetVariable();
  hmi_EnableDrawings(1);
  TimerReset(&Timer15);
}

void hmi_FreeFrameWidgets2()
{
  hmi_DisconnectWidgetVariable();
  WidgetRemove((tWidget *)(&CanvasConnexion));
  WidgetRemove((tWidget *)(&Timer15));
  WidgetRemove((tWidget *)(&Label16));
  WidgetRemove((tWidget *)(&Label106));
  WidgetRemove((tWidget *)(&BitButton124));
}


void hmi_hmi_OnTimer15Execute(tWidget *pWidget)
{
  Timer15OnExecute(pWidget);
}



void hmi_OnBitButton124Release(tWidget *pWidget)
{
}

void hmi_hmi_OnBitButton124Click(tWidget *pWidget) 
{
  BitButton124OnClick(pWidget);
}

static void hmi_ConnectWidgetVariable()
{
  if (g_hmi_CurrentFrame != 2) return;
}

static void hmi_DisconnectWidgetVariable()
{
}

void hmi_Connexion()
{
  hmi_var_table_init();
  hmi_FreeCurrentFrame();
  g_hmi_CurrentFrame = 2;
  hmi_InitFrameWidgets2();
}

