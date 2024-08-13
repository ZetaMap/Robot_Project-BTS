#include "hmiworks.h"
#pragma GCC diagnostic ignored "-Wunused-variable"

static tWidget *thisCanvas = (tWidget *)&CanvasMenu;
static tContext globalContext;
static tContext *thisContext = &globalContext;

#pragma GCC diagnostic warning "-Wunused-variable"


static void hmi_ConnectWidgetVariable();
static void hmi_DisconnectWidgetVariable();
const unsigned char * ObjectList198_210x50[] = {
IGF_Pictures_Stop_norm_210x50,
IGF_Pictures_Stop_press_var2_210x50,
};

#include "__menu.h"

RectangularButton(TextPushButton64, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 200, 70, 400, 50,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0xFFFFFF,
  g_pFontCmss22b, "unite : radiant", 0,
  200, 100,
  hmi_hmi_OnTextPushButton64Click, hmi_OnTextPushButton64Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton65, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 200, 140, 400, 50,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0xFFFFFF,
  g_pFontCmss22b, "calibration auto", 0,
  200, 100,
  hmi_hmi_OnTextPushButton65Click, hmi_OnTextPushButton65Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton30, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 200, 210, 400, 50,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0xFFFFFF,
  g_pFontCmss22b, "detection outil", 0,
  200, 100,
  hmi_hmi_OnTextPushButton30Click, hmi_OnTextPushButton30Release, 0,
  0, -1, 0);
Canvas(Label112, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 20, 350, 210, 57,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCm18, "messages", 0, 0);
RectangularButton(TextPushButton126, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 550, 415, 110, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "controle", 0,
  200, 100,
  hmi_hmi_OnTextPushButton126Click, hmi_OnTextPushButton126Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton127, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 680, 415, 110, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "trajectoirs", 0,
  200, 100,
  hmi_hmi_OnTextPushButton127Click, hmi_OnTextPushButton127Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton128, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 420, 415, 110, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "options", 0,
  200, 100,
  hmi_hmi_OnTextPushButton128Click, hmi_OnTextPushButton128Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton129, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 290, 415, 110, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "stats", 0,
  200, 100,
  hmi_hmi_OnTextPushButton129Click, hmi_OnTextPushButton129Release, 0,
  0, -1, 0);
TimerWidget(Timer145, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0, 32, 32,
  TS_STYLE_TIMER_ENABLED, 500, 0, hmi_hmi_OnTimer145Execute);
RectangularButton(TextPushButton148, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 20, 420, 210, 50,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFF0000, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss20b, "arret d'urgence", ObjectList198_210x50,
  500, 500,
  hmi_hmi_OnTextPushButton148Click, hmi_OnTextPushButton148Release, 0,
  0, 1, 2);
RectangularButton(TextPushButton152, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 200, 280, 400, 50,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0xFFFFFF,
  g_pFontCmss22b, "nettoyage des colisions", 0,
  200, 100,
  hmi_hmi_OnTextPushButton152Click, hmi_OnTextPushButton152Release, 0,
  0, -1, 0);
tSliderWidget Slider40 = SliderStruct(WIDGET_ROOT, 0, 0,
  HMI_DISPLAY_DRIVER_PTR, 740, 70, 40, 267,   10, 255, 10,
  (SL_STYLE_FILL | SL_STYLE_BACKG_FILL | SL_STYLE_OUTLINE |
  SL_STYLE_VERTICAL | SL_AOPT_VISIBLE | SL_AOPT_ENABLED |
  SL_STYLE_TEXT | SL_STYLE_BACKG_TEXT),
  0x00FF40, 0xFFFFFF, 0x000000, 0x000000, 0x000000,
  g_pFontCm18, "", 0, hmi_hmi_OnSlider40SliderChange, 0, 0);
tSliderWidget Slider200 = SliderStruct(WIDGET_ROOT, 0, 0,
  HMI_DISPLAY_DRIVER_PTR, 74, 64, 40, 267,   1, 200, 100,
  (SL_STYLE_FILL | SL_STYLE_BACKG_FILL | SL_STYLE_OUTLINE |
  SL_STYLE_VERTICAL | SL_AOPT_VISIBLE | SL_AOPT_ENABLED |
  SL_STYLE_TEXT | SL_STYLE_BACKG_TEXT),
  0x00FF40, 0xFFFFFF, 0x000000, 0x000000, 0x000000,
  g_pFontCm18, "", 0, hmi_hmi_OnSlider200SliderChange, 0, 0);
Canvas(Label202, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 34, 28, 120, 30,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCmss18b, "Vitesse Niryo", 0, 0);


