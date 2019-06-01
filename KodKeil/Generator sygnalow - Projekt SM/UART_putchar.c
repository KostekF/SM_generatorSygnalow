#include <reg51.h>

/**
* Wyslanie jednego znaku przez UART
* @param[in] c Znak do wyslania
* @return Wyslany znak
*/
char UART_putchar(char c)
{
	SBUF=c;
	while(!TI);
	TI=0;
	return c;
}