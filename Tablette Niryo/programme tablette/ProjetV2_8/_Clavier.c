#include "hmiworks.h"
#pragma GCC diagnostic ignored "-Wunused-variable"

static tWidget *thisCanvas = (tWidget *)&CanvasClavier;
static tContext globalContext;
static tContext *thisContext = &globalContext;

#pragma GCC diagnostic warning "-Wunused-variable"


static void hmi_ConnectWidgetVariable();
static void hmi_DisconnectWidgetVariable();

#include "__clavier.h"

RectangularButton(TextPushButton67, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 85, 170, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss18, "1", 0,
  200, 100,
  hmi_hmi_OnTextPushButton67Click, hmi_OnTextPushButton67Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton55, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 20, 170, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss18, "0", 0,
  200, 100,
  hmi_hmi_OnTextPushButton55Click, hmi_OnTextPushButton55Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton68, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 150, 170, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss18, "2", 0,
  200, 100,
  hmi_hmi_OnTextPushButton68Click, hmi_OnTextPushButton68Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton69, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 215, 170, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss18, "3", 0,
  200, 100,
  hmi_hmi_OnTextPushButton69Click, hmi_OnTextPushButton69Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton70, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 280, 170, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss18, "4", 0,
  200, 100,
  hmi_hmi_OnTextPushButton70Click, hmi_OnTextPushButton70Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton71, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 345, 170, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss18, "5", 0,
  200, 100,
  hmi_hmi_OnTextPushButton71Click, hmi_OnTextPushButton71Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton72, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 410, 170, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "6", 0,
  200, 100,
  hmi_hmi_OnTextPushButton72Click, hmi_OnTextPushButton72Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton73, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 475, 170, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss18, "7", 0,
  200, 100,
  hmi_hmi_OnTextPushButton73Click, hmi_OnTextPushButton73Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton74, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 540, 170, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss18, "8", 0,
  200, 100,
  hmi_hmi_OnTextPushButton74Click, hmi_OnTextPushButton74Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton75, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 605, 170, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0x40FF00, 0x000000, 0x000000,
  g_pFontCmss18, "9", 0,
  200, 100,
  hmi_hmi_OnTextPushButton75Click, hmi_OnTextPushButton75Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton76, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 70, 250, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "A", 0,
  200, 100,
  hmi_hmi_OnTextPushButton76Click, hmi_OnTextPushButton76Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton77, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 390, 390, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "B", 0,
  200, 100,
  hmi_hmi_OnTextPushButton77Click, hmi_OnTextPushButton77Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton78, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 260, 390, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "C", 0,
  200, 100,
  hmi_hmi_OnTextPushButton78Click, hmi_OnTextPushButton78Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton79, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 230, 320, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "D", 0,
  200, 100,
  hmi_hmi_OnTextPushButton79Click, hmi_OnTextPushButton79Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton80, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 200, 250, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "E", 0,
  200, 100,
  hmi_hmi_OnTextPushButton80Click, hmi_OnTextPushButton80Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton81, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 295, 320, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "F", 0,
  200, 100,
  hmi_hmi_OnTextPushButton81Click, hmi_OnTextPushButton81Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton82, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 360, 320, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "G", 0,
  200, 100,
  hmi_hmi_OnTextPushButton82Click, hmi_OnTextPushButton82Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton83, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 425, 320, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "H", 0,
  200, 100,
  hmi_hmi_OnTextPushButton83Click, hmi_OnTextPushButton83Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton84, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 525, 250, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "I", 0,
  200, 100,
  hmi_hmi_OnTextPushButton84Click, hmi_OnTextPushButton84Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton85, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 490, 320, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "J", 0,
  200, 100,
  hmi_hmi_OnTextPushButton85Click, hmi_OnTextPushButton85Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton86, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 555, 320, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "K", 0,
  200, 100,
  hmi_hmi_OnTextPushButton86Click, hmi_OnTextPushButton86Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton87, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 620, 320, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "L", 0,
  200, 100,
  hmi_hmi_OnTextPushButton87Click, hmi_OnTextPushButton87Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton88, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 685, 320, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "M", 0,
  200, 100,
  hmi_hmi_OnTextPushButton88Click, hmi_OnTextPushButton88Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton89, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 455, 390, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "N", 0,
  200, 100,
  hmi_hmi_OnTextPushButton89Click, hmi_OnTextPushButton89Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton90, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 590, 250, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "O", 0,
  200, 100,
  hmi_hmi_OnTextPushButton90Click, hmi_OnTextPushButton90Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton91, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 655, 250, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "P", 0,
  200, 100,
  hmi_hmi_OnTextPushButton91Click, hmi_OnTextPushButton91Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton92, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 100, 320, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "Q", 0,
  200, 100,
  hmi_hmi_OnTextPushButton92Click, hmi_OnTextPushButton92Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton93, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 265, 250, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "R", 0,
  200, 100,
  hmi_hmi_OnTextPushButton93Click, hmi_OnTextPushButton93Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton94, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 330, 250, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "T", 0,
  200, 100,
  hmi_hmi_OnTextPushButton94Click, hmi_OnTextPushButton94Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton95, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 460, 250, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "U", 0,
  200, 100,
  hmi_hmi_OnTextPushButton95Click, hmi_OnTextPushButton95Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton96, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 325, 390, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "V", 0,
  200, 100,
  hmi_hmi_OnTextPushButton96Click, hmi_OnTextPushButton96Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton97, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 130, 390, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "W", 0,
  200, 100,
  hmi_hmi_OnTextPushButton97Click, hmi_OnTextPushButton97Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton98, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 195, 390, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "X", 0,
  200, 100,
  hmi_hmi_OnTextPushButton98Click, hmi_OnTextPushButton98Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton99, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 395, 250, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "Y", 0,
  200, 100,
  hmi_hmi_OnTextPushButton99Click, hmi_OnTextPushButton99Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton100, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 135, 250, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "Z", 0,
  200, 100,
  hmi_hmi_OnTextPushButton100Click, hmi_OnTextPushButton100Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton102, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 165, 320, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x646464, 0xFF0000, 0x000000, 0x000000,
  g_pFontCmss18, "S", 0,
  200, 100,
  hmi_hmi_OnTextPushButton102Click, hmi_OnTextPushButton102Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton103, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 520, 390, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x40FF00, 0x1E7500, 0x000000, 0x000000,
  g_pFontCmss18, "effacer", 0,
  200, 100,
  hmi_hmi_OnTextPushButton103Click, hmi_OnTextPushButton103Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton104, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 585, 390, 60, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x40FF00, 0x1E7500, 0x000000, 0x000000,
  g_pFontCmss18, "annuler", 0,
  200, 100,
  hmi_hmi_OnTextPushButton104Click, hmi_OnTextPushButton104Release, 0,
  0, -1, 0);
