#include "hmiworks.h"
#pragma GCC diagnostic ignored "-Wunused-variable"

static tWidget *thisCanvas = (tWidget *)&CanvasTrajectoire;
static tContext globalContext;
static tContext *thisContext = &globalContext;

#pragma GCC diagnostic warning "-Wunused-variable"


static void hmi_ConnectWidgetVariable();
static void hmi_DisconnectWidgetVariable();
const unsigned char * ObjectList197_210x50[] = {
IGF_Pictures_Stop_norm_210x50,
IGF_Pictures_Stop_press_var2_210x50,
};

#include "__trajectoire.h"

RectangularButton(TextPushButton57, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 550, 415, 110, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "controle", 0,
  200, 100,
  hmi_hmi_OnTextPushButton57Click, hmi_OnTextPushButton57Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton63, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 680, 415, 110, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "trajectoirs", 0,
  200, 100,
  hmi_hmi_OnTextPushButton63Click, hmi_OnTextPushButton63Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton107, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 420, 415, 110, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "options", 0,
  200, 100,
  hmi_hmi_OnTextPushButton107Click, hmi_OnTextPushButton107Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton108, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 290, 415, 110, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "stats", 0,
  200, 100,
  hmi_hmi_OnTextPushButton108Click, hmi_OnTextPushButton108Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton111, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 410, 10, 358, 39,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0xFFFFFF,
  g_pFontCmss20b, "vers le haut", 0,
  200, 100,
  hmi_hmi_OnTextPushButton111Click, hmi_OnTextPushButton111Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton117, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 410, 48, 358, 39,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0xFFFFFF,
  g_pFontCmss20b, "TextPushButton117", 0,
  200, 100,
  hmi_hmi_OnTextPushButton117Click, hmi_OnTextPushButton117Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton122, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 410, 86, 358, 39,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0xFFFFFF,
  g_pFontCmss20b, "TextPushButton122", 0,
  200, 100,
  hmi_hmi_OnTextPushButton122Click, hmi_OnTextPushButton122Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton123, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 410, 124, 358, 39,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0xFFFFFF,
  g_pFontCmss20b, "TextPushButton123", 0,
  200, 100,
  hmi_hmi_OnTextPushButton123Click, hmi_OnTextPushButton123Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton125, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 410, 162, 358, 39,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0xFFFFFF,
  g_pFontCmss20b, "TextPushButton125", 0,
  200, 100,
  hmi_hmi_OnTextPushButton125Click, hmi_OnTextPushButton125Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton130, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 410, 200, 358, 39,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0xFFFFFF,
  g_pFontCmss20b, "TextPushButton130", 0,
  200, 100,
  hmi_hmi_OnTextPushButton130Click, hmi_OnTextPushButton130Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton131, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 410, 238, 358, 39,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0xFFFFFF,
  g_pFontCmss20b, "TextPushButton131", 0,
  200, 100,
  hmi_hmi_OnTextPushButton131Click, hmi_OnTextPushButton131Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton132, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 410, 276, 358, 39,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0xFFFFFF,
  g_pFontCmss20b, "TextPushButton132", 0,
  200, 100,
  hmi_hmi_OnTextPushButton132Click, hmi_OnTextPushButton132Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton133, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 410, 314, 358, 39,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0xFFFFFF,
  g_pFontCmss20b, "TextPushButton133", 0,
  200, 100,
  hmi_hmi_OnTextPushButton133Click, hmi_OnTextPushButton133Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton134, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 410, 352, 358, 39,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0xFFFFFF,
  g_pFontCmss20b, "vers le bas", 0,
  200, 100,
  hmi_hmi_OnTextPushButton134Click, hmi_OnTextPushButton134Release, 0,
  0, -1, 0);
TimerWidget(Timer135, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0, 32, 32,
  TS_STYLE_TIMER_ENABLED, 100, 0, hmi_hmi_OnTimer135Execute);
RectangularButton(TextPushButton144, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 30, 35, 240, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "lancer deplacement", 0,
  200, 100,
  hmi_hmi_OnTextPushButton144Click, hmi_OnTextPushButton144Release, 0,
  0, -1, 0);
