/*
fonction pour simplifier les demande de mouvement au niryo et gérer les erreurs 

*/
#ifndef NIRYO_H
#define NIRYO_H




int mvmt_niryo(float _axesRobotcible[6],tHandle *_h,int serverID,bool HardReset){
	//envoie des axes
	for( int i = 0;i<6;i++){//
		ecritureFNCT06 = RadiantToAxes(_axesRobotcible[i]);
		if(!EcritureFNCT06W(*_h,i)){
			return 1;
		}
		hmi_DelayUS(500);
	}
	
	//execution cmd
	if (demandeDeMouvementNiryo(*_h,100,false,false) != 0){
		return 2;
	}
	
	//reinitialisation de la connxion 
	if(HardReset){
		if(!TCPHardReset(_h,serverID)){
			return 3;
		}
	}
	
	return 0;
}

bool mvmt_niryo_show_error(int _error,tLabel *L){
	if(_error == 0){
		LabelTextSet(L, "pas d erreur");
	} else if(_error == 1){
		LabelTextSet(L, "erreur d'envoie");
	} else if(_error == 2){
		LabelTextSet(L, "err lancement mvmt");
	} else if(_error == 3){
		LabelTextSet(L, "erreur reset");
	}
	return true;
}

bool mvmt_arret(tHandle *_h, tLabel *L){
	bool err = false;
	
	ecritureFNCT06 = 0xffff;
	err = EcritureFNCT06W(*_h,110);//mvmt
	
	lectureFNCT03[0] = 0;
	LectureFNCT03R(*_h,110,1);
	if(err && lectureFNCT03[0] > 0){
		LabelTextSet(L,"signal envoyer");
	} else {
		LabelTextSet(L,"signal perdue");
	}
	return true;
}

bool mvmt_toggleOutil(tHandle *_h, tLabel *L,bool OnOff,int outilEquiper){
	bool error = false;
	int offset = 0;
	if(!OnOff){//si off / false est selectionner
		offset = 1;//change l'adresse pour fermer pince / relacher objet 
	}
	if(outilEquiper == 31){
		ecritureFNCT06 = 0xffff;
		error = EcritureFNCT06Wmvmt(*_h,(512+offset));
	} else if( outilEquiper == 11 || outilEquiper == 12 || outilEquiper == 13 ){
		ecritureFNCT06 = 0xffff;
		error = EcritureFNCT06Wmvmt(*_h,(511-offset));
	}
	
	if(error){
		LabelTextSet(L,"cmd outil envoyer");
	} else {
		LabelTextSet(L,"echec cmd outil");
	}
	
	return true;
}


int mvmt_calibration(tHandle *_h,int serverID,bool HardReset){
	
	//envoie demande calibration
	if (demandeDeMouvementNiryo(*_h,310,true,true) != 0){
		return 1;
	}
	//envoie depart calibration
	if (demandeDeMouvementNiryo(*_h,311,true,true) != 0){
		return 2;
	}
	//reinitialisation de la connxion 
	if(HardReset){
		if(!TCPHardReset(_h,serverID)){
			return 3;
		}
	}
	return 0;
}

bool mvmt_calibration_show_error(int _error,tLabel *L){
	if(_error == 0){
		LabelTextSet(L, "calibration demarrer");
	} else if(_error == 1){
		LabelTextSet(L, "erreur de demande");
	} else if(_error == 2){
		LabelTextSet(L, "err de demarrage calibration");
	} else if(_error == 3){
		LabelTextSet(L, "erreur reset");
	}
	return true;
}

bool mvmt_detect_tool(tHandle *_h,tLabel *L){
	if (demandeDeMouvementNiryo(*_h,500,false,true) != 0){
		LabelTextSet(L, "erreur detection outil");
		return false;
	}
	LabelTextSet(L, "outil mis a jour");
	return true;
}

///////// timer //////////

typedef struct {
	unsigned long ref_time;
	unsigned long distance_to_ref;
} timer ;


timer timer_create(unsigned long distanceMS){
	timer result;
	result.ref_time = hmi_GetTickCount();
	result.distance_to_ref = distanceMS;
	return result;
}

bool timer_isFinished(timer *t){
	if(hmi_GetTickCount() > (t->ref_time + t->distance_to_ref) || hmi_GetTickCount() < (t->ref_time - t->distance_to_ref)){
		return true;
	} else {
		return false;
	}
}

void timer_reset(timer *t){
	t->ref_time = hmi_GetTickCount();
}

