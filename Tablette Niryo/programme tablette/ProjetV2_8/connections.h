/*
	system de connection pour la tablette
	
	checkConnexion() permet de verifier la connexion tcp au robot
	et renvoi 
	0 si tout se passe comme prevu
	1 si id server est mauvais
	2 si le nombre d'essaie est dépasser
	
	connexionModBus() permet de se connecter au robot
	et renvoi
	les meme erreur que checkConnexion()
	
	18/03/2024
	
*/
#ifndef CONNECTIONS_H
#define CONNECTIONS_H
int server1DisconnectCount = 0;
int server2DisconnectCount = 0;

int connexionModBus(tHandle *_h,int serverID){//serverID normal = 1  custom = 2  
	int connexionStatus = 0;
	int state = -1;
	
	state = hmi_TCPState (*_h);
	
	if(state == -1){return 5;}
	if(state == 3){return 4;connexionStatus=2;}
	if(connexionStatus == 0){
		if(serverID == 1){
			*_h = mtm_Register(1, TCP_IPADDR(192,168,1,10), 5020);// connexion au serveur du niryo 
		} else if(serverID == 2){
			*_h = mtm_Register(1, TCP_IPADDR(192,168,1,10), 5022);// connexion au serveur pour le projet
		} else {
			return 1;
		}
		connexionStatus = 1;
	}
	int loopCount = 0;
	
	while(connexionStatus == 1){// tant que connexion en cours
		
		hmi_DelayUS(10000);
		state = hmi_TCPState (*_h);
		if (state == -1){
		} else if(state == 0){
		} else if(state == 1){
		} else if(state == 2){
		} else if(state == 3){
			connexionStatus = 2;
		}
		loopCount = loopCount + 1;
		if(loopCount >= 20){
			connexionStatus = 0;
			mtm_Unregister(*_h);
			*_h = -1;
			return 2;
		}
	}
	if(connexionStatus == 2){// si connexion reussi
		
	}
	return 0;
}

int checkConnexion(tHandle *_h,int serverID){//serverID normal = 1  custom = 2  
	//partie verification de l etat de la connection tcp
	int state = -1;
	state = hmi_TCPState (*_h);
	if (state == -1){
		mtm_Unregister(*_h);
		connexionModBus(_h,serverID);
	} else if(state == 0){//idle
		if(serverID == 1){server1DisconnectCount++;}
		else if(serverID == 2){server2DisconnectCount++;}
		else {return 1;}
	} else if(state == 1){//listen
		if(serverID == 1){server1DisconnectCount++;}
		else if(serverID == 2){server2DisconnectCount++;}
		else {return 1;}
	} else if(state == 2){//connecting
		
	} else if(state == 3){//connected
		if(serverID == 1){server1DisconnectCount = 0;}
		else if(serverID == 2){server2DisconnectCount = 0;}
		else {return 1;}
	}
	//partie reconnection si necessaire
	int erreur = 0;
	if((serverID == 1 ? server1DisconnectCount : server2DisconnectCount) > 10 && state != 3){
		if(server1DisconnectCount > 10 && serverID == 1){server1DisconnectCount = 0;}
		if(server2DisconnectCount > 10 && serverID == 2){server2DisconnectCount = 0;}
		mtm_Unregister(*_h);
		*_h = -1;
		erreur = connexionModBus(_h,serverID);
	}

	return erreur;
}


bool TCPHardReset(tHandle *_h,int serverID){//fonction pour regler les perte de connection lors du lancement de trajectoire
//termine a connexion pour en recreer une autre
	mtm_Unregister(*_h);
	*_h = -1;
	connexionModBus(_h,serverID);
	return true;
}

#endif