TimerWidget(Timer139, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0, 32, 32,
  TS_STYLE_TIMER_ENABLED, 500, 0, hmi_hmi_OnTimer139Execute);
RectangularButton(TextPushButton42, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 20, 420, 210, 50,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFF0000, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss20b, "arret d'urgence", ObjectList197_210x50,
  200, 100,
  hmi_hmi_OnTextPushButton42Click, hmi_OnTextPushButton42Release, 0,
  0, 1, 2);
Canvas(Label151, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 24, 375, 200, 40,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCmss20b, "resultat envoie", 0, 0);
TimerWidget(Timer206, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0, 32, 32,
  TS_STYLE_TIMER_ENABLED, 5000, 0, hmi_hmi_OnTimer206Execute);
Canvas(Label208, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 249, 198, 152, 40,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCmss20b, "val selectionner", 0, 0);
Canvas(Label209, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 249, 246, 152, 40,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCmss20b, "nb trajectoires", 0, 0);
Canvas(Label210, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 58, 195, 152, 40,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCmss20b, "val selectionner", 0, 0);
Canvas(Label211, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 58, 245, 152, 40,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCmss20b, "val selectionner", 0, 0);


Canvas(CanvasTrajectoire, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0,
       800, 480, (CANVAS_STYLE_APP_DRAWN | CV_AOPT_VISIBLE), 0, 0, 0, 0, 0, 0, hmi_OnTrajectoire27Paint);

void hmi_renderTrajectoire27Vector(tContext *pContext, int ox, int oy) {
  hmi_DrawImage(pContext, pucImage_Picture101, ox+0, oy+0);
}
void hmi_OnTrajectoire27Paint(tWidget *pWidget, tContext *pContext)
{
  hmi_SetForeground(pContext, 0x252525);
  hmi_FillRect(pContext, 0, 0, 800, 480);
  hmi_renderTrajectoire27Vector(pContext, 0, 0);
}

static void hmi_InitGlobalContext()
{
  GrContextInit(thisContext, thisCanvas->pDisplay);
  GrContextClipRegionSet(thisContext, &(thisCanvas->sPosition));
}
void hmi_InitFrameWidgets4()
{
  hmi_EnableDrawings(0);
  Trajectoire27OnCreate();
  WidgetAdd(WIDGET_ROOT, (tWidget *)(&CanvasTrajectoire));
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton57);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton63);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton107);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton108);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton111);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton117);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton122);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton123);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton125);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton130);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton131);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton132);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton133);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton134);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Timer135);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton144);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Timer139);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton42);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label151);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Timer206);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label208);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label209);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label210);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label211);
  hmi_InitGlobalContext();
  hmi_ConnectWidgetVariable();
  hmi_EnableDrawings(1);
  TimerReset(&Timer135);
  TimerReset(&Timer139);
  TimerReset(&Timer206);
}

void hmi_FreeFrameWidgets4()
{
  hmi_DisconnectWidgetVariable();
  WidgetRemove((tWidget *)(&CanvasTrajectoire));
  WidgetRemove((tWidget *)(&TextPushButton57));
  WidgetRemove((tWidget *)(&TextPushButton63));
  WidgetRemove((tWidget *)(&TextPushButton107));
  WidgetRemove((tWidget *)(&TextPushButton108));
  WidgetRemove((tWidget *)(&TextPushButton111));
  WidgetRemove((tWidget *)(&TextPushButton117));
  WidgetRemove((tWidget *)(&TextPushButton122));
  WidgetRemove((tWidget *)(&TextPushButton123));
  WidgetRemove((tWidget *)(&TextPushButton125));
  WidgetRemove((tWidget *)(&TextPushButton130));
  WidgetRemove((tWidget *)(&TextPushButton131));
  WidgetRemove((tWidget *)(&TextPushButton132));
  WidgetRemove((tWidget *)(&TextPushButton133));
  WidgetRemove((tWidget *)(&TextPushButton134));
  WidgetRemove((tWidget *)(&Timer135));
  WidgetRemove((tWidget *)(&TextPushButton144));
  WidgetRemove((tWidget *)(&Timer139));
  WidgetRemove((tWidget *)(&TextPushButton42));
  WidgetRemove((tWidget *)(&Label151));
  WidgetRemove((tWidget *)(&Timer206));
  WidgetRemove((tWidget *)(&Label208));
  WidgetRemove((tWidget *)(&Label209));
  WidgetRemove((tWidget *)(&Label210));
  WidgetRemove((tWidget *)(&Label211));
}


