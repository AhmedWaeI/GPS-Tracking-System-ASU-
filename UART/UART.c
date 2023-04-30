#include "TM4C123GH6pm.h"
#include "UART.h"


void UART0_GPS_init()
{
	SYSCTL_RCGCUART_R |= 0x01;
	SYSCTL_RCGCGPIO_R |= 0x01;
	while((SYSCTL_RCGCGPIO_R & 0x01)==0);
	UART0_CTL_R &= ~0x00000001;
	//baudrate = 9600 
	UART0_IBRD_R= 104;
	UART0_FBRD_R= ((0.1666667*64)+0.5);
	UART0_LCRH_R=0x00000070;
	UART0_CTL_R |= 0x301;
	GPIO_PORTA_AFSEL_R |= 0x1;
	GPIO_PORTA_PCTL_R |=(GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x11;
	GPIO_PORTA_DEN_R |=0x03;
	GPIO_PORTA_AMSEL_R=0x0;
}
char UART0_GPS_read()
{
	while((UART0_FR_R&0x10)!=0);
	return (char) (UART0_DR_R &0xFF);
}
void UART0_GPS_write(char x)
{
	while((UART0_FR_R&0x20)!=0);
	UART0_DR_R = x;
}
void UART0_ReadString(char *str)
{
	int i;
	char c;
	for(i = 0;str && str[i]!= '*';i++)
	{
		str[i]=UART0_GPS_read();	
	}
}
void UART0_WriteString(char *str)
{
	int i=0;
	while(str[i])
	{
		UART0_GPS_write(str[i]);
		i++;
	}
}
void UART1_7seg_init()
{
	SYSCTL_RCGCUART_R |= 0x02;
	SYSCTL_RCGCGPIO_R |= 0x02;
	while((SYSCTL_RCGCGPIO_R & 0x02)==0);
	UART1_CTL_R &= ~0x00000001;
	//baudrate = 9600 
	UART1_IBRD_R= 104;
	UART1_FBRD_R= ((0.1666667*64)+0.5);
	UART1_LCRH_R=0x00000070;
	UART1_CTL_R |= 0x301;
	GPIO_PORTB_AFSEL_R |= 0x1;
	GPIO_PORTB_PCTL_R |=(GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x11;
	GPIO_PORTB_DEN_R |=0x03;
	GPIO_PORTB_AMSEL_R=0x0;
}
char UART1_7seg_read()
{
	while((UART1_FR_R&0x10)!=0);
	return (char) (UART1_DR_R &0xFF);
}
void UART1_7seg_write(char x)
{
	while((UART1_FR_R&0x20)!=0);
	UART1_DR_R = x;
}
void UART1_ReadString(char *str)
{
	int i;
	char c;
	for(i = 0;str && str[i]!= '*';i++)
	{
		str[i]=UART1_7seg_read();
	}
}
void UART1_WriteString(char *str)
{
	int i=0;
	while(str[i])
	{
		UART1_7seg_write(str[i]);
		i++;
	}
}
