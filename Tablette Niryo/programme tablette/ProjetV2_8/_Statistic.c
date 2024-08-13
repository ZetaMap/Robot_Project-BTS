#include "hmiworks.h"
#pragma GCC diagnostic ignored "-Wunused-variable"

static tWidget *thisCanvas = (tWidget *)&CanvasStatistic;
static tContext globalContext;
static tContext *thisContext = &globalContext;

#pragma GCC diagnostic warning "-Wunused-variable"


static void hmi_ConnectWidgetVariable();
static void hmi_DisconnectWidgetVariable();
const unsigned char * ObjectList199_210x50[] = {
IGF_Pictures_Stop_norm_210x50,
IGF_Pictures_Stop_press_var2_210x50,
};

#include "__statistic.h"

RectangularButton(TextPushButton118, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 550, 415, 110, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "controle", 0,
  200, 100,
  hmi_hmi_OnTextPushButton118Click, hmi_OnTextPushButton118Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton119, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 680, 415, 110, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "trajectoirs", 0,
  200, 100,
  hmi_hmi_OnTextPushButton119Click, hmi_OnTextPushButton119Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton120, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 420, 415, 110, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "options", 0,
  200, 100,
  hmi_hmi_OnTextPushButton120Click, hmi_OnTextPushButton120Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton121, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 290, 415, 110, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "stats", 0,
  200, 100,
  hmi_hmi_OnTextPushButton121Click, hmi_OnTextPushButton121Release, 0,
  0, -1, 0);
TimerWidget(Timer115, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0, 32, 32,
  TS_STYLE_TIMER_ENABLED, 250, 0, hmi_hmi_OnTimer115Execute);
tSliderWidget Slider137 = SliderStruct(WIDGET_ROOT, 0, 0,
  HMI_DISPLAY_DRIVER_PTR, 25, 230, 200, 40,   0, 100, 0,
  (SL_STYLE_FILL | SL_STYLE_BACKG_FILL | SL_STYLE_OUTLINE |
   SL_AOPT_VISIBLE |
  SL_STYLE_TEXT | SL_STYLE_BACKG_TEXT),
  0x00FF40, 0xFFFFFF, 0x000000, 0x000000, 0x000000,
  g_pFontCmss18, "", 0, hmi_hmi_OnSlider137SliderChange, 0, 0);
Canvas(Label140, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 25, 80, 200, 40,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCmss18, "LabelMotors", 0, 0);
Canvas(Label141, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 25, 130, 200, 40,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCmss18b, "needCalibration", 0, 0);
Canvas(Label142, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 25, 180, 200, 40,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCmss18b, "calibrationInProgress", 0, 0);
Canvas(Label143, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 25, 330, 200, 39,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCmss18, "labelHWversion", 0, 0);
TimerWidget(Timer146, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0, 32, 32,
  TS_STYLE_TIMER_ENABLED, 500, 0, hmi_hmi_OnTimer146Execute);
RectangularButton(TextPushButton149, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 20, 420, 210, 50,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFF0000, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss20b, "arret d'urgence", ObjectList199_210x50,
  500, 500,
  hmi_hmi_OnTextPushButton149Click, hmi_OnTextPushButton149Release, 0,
  0, 1, 2);
Canvas(Label150, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 24, 375, 200, 40,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCmss18, "resultat envoie", 0, 0);
Canvas(Label153, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 240, 80, 200, 40,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCmss18, "colision", 0, 0);
RectangularButton(TextPushButton154, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 594, 343, 163, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "stats materiels", 0,
  200, 100,
  hmi_hmi_OnTextPushButton154Click, hmi_OnTextPushButton154Release, 0,
  0, -1, 0);


Canvas(CanvasStatistic, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0,
       800, 480, (CANVAS_STYLE_APP_DRAWN | CV_AOPT_VISIBLE), 0, 0, 0, 0, 0, 0, hmi_OnStatistic116Paint);