void hmi_OnTextPushButton57Release(tWidget *pWidget)
{
  hmi_GotoFrameByName("Statut");
}

void hmi_hmi_OnTextPushButton57Click(tWidget *pWidget)
{
  TextPushButton57OnClick(pWidget);
}


void hmi_OnTextPushButton63Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton63Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton107Release(tWidget *pWidget)
{
  hmi_GotoFrameByName("Menu");
}

void hmi_hmi_OnTextPushButton107Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton108Release(tWidget *pWidget)
{
  hmi_GotoFrameByName("Statistic");
}

void hmi_hmi_OnTextPushButton108Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton111Release(tWidget *pWidget)
{
  TextPushButtonTrajectorieSelectionOnRelease(pWidget);
}

void hmi_hmi_OnTextPushButton111Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton117Release(tWidget *pWidget)
{
  TextPushButtonTrajectorieSelectionOnRelease(pWidget);
}

void hmi_hmi_OnTextPushButton117Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton122Release(tWidget *pWidget)
{
  TextPushButtonTrajectorieSelectionOnRelease(pWidget);
}

void hmi_hmi_OnTextPushButton122Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton123Release(tWidget *pWidget)
{
  TextPushButtonTrajectorieSelectionOnRelease(pWidget);
}

void hmi_hmi_OnTextPushButton123Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton125Release(tWidget *pWidget)
{
  TextPushButtonTrajectorieSelectionOnRelease(pWidget);
}

void hmi_hmi_OnTextPushButton125Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton130Release(tWidget *pWidget)
{
  TextPushButtonTrajectorieSelectionOnRelease(pWidget);
}

void hmi_hmi_OnTextPushButton130Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton131Release(tWidget *pWidget)
{
  TextPushButtonTrajectorieSelectionOnRelease(pWidget);
}

void hmi_hmi_OnTextPushButton131Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton132Release(tWidget *pWidget)
{
  TextPushButtonTrajectorieSelectionOnRelease(pWidget);
}

void hmi_hmi_OnTextPushButton132Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton133Release(tWidget *pWidget)
{
  TextPushButtonTrajectorieSelectionOnRelease(pWidget);
}

void hmi_hmi_OnTextPushButton133Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton134Release(tWidget *pWidget)
{
  TextPushButtonTrajectorieSelectionOnRelease(pWidget);
}

void hmi_hmi_OnTextPushButton134Click(tWidget *pWidget)
{
}


void hmi_hmi_OnTimer135Execute(tWidget *pWidget)
{
  Timer135OnExecute(pWidget);
}


void hmi_OnTextPushButton144Release(tWidget *pWidget)
{
  TextPushButton144OnRelease(pWidget);
}

void hmi_hmi_OnTextPushButton144Click(tWidget *pWidget)
{
  TextPushButton144OnClick(pWidget);
}


void hmi_hmi_OnTimer139Execute(tWidget *pWidget)
{
  Timer139OnExecute(pWidget);
}


void hmi_OnTextPushButton42Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton42Click(tWidget *pWidget)
{
  TextPushButton42OnClick(pWidget);
}


void hmi_hmi_OnTimer206Execute(tWidget *pWidget)
{
  Timer206OnExecute(pWidget);
}


static void hmi_ConnectWidgetVariable()
{
  if (g_hmi_CurrentFrame != 4) return;
}

static void hmi_DisconnectWidgetVariable()
{
}

void hmi_Trajectoire()
{
  hmi_var_table_init();
  hmi_FreeCurrentFrame();
  g_hmi_CurrentFrame = 4;
  hmi_InitFrameWidgets4();
}

