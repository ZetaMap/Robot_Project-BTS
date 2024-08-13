tPushButtonWidget *pbTrajectoire[10];
int selectedBoutton = -1;
int selectedTrajectory = 1;

extern tHandle h;
extern tHandle h2;
bool trajectoirEnCour = false;
//recuperation des fonctions de modbus.h
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

extern bool traj_arret(tHandle*,tLabel*);

typedef struct {
	int ID;
	char name[21];
	int index;
	
} trajectory ;

extern int traj_indexation(trajectory t[],int,tHandle);
extern bool traj_indexation_show_error(int,tLabel*);
extern bool traj_getNbTraj(tHandle,int*);
extern int traj_lancerT(int,tHandle*);

int nombreDeTrajectoirs = 0;
static char trajectoirs[32][32];
int offset = 0;

trajectory traj[32];


void Trajectoire27OnCreate(){
	pbTrajectoire[0] = &TextPushButton111;// flech haut
	pbTrajectoire[1] = &TextPushButton117;
	pbTrajectoire[2] = &TextPushButton122;
	pbTrajectoire[3] = &TextPushButton123;
	pbTrajectoire[4] = &TextPushButton125;
	pbTrajectoire[5] = &TextPushButton130;
	pbTrajectoire[6] = &TextPushButton131;
	pbTrajectoire[7] = &TextPushButton132;
	pbTrajectoire[8] = &TextPushButton133;
	pbTrajectoire[9] = &TextPushButton134;// flech bas
	for(int i = 0 ; i < 32 ; i++){
		sprintf(trajectoirs[i],"vide %d",i);
	}
	
	for(int i = 1 ; i < 9 ; i++){
		TextButtonTextSet(pbTrajectoire[i],trajectoirs[i+(offset-1)]);
	}
	
}
static char str1[32];
void TextPushButtonTrajectorieSelectionOnRelease(tWidget *pWidget){
	for(int i = 0; i < 10 ; i++){
		if(pWidget != (tWidget*)pbTrajectoire[i]){
			continue;
		} else {
			selectedBoutton = i;
		}
	}
	for(int i = 0; i < 10 ;i++){
		PushButtonFillColorSet(pbTrajectoire[i],0x646464);
		WidgetPaint((tWidget*)pbTrajectoire[i]);//redessine les boutton pour changer la couleur
	}
	if(selectedBoutton >= 0){
		PushButtonFillColorSet(pbTrajectoire[selectedBoutton],0x00ff40);
		//TextButtonTextSet(pbTrajectoire[selectedBoutton],str1);
	}
	
	
	sprintf(str1,"%d",selectedBoutton);
}



void Timer135OnExecute(tWidget *pWidget){
	static char strDebug3000[32];
	usnprintf(strDebug3000, sizeof(strDebug3000), "h : %X", h);
	LabelTextSet(&Label210,strDebug3000);
	static char strDebug3001[32];
	usnprintf(strDebug3001, sizeof(strDebug3001), "h2 : %X", h2);
	LabelTextSet(&Label211,strDebug3001);
	
	bool arrowPressed = false; 
	
	if(selectedBoutton == 9 || selectedBoutton == 0){
		arrowPressed = true;
	}
	
	if(selectedBoutton == 9 && offset < 23){
		offset = offset + 2;
	} else if ((selectedBoutton == 9 && offset == 23)){
		offset++;
	} else if (selectedBoutton == 0 && offset > 1){
		offset = offset - 2;
	} else if ((selectedBoutton == 0 && offset == 1)){
		offset--;
	} else {
	}
	if(arrowPressed){
		selectedBoutton = -1;
		for(int i = 1 ; i < 9 ; i++){
			TextButtonTextSet(pbTrajectoire[i],trajectoirs[i+(offset-1)]);
		}
		arrowPressed = false;
		for(int i = 0; i < 10 ;i++){
			PushButtonFillColorSet(pbTrajectoire[i],0x646464);
			WidgetPaint((tWidget*)pbTrajectoire[i]);
		}
		if((selectedTrajectory - offset) > 0 && selectedTrajectory - offset < 9){
			PushButtonFillColorSet(pbTrajectoire[(selectedTrajectory - offset)],0x00ff40);
		}
	}
	
	static char txt1[32];
	if(selectedBoutton >= 0 ){
		selectedTrajectory = (selectedBoutton+offset);
	}
	
	sprintf(txt1,"%d",(selectedTrajectory));
	LabelTextSet(&Label208,txt1);
}

void Timer139OnExecute(tWidget *pWidget){ // verification periodique de la connexion au niryo

	checkConnexion(&h,serveurNormal);
	checkConnexion(&h2,serveurCustom);
}

int LancerTrajectoire(int _trajectoire){
	if(selectedTrajectory > 0 && selectedTrajectory <= 32){
		traj_lancerT(_trajectoire-1,&h2);
		trajectoirEnCour = true;
	}
	return 0;
}

void TextPushButton144OnRelease(tWidget *pWidget){ // boutton lancer trajectoire

	LancerTrajectoire(selectedBoutton);
}


void TextPushButton42OnClick(tWidget *pWidget){ //arret

	mvmt_arret(&h,&Label151);
	traj_arret(&h2,&Label151);
}

void TextPushButton144OnClick(tWidget *pWidget){ //lance une trajectoire 


}

void Timer206OnExecute(tWidget *pWidget){
	if(trajectoirEnCour){return;}
	traj_indexation_show_error(traj_indexation(traj,32,h2),&Label151);
	
	traj_getNbTraj(h2,&nombreDeTrajectoirs);
	
	static char txt2[32];
	sprintf(txt2,"%d",(nombreDeTrajectoirs));
	LabelTextSet(&Label209,txt2);
	
	if(nombreDeTrajectoirs < 0){nombreDeTrajectoirs = 0;}
	if(nombreDeTrajectoirs > 32){nombreDeTrajectoirs = 32;}
	
	int x = 0;
	while(x < nombreDeTrajectoirs){
		
		sprintf(trajectoirs[x],"%s - %d",traj[x].name,traj[x].ID);
		//sprintf(trajectoirs[i],"test ligne %d",i+10);
		x++;
	}
	
	for(int i = 1 ; i < 9 ; i++){
		TextButtonTextSet(pbTrajectoire[i],trajectoirs[i+(offset-1)]);
	}
	
}


void TextPushButton57OnClick(tWidget *pWidget)
{

}