Canvas(CanvasMenu, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0,
       800, 480, (CANVAS_STYLE_APP_DRAWN | CV_AOPT_VISIBLE), 0, 0, 0, 0, 0, 0, hmi_OnMenu61Paint);

void hmi_renderMenu61Vector(tContext *pContext, int ox, int oy) {
  hmi_DrawImage(pContext, pucImage_Picture101, ox+0, oy+0);
}
void hmi_OnMenu61Paint(tWidget *pWidget, tContext *pContext)
{
  hmi_SetForeground(pContext, 0x252525);
  hmi_FillRect(pContext, 0, 0, 800, 480);
  hmi_renderMenu61Vector(pContext, 0, 0);
}

static void hmi_InitGlobalContext()
{
  GrContextInit(thisContext, thisCanvas->pDisplay);
  GrContextClipRegionSet(thisContext, &(thisCanvas->sPosition));
}
void hmi_InitFrameWidgets5()
{
  hmi_EnableDrawings(0);
  Menu61OnCreate();
  WidgetAdd(WIDGET_ROOT, (tWidget *)(&CanvasMenu));
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton64);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton65);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton30);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label112);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton126);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton127);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton128);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton129);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Timer145);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton148);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton152);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Slider40);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Slider200);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label202);
  hmi_InitGlobalContext();
  hmi_ConnectWidgetVariable();
  hmi_EnableDrawings(1);
  TimerReset(&Timer145);
}

void hmi_FreeFrameWidgets5()
{
  hmi_DisconnectWidgetVariable();
  WidgetRemove((tWidget *)(&CanvasMenu));
  WidgetRemove((tWidget *)(&TextPushButton64));
  WidgetRemove((tWidget *)(&TextPushButton65));
  WidgetRemove((tWidget *)(&TextPushButton30));
  WidgetRemove((tWidget *)(&Label112));
  WidgetRemove((tWidget *)(&TextPushButton126));
  WidgetRemove((tWidget *)(&TextPushButton127));
  WidgetRemove((tWidget *)(&TextPushButton128));
  WidgetRemove((tWidget *)(&TextPushButton129));
  WidgetRemove((tWidget *)(&Timer145));
  WidgetRemove((tWidget *)(&TextPushButton148));
  WidgetRemove((tWidget *)(&TextPushButton152));
  WidgetRemove((tWidget *)(&Slider40));
  WidgetRemove((tWidget *)(&Slider200));
  WidgetRemove((tWidget *)(&Label202));
}


void hmi_OnTextPushButton64Release(tWidget *pWidget)
{
  TextPushButton64OnRelease(pWidget);
}

void hmi_hmi_OnTextPushButton64Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton65Release(tWidget *pWidget)
{
  TextPushButton65OnRelease(pWidget);
}

void hmi_hmi_OnTextPushButton65Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton30Release(tWidget *pWidget)
{
  TextPushButton30OnRelease(pWidget);
}

void hmi_hmi_OnTextPushButton30Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton126Release(tWidget *pWidget)
{
  hmi_GotoFrameByName("Statut");
}

void hmi_hmi_OnTextPushButton126Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton127Release(tWidget *pWidget)
{
  hmi_GotoFrameByName("Trajectoire");
}

void hmi_hmi_OnTextPushButton127Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton128Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton128Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton129Release(tWidget *pWidget)
{
  hmi_GotoFrameByName("Statistic");
}

void hmi_hmi_OnTextPushButton129Click(tWidget *pWidget)
{
}


void hmi_hmi_OnTimer145Execute(tWidget *pWidget)
{
  Timer145OnExecute(pWidget);
}


void hmi_OnTextPushButton148Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton148Click(tWidget *pWidget)
{
  TextPushButton148OnClick(pWidget);
}


void hmi_OnTextPushButton152Release(tWidget *pWidget)
{
  TextPushButton152OnRelease(pWidget);
}

void hmi_hmi_OnTextPushButton152Click(tWidget *pWidget)
{
}


void hmi_hmi_OnSlider40SliderChange(tWidget *pWidget, long lValue)
{
  Slider40OnSliderChange(pWidget, lValue);
}


void hmi_hmi_OnSlider200SliderChange(tWidget *pWidget, long lValue)
{
  Slider200OnSliderChange(pWidget, lValue);
}


static void hmi_ConnectWidgetVariable()
{
  if (g_hmi_CurrentFrame != 5) return;
}

static void hmi_DisconnectWidgetVariable()
{
}

void hmi_Menu()
{
  hmi_var_table_init();
  hmi_FreeCurrentFrame();
  g_hmi_CurrentFrame = 5;
  hmi_InitFrameWidgets5();
}

