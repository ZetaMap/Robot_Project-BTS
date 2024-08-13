#include "hmiworks.h"
#pragma GCC diagnostic ignored "-Wunused-variable"

static tWidget *thisCanvas = (tWidget *)&CanvasStatut;
static tContext globalContext;
static tContext *thisContext = &globalContext;

#pragma GCC diagnostic warning "-Wunused-variable"


static void hmi_ConnectWidgetVariable();
static void hmi_DisconnectWidgetVariable();
static const unsigned char * ImageArr_BitButton22[] = 
{
pucImage_BitButton22, 
pucImagePress_BitButton22
};
const unsigned char * ObjectList59_40x35[] = {
IGF_Pictures_Boutton_35x40_plus_40x35,
IGF_Pictures_Boutton_35x40_plus_press_40x35,
};
const unsigned char * ObjectList60_40x35[] = {
IGF_Pictures_Boutton_35x40_moins_40x35,
IGF_Pictures_Boutton_35x40_moins_press_40x35,
};
const unsigned char * ObjectList196_210x50[] = {
IGF_Pictures_Stop_norm_210x50,
IGF_Pictures_Stop_press_var2_210x50,
};
const unsigned char * ObjectList203_70x70[] = {
IGF_Pictures_rest_pose_icon_70x70,
IGF_Pictures_rest_pose_icon_pressed_70x70,
};
const unsigned char * ObjectList205_70x70[] = {
IGF_Pictures_reset_valeur_cible_icon_70x70,
IGF_Pictures_reset_valeur_cible_icon_pressed_70x70,
};
const unsigned char * ObjectList204_70x70[] = {
IGF_Pictures_zero_pose_icon_70x70,
IGF_Pictures_zero_pose_icon_pressed_70x70,
};

#include "__statut.h"

Canvas(Label5, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 10, 5, 230, 35,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x646464, 0x000000, 0xFFFFFF,
  g_pFontCmss18b, "resultat", 0, 0);
TimerWidget(Timer8, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0, 32, 32,
  TS_STYLE_TIMER_ENABLED, 100, 0, hmi_hmi_OnTimer8Execute);
TimerWidget(Timer10, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0, 32, 32,
  TS_STYLE_TIMER_ENABLED, 1000, 0, hmi_hmi_OnTimer10Execute);
tSliderWidget Slider11 = SliderStruct(WIDGET_ROOT, 0, 0,
  HMI_DISPLAY_DRIVER_PTR, 602, 4, 192, 29,   0, 100, 0,
  (SL_STYLE_FILL | SL_STYLE_BACKG_FILL | SL_STYLE_OUTLINE |
  SL_STYLE_TEXT | SL_STYLE_BACKG_TEXT),
  0x00FF40, 0xFFFFFF, 0x000000, 0x000000, 0x000000,
  g_pFontCmss18b, "", 0, hmi_hmi_OnSlider11SliderChange, 0, 0);
tSliderWidget Slider9 = SliderStruct(WIDGET_ROOT, 0, 0,
  HMI_DISPLAY_DRIVER_PTR, 400, 120, 330, 35,   -2860, 2900, 0,
  (SL_STYLE_FILL | SL_STYLE_BACKG_FILL | SL_STYLE_OUTLINE |
   SL_AOPT_VISIBLE | SL_AOPT_ENABLED |
  SL_STYLE_TEXT | SL_STYLE_BACKG_TEXT),
  0x00FF40, 0x45B8B8, 0x000000, 0x000000, 0x000000,
  g_pFontCmss20b, "", 0, hmi_hmi_OnSlider9SliderChange, 0, 0);
tSliderWidget Slider18 = SliderStruct(WIDGET_ROOT, 0, 0,
  HMI_DISPLAY_DRIVER_PTR, 400, 170, 330, 35,   -1820, 600, 0,
  (SL_STYLE_FILL | SL_STYLE_BACKG_FILL | SL_STYLE_OUTLINE |
   SL_AOPT_VISIBLE | SL_AOPT_ENABLED |
  SL_STYLE_TEXT | SL_STYLE_BACKG_TEXT),
  0x00FF40, 0x45B8B8, 0x000000, 0x000000, 0x000000,
  g_pFontCmss20b, "", 0, hmi_hmi_OnSlider18SliderChange, 0, 0);
