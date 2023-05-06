#include "GPIO.h"
#include "TM4C123.h"
# include "seven_seg.h"
unsigned char seven_seg array[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
unsigned seg1,seg2,seg3;
unsigned char counter =0;
void split_dist(double distance){ 
int d=(int)distance;
seg1 = d%10;
d/=10;
seg2 = d%10;
d/=10;
seg3=d%10;
d/=10;
}
void set_seven_segment(unsigned char index_of_seven_seg_array){
GPIO_PORTB_setport(seven_seg array[index_of_seven_seg_array]);
}

void show(int digit , char value){
	GPIO_PORTB_DATA_R=0X00;
	GPIO_PORTE_DATA_R=digit;
	set_seven_segment(value);
}
void sys_tick_int(void){
	NVTC_ST_CTRL =0;
	NVTC_ST_RELOAD_R=400000;  // as our clk is 80MHZ 
  NVTC_ST_CURRENT_R=0;
  NVTC_ST_CTRL_R =0X7;
	_enable_irq();
}
void sys_tick_Handler(void){
	if(counter==0){ 
	show(8,seg3);
		counter++;
	}
	if(counter==1){
	show(8,seg2);
		counter++;
	}
	if(counter==2){
	show(8,seg1);
		counter=0;
	
	}
}

