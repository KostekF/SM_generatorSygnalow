#include<reg51.h>

char getstring(char * str,int rozmiar){
	int licznik=0;
	while(SBUF==0x00);
	while(SBUF!=0x0D && licznik<rozmiar)
	{
		*str=getkey();
			str++;
		licznik++;
	}
}
	


//#include<reg51.h>

//char _getkey(){
//	char c;
//	
//	while(!RI);
//	c=SBUF;
//	RI=0;
//	return (c);
//}
//	


//void UART_puts(char* str)
//{
//	while(*str!='\0')
//	{
//		UART_putchar(*str);
//		str++;
//	}

//}