tSliderWidget Slider19 = SliderStruct(WIDGET_ROOT, 0, 0,
  HMI_DISPLAY_DRIVER_PTR, 400, 220, 330, 35,   -1290, 1540, 0,
  (SL_STYLE_FILL | SL_STYLE_BACKG_FILL | SL_STYLE_OUTLINE |
   SL_AOPT_VISIBLE | SL_AOPT_ENABLED |
  SL_STYLE_TEXT | SL_STYLE_BACKG_TEXT),
  0x00FF40, 0x45B8B8, 0x000000, 0x000000, 0x000000,
  g_pFontCmss20b, "", 0, hmi_hmi_OnSlider19SliderChange, 0, 0);
Canvas(Label21, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 20, 50, 210, 40,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x646464, 0x000000, 0xFFFFFF,
  g_pFontCmss20b, "outil : ", 0, 0);
RectangularButton(BitButton22, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR,
  611, 30, 170, 55, PB_STYLE_FILL|PB_STYLE_IMG |PB_AOPT_VISIBLE|PB_AOPT_ENABLED, ClrSilver, ClrSilver, 0, ClrSilver,
  0, 0, ImageArr_BitButton22, 0, 0,
  hmi_hmi_OnBitButton22Click, hmi_OnBitButton22Release, 0, 0, 1, 2);
tSliderWidget Slider24 = SliderStruct(WIDGET_ROOT, 0, 0,
  HMI_DISPLAY_DRIVER_PTR, 400, 270, 330, 35,   -2080, 2070, 0,
  (SL_STYLE_FILL | SL_STYLE_BACKG_FILL | SL_STYLE_OUTLINE |
   SL_AOPT_VISIBLE | SL_AOPT_ENABLED |
  SL_STYLE_TEXT | SL_STYLE_BACKG_TEXT),
  0x00FF40, 0x45B8B8, 0x000000, 0x000000, 0x000000,
  g_pFontCmss20b, "", 0, hmi_hmi_OnSlider24SliderChange, 0, 0);
tSliderWidget Slider25 = SliderStruct(WIDGET_ROOT, 0, 0,
  HMI_DISPLAY_DRIVER_PTR, 400, 320, 330, 35,   -1910, 1910, 0,
  (SL_STYLE_FILL | SL_STYLE_BACKG_FILL | SL_STYLE_OUTLINE |
   SL_AOPT_VISIBLE | SL_AOPT_ENABLED |
  SL_STYLE_TEXT | SL_STYLE_BACKG_TEXT),
  0x00FF40, 0x45B8B8, 0x000000, 0x000000, 0x000000,
  g_pFontCmss20b, "", 0, hmi_hmi_OnSlider25SliderChange, 0, 0);
tSliderWidget Slider26 = SliderStruct(WIDGET_ROOT, 0, 0,
  HMI_DISPLAY_DRIVER_PTR, 400, 370, 330, 35,   -2510, 2520, 0,
  (SL_STYLE_FILL | SL_STYLE_BACKG_FILL | SL_STYLE_OUTLINE |
   SL_AOPT_VISIBLE | SL_AOPT_ENABLED |
  SL_STYLE_TEXT | SL_STYLE_BACKG_TEXT),
  0x00FF40, 0x45B8B8, 0x000000, 0x000000, 0x000000,
  g_pFontCmss20b, "", 0, hmi_hmi_OnSlider26SliderChange, 0, 0);
TimerWidget(Timer29, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0, 32, 32,
  TS_STYLE_TIMER_ENABLED, 500, 0, hmi_hmi_OnTimer29Execute);
Canvas(Label34, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 300, 120, 90, 30,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x0040FF, 0x000000, 0x000000,
  g_pFontCmss20b, "Label34", 0, 0);
Canvas(Label35, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 300, 170, 90, 30,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x0040FF, 0x000000, 0x000000,
  g_pFontCmss20b, "Label35", 0, 0);
Canvas(Label36, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 300, 220, 90, 30,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x0040FF, 0x000000, 0x000000,
  g_pFontCmss20b, "Label36", 0, 0);
Canvas(Label37, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 300, 270, 90, 30,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x0040FF, 0x000000, 0x000000,
  g_pFontCmss20b, "Label37", 0, 0);
Canvas(Label38, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 300, 320, 90, 30,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x0040FF, 0x000000, 0x000000,
  g_pFontCmss20b, "Label38", 0, 0);
Canvas(Label39, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 300, 370, 90, 30,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x0040FF, 0x000000, 0x000000,
  g_pFontCmss20b, "Label39", 0, 0);
