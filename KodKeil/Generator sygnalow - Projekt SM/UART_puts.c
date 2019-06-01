#include "UART_definicje.h"

/**
* Wyslanie ciagu znakow przez UART
* @param[in] str tablica znakow do wyslania
*/
void UART_puts(char* str)
{
	while(*str!='\0')
	{
		UART_putchar(*str);
		str++;
	}

}