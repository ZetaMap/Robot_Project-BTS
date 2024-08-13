#ifndef __HMI_FRAME0_H
#define __HMI_FRAME0_H
extern volatile unsigned long g_TimerTicksCount;
extern int g_hmi_CurrentFrame;
extern void hmi_frame0();
extern void hmi_FreeCurrentFrame();
extern void hmi_GotoFrame(int nFrame);
extern void hmi_TimerTrigger();
extern void hmi_TurnBacklight(int bOn);
extern void hmi_IOScan_Process(void);

extern tCanvasWidget Label5;
extern tTimerWidget Timer8;
extern void hmi_hmi_OnTimer8Execute(tWidget *pWidget);
extern tTimerWidget Timer10;
extern void hmi_hmi_OnTimer10Execute(tWidget *pWidget);
extern tSliderWidget Slider11;
extern void hmi_hmi_OnSlider11SliderChange(tWidget *pWidget, long lValue);

extern tSliderWidget Slider9;
extern void hmi_hmi_OnSlider9SliderChange(tWidget *pWidget, long lValue);

extern tSliderWidget Slider18;
extern void hmi_hmi_OnSlider18SliderChange(tWidget *pWidget, long lValue);

extern tSliderWidget Slider19;
extern void hmi_hmi_OnSlider19SliderChange(tWidget *pWidget, long lValue);

extern tCanvasWidget Label21;
extern tPushButtonWidget BitButton22;
extern void hmi_hmi_OnBitButton22Click(tWidget *pWidget);
extern void hmi_OnBitButton22Release(tWidget *pWidget);

extern tSliderWidget Slider24;
extern void hmi_hmi_OnSlider24SliderChange(tWidget *pWidget, long lValue);

extern tSliderWidget Slider25;
extern void hmi_hmi_OnSlider25SliderChange(tWidget *pWidget, long lValue);

extern tSliderWidget Slider26;
extern void hmi_hmi_OnSlider26SliderChange(tWidget *pWidget, long lValue);

extern tTimerWidget Timer29;
extern void hmi_hmi_OnTimer29Execute(tWidget *pWidget);
extern tCanvasWidget Label34;
extern tCanvasWidget Label35;
extern tCanvasWidget Label36;
extern tCanvasWidget Label37;
extern tCanvasWidget Label38;
extern tCanvasWidget Label39;
extern tCanvasWidget Label41;
extern tPushButtonWidget TextPushButton43;
extern void _hmi_OnTextPushButton43Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton43Click(tWidget *pWidget);
extern void hmi_OnTextPushButton43Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton49;
extern void _hmi_OnTextPushButton49Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton49Click(tWidget *pWidget);
extern void hmi_OnTextPushButton49Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton44;
extern void _hmi_OnTextPushButton44Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton44Click(tWidget *pWidget);
extern void hmi_OnTextPushButton44Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton50;
extern void _hmi_OnTextPushButton50Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton50Click(tWidget *pWidget);
extern void hmi_OnTextPushButton50Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton45;
extern void _hmi_OnTextPushButton45Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton45Click(tWidget *pWidget);
extern void hmi_OnTextPushButton45Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton51;
extern void _hmi_OnTextPushButton51Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton51Click(tWidget *pWidget);
extern void hmi_OnTextPushButton51Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton46;
extern void _hmi_OnTextPushButton46Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton46Click(tWidget *pWidget);
extern void hmi_OnTextPushButton46Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton52;
extern void _hmi_OnTextPushButton52Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton52Click(tWidget *pWidget);
extern void hmi_OnTextPushButton52Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton47;
extern void _hmi_OnTextPushButton47Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton47Click(tWidget *pWidget);
extern void hmi_OnTextPushButton47Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton53;
extern void _hmi_OnTextPushButton53Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton53Click(tWidget *pWidget);
extern void hmi_OnTextPushButton53Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton48;
extern void _hmi_OnTextPushButton48Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton48Click(tWidget *pWidget);
extern void hmi_OnTextPushButton48Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton54;
extern void _hmi_OnTextPushButton54Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton54Click(tWidget *pWidget);
extern void hmi_OnTextPushButton54Release(tWidget *pWidget);