Canvas(Label41, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 20, 291, 210, 35,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18b, "Label41", 0, 0);
RectangularButton(TextPushButton43, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 750, 120, 40, 35,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x00C0FF, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss24, "+", ObjectList59_40x35,
  50, 10,
  hmi_hmi_OnTextPushButton43Click, hmi_OnTextPushButton43Release, 0,
  0, 1, 2);
RectangularButton(TextPushButton49, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 255, 120, 40, 35,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x00C0FF, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss24, "-", ObjectList60_40x35,
  50, 10,
  hmi_hmi_OnTextPushButton49Click, hmi_OnTextPushButton49Release, 0,
  0, 1, 2);
RectangularButton(TextPushButton44, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 750, 170, 40, 35,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x00C0FF, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss24, "+", ObjectList59_40x35,
  50, 10,
  hmi_hmi_OnTextPushButton44Click, hmi_OnTextPushButton44Release, 0,
  0, 1, 2);
RectangularButton(TextPushButton50, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 255, 170, 40, 35,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x00C0FF, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss24, "-", ObjectList60_40x35,
  50, 10,
  hmi_hmi_OnTextPushButton50Click, hmi_OnTextPushButton50Release, 0,
  0, 1, 2);
RectangularButton(TextPushButton45, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 750, 220, 40, 35,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x00C0FF, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss24, "+", ObjectList59_40x35,
  50, 10,
  hmi_hmi_OnTextPushButton45Click, hmi_OnTextPushButton45Release, 0,
  0, 1, 2);
RectangularButton(TextPushButton51, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 255, 220, 40, 35,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x00C0FF, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss24, "-", ObjectList60_40x35,
  50, 10,
  hmi_hmi_OnTextPushButton51Click, hmi_OnTextPushButton51Release, 0,
  0, 1, 2);
RectangularButton(TextPushButton46, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 750, 270, 40, 35,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x00C0FF, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss24, "+", ObjectList59_40x35,
  50, 10,
  hmi_hmi_OnTextPushButton46Click, hmi_OnTextPushButton46Release, 0,
  0, 1, 2);
RectangularButton(TextPushButton52, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 255, 270, 40, 35,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x00C0FF, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss24, "-", ObjectList60_40x35,
  50, 10,
  hmi_hmi_OnTextPushButton52Click, hmi_OnTextPushButton52Release, 0,
  0, 1, 2);
RectangularButton(TextPushButton47, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 750, 320, 40, 35,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x00C0FF, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss24, "+", ObjectList59_40x35,
  50, 10,
  hmi_hmi_OnTextPushButton47Click, hmi_OnTextPushButton47Release, 0,
  0, 1, 2);
RectangularButton(TextPushButton53, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 255, 320, 40, 35,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x00C0FF, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss24, "-", ObjectList60_40x35,
  50, 10,
  hmi_hmi_OnTextPushButton53Click, hmi_OnTextPushButton53Release, 0,
  0, 1, 2);
RectangularButton(TextPushButton48, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 750, 370, 40, 35,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x00C0FF, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss24, "+", ObjectList59_40x35,
  50, 10,
  hmi_hmi_OnTextPushButton48Click, hmi_OnTextPushButton48Release, 0,
  0, 1, 2);
RectangularButton(TextPushButton54, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 255, 370, 40, 35,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x00C0FF, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss24, "-", ObjectList60_40x35,
  50, 10,
  hmi_hmi_OnTextPushButton54Click, hmi_OnTextPushButton54Release, 0,
  0, 1, 2);
Canvas(Label58, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 275, 9, 110, 50,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x646464, 0x000000, 0xFFFFFF,
  g_pFontCmss18b, "Label58", 0, 0);
Canvas(Label66, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 20, 333, 210, 35,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x646464, 0x000000, 0xFFFFFF,
  g_pFontCmss18b, "exe cmd", 0, 0);
Canvas(Label28, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 20, 375, 210, 35,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x646464, 0x000000, 0xFFFFFF,
  g_pFontCmss18b, "resultat envoie", 0, 0);
RectangularButton(TextPushButton56, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 550, 415, 110, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "controle", 0,
  200, 100,
  hmi_hmi_OnTextPushButton56Click, hmi_OnTextPushButton56Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton62, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 680, 415, 110, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "trajectoirs", 0,
  200, 100,
  hmi_hmi_OnTextPushButton62Click, hmi_OnTextPushButton62Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton109, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 420, 415, 110, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "options", 0,
  200, 100,
  hmi_hmi_OnTextPushButton109Click, hmi_OnTextPushButton109Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton110, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 290, 415, 110, 54,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss20b, "stats", 0,
  200, 100,
  hmi_hmi_OnTextPushButton110Click, hmi_OnTextPushButton110Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton147, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 20, 420, 210, 50,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFF0000, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss20b, "arret d'urgence", ObjectList196_210x50,
  200, 100,
  hmi_hmi_OnTextPushButton147Click, hmi_OnTextPushButton147Release, 0,
  0, 1, 2);
