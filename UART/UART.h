#ifndef UART_H
#define UART_H
void UART0_GPS_init();
char UART0_GPS_read();
void UART0_GPS_write(char x);
void UART0_ReadString(char *str);
void UART0_WriteString(char *str);
void UART1_7seg_init();
char UART1_7seg_read();
void UART1_7seg_write(char x);
void UART1_ReadString(char *str);
void UART1_WriteString(char *str);
#endif