extern tCanvasWidget Label58;
extern tCanvasWidget Label66;
extern tCanvasWidget Label28;
extern tPushButtonWidget TextPushButton56;
extern void _hmi_OnTextPushButton56Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton56Click(tWidget *pWidget);
extern void hmi_OnTextPushButton56Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton62;
extern void _hmi_OnTextPushButton62Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton62Click(tWidget *pWidget);
extern void hmi_OnTextPushButton62Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton109;
extern void _hmi_OnTextPushButton109Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton109Click(tWidget *pWidget);
extern void hmi_OnTextPushButton109Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton110;
extern void _hmi_OnTextPushButton110Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton110Click(tWidget *pWidget);
extern void hmi_OnTextPushButton110Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton147;
extern void _hmi_OnTextPushButton147Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton147Click(tWidget *pWidget);
extern void hmi_OnTextPushButton147Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton6;
extern void _hmi_OnTextPushButton6Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton6Click(tWidget *pWidget);
extern void hmi_OnTextPushButton6Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton13;
extern void _hmi_OnTextPushButton13Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton13Click(tWidget *pWidget);
extern void hmi_OnTextPushButton13Release(tWidget *pWidget);

extern tCanvasWidget Label31;
extern tPushButtonWidget TextPushButton32;
extern void _hmi_OnTextPushButton32Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton32Click(tWidget *pWidget);
extern void hmi_OnTextPushButton32Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton33;
extern void _hmi_OnTextPushButton33Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton33Click(tWidget *pWidget);
extern void hmi_OnTextPushButton33Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton193;
extern void _hmi_OnTextPushButton193Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton193Click(tWidget *pWidget);
extern void hmi_OnTextPushButton193Release(tWidget *pWidget);

