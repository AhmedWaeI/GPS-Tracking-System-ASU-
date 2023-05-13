#include "GPIO.h"
#include "UART.h"
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
const double EARTHRADIUS = 6371000;
const double PI = 3.14159265358979323846;

char GPS_string[80] = "";
char GPS_logName[] = "$GPRMC,";
char GPS_formated[12][20];
char *token;
float currentLat, currentLong, speed;
float endLong = 30 ;
float endLat=31;
float displacement;

float  toDeg(float angle) {
    int degree = angle / 100;
    int minutes = angle - degree * 100;
    return (degree + minutes / 60);
}

float  toRad(float angle) {
    return (angle * PI / 180);
}
//this function returns the distance between our current coordinations and the final coordination
float  getDistance(int startLong, int startLat, int endLong, int endLat) {
    float lamda_A = toRad(toDeg(startLong));
    float phi_A = toRad(toDeg(startLat));
    float lamda_B = toRad(toDeg(endLong));
    float phi_B = toRad(toDeg(endLat));
    float a = pow(sin((phi_B - phi_A) / 2), 2) + cos(phi_A) * cos(phi_B) * pow(sin((lamda_B - lamda_A) / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTHRADIUS * c;
}

int GPS_read() {
    char receivedChar;
    char flag;
    char i;
    //do {
        flag = 1;
        for (i = 0; i < 7; i++) {
            if (UART5_GPS_read() != GPS_logName[i]) {
                flag = 0;
								return 0;							// removing flag assignment
            }
        }
  //  } while (flag == 0); // checking for desired log name
    do {
        static char GPS_counter = 0; // using static to retain value between function calls
        receivedChar = UART5_GPS_read();
        GPS_string[GPS_counter++] = receivedChar;
    } while (receivedChar != '*');
		return 1;
}

void GPS_format() {
    char noOfTokenStrings = 0;
    token = strtok(GPS_string, ",");
    do {
        strcpy(GPS_formated[noOfTokenStrings], token);
        token = strtok(NULL, ",");
        noOfTokenStrings++;
    } while (token != NULL);
    if (strcmp(GPS_formated[1], "A") == 0) { // Valid
        if (strcmp(GPS_formated[3], "N") == 0)
            currentLat = atoi(GPS_formated[2]);
        else
            currentLat = -atoi(GPS_formated[2]);
        if (strcmp(GPS_formated[5], "E") == 0)
            currentLong = atoi(GPS_formated[4]);
        else
            currentLong = -atoi(GPS_formated[4]);
    }
}

int main(void){
	int p;
	char a;
  initPortF();
	initPortD();
	UART5_GPS_init();
	UART0_GPS_init();
	while(1){
		p=GPS_read();
		if(p==0)
		{
			UART0_GPS_write('e');
			waitseconds(1);
		}
		else
		{
		GPS_format();
		displacement=getDistance(currentLong,currentLat,endLong,endLat);
		if(displacement>5)
			turn_led(RED);
		else if(displacement<5)
			turn_led(YELLOW);
		else 
			turn_led(GREEN);
		}
	
}
}
