//frame pour le clavier

tPushButtonWidget *pb[39];

#define PB_COUNT() (sizeof(pb)/sizeof(pb[0]))

extern tHandle h;
extern tHandle h2;

extern int serveurNormal;
extern int serveurCustom;
extern int checkConnexion(tHandle,int);


char charList[36] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};


void Clavier23OnCreate()
{
	pb[0] = &TextPushButton55;   // 0
	pb[1] = &TextPushButton67;   // 1
	pb[2] = &TextPushButton68;   // 2
	pb[3] = &TextPushButton69;   // 3
	pb[4] = &TextPushButton70;   // 4
	pb[5] = &TextPushButton71;   // 5
	pb[6] = &TextPushButton72;   // 6
	pb[7] = &TextPushButton73;   // 7
	pb[8] = &TextPushButton74;   // 8
	pb[9] = &TextPushButton75;   // 9
	pb[10] = &TextPushButton76;   // A
	pb[11] = &TextPushButton77;   // B
	pb[12] = &TextPushButton78;   // C
	pb[13] = &TextPushButton79;   // D
	pb[14] = &TextPushButton80;   // E
	pb[15] = &TextPushButton81;   // F
	pb[16] = &TextPushButton82;   // G
	pb[17] = &TextPushButton83;   // H
	pb[18] = &TextPushButton84;   // I
	pb[19] = &TextPushButton85;   // J
	pb[20] = &TextPushButton86;   // K
	pb[21] = &TextPushButton87;   // L
	pb[22] = &TextPushButton88;   // M
	pb[23] = &TextPushButton89;   // N
	pb[24] = &TextPushButton90;   // O
	pb[25] = &TextPushButton91;   // P
	pb[26] = &TextPushButton92;   // Q
	pb[27] = &TextPushButton93;   // R
	pb[28] = &TextPushButton102;   // S 102
	pb[29] = &TextPushButton94;   // T
	pb[30] = &TextPushButton95;   // U
	pb[31] = &TextPushButton96;   // V
	pb[32] = &TextPushButton97;   // W
	pb[33] = &TextPushButton98;   // X
	pb[34] = &TextPushButton99;   // Y
	pb[35] = &TextPushButton100;   // Z
	pb[36] = &TextPushButton100;   // effacer
	pb[37] = &TextPushButton100;   // annuler
	pb[38] = &TextPushButton100;   // entrer
	
	
}



//static char temp[100];
//static char starsign[15];
//static int flag;

static char outString[40];

void TextPushButtonClavierOnClick(tWidget *pWidget)
{
	static int positionCurseur = 0;
	char str[10];
	
	for(int i = 0 ; i < PB_COUNT() ; i++)
	{
		if(pWidget != (tWidget*)pb[i]) continue; //si widget different de pushboutton[i] continue
	
		if(i<36){
			usnprintf(str, sizeof(str), "%c", charList[i]);// char list vers char[]
			strcat(outString , str) ;//temp append str
			//LabelTextSet(&Label65, outString);//afficher
		} else if(i==36){ //effacer
			positionCurseur--;
			if(positionCurseur < 0) positionCurseur = 0;
			outString[positionCurseur] = '\0';
		} else if(i==37){ //annuler
			
		} else if(i==38){ //entree
			hmi_GotoFrameByName("Trajectoire");
		}
		
	
	}
	/*
	static int positionChar = -1;//position du curser dans la chaine de character

	char str[10];

	for(int i = 0 ; i < PB_COUNT() ; i++)
	{
		if(pWidget != (tWidget*)pb[i]) continue; //si widget different de pushboutton[i] continue
		flag = 1;
     
		if(i < 10)//partie nombre
		{
			if(strlen(temp) > 9) break;//si chaine temporaire trop long
			if(strlen(starsign) < 1)//?
			{
			usnprintf(str, sizeof(str), "%d", i);//print int vers str
			strcat(temp , str) ;//temp append str
			LabelTextSet(&Label65, temp);//afficher
			}
			else
			{
				usnprintf(str, sizeof(str), "%d", i);
				strcat(temp , str) ;
				strcat(starsign, str);
				LabelTextSet(&Label65, starsign);
			}
		  
			WidgetPaint((tWidget*)&Label65);
			positionChar++;
			if(positionChar > 9) positionChar = 9;
		}
		else if((i >= 10) && (i <= 35))//partie characteres
		{
			if(strlen(temp) > 9) break;
			if(strlen(starsign) < 1)
			{
				usnprintf(str, sizeof(str), "%c", i+55);
				strcat(temp, str);
				LabelTextSet(&Label65, temp);
			}
			else
			{
				usnprintf(str, sizeof(str), "%c", i+55);
				strcat(temp, str);
				strcat(starsign, str);
				LabelTextSet(&Label65, starsign);
			}

			WidgetPaint((tWidget*)&Label65);
			positionChar++;
			if(positionChar > 9) positionChar = 9;
		}
		else if( i == 36)// si touche efaccer
		{
			positionChar--;
			if(positionChar < 0) positionChar = 0;
			temp[positionChar] = 0;
			starsign[positionChar] = 0;
			
			if(strlen(starsign) < 1) LabelTextSet(&Label65, temp);
			else LabelTextSet(&Label65, starsign);
			
			WidgetPaint((tWidget*)&Label65);
		}
		else if( i == 37)//si touch remise a zero / annuler
		{
			temp[0] = 0;char 0 == '\0' == string termination 
			starsign[0] =0 ;
			positionChar = 0;
			LabelTextSet(&Label65, starsign);
			WidgetPaint((tWidget*)&Label65);
		}
		else if(i == 38)//si touche entree
		{
			char pasword[] = "2018ICPDAS";
			
			if(strcmp(pasword, temp) == 0)
			{
				LabelTextSet(&Label65, "Password Correct!");
				WidgetPaint((tWidget*)&Label65);
			}
			else
			{
				LabelTextSet(&Label65, "Password Error!");
				WidgetPaint((tWidget*)&Label65);
			}
			temp[0] = 0;
			starsign[0] = 0;
			positionChar = 0;
		}
	}
	*/
}