/////////// trajectory /////////////

typedef struct {
	int ID;
	char name[21];
	int index;
	
} trajectory ;

int traj_indexation(trajectory t[],int sizeOfTArray,tHandle _h){
	if(!LectureFNCT03R(_h,50,1)){return 1;}
	
	int nbTraj = (int)lectureFNCT03[0];
	if(nbTraj < 1 || nbTraj > sizeOfTArray){return 2;}
	
	if(!LectureFNCT03R(_h,0,1)){return 1;}
	if(lectureFNCT03[0] > 0){return 5;}
	
	for(int i = 0 ; i < nbTraj ; i++){
		ecritureFNCT06 = (WORD)i; 				
		if(!EcritureFNCT06W(_h,41)){return 3;}	// selection traj. i sur le robot
		int loopcount = 0;
		do{
			hmi_DelayUS(500);
			LectureFNCT03R(_h,51,1);
			loopcount ++;
		} while(lectureFNCT03[0] == 0 && loopcount < 100);	//tant que pas de traj. selectionner
		if(loopcount > 100){return 4;}
		if(!LectureFNCT03R(_h,10,22)){return 1;}
		
		// mise des valeur dans le tableau de traj.
		t[i].index = i;
		for(int j = 0 ; j < 20 ; j++){ // mise du nom dans le tableau (20 char)
			t[i].name[j] = (char)lectureFNCT03[j];
		}
		t[i].name[20] = '\0'; // termination du nom
		t[i].ID = (int)lectureFNCT03[21];
		
		ecritureFNCT06 = 0x00;
		if(!EcritureFNCT06W(_h,51)){return 3;}//desecionne la trajectoire
	}
	return 0;
}

bool traj_indexation_show_error(int _error,tLabel *L){
	if(_error == 0){
	LabelTextSet(L, "indexation terminee");
	} else if(_error == 1){
		LabelTextSet(L, "erreur de lecture");
	} else if(_error == 2){
		LabelTextSet(L, "trop de traj");
	} else if(_error == 3){
		LabelTextSet(L, "erreur d ecriture");
	} else if(_error == 4){
		LabelTextSet(L, "echec selection traj");
	} else if(_error == 5){
		LabelTextSet(L, "apprentissage en cour");
	}
	return true;
}

bool traj_getNbTraj(tHandle _h,int *_nbTraj){
	if(!LectureFNCT03R(_h,50,1)){return false;}
	else {
		*_nbTraj = (int)lectureFNCT03[0];
		return true;
	}
}	

int traj_lancerT(int _indexT,tHandle *_h){
	if(_indexT < 0 && _indexT > 32){return 4;}
	ecritureFNCT06 = _indexT;
	if(!EcritureFNCT06W(*_h,41)){return 3;}	// selection traj. i sur le robot
	
	int loopcount = 0;
	do{
		hmi_DelayUS(500);
		LectureFNCT03R(*_h,51,1);
		loopcount ++;
	} while(lectureFNCT03[0] == 0 && loopcount < 100);//selection de la trajectoire
	
	ecritureFNCT06 = 0x1;
	if(!EcritureFNCT06W(*_h,42)){return 1;}
	else {
		
		if(!EcritureFNCT06W(*_h,51)){return 2;}//desecionne la trajectoire
	}
	return 0;
}

bool traj_lancerT_show_error(int _error,tLabel *L){
	switch(_error){
		case 0:
			LabelTextSet(L, "trajectoire Lancee");
			break;
		case 1:
			LabelTextSet(L, "erreur de comm.");
			break;
		case 2:
			LabelTextSet(L, "erreur de comm.");
			break;
		case 3:
			LabelTextSet(L, "erreur de comm.");
			break;
		case 4:
			LabelTextSet(L, "erreur traj trop bas haut");
			break;
		default:
			LabelTextSet(L, "erreur inconnue");
	}
	return true;
}

bool traj_arret(tHandle *_h, tLabel *L){
	bool err = false;
	
	ecritureFNCT06 = 0xffff;
	err = EcritureFNCT06W(*_h,43);
	
	hmi_DelayUS(100000);
	
	lectureFNCT03[0] = 0;
	LectureFNCT03R(*_h,43,1);
	if(err && lectureFNCT03[0] > 0){
		LabelTextSet(L,"signal envoyer");
	} else {
		LabelTextSet(L,"signal perdue");
	}
	return true;
}

#endif