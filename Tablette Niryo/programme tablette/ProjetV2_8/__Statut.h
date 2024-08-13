/*

programme tablette projet V2.7

avec fichier conversion.h , modbus.h , connections.h et niryo.h

le fichier modbus.h gère la communication au robot en ModBus

et le fichier conversion possède toutes le fonction de conversion pour
les donnes venant du robot, le passage de degree a radiant et vice versa

le fichier modbus adapte les fonction pre existante et les simplifie pour
eviter d avoir a tous reecrire a chaque fois

le fichier connexions contient de fonctions pour permettre le fonctionnement 
avec 2 serveur modbus

le fichier niryo.h contient des fonction utilisant les autres librairies 
pour creer des fonction avec une verification d'erreur et simplifier

date de la derniere modification => 16/04/2024


////////////////////////////////////////////////////// notes


limits robot 
join 1 [-2860 , 2900]
join 2 [-1820 , 600]
join 3 [-1290 , 1540]
join 4 [-2080 , 2070]
join 5 [-1910 , 1910]
join 6 [-2510 , 2520]

301 reg colision

410-434 voltage et temperature

418-425voltage

410-417 temperature

426-434 erreurs

//outils

11 a 14 grripper 1 a 4

1 calib tip  

30 elctromagnet 
31 vac pump 

////////////////////////////////////////////////////// fin notes
*/

//inclusions
#include "conversion.h"
#include "modbus.h"
#include "connections.h"
#include "niryo.h"

extern tHandle h;
extern tHandle h2;
extern bool trajectoirEnCour;

//variable du niryo ned 2
//table des axes en radiant
float axesRobot[6]={0.00,0.00,0.00,0.00,0.00,0.00};
//valeurs des axes cible en radiant
float axesRobotCible[6]={0.00,0.50,-1.25,0.00,0.00,0.00};
//serveurs
int serveurNormal = 1;
int serveurCustom = 2;

//outil equiper
WORD outilEquiper = 0;


tSliderWidget *SliderAxes[6];
tLabel *LabelAxes[6];
tPushButtonWidget *pushButtonAxes[12];


//si vraie toutes les axes sont affiché en degrées
extern bool degree;

//error handling/gestion d'erreurs les fonction de hmi works renvoie vraie si l'action est reussi
bool errorCatching[6][10] = {false};
int disconnectedCount = 0;

/////////////////////////////////////////////////////////////////////////////////
//   Variables de textes car la fonction LabelTextSet n'a pas de buffer (et necesite un string par label)
/////////////////////////////////////////////////////////////////////////////////

static char tabCharCible[6][32];//variables des label cible pour le robot
static char tabCharAxes[6][32];//variables des slider des axes du robot
static char tabCharAutre[10][32];//pour les autres labels


/////////////////////////////////////////////////////////////////////////////////
//                 			fonction utile
/////////////////////////////////////////////////////////////////////////////////

void UpdateAllTargetValues(){
	for(int i = 0; i<6 ; i++ ){
		if(degree == true){
			sprintf(tabCharCible[i], "%d", (int)(radiantToDegree(axesRobotCible[i])));
		} else {
			FloatToStr(tabCharCible[i],axesRobotCible[i],3);
		}
		LabelTextSet(LabelAxes[i],tabCharCible[i]);
	}
}


/////////////////////////////////////////////////////////////////////////////////
//                 code principal (fonction bouttons, minuteur, etc)
/////////////////////////////////////////////////////////////////////////////////


bool led = false;

void Statut2OnCreate(){
	SliderAxes[0] = &Slider9;
	SliderAxes[1] = &Slider18;
	SliderAxes[2] = &Slider19;
	SliderAxes[3] = &Slider24;
	SliderAxes[4] = &Slider25;
	SliderAxes[5] = &Slider26;
	
	LabelAxes[0] = &Label34;
	LabelAxes[1] = &Label35;
	LabelAxes[2] = &Label36;
	LabelAxes[3] = &Label37;
	LabelAxes[4] = &Label38;
	LabelAxes[5] = &Label39;
	
	pushButtonAxes[0] = &TextPushButton43;
	pushButtonAxes[1] = &TextPushButton44;
	pushButtonAxes[2] = &TextPushButton45;
	pushButtonAxes[3] = &TextPushButton46;
	pushButtonAxes[4] = &TextPushButton47;
	pushButtonAxes[5] = &TextPushButton48;
	pushButtonAxes[6] = &TextPushButton49;
	pushButtonAxes[7] = &TextPushButton50;
	pushButtonAxes[8] = &TextPushButton51;
	pushButtonAxes[9] = &TextPushButton52;
	pushButtonAxes[10] = &TextPushButton53;
	pushButtonAxes[11] = &TextPushButton54;
	
	for(int i = 0; i < 6; i++){
		sprintf(tabCharCible[i], "%d" , (int)(axesRobotCible[i]*1000.00));
		LabelTextSet(LabelAxes[i],tabCharCible[i]);
	}
	
	UpdateAllTargetValues();
}

