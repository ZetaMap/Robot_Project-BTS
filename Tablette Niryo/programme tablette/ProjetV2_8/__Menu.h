
extern tHandle h;
extern tHandle h2;
extern WORD lectureFNCT04[];
extern bool LectureFNCT04R(tHandle,int,int);
extern WORD ecritureFNCT06;
extern bool EcritureFNCT06W(tHandle,int);
extern bool EcritureFNCT06Wmvmt(tHandle,int);

bool degree = true;


extern int serveurNormal;
extern int serveurCustom;
extern int checkConnexion(tHandle*,int);

extern bool nettoyageColision(tHandle);
extern bool mvmt_arret(tHandle*,tLabel*);
extern int mvmt_calibration(tHandle*,int,bool);
extern bool mvmt_calibration_show_error(int,tLabel*);
extern bool mvmt_detect_tool(tHandle*,tLabel*);


void Menu61OnCreate(){
	if(degree == true){
		TextButtonTextSet(&TextPushButton64,"unite : degree");
	} else {
		TextButtonTextSet(&TextPushButton64,"unite : radiant");
	}
	LabelTextSet(&Label112, "message");
	
	int i = ((int)hmi_BacklightGet());
	SliderValueSet(&Slider40,i);
}

void TextPushButton64OnRelease(tWidget *pWidget){
	degree = !degree;
	if(degree == true){
		TextButtonTextSet(&TextPushButton64,"unite : degree");
	} else {
		TextButtonTextSet(&TextPushButton64,"unite : radiant");
	}
}

void TextPushButton65OnRelease(tWidget *pWidget){ //calibration auto
	mvmt_calibration_show_error(mvmt_calibration(&h,serveurNormal,true),&Label112);
}

void TextPushButton30OnRelease(tWidget *pWidget){
	mvmt_detect_tool(&h,&Label112);
}

void Timer145OnExecute(tWidget *pWidget){
	checkConnexion(&h,serveurNormal);
	checkConnexion(&h2,serveurCustom);
}

void TextPushButton148OnClick(tWidget *pWidget)//arret
{
	mvmt_arret(&h,&Label112);
}

void TextPushButton152OnRelease(tWidget *pWidget){
	
	if(nettoyageColision(h))//
	{
		LabelTextSet(&Label112, "colision nettoyer");
	} else {
		LabelTextSet(&Label112, "nettoyage echoue");
	}
}

void Slider40OnSliderChange(tWidget *pWidget, long lValue){
	if(lValue < 256 && lValue > 0){
		unsigned char b = (unsigned char)lValue;
		hmi_BacklightSet(b);
		//hmi_UserParamsSet(0,1,b);
	}
	
}


void Slider200OnSliderChange(tWidget *pWidget, long lValue)
{
	static char str200[32];
	usnprintf(str200 , sizeof(str200) , "%d" , (int)lValue);
	ecritureFNCT06 = (WORD)lValue;
	EcritureFNCT06W(h,514);
	SliderTextSet(&Slider200, str200);
}