extern tCanvasWidget Label201;
extern tCanvasWidget Label212;
extern tCanvasWidget Label213;
extern tTimerWidget Timer15;
extern void hmi_hmi_OnTimer15Execute(tWidget *pWidget);
extern tCanvasWidget Label16;
extern tCanvasWidget Label106;
extern tPushButtonWidget BitButton124;
extern void hmi_hmi_OnBitButton124Click(tWidget *pWidget);
extern void hmi_OnBitButton124Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton67;
extern void _hmi_OnTextPushButton67Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton67Click(tWidget *pWidget);
extern void hmi_OnTextPushButton67Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton55;
extern void _hmi_OnTextPushButton55Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton55Click(tWidget *pWidget);
extern void hmi_OnTextPushButton55Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton68;
extern void _hmi_OnTextPushButton68Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton68Click(tWidget *pWidget);
extern void hmi_OnTextPushButton68Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton69;
extern void _hmi_OnTextPushButton69Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton69Click(tWidget *pWidget);
extern void hmi_OnTextPushButton69Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton70;
extern void _hmi_OnTextPushButton70Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton70Click(tWidget *pWidget);
extern void hmi_OnTextPushButton70Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton71;
extern void _hmi_OnTextPushButton71Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton71Click(tWidget *pWidget);
extern void hmi_OnTextPushButton71Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton72;
extern void _hmi_OnTextPushButton72Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton72Click(tWidget *pWidget);
extern void hmi_OnTextPushButton72Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton73;
extern void _hmi_OnTextPushButton73Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton73Click(tWidget *pWidget);
extern void hmi_OnTextPushButton73Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton74;
extern void _hmi_OnTextPushButton74Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton74Click(tWidget *pWidget);
extern void hmi_OnTextPushButton74Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton75;
extern void _hmi_OnTextPushButton75Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton75Click(tWidget *pWidget);
extern void hmi_OnTextPushButton75Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton76;
extern void _hmi_OnTextPushButton76Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton76Click(tWidget *pWidget);
extern void hmi_OnTextPushButton76Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton77;
extern void _hmi_OnTextPushButton77Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton77Click(tWidget *pWidget);
extern void hmi_OnTextPushButton77Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton78;
extern void _hmi_OnTextPushButton78Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton78Click(tWidget *pWidget);
extern void hmi_OnTextPushButton78Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton79;
extern void _hmi_OnTextPushButton79Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton79Click(tWidget *pWidget);
extern void hmi_OnTextPushButton79Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton80;
extern void _hmi_OnTextPushButton80Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton80Click(tWidget *pWidget);
extern void hmi_OnTextPushButton80Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton81;
extern void _hmi_OnTextPushButton81Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton81Click(tWidget *pWidget);
extern void hmi_OnTextPushButton81Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton82;
extern void _hmi_OnTextPushButton82Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton82Click(tWidget *pWidget);
extern void hmi_OnTextPushButton82Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton83;
extern void _hmi_OnTextPushButton83Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton83Click(tWidget *pWidget);
extern void hmi_OnTextPushButton83Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton84;
extern void _hmi_OnTextPushButton84Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton84Click(tWidget *pWidget);
extern void hmi_OnTextPushButton84Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton85;
extern void _hmi_OnTextPushButton85Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton85Click(tWidget *pWidget);
extern void hmi_OnTextPushButton85Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton86;
extern void _hmi_OnTextPushButton86Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton86Click(tWidget *pWidget);
extern void hmi_OnTextPushButton86Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton87;
extern void _hmi_OnTextPushButton87Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton87Click(tWidget *pWidget);
extern void hmi_OnTextPushButton87Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton88;
extern void _hmi_OnTextPushButton88Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton88Click(tWidget *pWidget);
extern void hmi_OnTextPushButton88Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton89;
extern void _hmi_OnTextPushButton89Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton89Click(tWidget *pWidget);
extern void hmi_OnTextPushButton89Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton90;
extern void _hmi_OnTextPushButton90Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton90Click(tWidget *pWidget);
extern void hmi_OnTextPushButton90Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton91;
extern void _hmi_OnTextPushButton91Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton91Click(tWidget *pWidget);
extern void hmi_OnTextPushButton91Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton92;
extern void _hmi_OnTextPushButton92Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton92Click(tWidget *pWidget);
extern void hmi_OnTextPushButton92Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton93;
extern void _hmi_OnTextPushButton93Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton93Click(tWidget *pWidget);
extern void hmi_OnTextPushButton93Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton94;
extern void _hmi_OnTextPushButton94Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton94Click(tWidget *pWidget);
extern void hmi_OnTextPushButton94Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton95;
extern void _hmi_OnTextPushButton95Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton95Click(tWidget *pWidget);
extern void hmi_OnTextPushButton95Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton96;
extern void _hmi_OnTextPushButton96Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton96Click(tWidget *pWidget);
extern void hmi_OnTextPushButton96Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton97;
extern void _hmi_OnTextPushButton97Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton97Click(tWidget *pWidget);
extern void hmi_OnTextPushButton97Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton98;
extern void _hmi_OnTextPushButton98Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton98Click(tWidget *pWidget);
extern void hmi_OnTextPushButton98Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton99;
extern void _hmi_OnTextPushButton99Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton99Click(tWidget *pWidget);
extern void hmi_OnTextPushButton99Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton100;
extern void _hmi_OnTextPushButton100Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton100Click(tWidget *pWidget);
extern void hmi_OnTextPushButton100Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton102;
extern void _hmi_OnTextPushButton102Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton102Click(tWidget *pWidget);
extern void hmi_OnTextPushButton102Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton103;
extern void _hmi_OnTextPushButton103Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton103Click(tWidget *pWidget);
extern void hmi_OnTextPushButton103Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton104;
extern void _hmi_OnTextPushButton104Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton104Click(tWidget *pWidget);
extern void hmi_OnTextPushButton104Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton105;
extern void _hmi_OnTextPushButton105Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton105Click(tWidget *pWidget);
extern void hmi_OnTextPushButton105Release(tWidget *pWidget);

extern tCanvasWidget Label207;
extern tPushButtonWidget TextPushButton57;
extern void _hmi_OnTextPushButton57Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton57Click(tWidget *pWidget);
extern void hmi_OnTextPushButton57Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton63;
extern void _hmi_OnTextPushButton63Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton63Click(tWidget *pWidget);
extern void hmi_OnTextPushButton63Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton107;
extern void _hmi_OnTextPushButton107Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton107Click(tWidget *pWidget);
extern void hmi_OnTextPushButton107Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton108;
extern void _hmi_OnTextPushButton108Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton108Click(tWidget *pWidget);
extern void hmi_OnTextPushButton108Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton111;
extern void _hmi_OnTextPushButton111Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton111Click(tWidget *pWidget);
extern void hmi_OnTextPushButton111Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton117;
extern void _hmi_OnTextPushButton117Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton117Click(tWidget *pWidget);
extern void hmi_OnTextPushButton117Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton122;
extern void _hmi_OnTextPushButton122Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton122Click(tWidget *pWidget);
extern void hmi_OnTextPushButton122Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton123;
extern void _hmi_OnTextPushButton123Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton123Click(tWidget *pWidget);
extern void hmi_OnTextPushButton123Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton125;
extern void _hmi_OnTextPushButton125Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton125Click(tWidget *pWidget);
extern void hmi_OnTextPushButton125Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton130;
extern void _hmi_OnTextPushButton130Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton130Click(tWidget *pWidget);
extern void hmi_OnTextPushButton130Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton131;
extern void _hmi_OnTextPushButton131Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton131Click(tWidget *pWidget);
extern void hmi_OnTextPushButton131Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton132;
extern void _hmi_OnTextPushButton132Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton132Click(tWidget *pWidget);
extern void hmi_OnTextPushButton132Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton133;
extern void _hmi_OnTextPushButton133Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton133Click(tWidget *pWidget);
extern void hmi_OnTextPushButton133Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton134;
extern void _hmi_OnTextPushButton134Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton134Click(tWidget *pWidget);
extern void hmi_OnTextPushButton134Release(tWidget *pWidget);