void TextPushButton13OnClick(tWidget *pWidget){ //boutton desactiver outil / lacher objet
	mvmt_toggleOutil(&h,&Label28,false,outilEquiper);
}

void TextPushButton6OnClick(tWidget *pWidget){  //boutton activer / attraper objet
	mvmt_toggleOutil(&h,&Label28,true,outilEquiper);
}





void Timer8OnExecute(tWidget *pWidget){	//minuteur pour le code a executer une fois par seconde
	static char strDebug3000[32];
	usnprintf(strDebug3000, sizeof(strDebug3000), "h : %X  %X", h, &h );
	LabelTextSet(&Label212,strDebug3000);
	static char strDebug3001[32];
	usnprintf(strDebug3001, sizeof(strDebug3001), "h2 : %X %X", h2, &h2);
	LabelTextSet(&Label213,strDebug3001);
	
	UpdateAllTargetValues();
	
	LectureFNCT04R(h,402,2);
	
	bool calibration = (lectureFNCT04[0] == 0);
	
	
	
    SliderValueSet(&Slider11, lectureFNCT04[1]);
    usnprintf(tabCharAutre[0], sizeof(tabCharAutre[0]), "%d", lectureFNCT04[1]);
    SliderTextSet(&Slider11,tabCharAutre[1]);
	
	
    
	errorCatching[0][0] = LectureFNCT04R(h,0,6); // lecture des axes ----------------------
	
	if(errorCatching[0][0] == false){
		LabelTextSet(&Label41, "connexion perdue");
		for(int i = 0; i < 6 ; i++){
			SliderTextSet(SliderAxes[i], "deconnecter");
		}
	} else {
		LabelTextSet(&Label41, "connexion OK");
		for(int i = 0; i<6;i++){
			axesRobot[i] = axesToRadiant(lectureFNCT04[i]);
		}
		
		//char axeName[6][11]={"J1-Base","J2-Shoulder","J3-Elbow","J4-Forearm","J5-Wrist","J6-Hand"};
		
		for(int i = 0; i < 6 ; i++){
			SliderValueSet(SliderAxes[i], (int)(axesRobot[i]*1000));
			if(degree == true){
				//snprintf(tabCharAxes[i], sizeof(tabCharAxes[i]), "%s %d",axeName[i], (int)(radiantToDegree(axesRobot[i]))); 
				snprintf(tabCharAxes[i], sizeof(tabCharAxes[i]), "J%d %d",i+1, (int)(radiantToDegree(axesRobot[i]))); 
				//usnprintf(tabCharAxes[i], sizeof(tabCharAxes[i]), "%d", (int)(radiantToDegree(axesRobot[i]))); 
			} else {
				char tstr[32];
				FloatToStr(tstr,axesRobot[i],3);
				//usnprintf(tabCharAxes[i], sizeof(tabCharAxes[i]), "J %d", (int)(axesRobot[i]*1000));
				//usnprintf(tabCharAxes[i], sizeof(tabCharAxes[i]), "%s %s",axeName[i], tstr );
				usnprintf(tabCharAxes[i], sizeof(tabCharAxes[i]), "J%d %s",i+1, tstr );
			}
			SliderTextSet(SliderAxes[i], tabCharAxes[i]);
		}
		
	}
	
	
	//bool error200 = false;
    LectureFNCT03R(h,150,3);//lecture des adresse pour les resultats de commande
	LectureFNCT04R(h,301,1);
	if(true){
		/*
		enum codeDErreur{
			
		};
		*/
		
		if(lectureFNCT03[1] == 0){
			sprintf(tabCharAutre[1],"attente de resultat");
		} else if(lectureFNCT03[1] == 1){
			//LabelTextSet(&Label5, "success");
			sprintf(tabCharAutre[1],"success");
		} else if(lectureFNCT03[1] == 2){
			sprintf(tabCharAutre[1],"commande rejeter");//parametre non valid etc
		} else if(lectureFNCT03[1] == 3){
			sprintf(tabCharAutre[1],"commande abandoner");
		} else if(lectureFNCT03[1] == 4){
			sprintf(tabCharAutre[1],"commande annuler");
		} else if(lectureFNCT03[1] == 5){
			sprintf(tabCharAutre[1],"erreure inattendue");
		} else if(lectureFNCT03[1] == 6){
			sprintf(tabCharAutre[1],"delai depasser");
		} else if(lectureFNCT03[1] == 7){
			sprintf(tabCharAutre[1],"erreure interne");
		} else if(lectureFNCT03[1] == 8){
			sprintf(tabCharAutre[1],"commande deja en cour");
		} else if(lectureFNCT03[1] == 9){
			sprintf(tabCharAutre[1],"colision");
			
		} else {
			//LabelTextSet(&Label5, "valeur inattendue");
			sprintf(tabCharAutre[1],"valeur inattendue");
			//usnprintf(tabCharAutre[1], sizeof(tabCharAutre[1]), "%X", lectureFNCT04[0]);
			//LabelTextSet(&Label5,tabCharAutre[1]);
		}
		
		
		usprintf(tabCharAutre[2], "%s : %X",tabCharAutre[1], lectureFNCT03[2]);
		LabelTextSet(&Label5,tabCharAutre[2]);
		
		if(lectureFNCT04[0] == 0){//affichage label 66
			if(lectureFNCT03[0] == 1){
				if(calibration){
					LabelTextSet(&Label66, "calibration en cour");
				} else {
					LabelTextSet(&Label66, "execute cmd");
				}
			} else {
				LabelTextSet(&Label66, "pas d execution");
			}
		} else {
			LabelTextSet(&Label66, "colision detecte");
		}
		
		
		if(degree == true){
			LabelTextSet(&Label58,"degree");
		} else {
			LabelTextSet(&Label58,"radiant");
		}

	}

    errorCatching[0][2] = LectureFNCT04R(h,200,1);//lecture de l'outil ------------------
	
	if(errorCatching[0][2] == true){
	
		static char stroutil[2][32];
		memset(stroutil[0],0,sizeof(stroutil));
		sprintf(stroutil[0],"outil: ");
		
		outilEquiper = lectureFNCT04[0];
		
		if(lectureFNCT04[0] == 31){
			strcat(stroutil[0], "pompe a vide" );
		} else if(lectureFNCT04[0] == 11){
			strcat(stroutil[0], "pince 1" );
		} else if(lectureFNCT04[0] == 12){
			strcat(stroutil[0], "pince 2" );
		} else if(lectureFNCT04[0] == 13){
			strcat(stroutil[0], "pince 3" );
		} else {
			strcat(stroutil[0], "inconnu" );
		}
		LabelTextSet(&Label21, stroutil[0]);
		
		// if(lectureFNCT04[0] == 31){
			// sprintf(stroutil[1],"pompe");
		// } else if(lectureFNCT04[0] == 11 || lectureFNCT04[0] == 12 || lectureFNCT04[0] == 13){
			// sprintf(stroutil[1],"pince");
		// } else {
			// sprintf(stroutil[1],"inconnue");
		// }
		// LabelTextSet(&Label31, stroutil[1]);
	}
	LectureFNCT03R(h,100,1);
	usnprintf(tabCharAutre[9], sizeof(tabCharAutre[9]), "%X", lectureFNCT03[0]);
	LabelTextSet(&Label201,tabCharAutre[9]);
}





