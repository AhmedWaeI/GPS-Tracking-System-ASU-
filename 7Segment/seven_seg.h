#ifndef SEVEN_SEG.H
#define SEVEN_SEG.H
//function to divide distance to be displayed on the 3 7_segment_displays
void split_dist(double distance);

// function to represent which segments of the seven-segment display should be lit up in order to display the desired digit.
void set_seven_segment(unsigned char index_of_seven_seg_array);

/*function to display a specific digit on a multi-digit seven-segment display by specifying which digit to
display it on and what the digit should be.
*/
void show(int digit , char value);

//function to generate interrupt every 5ms
void sys_tick_int(void);

//function to cycle through the 3 digits to display a changing value on the 7_segment_displays at equal intervals
void sys_tick_Handler(void);
#endif
