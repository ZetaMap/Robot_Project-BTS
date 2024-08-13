
extern tHandle h;
extern tHandle h2;
extern char lectureFNCT01[];
extern bool LectureFNCT01R(tHandle,int,int);
extern char lectureFNCT02[];
extern bool LectureFNCT02R(tHandle,int,int);
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

extern bool mvmt_arret(tHandle*,tLabel*);

static char tabCharStat[10][32];

void Timer115OnExecute(tWidget *pWidget){
    //LectureFNCT04R(h2,1000,1);//lecture des adresses de test
	//static char test[32];
	
	//sprintf(test, "%d" , (int)lectureFNCT04[0]);
	
	//LabelTextSet(&Label114,test);
	
	bool works = false;//si il y a une erreur la variable va rester a false
	
	works = LectureFNCT04R(h,400,10);
	
	if(works == true){
		if(lectureFNCT04[0] == 1){LabelTextSet(&Label140,"moteur OK");
		} else if(lectureFNCT04[0] == 0){LabelTextSet(&Label140,"moteurs pas OK");
		} else {LabelTextSet(&Label140,"valeur non reconnu");}
		
		if(lectureFNCT04[1] == 1){LabelTextSet(&Label141,"calibration necessaire");
		} else if(lectureFNCT04[1] == 0){LabelTextSet(&Label141,"calibration non necessaire");
		} else {LabelTextSet(&Label141,"valeur non reconnu");}
		
		
		
		if(lectureFNCT04[2] == 1){LabelTextSet(&Label142,"calibration en cour");
		} else if(lectureFNCT04[2] == 0){LabelTextSet(&Label142,"pas de calibration en cour");
		} else {LabelTextSet(&Label142,"valeur non reconnu");}
		
		
		SliderValueSet(&Slider137, lectureFNCT04[3]);
		usnprintf(tabCharStat[3], sizeof(tabCharStat[3]), "temperature cpu : %d", lectureFNCT04[3]);
		SliderTextSet(&Slider137,tabCharStat[3]);
		
		
		usnprintf(tabCharStat[9], sizeof(tabCharStat[9]), "HWversion : %X", lectureFNCT04[9]);
		LabelTextSet(&Label143,tabCharStat[9]);
	}
	works = false;
	works = LectureFNCT04R(h,301,1);
	
	if(works == true){
		if(lectureFNCT04[0] == 1){LabelTextSet(&Label153,"colision detecte");
		} else if(lectureFNCT04[0] == 0){LabelTextSet(&Label153,"pas de colision");
		} 
	}
}

void Timer146OnExecute(tWidget *pWidget){
	checkConnexion(&h,serveurNormal);
	checkConnexion(&h2,serveurCustom);
}

void TextPushButton149OnClick(tWidget *pWidget){ //arret
	mvmt_arret(&h,&Label150);
}