extern tTimerWidget Timer135;
extern void hmi_hmi_OnTimer135Execute(tWidget *pWidget);
extern tPushButtonWidget TextPushButton144;
extern void _hmi_OnTextPushButton144Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton144Click(tWidget *pWidget);
extern void hmi_OnTextPushButton144Release(tWidget *pWidget);

extern tTimerWidget Timer139;
extern void hmi_hmi_OnTimer139Execute(tWidget *pWidget);
extern tPushButtonWidget TextPushButton42;
extern void _hmi_OnTextPushButton42Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton42Click(tWidget *pWidget);
extern void hmi_OnTextPushButton42Release(tWidget *pWidget);

extern tCanvasWidget Label151;
extern tTimerWidget Timer206;
extern void hmi_hmi_OnTimer206Execute(tWidget *pWidget);
extern tCanvasWidget Label208;
extern tCanvasWidget Label209;
extern tCanvasWidget Label210;
extern tCanvasWidget Label211;
extern tPushButtonWidget TextPushButton64;
extern void _hmi_OnTextPushButton64Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton64Click(tWidget *pWidget);
extern void hmi_OnTextPushButton64Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton65;
extern void _hmi_OnTextPushButton65Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton65Click(tWidget *pWidget);
extern void hmi_OnTextPushButton65Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton30;
extern void _hmi_OnTextPushButton30Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton30Click(tWidget *pWidget);
extern void hmi_OnTextPushButton30Release(tWidget *pWidget);

extern tCanvasWidget Label112;
extern tPushButtonWidget TextPushButton126;
extern void _hmi_OnTextPushButton126Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton126Click(tWidget *pWidget);
extern void hmi_OnTextPushButton126Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton127;
extern void _hmi_OnTextPushButton127Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton127Click(tWidget *pWidget);
extern void hmi_OnTextPushButton127Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton128;
extern void _hmi_OnTextPushButton128Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton128Click(tWidget *pWidget);
extern void hmi_OnTextPushButton128Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton129;
extern void _hmi_OnTextPushButton129Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton129Click(tWidget *pWidget);
extern void hmi_OnTextPushButton129Release(tWidget *pWidget);

extern tTimerWidget Timer145;
extern void hmi_hmi_OnTimer145Execute(tWidget *pWidget);
extern tPushButtonWidget TextPushButton148;
extern void _hmi_OnTextPushButton148Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton148Click(tWidget *pWidget);
extern void hmi_OnTextPushButton148Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton152;
extern void _hmi_OnTextPushButton152Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton152Click(tWidget *pWidget);
extern void hmi_OnTextPushButton152Release(tWidget *pWidget);

extern tSliderWidget Slider40;
extern void hmi_hmi_OnSlider40SliderChange(tWidget *pWidget, long lValue);

extern tSliderWidget Slider200;
extern void hmi_hmi_OnSlider200SliderChange(tWidget *pWidget, long lValue);

extern tCanvasWidget Label202;
extern tPushButtonWidget TextPushButton118;
extern void _hmi_OnTextPushButton118Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton118Click(tWidget *pWidget);
extern void hmi_OnTextPushButton118Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton119;
extern void _hmi_OnTextPushButton119Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton119Click(tWidget *pWidget);
extern void hmi_OnTextPushButton119Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton120;
extern void _hmi_OnTextPushButton120Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton120Click(tWidget *pWidget);
extern void hmi_OnTextPushButton120Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton121;
extern void _hmi_OnTextPushButton121Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton121Click(tWidget *pWidget);
extern void hmi_OnTextPushButton121Release(tWidget *pWidget);

extern tTimerWidget Timer115;
extern void hmi_hmi_OnTimer115Execute(tWidget *pWidget);
extern tSliderWidget Slider137;
extern void hmi_hmi_OnSlider137SliderChange(tWidget *pWidget, long lValue);