RectangularButton(TextPushButton6, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 12, 105, 100, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x45C0F0, 0x000000, 0x000000,
  g_pFontCmss18b, "Attraper", 0,
  500, 500,
  hmi_hmi_OnTextPushButton6Click, hmi_OnTextPushButton6Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton13, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 125, 105, 100, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x45C0F0, 0x000000, 0x000000,
  g_pFontCmss18b, "Lacher", 0,
  500, 500,
  hmi_hmi_OnTextPushButton13Click, hmi_OnTextPushButton13Release, 0,
  0, -1, 0);
Canvas(Label31, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 275, 82, 150, 30,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x0040FF, 0x000000, 0xFFFFFF,
  g_pFontCmss20b, "Valeurs Cibles:", 0, 0);
RectangularButton(TextPushButton32, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 10, 202, 70, 70,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x45C0F0, 0x000000, 0x000000,
  g_pFontCmss18, "Pose Default", ObjectList203_70x70,
  500, 500,
  hmi_hmi_OnTextPushButton32Click, hmi_OnTextPushButton32Release, 0,
  0, 1, 2);
RectangularButton(TextPushButton33, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 160, 203, 70, 70,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x45C0F0, 0x000000, 0x000000,
  g_pFontCmss18, "Reinitialisation Valeur Cible ", ObjectList205_70x70,
  500, 500,
  hmi_hmi_OnTextPushButton33Click, hmi_OnTextPushButton33Release, 0,
  0, 1, 2);
RectangularButton(TextPushButton193, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 85, 202, 70, 70,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_IMG | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0xFFFFFF, 0x45C0F0, 0x000000, 0x000000,
  g_pFontCmss18, "Pose Zero", ObjectList204_70x70,
  500, 500,
  hmi_hmi_OnTextPushButton193Click, hmi_OnTextPushButton193Release, 0,
  0, 1, 2);
Canvas(Label201, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 434, 82, 117, 27,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCm18, "Label201", 0, 0);
Canvas(Label212, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 432, 45, 117, 27,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCm18, "Label201", 0, 0);
Canvas(Label213, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 431, 11, 117, 27,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0xFFFFFF, 0x000000, 0x000000,
  g_pFontCm18, "Label201", 0, 0);


Canvas(CanvasStatut, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0,
       800, 480, (CANVAS_STYLE_APP_DRAWN | CV_AOPT_VISIBLE), 0, 0, 0, 0, 0, 0, hmi_OnStatut2Paint);

void hmi_renderStatut2Vector(tContext *pContext, int ox, int oy) {
  hmi_DrawImage(pContext, pucImage_Picture101, ox+0, oy+0);
hmi_SetForeground(pContext, 0x0000FF40);
hmi_FillRect(pContext, 5 + ox, 95 + oy, 235 + ox, 175 + oy);
hmi_SetForeground(pContext, 0x00000000);
hmi_DrawRect(pContext, 5 + ox, 95 + oy, 235 + ox, 175 + oy);
hmi_SetForeground(pContext, 0x0000FF40);
hmi_FillRect(pContext, 5 + ox, 185 + oy, 235 + ox, 285 + oy);
hmi_SetForeground(pContext, 0x00000000);
hmi_DrawRect(pContext, 5 + ox, 185 + oy, 235 + ox, 285 + oy);
}
void hmi_OnStatut2Paint(tWidget *pWidget, tContext *pContext)
{
  hmi_SetForeground(pContext, 0x2B7171);
  hmi_FillRect(pContext, 0, 0, 800, 480);
  hmi_renderStatut2Vector(pContext, 0, 0);
}

