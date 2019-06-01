#include<reg51.h>

/**
* Pobieranie ciagu znakow przez UART
* @param[in,out] str tablica znakow 
* @param[in] rozmiar rozmiar tablicy znakow 
*/
void UART_getstring(char * str,int rozmiar){
	int licznik=0;
	while(SBUF==0x00);
	while(SBUF!=0x0D && licznik<rozmiar)
	{
		*str=UART_getkey();
			str++;
		licznik++;
	}
}
	