extern tCanvasWidget Label140;
extern tCanvasWidget Label141;
extern tCanvasWidget Label142;
extern tCanvasWidget Label143;
extern tTimerWidget Timer146;
extern void hmi_hmi_OnTimer146Execute(tWidget *pWidget);
extern tPushButtonWidget TextPushButton149;
extern void _hmi_OnTextPushButton149Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton149Click(tWidget *pWidget);
extern void hmi_OnTextPushButton149Release(tWidget *pWidget);

extern tCanvasWidget Label150;
extern tCanvasWidget Label153;
extern tPushButtonWidget TextPushButton154;
extern void _hmi_OnTextPushButton154Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton154Click(tWidget *pWidget);
extern void hmi_OnTextPushButton154Release(tWidget *pWidget);

extern tPushButtonWidget TextPushButton155;
extern void _hmi_OnTextPushButton155Paint(tWidget *, unsigned long);
extern void hmi_hmi_OnTextPushButton155Click(tWidget *pWidget);
extern void hmi_OnTextPushButton155Release(tWidget *pWidget);

extern tCanvasWidget Label157;
extern tCanvasWidget Label158;
extern tCanvasWidget Label159;
extern tCanvasWidget Label160;
extern tCanvasWidget Label156;
extern tCanvasWidget Label161;
extern tCanvasWidget Label162;
extern tCanvasWidget Label163;
extern tCanvasWidget Label164;
extern tCanvasWidget Label165;
extern tCanvasWidget Label166;
extern tCanvasWidget Label167;
extern tCanvasWidget Label168;
extern tCanvasWidget Label169;
extern tCanvasWidget Label170;
extern tCanvasWidget Label171;
extern tCanvasWidget Label172;
extern tCanvasWidget Label173;
extern tCanvasWidget Label174;
extern tCanvasWidget Label175;
extern tCanvasWidget Label176;
extern tCanvasWidget Label177;
extern tCanvasWidget Label178;
extern tCanvasWidget Label179;
extern tCanvasWidget Label180;
extern tCanvasWidget Label181;
extern tTimerWidget Timer182;
extern void hmi_hmi_OnTimer182Execute(tWidget *pWidget);
extern tTimerWidget Timer183;
extern void hmi_hmi_OnTimer183Execute(tWidget *pWidget);
extern tCanvasWidget Label184;
extern tCanvasWidget Label185;
extern tCanvasWidget Label186;
extern tCanvasWidget Label187;
extern tCanvasWidget Label188;
extern tCanvasWidget Label189;
extern tCanvasWidget Label190;
extern tCanvasWidget Label191;
extern tCanvasWidget Label192;
extern tCanvasWidget Label195;
extern tCanvasWidget Label194;
extern void hmi_OnStatut2Paint(tWidget *pWidget, tContext *pContext);
extern void hmi_OnConnexion12Paint(tWidget *pWidget, tContext *pContext);
extern void hmi_OnClavier23Paint(tWidget *pWidget, tContext *pContext);
extern void hmi_OnTrajectoire27Paint(tWidget *pWidget, tContext *pContext);
extern void hmi_OnMenu61Paint(tWidget *pWidget, tContext *pContext);
extern void hmi_OnStatistic116Paint(tWidget *pWidget, tContext *pContext);
extern void hmi_OnStatisticMoteurs17Paint(tWidget *pWidget, tContext *pContext);

extern tCanvasWidget CanvasStatut;
extern tCanvasWidget CanvasConnexion;
extern tCanvasWidget CanvasClavier;
extern tCanvasWidget CanvasTrajectoire;
extern tCanvasWidget CanvasMenu;
extern tCanvasWidget CanvasStatistic;
extern tCanvasWidget CanvasStatisticMoteurs;

extern void hmi_FreeFrameWidgets1();
extern void hmi_FreeFrameWidgets2();
extern void hmi_FreeFrameWidgets3();
extern void hmi_FreeFrameWidgets4();
extern void hmi_FreeFrameWidgets5();
extern void hmi_FreeFrameWidgets6();
extern void hmi_FreeFrameWidgets7();


extern void hmi_Statut();
extern void hmi_Connexion();
extern void hmi_Clavier();
extern void hmi_Trajectoire();
extern void hmi_Menu();
extern void hmi_Statistic();
extern void hmi_StatisticMoteurs();

#endif