static void hmi_InitGlobalContext()
{
  GrContextInit(thisContext, thisCanvas->pDisplay);
  GrContextClipRegionSet(thisContext, &(thisCanvas->sPosition));
}
void hmi_InitFrameWidgets1()
{
  hmi_EnableDrawings(0);
  Statut2OnCreate();
  WidgetAdd(WIDGET_ROOT, (tWidget *)(&CanvasStatut));
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label5);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Timer8);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Timer10);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Slider11);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Slider9);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Slider18);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Slider19);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label21);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&BitButton22);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Slider24);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Slider25);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Slider26);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Timer29);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label34);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label35);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label36);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label37);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label38);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label39);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label41);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton43);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton49);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton44);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton50);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton45);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton51);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton46);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton52);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton47);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton53);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton48);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton54);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label58);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label66);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label28);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton56);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton62);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton109);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton110);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton147);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton6);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton13);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label31);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton32);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton33);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton193);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label201);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label212);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label213);
  hmi_InitGlobalContext();
  hmi_ConnectWidgetVariable();
  hmi_EnableDrawings(1);
  TimerReset(&Timer8);
  TimerReset(&Timer10);
  TimerReset(&Timer29);
}

void hmi_FreeFrameWidgets1()
{
  hmi_DisconnectWidgetVariable();
  WidgetRemove((tWidget *)(&CanvasStatut));
  WidgetRemove((tWidget *)(&Label5));
  WidgetRemove((tWidget *)(&Timer8));
  WidgetRemove((tWidget *)(&Timer10));
  WidgetRemove((tWidget *)(&Slider11));
  WidgetRemove((tWidget *)(&Slider9));
  WidgetRemove((tWidget *)(&Slider18));
  WidgetRemove((tWidget *)(&Slider19));
  WidgetRemove((tWidget *)(&Label21));
  WidgetRemove((tWidget *)(&BitButton22));
  WidgetRemove((tWidget *)(&Slider24));
  WidgetRemove((tWidget *)(&Slider25));
  WidgetRemove((tWidget *)(&Slider26));
  WidgetRemove((tWidget *)(&Timer29));
  WidgetRemove((tWidget *)(&Label34));
  WidgetRemove((tWidget *)(&Label35));
  WidgetRemove((tWidget *)(&Label36));
  WidgetRemove((tWidget *)(&Label37));
  WidgetRemove((tWidget *)(&Label38));
  WidgetRemove((tWidget *)(&Label39));
  WidgetRemove((tWidget *)(&Label41));
  WidgetRemove((tWidget *)(&TextPushButton43));
  WidgetRemove((tWidget *)(&TextPushButton49));
  WidgetRemove((tWidget *)(&TextPushButton44));
  WidgetRemove((tWidget *)(&TextPushButton50));
  WidgetRemove((tWidget *)(&TextPushButton45));
  WidgetRemove((tWidget *)(&TextPushButton51));
  WidgetRemove((tWidget *)(&TextPushButton46));
  WidgetRemove((tWidget *)(&TextPushButton52));
  WidgetRemove((tWidget *)(&TextPushButton47));
  WidgetRemove((tWidget *)(&TextPushButton53));
  WidgetRemove((tWidget *)(&TextPushButton48));
  WidgetRemove((tWidget *)(&TextPushButton54));
  WidgetRemove((tWidget *)(&Label58));
  WidgetRemove((tWidget *)(&Label66));
  WidgetRemove((tWidget *)(&Label28));
  WidgetRemove((tWidget *)(&TextPushButton56));
  WidgetRemove((tWidget *)(&TextPushButton62));
  WidgetRemove((tWidget *)(&TextPushButton109));
  WidgetRemove((tWidget *)(&TextPushButton110));
  WidgetRemove((tWidget *)(&TextPushButton147));
  WidgetRemove((tWidget *)(&TextPushButton6));
  WidgetRemove((tWidget *)(&TextPushButton13));
  WidgetRemove((tWidget *)(&Label31));
  WidgetRemove((tWidget *)(&TextPushButton32));
  WidgetRemove((tWidget *)(&TextPushButton33));
  WidgetRemove((tWidget *)(&TextPushButton193));
  WidgetRemove((tWidget *)(&Label201));
  WidgetRemove((tWidget *)(&Label212));
  WidgetRemove((tWidget *)(&Label213));
}


void hmi_hmi_OnTimer8Execute(tWidget *pWidget)
{
  Timer8OnExecute(pWidget);
}


void hmi_hmi_OnTimer10Execute(tWidget *pWidget)
{
  Timer10OnExecute(pWidget);
}


void hmi_hmi_OnSlider11SliderChange(tWidget *pWidget, long lValue)
{
  Slider11OnSliderChange(pWidget, lValue);
}


void hmi_hmi_OnSlider9SliderChange(tWidget *pWidget, long lValue)
{
  SliderAxeOnChange(pWidget, lValue);
}


