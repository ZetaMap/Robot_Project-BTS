#include "hmiworks.h"
#pragma GCC diagnostic ignored "-Wunused-variable"

static tWidget *thisCanvas = (tWidget *)&CanvasStatisticMoteurs;
static tContext globalContext;
static tContext *thisContext = &globalContext;

#pragma GCC diagnostic warning "-Wunused-variable"


static void hmi_ConnectWidgetVariable();
static void hmi_DisconnectWidgetVariable();

#include "__statisticmoteurs.h"

RectangularButton(TextPushButton155, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 631, 410, 163, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "retour", 0,
  200, 100,
  hmi_hmi_OnTextPushButton155Click, hmi_OnTextPushButton155Release, 0,
  0, -1, 0);
Canvas(Label157, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 14, 69, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x00FF40, 0x000000, 0x000000,
  g_pFontCmss18b, "J1-Base", 0, 0);
Canvas(Label158, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 14, 119, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x00FF40, 0x000000, 0x000000,
  g_pFontCmss18b, "J2-Shoulder", 0, 0);
Canvas(Label159, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 164, 19, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x0000FF, 0x000000, 0xFFFFFF,
  g_pFontCmss18b, "voltage", 0, 0);
Canvas(Label160, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 164, 69, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x808080, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label156, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 314, 19, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x0000FF, 0x000000, 0xFFFFFF,
  g_pFontCmss18b, "temperature", 0, 0);
Canvas(Label161, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 164, 119, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x2B7171, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label162, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 314, 69, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x808080, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label163, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 314, 119, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x2B7171, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label164, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 14, 169, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x00FF40, 0x000000, 0x000000,
  g_pFontCmss18b, "J3-Elbow", 0, 0);
Canvas(Label165, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 164, 169, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x808080, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label166, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 314, 169, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x808080, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label167, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 14, 219, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x00FF40, 0x000000, 0x000000,
  g_pFontCmss18b, "J4-Forearm", 0, 0);
Canvas(Label168, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 164, 219, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x2B7171, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label169, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 314, 219, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x2B7171, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label170, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 14, 269, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x00FF40, 0x000000, 0x000000,
  g_pFontCmss18b, "J5-Wrist", 0, 0);
Canvas(Label171, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 164, 269, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x808080, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label172, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 314, 269, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x808080, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label173, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 14, 319, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x00FF40, 0x000000, 0x000000,
  g_pFontCmss18b, "J6-Hand", 0, 0);
Canvas(Label174, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 164, 319, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x2B7171, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label175, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 314, 319, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x2B7171, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label176, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 14, 369, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x00FF40, 0x000000, 0x000000,
  g_pFontCmss18b, "End Effector", 0, 0);
Canvas(Label177, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 164, 369, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x808080, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label178, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 314, 369, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x808080, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label179, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 14, 419, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x00FF40, 0x000000, 0x000000,
  g_pFontCmss18b, "Tool", 0, 0);
Canvas(Label180, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 164, 419, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x2B7171, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label181, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 314, 419, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x2B7171, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
TimerWidget(Timer182, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0, 32, 32,
  TS_STYLE_TIMER_ENABLED, 1000, 0, hmi_hmi_OnTimer182Execute);
TimerWidget(Timer183, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0, 32, 32,
  TS_STYLE_TIMER_ENABLED, 500, 0, hmi_hmi_OnTimer183Execute);
Canvas(Label184, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 464, 69, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x808080, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label185, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 464, 119, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x2B7171, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label186, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 464, 169, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x808080, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label187, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 464, 219, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x2B7171, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label188, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 464, 269, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x808080, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label189, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 464, 319, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x2B7171, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label190, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 464, 369, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x808080, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label191, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 464, 419, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x2B7171, 0x000000, 0x000000,
  g_pFontCmss18b, "LabelMotors", 0, 0);
Canvas(Label192, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 464, 19, 151, 51,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x0000FF, 0x000000, 0xFFFFFF,
  g_pFontCmss18, "", 0, 0);
Canvas(Label195, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 475, 23, 130, 20,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x0000FF, 0x0000FF, 0xFFFFFF,
  g_pFontCmss18b, "Code d'erreur", 0, 0);
Canvas(Label194, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 476, 48, 130, 20,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x0000FF, 0x0000FF, 0xFFFFFF,
  g_pFontCmss18b, "0 = OK", 0, 0);


Canvas(CanvasStatisticMoteurs, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0,
       800, 480, (CANVAS_STYLE_APP_DRAWN | CV_AOPT_VISIBLE), 0, 0, 0, 0, 0, 0, hmi_OnStatisticMoteurs17Paint);

void hmi_renderStatisticMoteurs17Vector(tContext *pContext, int ox, int oy) {
  hmi_DrawImage(pContext, pucImage_Picture101, ox+0, oy+0);
}
void hmi_OnStatisticMoteurs17Paint(tWidget *pWidget, tContext *pContext)
{
  hmi_SetForeground(pContext, 0x2B7171);
  hmi_FillRect(pContext, 0, 0, 800, 480);
  hmi_renderStatisticMoteurs17Vector(pContext, 0, 0);
}

static void hmi_InitGlobalContext()
{
  GrContextInit(thisContext, thisCanvas->pDisplay);
  GrContextClipRegionSet(thisContext, &(thisCanvas->sPosition));
}
void hmi_InitFrameWidgets7()
{
  hmi_EnableDrawings(0);
  StatisticMoteurs17OnCreate();
  WidgetAdd(WIDGET_ROOT, (tWidget *)(&CanvasStatisticMoteurs));
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton155);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label157);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label158);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label159);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label160);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label156);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label161);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label162);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label163);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label164);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label165);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label166);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label167);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label168);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label169);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label170);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label171);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label172);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label173);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label174);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label175);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label176);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label177);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label178);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label179);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label180);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label181);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Timer182);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Timer183);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label184);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label185);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label186);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label187);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label188);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label189);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label190);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label191);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label192);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label195);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label194);
  hmi_InitGlobalContext();
  hmi_ConnectWidgetVariable();
  hmi_EnableDrawings(1);
  TimerReset(&Timer182);
  TimerReset(&Timer183);
}

