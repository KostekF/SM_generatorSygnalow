#include<reg51.h>

/**
* Pobranie jednego znaku (char) przez UART
* @return Pobrany znak (char)
*/
char UART_getkey(){
	char c;
	
	while(!RI);
	c=SBUF;
	RI=0;
	return (c);
}
