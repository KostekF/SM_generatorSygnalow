#ifndef __UART_definicje_h
#define __UART_definicje_h

char UART_putchar(char c);
char UART_getkey();
void UART_puts(char* str);
void UART_printf(const char*format,...);
void UART_getstring(char * str,int rozmiar);
#endif