RectangularButton(TextPushButton105, WIDGET_ROOT, 0,
   0, HMI_DISPLAY_DRIVER_PTR, 650, 390, 120, 60,
   (PB_STYLE_OUTLINE | PB_STYLE_TEXT_OPAQUE | PB_STYLE_TEXT | PB_AOPT_VISIBLE | PB_AOPT_ENABLED | PB_STYLE_AUTO_REPEAT | 
   PB_STYLE_FILL), 0x40FF00, 0x1E7500, 0x000000, 0x000000,
  g_pFontCmss18, "entrer", 0,
  200, 100,
  hmi_hmi_OnTextPushButton105Click, hmi_OnTextPushButton105Release, 0,
  0, -1, 0);
Canvas(Label207, WIDGET_ROOT, 0, 0,
   HMI_DISPLAY_DRIVER_PTR, 44, 45, 436, 94,
   CANVAS_STYLE_TEXT | CANVAS_STYLE_FILL | CANVAS_STYLE_OUTLINE
    | CANVAS_STYLE_TEXT_HCENTER | CV_AOPT_VISIBLE | CV_AOPT_ENABLED | CANVAS_STYLE_TEXT_OPAQUE
  , 0x000000, 0x000000, 0xFFFFFF,
  g_pFontCmss22b, "Label207", 0, 0);


Canvas(CanvasClavier, WIDGET_ROOT, 0, 0, HMI_DISPLAY_DRIVER_PTR, 0, 0,
       800, 480, (CANVAS_STYLE_APP_DRAWN | CV_AOPT_VISIBLE), 0, 0, 0, 0, 0, 0, hmi_OnClavier23Paint);

void hmi_renderClavier23Vector(tContext *pContext, int ox, int oy) {
}
void hmi_OnClavier23Paint(tWidget *pWidget, tContext *pContext)
{
  hmi_SetForeground(pContext, 0x252525);
  hmi_FillRect(pContext, 0, 0, 800, 480);
  hmi_renderClavier23Vector(pContext, 0, 0);
}

static void hmi_InitGlobalContext()
{
  GrContextInit(thisContext, thisCanvas->pDisplay);
  GrContextClipRegionSet(thisContext, &(thisCanvas->sPosition));
}
void hmi_InitFrameWidgets3()
{
  hmi_EnableDrawings(0);
  Clavier23OnCreate();
  WidgetAdd(WIDGET_ROOT, (tWidget *)(&CanvasClavier));
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton67);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton55);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton68);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton69);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton70);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton71);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton72);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton73);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton74);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton75);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton76);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton77);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton78);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton79);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton80);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton81);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton82);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton83);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton84);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton85);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton86);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton87);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton88);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton89);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton90);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton91);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton92);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton93);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton94);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton95);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton96);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton97);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton98);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton99);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton100);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton102);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton103);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton104);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&TextPushButton105);
  WidgetAdd(WIDGET_ROOT, (tWidget *)&Label207);
  hmi_InitGlobalContext();
  hmi_ConnectWidgetVariable();
  hmi_EnableDrawings(1);
}

