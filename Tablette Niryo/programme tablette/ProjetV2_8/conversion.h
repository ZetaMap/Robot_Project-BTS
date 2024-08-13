
#ifndef CONVERSION_H
#define CONVERSION_H

//definition de pi car il n est pas definit 
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164


/////////////////////////////////////////////////////////////////////////////////
//								conversion de connées
/////////////////////////////////////////////////////////////////////////////////

int customDataToInt(WORD w){//conversion des voltages moteurs
	return (((int)w)/1000);
}
float customDataToFloat(WORD w){//conversion des voltages moteurs
	return (((float)w)/1000);
}

signed short axesToSignedShort(WORD w){// transforme les données d'axes du robot en Signed short
	signed short result = -1;
	if ((w >> 15) == 1){
		result = 0-(signed short)(w & 0x7fff);
	} else {
		result = (signed short)(w & 0x7fff);
	}
	return result;
}

int axesToInt(WORD w){// transforme les données d'axes du robot en Int
	int result = -1;
	if ((w >> 15) == 1){
		result = 0-(int)(w & 0x7fff);
	} else {
		result = (int)(w & 0x7fff);
	}
	return result;
}

float axesToFloat(WORD w){// transforme les données d'axes du robot en float
	float result = -1;
	if ((w >> 15) == 1){
		result = 0-(float)(w & 0x7fff);
	} else {
		result = (float)(w & 0x7fff);
	}
	return result;
}

float axesToRadiant(WORD w){// transforme les données d'axes du robot en float et en radiant
	float result = -1;
	if ((w >> 15) == 1){
		result = 0-(float)(w & 0x7fff);
	} else {
		result = (float)(w & 0x7fff);
	}
	result = result / 1000;
	return result;
}

float axesToDegrees(WORD w){// transforme les données d'axes du robot en float et en degree
	float result = -1;
	if ((w >> 15) == 1){
		result = 0-(float)(w & 0x7fff);
	} else {
		result = (float)(w & 0x7fff);
	}
	result = result / 1000;
	result = (result*(180/PI));
	return result;
}

WORD RadiantToAxes(float f){// transforme un float en radiant en donnees pour le robot
	WORD result = 0;
	f = f*1000;
	if(f < 0){
		result = (1 << 15) + (((WORD)-f) & 0x7fff);
	} else {
		result = (((WORD)f) & 0x7fff);
	}
	return result;
}

WORD DegreeToAxes(float f){// transforme un float en degrees en donnees pour le robot
	WORD result = 0;
	f = (f*(PI/180));
	f = f*1000;
	if(f < 0){
		result = (1 << 15) - (((unsigned short)f) & 0x7fff);
	} else {
		result = (((unsigned short)f) & 0x7fff);
	}
	return result;
}

float degreeToRadiant(float f){// transforme les degree en radiant
	f = (f*(PI/180));
	return f;
}

float radiantToDegree(float f){// transforme les radiant en degrees
	f = (f*(180/PI));
	return f;
}


/////////////////////////////////////////////////////////////////////////////////
//							fin de conversion de connées
/////////////////////////////////////////////////////////////////////////////////

#endif