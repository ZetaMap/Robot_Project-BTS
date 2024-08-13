extern tHandle h;
extern tHandle h2;


extern WORD lectureFNCT03[];
extern bool LectureFNCT03R(tHandle,int,int);
extern WORD lectureFNCT04[];
extern bool LectureFNCT04R(tHandle,int,int);
extern char lectureFNCT05;
extern bool EcritureFNCT05W(tHandle,int);
extern WORD ecritureFNCT06;
extern bool EcritureFNCT06W(tHandle,int);

extern int serveurNormal;
extern int serveurCustom;
extern int checkConnexion(tHandle*,int);

extern int customDataToInt(WORD);
extern float customDataToFloat(WORD);

tLabel *LabelVoltage[8];
tLabel *LabelTemperature[8];
tLabel *LabelCodeErreur[8];

static char tabCharVolt[8][32];
static char tabCharTemp[8][32];
static char tabCharErreur[8][32];

void StatisticMoteurs17OnCreate()
{
	LabelVoltage[0] = &Label160;
	LabelVoltage[1] = &Label161;
	LabelVoltage[2] = &Label165;
	LabelVoltage[3] = &Label168;
	LabelVoltage[4] = &Label171;
	LabelVoltage[5] = &Label174;
	LabelVoltage[6] = &Label177;
	LabelVoltage[7] = &Label180;
	
	LabelTemperature[0] = &Label162;
	LabelTemperature[1] = &Label163;
	LabelTemperature[2] = &Label166;
	LabelTemperature[3] = &Label169;
	LabelTemperature[4] = &Label172;
	LabelTemperature[5] = &Label175;
	LabelTemperature[6] = &Label178;
	LabelTemperature[7] = &Label181;
	
	LabelCodeErreur[0] = &Label184;
	LabelCodeErreur[1] = &Label185;
	LabelCodeErreur[2] = &Label186;
	LabelCodeErreur[3] = &Label187;
	LabelCodeErreur[4] = &Label188;
	LabelCodeErreur[5] = &Label189;
	LabelCodeErreur[6] = &Label190;
	LabelCodeErreur[7] = &Label191;
	
}



void Timer183OnExecute(tWidget *pWidget)
{
	checkConnexion(&h,serveurNormal);
	checkConnexion(&h2,serveurCustom);
}

void Timer182OnExecute(tWidget *pWidget)
{
	bool works = false;
	works = LectureFNCT04R(h,410,24);
	if(works){
		for(int i = 0;i<8;i++){
			char temp[32];
			FloatToStr(temp,customDataToFloat(lectureFNCT04[i+8]),3);
			usnprintf(tabCharVolt[i], sizeof(tabCharVolt[i]), "%s V", temp);
			LabelTextSet(LabelVoltage[i],tabCharVolt[i]);
			
			usnprintf(tabCharTemp[i], sizeof(tabCharTemp[i]), "%d C", ((int)lectureFNCT04[i]));
			LabelTextSet(LabelTemperature[i],tabCharTemp[i]);
			
			usnprintf(tabCharErreur[i], sizeof(tabCharErreur[i]), "%d", ((int)lectureFNCT04[i+16]));
			LabelTextSet(LabelCodeErreur[i],tabCharErreur[i]);
		}
	}
}


