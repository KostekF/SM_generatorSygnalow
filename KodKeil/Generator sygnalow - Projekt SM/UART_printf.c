#include "UART_definicje.h"
#include <aduc831.h>
#include <stdio.h>
#include <stdarg.h>

void UART_printf(const char*format,...)
{
	char buffer[4];
	va_list args;
	int i=0;
	va_start(args,format);
	vsprintf(buffer,format,args);
	va_end(args);
	
	UART_puts(buffer);
}