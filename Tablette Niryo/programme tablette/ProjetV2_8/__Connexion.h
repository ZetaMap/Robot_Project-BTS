tHandle h = -1;
tHandle h2 = -1;
tHandle hdebug = -1;

extern int serveurNormal;
extern int serveurCustom;
extern int connexionModBus(tHandle*,int);

/*
struct connection{
	tHandle srvrNormal;
	tHandle srvrCustom;
};
*/


int state = 0;
bool run = true;
int connexionStatus = 0;// 0 = pas dessaie 1 = essaie en cour 2 = connecter
int connexionStatusSecondaire = 0;//
void Timer15OnExecute(tWidget *pWidget)
{
	connexionModBus(&h,serveurNormal);
	hmi_DelayUS(500000);
	connexionModBus(&h2,serveurCustom);
	/*
	hdebug = hmi_TCPNew();
	if(hdebug != -1){
		hmi_TCPOpen(hdebug,TCP_IPADDR(192,168,1,20), 12345, 42000);
		hmi_DelayUS(500);
		char t[32];
		sprintf(t,"test");
		hmi_TCPWrite(hdebug,(unsigned char*)t,32);
	}
	*/
	
	
	
	
	
	
	TimerEnabledSet(&Timer29, 1);
	TimerEnabledSet(&Timer15, 0);
	hmi_GotoFrameByName("Statut");
	
}

void BitButton124OnClick(tWidget *pWidget)
{
	TimerEnabledSet(&Timer29, 1);
	TimerEnabledSet(&Timer15, 0);
	hmi_GotoFrameByName("Statut");
}

void Connexion12OnCreate()
{
	/*
	unsigned char backlight[3];
	
	hmi_UserParamsGet(0,1,backlight);
	int ibacklight = ((int)backlight[0]);
	if(ibacklight > 9 && ibacklight <256){
		hmi_BacklightSet(backlight[0]);
	}
	*/
}
