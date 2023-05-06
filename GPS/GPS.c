#include "GPS.h"
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "UART.h"
const double EARTHRADIUS = 6371000;
const double PI=3.14159265358979323846;
char GPS_string[80];
char GPS_logName []="$GPRMC, ";
char GPS_formated [12][20];
char * token;
float currentLat,currentLong,speed; 
//endLat= ...........;
float toDeg (float angle){
	int degree = (int)angle/100;
	float minutes= angle - (float)degree*100;
	return (degree+minutes/60);
}

float toRad (float angle){
	return angle*PI/180;
}

float getDistance (float startLong, float startLat,float endLong,float endLat){
	float lamda_A = toRad(toDeg (startLong) ) ;
	float  phi_A= toRad (toDeg (startLat) ) ;
	float lamda_B = toRad (toDeg (endLong) ) ;
	float  phi_B= toRad (toDeg (endLat) ) ;
	float a = pow (sin ((phi_B-phi_A)/2), 2) +cos (phi_A) *cos (phi_B)*pow (sin ((lamda_B-lamda_B)/2),2); // Haversine formula: a = sin' (dp/2) + cos p1 O cos p2 D sin° (4X/2)
	double c = 2 * atan2(sqrt(a),sqrt(1-a));
return EARTHRADIUS * c;
}

void GPS_read () {
	char recievedChar;
	char flag;
		char i;
	do{ flag = 1;
	for (i=0;i<7;i++) {
	if (UART0_getChar() != GPS_logName [i]) {
		flag = 0; //removing break
				}
			}
		}while (flag==0); // checking for desired log name
	strcpy(GPS_string, ""); //Init GPS Array
	do{
		char GPS_counter =0; //using char not int to decrease memory used
	recievedChar = UART0_GPS_read(); 
	GPS_string [GPS_counter++] = recievedChar;
	}while(recievedChar!='*');
}

void GPS_format () {
	char noOfTokenStrings = 0 ;
	token = strtok (GPS_string,",");
	do{
		strcpy (GPS_formated [noOfTokenStrings], token) ;
		token = strtok (NULL,",");
		noOfTokenStrings++;
	}while(token!=NULL);
	if (strcmp (GPS_formated[1], "A")==0) { //Valid
		if (strcmp (GPS_formated [3], "N") ==0)
			currentLat = atof (GPS_formated [2]);
		else
			currentLat = -atof (GPS_formated [2]);
		if (strcmp (GPS_formated [5], "E") ==0)
			currentLong = atof (GPS_formated [4]);
		else 
			currentLong = -atof (GPS_formated[4]);	
		}
	}
