#include "GPS.h"
#include "UART.h"
#include "seven_seg.h"
#include "GPIO.h"
int main(void)
{
     sys_tick_int();
     initPortE();
     initPortB();
     initPortF();
     UART1_7seg_init();
     UART0_GPS_init();
    while(1)
         {

        GPS_read();
        GPR_format();
        if(flag==1){
            latitude2=latitude1;
            longitude2=longitude1;
                 }
                                                       //distance+=calculateDistance( latitude1, longitude1, latitude2, longitude2)
        split_dist(distance);

        if(speed>0.8){
            distance+=getDistance(latitude1,longitude1,latitude2,longitude2);
                }

        if(!(GPIO_PORTF_DATA_R & 0x10)&&distance>=100){ //turn on the led if the push button on pf4 pressed and the distance more than 100
            while(1) { 
        turn_led(RED);                       //Turn on the red led if the distance exceeded 100 meters

         }
           }
        flag=0;
        latitude2=latitude1;
        longitude2=longitude1;

    }
}