void hmi_FreeFrameWidgets3()
{
  hmi_DisconnectWidgetVariable();
  WidgetRemove((tWidget *)(&CanvasClavier));
  WidgetRemove((tWidget *)(&TextPushButton67));
  WidgetRemove((tWidget *)(&TextPushButton55));
  WidgetRemove((tWidget *)(&TextPushButton68));
  WidgetRemove((tWidget *)(&TextPushButton69));
  WidgetRemove((tWidget *)(&TextPushButton70));
  WidgetRemove((tWidget *)(&TextPushButton71));
  WidgetRemove((tWidget *)(&TextPushButton72));
  WidgetRemove((tWidget *)(&TextPushButton73));
  WidgetRemove((tWidget *)(&TextPushButton74));
  WidgetRemove((tWidget *)(&TextPushButton75));
  WidgetRemove((tWidget *)(&TextPushButton76));
  WidgetRemove((tWidget *)(&TextPushButton77));
  WidgetRemove((tWidget *)(&TextPushButton78));
  WidgetRemove((tWidget *)(&TextPushButton79));
  WidgetRemove((tWidget *)(&TextPushButton80));
  WidgetRemove((tWidget *)(&TextPushButton81));
  WidgetRemove((tWidget *)(&TextPushButton82));
  WidgetRemove((tWidget *)(&TextPushButton83));
  WidgetRemove((tWidget *)(&TextPushButton84));
  WidgetRemove((tWidget *)(&TextPushButton85));
  WidgetRemove((tWidget *)(&TextPushButton86));
  WidgetRemove((tWidget *)(&TextPushButton87));
  WidgetRemove((tWidget *)(&TextPushButton88));
  WidgetRemove((tWidget *)(&TextPushButton89));
  WidgetRemove((tWidget *)(&TextPushButton90));
  WidgetRemove((tWidget *)(&TextPushButton91));
  WidgetRemove((tWidget *)(&TextPushButton92));
  WidgetRemove((tWidget *)(&TextPushButton93));
  WidgetRemove((tWidget *)(&TextPushButton94));
  WidgetRemove((tWidget *)(&TextPushButton95));
  WidgetRemove((tWidget *)(&TextPushButton96));
  WidgetRemove((tWidget *)(&TextPushButton97));
  WidgetRemove((tWidget *)(&TextPushButton98));
  WidgetRemove((tWidget *)(&TextPushButton99));
  WidgetRemove((tWidget *)(&TextPushButton100));
  WidgetRemove((tWidget *)(&TextPushButton102));
  WidgetRemove((tWidget *)(&TextPushButton103));
  WidgetRemove((tWidget *)(&TextPushButton104));
  WidgetRemove((tWidget *)(&TextPushButton105));
  WidgetRemove((tWidget *)(&Label207));
}


void hmi_OnTextPushButton67Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton67Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton55Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton55Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton68Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton68Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton69Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton69Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton70Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton70Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton71Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton71Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton72Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton72Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton73Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton73Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton74Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton74Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton75Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton75Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton76Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton76Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton77Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton77Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton78Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton78Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton79Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton79Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton80Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton80Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton81Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton81Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton82Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton82Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton83Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton83Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton84Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton84Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton85Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton85Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton86Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton86Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton87Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton87Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton88Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton88Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton89Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton89Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton90Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton90Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton91Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton91Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton92Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton92Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton93Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton93Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton94Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton94Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton95Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton95Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton96Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton96Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton97Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton97Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton98Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton98Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton99Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton99Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton100Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton100Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton102Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton102Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton103Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton103Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton104Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton104Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


void hmi_OnTextPushButton105Release(tWidget *pWidget)
{
}

void hmi_hmi_OnTextPushButton105Click(tWidget *pWidget)
{
  TextPushButtonClavierOnClick(pWidget);
}


static void hmi_ConnectWidgetVariable()
{
  if (g_hmi_CurrentFrame != 3) return;
}

static void hmi_DisconnectWidgetVariable()
{
}

void hmi_Clavier()
{
  hmi_var_table_init();
  hmi_FreeCurrentFrame();
  g_hmi_CurrentFrame = 3;
  hmi_InitFrameWidgets3();
}

