#include<reg51.h>

char getkey(){
	char c;
	
	while(!RI);
	c=SBUF;
	RI=0;
	return (c);
}
	