void hmi_FreeFrameWidgets7()
{
  hmi_DisconnectWidgetVariable();
  WidgetRemove((tWidget *)(&CanvasStatisticMoteurs));
  WidgetRemove((tWidget *)(&TextPushButton155));
  WidgetRemove((tWidget *)(&Label157));
  WidgetRemove((tWidget *)(&Label158));
  WidgetRemove((tWidget *)(&Label159));
  WidgetRemove((tWidget *)(&Label160));
  WidgetRemove((tWidget *)(&Label156));
  WidgetRemove((tWidget *)(&Label161));
  WidgetRemove((tWidget *)(&Label162));
  WidgetRemove((tWidget *)(&Label163));
  WidgetRemove((tWidget *)(&Label164));
  WidgetRemove((tWidget *)(&Label165));
  WidgetRemove((tWidget *)(&Label166));
  WidgetRemove((tWidget *)(&Label167));
  WidgetRemove((tWidget *)(&Label168));
  WidgetRemove((tWidget *)(&Label169));
  WidgetRemove((tWidget *)(&Label170));
  WidgetRemove((tWidget *)(&Label171));
  WidgetRemove((tWidget *)(&Label172));
  WidgetRemove((tWidget *)(&Label173));
  WidgetRemove((tWidget *)(&Label174));
  WidgetRemove((tWidget *)(&Label175));
  WidgetRemove((tWidget *)(&Label176));
  WidgetRemove((tWidget *)(&Label177));
  WidgetRemove((tWidget *)(&Label178));
  WidgetRemove((tWidget *)(&Label179));
  WidgetRemove((tWidget *)(&Label180));
  WidgetRemove((tWidget *)(&Label181));
  WidgetRemove((tWidget *)(&Timer182));
  WidgetRemove((tWidget *)(&Timer183));
  WidgetRemove((tWidget *)(&Label184));
  WidgetRemove((tWidget *)(&Label185));
  WidgetRemove((tWidget *)(&Label186));
  WidgetRemove((tWidget *)(&Label187));
  WidgetRemove((tWidget *)(&Label188));
  WidgetRemove((tWidget *)(&Label189));
  WidgetRemove((tWidget *)(&Label190));
  WidgetRemove((tWidget *)(&Label191));
  WidgetRemove((tWidget *)(&Label192));
  WidgetRemove((tWidget *)(&Label195));
  WidgetRemove((tWidget *)(&Label194));
}


void hmi_OnTextPushButton155Release(tWidget *pWidget)
{
  hmi_GotoFrameByName("Statistic");
}

void hmi_hmi_OnTextPushButton155Click(tWidget *pWidget)
{
}


void hmi_hmi_OnTimer182Execute(tWidget *pWidget)
{
  Timer182OnExecute(pWidget);
}


void hmi_hmi_OnTimer183Execute(tWidget *pWidget)
{
  Timer183OnExecute(pWidget);
}


static void hmi_ConnectWidgetVariable()
{
  if (g_hmi_CurrentFrame != 7) return;
}

static void hmi_DisconnectWidgetVariable()
{
}

void hmi_StatisticMoteurs()
{
  hmi_var_table_init();
  hmi_FreeCurrentFrame();
  g_hmi_CurrentFrame = 7;
  hmi_InitFrameWidgets7();
}