void hmi_renderStatistic116Vector(tContext *pContext, int ox, int oy) {
  hmi_DrawImage(pContext, pucImage_Picture101, ox+0, oy+0);
}
void hmi_OnStatistic116Paint(tWidget *pWidget, tContext *pContext)
{
  hmi_SetForeground(pContext, 0x252525);
  hmi_FillRect(pContext, 0, 0, 800, 480);
  hmi_renderStatistic116Vector(pContext, 0, 0);
}

static void hmi_InitGlobalContext()
{
  GrContextInit(thisContext, thisCanvas->pDisplay);
  GrContextClipRegionSet(thisContext, &(thisCanvas->sPosition));
}
void hmi_InitFrameWidgets6()
{
  hmi_EnableDrawings(0);
  WidgetAdd(WIDGET_ROOT, (tWidget *)(&CanvasStatistic));
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton118);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton119);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton120);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton121);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Timer115);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Slider137);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label140);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label141);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label142);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label143);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Timer146);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton149);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label150);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label153);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton154);
  hmi_InitGlobalContext();
  hmi_ConnectWidgetVariable();
  hmi_EnableDrawings(1);
  TimerReset(&Timer115);
  TimerReset(&Timer146);
}

void hmi_FreeFrameWidgets6()
{
  hmi_DisconnectWidgetVariable();
  WidgetRemove((tWidget *)(&CanvasStatistic));
  WidgetRemove((tWidget *)(&TextPushButton118));
  WidgetRemove((tWidget *)(&TextPushButton119));
  WidgetRemove((tWidget *)(&TextPushButton120));
  WidgetRemove((tWidget *)(&TextPushButton121));
  WidgetRemove((tWidget *)(&Timer115));
  WidgetRemove((tWidget *)(&Slider137));
  WidgetRemove((tWidget *)(&Label140));
  WidgetRemove((tWidget *)(&Label141));
  WidgetRemove((tWidget *)(&Label142));
  WidgetRemove((tWidget *)(&Label143));
  WidgetRemove((tWidget *)(&Timer146));
  WidgetRemove((tWidget *)(&TextPushButton149));
  WidgetRemove((tWidget *)(&Label150));
  WidgetRemove((tWidget *)(&Label153));
  WidgetRemove((tWidget *)(&TextPushButton154));
}


void hmi_OnTextPushButton118Release(tWidget *pWidget)
{
  hmi_GotoFrameByName("Statut");
}

void hmi_hmi_OnTextPushButton118Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton119Release(tWidget *pWidget)
{
  hmi_GotoFrameByName("Trajectoire");
}

void hmi_hmi_OnTextPushButton119Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton120Release(tWidget *pWidget)
{
  hmi_GotoFrameByName("Menu");
}

void hmi_hmi_OnTextPushButton120Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton121Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton121Click(tWidget *pWidget)
{
}


void hmi_hmi_OnTimer115Execute(tWidget *pWidget)
{
  Timer115OnExecute(pWidget);
}


void hmi_hmi_OnSlider137SliderChange(tWidget *pWidget, long lValue)
{
}


void hmi_hmi_OnTimer146Execute(tWidget *pWidget)
{
  Timer146OnExecute(pWidget);
}


void hmi_OnTextPushButton149Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton149Click(tWidget *pWidget)
{
  TextPushButton149OnClick(pWidget);
}


void hmi_OnTextPushButton154Release(tWidget *pWidget)
{
  hmi_GotoFrameByName("StatisticMoteurs");
}

void hmi_hmi_OnTextPushButton154Click(tWidget *pWidget)
{
}


static void hmi_ConnectWidgetVariable()
{
  if (g_hmi_CurrentFrame != 6) return;
}

static void hmi_DisconnectWidgetVariable()
{
}

void hmi_Statistic()
{
  hmi_var_table_init();
  hmi_FreeCurrentFrame();
  g_hmi_CurrentFrame = 6;
  hmi_InitFrameWidgets6();
}

