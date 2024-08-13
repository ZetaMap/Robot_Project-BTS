
#ifndef MODBUS_H
#define MODBUS_H

#define ArraySize 32

/////////////////////////////////////////////////////////////////////////////////
//                          variables de communication ModBus
/////////////////////////////////////////////////////////////////////////////////

// variable pour les fonctions mtm fourni par HMIWorks
bool verrouMvmt = false;
int adressMemoire = 0;
int IDModBusServer = 1;
int nbDeMots = 1;
DWORD timeout = 200;
//mtm_ReadDO
char lectureFNCT01[ArraySize];
//mtm_ReadADI
char lectureFNCT02[ArraySize];
//mtm_ReadAO
WORD lectureFNCT03[ArraySize];
//mtm_ReadAI
WORD lectureFNCT04[ArraySize];
//mtm_WriteAO
char ecritureFNCT05;
//mtm_WriteAO
WORD ecritureFNCT06;
//mtm_WriteAO nbDeMots > 1
char ecritureFNCT15[ArraySize];
//mtm_WriteAO nbDeMots > 1
WORD ecritureFNCT16[ArraySize];


/////////////////////////////////////////////////////////////////////////////////
//                          fonctions de communication ModBus
/////////////////////////////////////////////////////////////////////////////////

bool LectureFNCT01R(tHandle h,int _adressMemoire,int _nbDeMots){
	adressMemoire = _adressMemoire;//mise des variable dans les variables global
	nbDeMots = _nbDeMots;
	bool erreur = false;
	
	memset(&lectureFNCT01, 0, ArraySize);//remet a zero la liste
	
	erreur = mtm_ReadDO(h, IDModBusServer, adressMemoire, nbDeMots, lectureFNCT01, timeout);//utilisation de la commande de la tablette
	
	return erreur;// renvoie d'erreur
}

bool LectureFNCT02R(tHandle h,int _adressMemoire,int _nbDeMots){
	adressMemoire = _adressMemoire;
	nbDeMots = _nbDeMots;
	bool erreur = false;
	
	memset(&lectureFNCT02, 0, ArraySize);
	
	erreur = mtm_ReadDI(h, IDModBusServer, adressMemoire, nbDeMots, lectureFNCT02, timeout);
	
	return erreur;
}

bool LectureFNCT03R(tHandle h,int _adressMemoire,int _nbDeMots){
	adressMemoire = _adressMemoire;
	nbDeMots = _nbDeMots;
	bool erreur = false;
	
	for(int i = 0; i < ArraySize; i++){//remet a zero la liste
		lectureFNCT03[i] = 0;
	}
	
	erreur = mtm_ReadAO(h, IDModBusServer, adressMemoire, nbDeMots, lectureFNCT03, timeout);
	
	return erreur;
}


bool LectureFNCT04R(tHandle h,int _adressMemoire,int _nbDeMots){
	adressMemoire = _adressMemoire;
	nbDeMots = _nbDeMots;
	bool erreur = false;
	
	for(int i = 0; i < ArraySize; i++){
		lectureFNCT04[i] = 0;
	}
	
	erreur = mtm_ReadAI(h, IDModBusServer, adressMemoire, nbDeMots, lectureFNCT04, timeout);
	
	return erreur;
}

bool EcritureFNCT05W(tHandle h,int _adressMemoire){
	adressMemoire = _adressMemoire;
	nbDeMots = 1;
	bool erreur = false;
	
	erreur = mtm_WriteDO(h, IDModBusServer, adressMemoire, nbDeMots, &ecritureFNCT05, timeout);
	
	//memset(&ecritureFNCT05, 0, 1);
	
	return erreur;
}

bool EcritureFNCT06W(tHandle h,int _adressMemoire){
	adressMemoire = _adressMemoire;
	nbDeMots = 1;
	bool erreur = false;
	
	erreur = mtm_WriteAO(h, IDModBusServer, adressMemoire, nbDeMots, &ecritureFNCT06, timeout);
	
	
	ecritureFNCT06 = 0;
	
	
	return erreur;
}

/*
afin de regler un problem avec la facon dons le robot communique en modbus et cesse de répondre
lorsqu'un mouvement est lancer par la tablette cette fonction est une copie de EcritureFNCT06W
mais avec un timeout de 10 000 ms
*/

bool EcritureFNCT06Wmvmt(tHandle h,int _adressMemoire){
	adressMemoire = _adressMemoire;
	nbDeMots = 1;
	bool erreur = false;
	
	erreur = mtm_WriteAO(h, IDModBusServer, adressMemoire, nbDeMots, &ecritureFNCT06, (DWORD)1500);
	
	
	ecritureFNCT06 = 0;
	
	
	return erreur;
}

//les fonctions suivante ne sont pas accepter par le niryo ned 2 et donc inutiliser

bool EcritureFNCT15W(tHandle h,int _adressMemoire,int _nbDeMots){
	adressMemoire = _adressMemoire;
	nbDeMots = _nbDeMots;
	bool erreur = false;
	
	erreur = mtm_WriteDO(h, IDModBusServer, adressMemoire, nbDeMots, ecritureFNCT15, timeout);
	
	memset(&ecritureFNCT15, 0, 1);
	
	return erreur;
}

bool EcritureFNCT16W(tHandle h,int _adressMemoire,int _nbDeMots){
	adressMemoire = _adressMemoire;
	nbDeMots = _nbDeMots;
	bool erreur = false;
	
	erreur = mtm_WriteAO(h, IDModBusServer, adressMemoire, nbDeMots, ecritureFNCT16, timeout);
	
	for(int i = 0; i < ArraySize; i++){
		ecritureFNCT16[i] = 0;
	}
	
	return erreur;
}



/////////////////////////////////////////////////////////////////////////////////
//					demande de mouvement ModBus
/////////////////////////////////////////////////////////////////////////////////
int demandeDeMouvementNiryo(tHandle _h, int _adressMemoire,bool noExeT,bool noColT){//gere les verification pour empecher les demandes lorsque le robot est en 
//mouvement(is executing command flag holding reg 150)
	if(hmi_TCPState(_h) == 3){
		LectureFNCT03R(_h,150,1);
		LectureFNCT04R(_h,301,1);
		if(lectureFNCT03[0] == 0 || noExeT){//si pas d'execution ou noExeT == true
			if(lectureFNCT04[0] == 0 || noColT){//si pas de colision ou noColT == true
				ecritureFNCT06 = 0xFFFF;
				EcritureFNCT06Wmvmt(_h,_adressMemoire);
				hmi_DelayUS(500);
			} else {
				return 3;
			}
		} else {
			return 2;
		}
	} else {
		return 1;
	}
	return 0;
}

bool nettoyageColision(tHandle _h){
	bool error = false;
	ecritureFNCT06 = 0xFFFF;
	error = EcritureFNCT06W(_h,103);
	return error;
}


/////////////////////////////////////////////////////////////////////////////////
//					fin des fonctions de communication ModBus
/////////////////////////////////////////////////////////////////////////////////


#endif