void hmi_hmi_OnSlider18SliderChange(tWidget *pWidget, long lValue)
{
  SliderAxeOnChange(pWidget, lValue);
}


void hmi_hmi_OnSlider19SliderChange(tWidget *pWidget, long lValue)
{
  SliderAxeOnChange(pWidget, lValue);
}



void hmi_OnBitButton22Release(tWidget *pWidget)
{
}

void hmi_hmi_OnBitButton22Click(tWidget *pWidget) 
{
  BitButton22OnClick(pWidget);
}

void hmi_hmi_OnSlider24SliderChange(tWidget *pWidget, long lValue)
{
  SliderAxeOnChange(pWidget, lValue);
}


void hmi_hmi_OnSlider25SliderChange(tWidget *pWidget, long lValue)
{
  SliderAxeOnChange(pWidget, lValue);
}


void hmi_hmi_OnSlider26SliderChange(tWidget *pWidget, long lValue)
{
  SliderAxeOnChange(pWidget, lValue);
}


void hmi_hmi_OnTimer29Execute(tWidget *pWidget)
{
  Timer29OnExecute(pWidget);
}


void hmi_OnTextPushButton43Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton43Click(tWidget *pWidget)
{
  TextButtonOnClick(pWidget);
}


void hmi_OnTextPushButton49Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton49Click(tWidget *pWidget)
{
  TextButtonOnClick(pWidget);
}


void hmi_OnTextPushButton44Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton44Click(tWidget *pWidget)
{
  TextButtonOnClick(pWidget);
}


void hmi_OnTextPushButton50Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton50Click(tWidget *pWidget)
{
  TextButtonOnClick(pWidget);
}


void hmi_OnTextPushButton45Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton45Click(tWidget *pWidget)
{
  TextButtonOnClick(pWidget);
}


void hmi_OnTextPushButton51Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton51Click(tWidget *pWidget)
{
  TextButtonOnClick(pWidget);
}


void hmi_OnTextPushButton46Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton46Click(tWidget *pWidget)
{
  TextButtonOnClick(pWidget);
}


void hmi_OnTextPushButton52Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton52Click(tWidget *pWidget)
{
  TextButtonOnClick(pWidget);
}


void hmi_OnTextPushButton47Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton47Click(tWidget *pWidget)
{
  TextButtonOnClick(pWidget);
}


void hmi_OnTextPushButton53Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton53Click(tWidget *pWidget)
{
  TextButtonOnClick(pWidget);
}


void hmi_OnTextPushButton48Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton48Click(tWidget *pWidget)
{
  TextButtonOnClick(pWidget);
}


void hmi_OnTextPushButton54Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton54Click(tWidget *pWidget)
{
  TextButtonOnClick(pWidget);
}


void hmi_OnTextPushButton56Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton56Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton62Release(tWidget *pWidget)
{
  hmi_GotoFrameByName("Trajectoire");
}

void hmi_hmi_OnTextPushButton62Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton109Release(tWidget *pWidget)
{
  hmi_GotoFrameByName("Menu");
}

void hmi_hmi_OnTextPushButton109Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton110Release(tWidget *pWidget)
{
  hmi_GotoFrameByName("Statistic");
}

void hmi_hmi_OnTextPushButton110Click(tWidget *pWidget)
{
}


void hmi_OnTextPushButton147Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton147Click(tWidget *pWidget)
{
  TextPushButton147OnClick(pWidget);
}


void hmi_OnTextPushButton6Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton6Click(tWidget *pWidget)
{
  TextPushButton6OnClick(pWidget);
}


void hmi_OnTextPushButton13Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton13Click(tWidget *pWidget)
{
  TextPushButton13OnClick(pWidget);
}


void hmi_OnTextPushButton32Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton32Click(tWidget *pWidget)
{
  TextPushButton32OnClick(pWidget);
}


void hmi_OnTextPushButton33Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton33Click(tWidget *pWidget)
{
  TextPushButton33OnClick(pWidget);
}


void hmi_OnTextPushButton193Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton193Click(tWidget *pWidget)
{
  TextPushButton193OnClick(pWidget);
}


static void hmi_ConnectWidgetVariable()
{
  if (g_hmi_CurrentFrame != 1) return;
}

static void hmi_DisconnectWidgetVariable()
{
}

void hmi_Statut()
{
  hmi_var_table_init();
  hmi_FreeCurrentFrame();
  g_hmi_CurrentFrame = 1;
  hmi_InitFrameWidgets1();
}