void Timer10OnExecute(tWidget *pWidget){ //test indicateur led


    if(led == true){
        hmi_SetLED(HMI_LED_ON);
        led = false;
    } else {
        hmi_SetLED(HMI_LED_OFF);
        led = true;
    }
}


void Slider11OnSliderChange(tWidget *pWidget, long lValue){ //slider de test(demande la temperature du robot niryo)

    static char strValue[10];
    usnprintf(strValue , sizeof(strValue) , "%d" , lValue);
    SliderTextSet(&Slider11 , strValue);
    WidgetPaint((tWidget*)&Slider11);
}








void BitButton22OnClick(tWidget *pWidget){ //boutton demarrer mouvement

	mvmt_niryo_show_error(mvmt_niryo(axesRobotCible,&h,serveurNormal,false),&Label28);
}




void Timer29OnExecute(tWidget *pWidget){ //detection de deconnexion

	//int erreurs[2] = {0,0};
	//static char temp[2][32];
	checkConnexion(&h,serveurNormal);
	checkConnexion(&h2,serveurCustom);
	//usnprintf(temp[0], sizeof(temp[0]), "erreur : %d", erreurs[0]);
	//LabelTextSet(&Label5,temp[0]);
	//usnprintf(temp[1], sizeof(temp[1]), "erreur : %d", erreurs[1]);
	//LabelTextSet(&Label20,temp[1]);
}


void TextPushButton32OnClick(tWidget *pWidget){ //remise a la position par defaut

	float axesRobotTemp[6]={0.00,0.50,-1.25,0.00,0.00,0.00};
	mvmt_niryo_show_error(mvmt_niryo(axesRobotTemp,&h,serveurNormal,false),&Label28);
}

void TextPushButton193OnClick(tWidget *pWidget)
{
	float axesRobotTemp[6]={0.00,0.00,0.00,0.00,0.00,0.00}; //remise a la position zero
	mvmt_niryo_show_error(mvmt_niryo(axesRobotTemp,&h,serveurNormal,false),&Label28);
}

void TextPushButton33OnClick(tWidget *pWidget)
{
	for(int i = 0; i<6 ; i++ ){
		axesRobotCible[i] = axesRobot[i];
	}
	UpdateAllTargetValues();
}



void SliderAxeOnChange(tWidget *pWidget, long lValue){ // mise a jour de la valeur cible quand un axe est changer

	for(int i = 0; i < 6 ; i++){
		if(pWidget != (tWidget*)SliderAxes[i]){
			continue;
		} else {
			if(degree == true){
				usnprintf(tabCharCible[i] , sizeof(tabCharCible[i]) , "%d" , (int)(radiantToDegree(((float)lValue)/1000.00)));//degree
			} else {
				FloatToStr(tabCharCible[i],(((float)lValue)/1000),3);//radiant
				//usnprintf(tabCharCible[i] , sizeof(tabCharCible[i]) , "%d" , (int)lValue);
			}
			SliderTextSet(SliderAxes[i] , tabCharCible[i]);
			WidgetPaint((tWidget*)SliderAxes[i]);
			axesRobotCible[i] = (((float)lValue)/1000);
			LabelTextSet(LabelAxes[i],tabCharCible[i]);
		}
	}
}






void TextButtonOnClick(tWidget *pWidget){
	for(int i = 0; i < 12 ; i++){
		if(pWidget != (tWidget*)pushButtonAxes[i]){
			continue;
		} else {
			if(i < 6){
				long min,max;
				SliderRangeGet(SliderAxes[i],min,max);
				if(min == 0){min = 0;};//evite le warning du compilateur
				float fmax = (((float)max)/1000);
				if(axesRobotCible[i] < fmax){
					axesRobotCible[i] = axesRobotCible[i] + 0.010;
				}
				if(axesRobotCible[i] > fmax){
					axesRobotCible[i] = fmax;
				}
				if(degree == true){
					sprintf(tabCharCible[i], "%d" , (int)(radiantToDegree(axesRobotCible[i])));//degree
				} else {
					FloatToStr(tabCharCible[i],axesRobotCible[i],3);//radiant
					//sprintf(tabCharCible[i], "%d" , (int)(axesRobotCible[i]*1000.00));
				}
				LabelTextSet(LabelAxes[i],tabCharCible[i]);
				
			} else if (i >= 6 && i < 12){
				long min,max;
				SliderRangeGet(SliderAxes[i-6],min,max);
				if(max == 0){max = 0;};//evite le warning du compilateur
				float fmin = (((float)min)/1000);
				
				if(axesRobotCible[i-6] > fmin){
					axesRobotCible[i-6] = axesRobotCible[i-6] - 0.010;
				} 
				if(axesRobotCible[i-6] < fmin){
					axesRobotCible[i-6] = fmin;
				}
				if(degree == true){
					sprintf(tabCharCible[i-6], "%d" , (int)(radiantToDegree(axesRobotCible[i-6])));
				} else {
					FloatToStr(tabCharCible[i],axesRobotCible[i-6],3);
					//sprintf(tabCharCible[i-6], "%d" , (int)(axesRobotCible[i-6]*1000.00));
				}
				LabelTextSet(LabelAxes[i-6],tabCharCible[i-6]);
			}
		}
	}
}


void BitButton62OnClick(tWidget *pWidget){

}



void TextPushButton147OnClick(tWidget *pWidget){ //arret
	mvmt_arret(&h,&Label41);
}




/*


void TextPushButton197OnClick(tWidget *pWidget)
{
	TextButtonVisibleSet(&TextPushButton196,true);
	TextButtonEnabledSet(&TextPushButton196,true);
	WidgetPaint((tWidget*)&TextPushButton196);
	//WidgetPaint(WIDGET_ROOT);
}

void TextPushButton196OnClick(tWidget *pWidget)
{
	TextButtonVisibleSet(&TextPushButton196,false);
	TextButtonEnabledSet(&TextPushButton196,false);
	WidgetPaint(((tWidget*)&TextPushButton196)->pParent);
	//WidgetPaint(WIDGET_ROOT);
}
*/

