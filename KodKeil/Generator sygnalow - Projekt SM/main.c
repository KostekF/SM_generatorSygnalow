#include <aduc831.h>
#include "definicjeTypow.h"
#include "timeryCountery.h"
#include <stdio.h>
#include "UART_definicje.h"
#include "operacjeBitowe.h"
#define GENERATOR_okres_probkowania 50 //ms
#define CA_Vref 5.0
#define CA_rozdzielczosc 12
#define CA_wartosc_maksymalna ((0x000001ul<<CA_rozdzielczosc)-1)
 
//Probka napiecia zapisana na dwoch bajtach
typedef union{
    uint16_t wartosc;
    struct{
    uint8_t bajt_gorny;
    uint8_t bajt_dolny;
    }slowo;
}probka_t;
 
//Struktura zawierajaca parametry sygnalu
typedef struct{
    float okres;
    float amplituda;
    float offset;
    float t;
    float delta_t;
    float narastanie_t;
    float opadanie_t;
    float utrzymanie_t;
   
}parametry_sygnalu_t;
 
//Zmienne globalne
probka_t probka={0};
float32_t probka_napiecie=0;
parametry_sygnalu_t parametry_sygnalu;
char xdata napisXDATA[40]="";
int wyslijFlaga=0;
 
 //Tablica sprobkowanego sinusa
double xdata sinusXDATA[80]={
0.500000000000000,
0.539458926235830,
0.578671717363745,
0.617393773606290,
0.655383556269914,
0.692404094404123,
0.728224462968172,
0.762621223284857,
0.795379816796201,
0.826295903427138,
0.855176636208804,
0.881841864210650,
0.906125256277778,
0.927875338563910,
0.946956439388101,
0.963249535521427,
0.976652994624704,
0.987083209206103,
0.994475118144188,
0.998782612523240,
0.999978823249370,
0.998056288653336,
0.993027001034611,
0.984922331856354,
0.973792836057921,
0.959707936705539,
0.942755491948245,
0.923041246980291,
0.900688174428545,
0.875835707279397,
0.848638869129969,
0.819267307188927,
0.787904234058784,
0.754745284900598,
0.719997297109810,
0.683877020115269,
0.646609763349443,
0.608427990823414,
0.569569871073367,
0.530277791523656,
0.490796846533473,
0.451373308558324,
0.412253091962829,
0.373680219067207,
0.335895297995865,
0.299134021822910,
0.263625698376532,
0.229591819872996,
0.197244681302494,
0.166786056185044,
0.138405937956744,
0.112281354837292,
0.0885752655713559,
0.0674355429318754,
0.0489940513259571,
0.0333658242570322,
0.0206483467740637,
0.0109209473837108,
0.00424430321855374,
0.000660061548015734,
0.000190579992907280,
0.00283878706406882,
0.00858816389503786,
0.0174028472826882,
0.0292278533930990,
0.0439894207372301,
0.0615954702770070,
0.0819361797917864,
0.104884668922444,
0.130297790619946,
0.158017024061549,
0.187869463464830,
0.219668896631560,
0.253216966493751,
0.288304408416413,
0.324712355539041,
0.362213704013436,
0.400574529621830,
0.439555546938805,
0.478913601935117};
 
char tablicaZnakow[6];
uint8_t i=0;
 
char ktorySygnal='2';				//trojkat jako domyslny sygnal
int timerStart=1;						//rysowanie domyslnie odpalone
uint8_t probkaSinus=-1;
 
/**
* Generacja jednej probki sygnalu sinus
* @param[in] syg Parametry sygnalu sinus
* @return Wartosc probki sygnalu sinus dla podanych parametrow
*/
float32_t sinus(parametry_sygnalu_t* syg)
{
    probkaSinus++;
    if(probkaSinus>79)
    {probkaSinus=0;}
    return syg->amplituda*sinusXDATA[probkaSinus]+syg->offset;
}
 
/**
* Generacja jednej probki sygnalu pila
* @param[in] syg Parametry sygnalu pila
* @return Wartosc probki sygnalu pila dla podanych parametrow
*/
float32_t pila(parametry_sygnalu_t* syg)
{
    return syg->amplituda* (syg->t)/(syg->okres) + syg->offset;
}
 
/**
* Generacja jednej probki sygnalu trojkat
* @param[in] syg Parametry sygnalu trojkat
* @return Wartosc probki sygnalu trojkat dla podanych parametrow
*/
float32_t trojkat(parametry_sygnalu_t* syg)
{
    if(syg->t<syg->narastanie_t)
    {
    return syg->amplituda* (syg->t)/(syg->narastanie_t) + syg->offset;
    }
    else if(syg->t>=syg->narastanie_t)
    {
    return -syg->amplituda* (syg->t-syg->narastanie_t)/(syg->opadanie_t) +syg->amplituda + syg->offset;
    }
    else return 0;
}  
 
/**
* Generacja jednej probki sygnalu trapez
* @param[in] syg Parametry sygnalu trapez
* @return Wartosc probki sygnalu trapez dla podanych parametrow
*/
float32_t trapez(parametry_sygnalu_t* syg)
{
    if(syg->t<syg->narastanie_t)
    {
			return syg->amplituda* (syg->t)/(syg->narastanie_t) + syg->offset;
    }
    else if((syg->t>=syg->narastanie_t) && (syg->t<(syg->narastanie_t+syg->utrzymanie_t)))
    {
			return syg->amplituda+syg->offset;
    }
    else if(syg->t>=(syg->narastanie_t+syg->utrzymanie_t))
    {
			return -syg->amplituda* (syg->t-(syg->narastanie_t+syg->utrzymanie_t))/(syg->opadanie_t) +syg->amplituda + syg->offset;
    }
    else return 0;
}  
 
/**
* Generacja jednej probki sygnalu prostokat
* @param[in] syg Parametry sygnalu prostokat
* @return Wartosc probki sygnalu prostokat dla podanych parametrow
*/
float32_t prostokat(parametry_sygnalu_t* syg)
{
    if(syg->t<syg->utrzymanie_t)
    {
        return syg->amplituda+syg->offset;
    }
    else return syg->offset;
}  
 
/**
* Funkcja obslugujaca przerwanie od UARTa
*/
void UART_obsluga(void) interrupt 4
{
if(RI){    
   RI=0;
}
  return;
}
/**
* Funkcja obslugujaca timer 1
*/
void timer1() interrupt 3
{
    //Ustaw T1
    T1_ustaw_czas_ms(GENERATOR_okres_probkowania);
   
    //Zmiana czasu sygnalu
    parametry_sygnalu.t += parametry_sygnalu.delta_t;
    if(parametry_sygnalu.t >= parametry_sygnalu.okres)
    {  
    parametry_sygnalu.t=parametry_sygnalu.delta_t;
    }
    //Wyznaczanie probki sygnalu
    if(ktorySygnal=='1')        probka_napiecie = pila(&parametry_sygnalu);
    else if (ktorySygnal=='2')  probka_napiecie = trojkat(&parametry_sygnalu);
    else if (ktorySygnal=='3')  probka_napiecie = trapez(&parametry_sygnalu);
    else if (ktorySygnal=='4')  probka_napiecie = prostokat(&parametry_sygnalu);
    else if (ktorySygnal=='5') probka_napiecie=sinus(&parametry_sygnalu);
   
    //Ograniczenie sygnalu
    probka_napiecie = (probka_napiecie>CA_Vref)? CA_Vref : probka_napiecie;
    probka_napiecie = (probka_napiecie<0)? 0 :probka_napiecie;
   
    //Konwersja na wartosc rejestru
    probka.wartosc = (uint16_t)(probka_napiecie/CA_Vref*(float32_t)CA_wartosc_maksymalna);
 
    //Ustaw przetwornik
    DAC0H = probka.slowo.bajt_gorny;
    DAC0L = probka.slowo.bajt_dolny;    //Synchronizacja wyjscia zerowego
}
 
/**
* Funkcja glowna
*/
void main(void)
{
    //mode1 - 8-bit UART variable baud rate
    SM0=0;
    SM1=1;
    SM2=0;
    REN=1; //pozwolenie na odbior
    T3CON=0x84; //19200 baud rate
    T3FD=0x08;
    TI=0;
    RI=0;
    
	  //Zgoda na obsluge przerwan
    ET1 = 1;		//zgoda na przerwanie timer 1 	
    ES=1; 			//zgoda na przerwanie UART
		EA = 1;			//ogolna zgoda na przerwania
    
	  //Priorytety przerwan
    PS=1;
    PT1=0;
   
    //Konfiguracja DAC
    DACCON = 0x7F; //MODE=0; RNGx=11; CLRx=11; SYNC=1; PDx=11;
		
    //Konfiguracja programowalnych ukladów licznikowych
    TMOD = 0x10;    //konfiguracja programowalnego ukladu licznikowego 1 - jako czasomierz 16 bitowy
   
		//Ustawianie bazowych parametrow sygnalu generowanego
    parametry_sygnalu.amplituda 				= 3.0;
    parametry_sygnalu.offset            = 1.0;
    parametry_sygnalu.t                 = 0.0;
    parametry_sygnalu.delta_t      			= ((float32_t)GENERATOR_okres_probkowania)/1000.0;      //sekundy
    parametry_sygnalu.narastanie_t			= 1.0;
    parametry_sygnalu.opadanie_t				= 1.0;
    parametry_sygnalu.utrzymanie_t			= 1.0;
    parametry_sygnalu.okres         		= 2.0;
    //XRAM
    BitKasuj(CFG831,0);    
 
    while(1)
    {
        if(SBUF=='x')						//'x' rozpoczyna wprowadzanie komendy do UART
		{
        for(i=0;i<6;i++)        //czyszczenie tablicy znakow        
		{
			tablicaZnakow[i]=0;
		}
      UART_getstring(tablicaZnakow,6);
		}
    
		//Komendy do wprowadzania parametrów. Przykladowe urzycie komendy "xF1.5" - ofset zostanie ustawiony na 1.5V
		
		sscanf( tablicaZnakow, "S%c", &ktorySygnal);                        //wybieranie sygnalu 1-pila,2-trojkat,3-trapez,4-prostokat
    sscanf( tablicaZnakow, "F%f", &parametry_sygnalu.offset);           //ofset
    sscanf( tablicaZnakow, "A%f", &parametry_sygnalu.amplituda );       //amplituda
    sscanf( tablicaZnakow, "N%f", &parametry_sygnalu.narastanie_t);   	//czas narastania
    sscanf( tablicaZnakow, "O%f", &parametry_sygnalu.opadanie_t);       //czas opadania
    sscanf( tablicaZnakow, "U%f", &parametry_sygnalu.utrzymanie_t);     //czas podtrzymania
    if((ktorySygnal=='1') ||(ktorySygnal=='4'))
    {sscanf( tablicaZnakow, "T%f", &parametry_sygnalu.okres); }     		//okres
    sscanf( tablicaZnakow, "Z1%d", &timerStart);                        //Z11 = timer1 start,  Z10 = timer1 stop
    sscanf( tablicaZnakow, "W%d", &wyslijFlaga);  											//Gdy flaga ustawiona na 1 to parametry sygnalu sa
																																				//przesylane do programu zewnetrzengo
       
		//Obliczanie okresu sygnalow trojkat i trapez na podstawie t_narastania, t_opadania, t_podtrzymania
    if(ktorySygnal=='2')parametry_sygnalu.okres = parametry_sygnalu.narastanie_t + parametry_sygnalu.opadanie_t;
    else if (ktorySygnal=='3')parametry_sygnalu.okres   = parametry_sygnalu.narastanie_t + parametry_sygnalu.opadanie_t + parametry_sygnalu.utrzymanie_t;
   
		//Zatrzymanie timera 1 gdy dane parametry sa mniejsze od zera
    if((parametry_sygnalu.amplituda<0) || (parametry_sygnalu.offset<0) || (parametry_sygnalu.narastanie_t<0)  || (parametry_sygnalu.opadanie_t<0)|| (parametry_sygnalu.utrzymanie_t<0) || (parametry_sygnalu.okres<0))
    {timerStart=0;}
    if(timerStart)TR1 = 1;      //start timera 1
    else TR1 = 0;
       
    //Wysylanie danych do programu zewnetrzengo
    if(wyslijFlaga)
		{
		sprintf(napisXDATA ,"%c %.2f %.2f",ktorySygnal,parametry_sygnalu.offset ,parametry_sygnalu.amplituda);
		UART_puts(napisXDATA);
		sprintf(napisXDATA ," %.2f",parametry_sygnalu.narastanie_t);
		UART_puts(napisXDATA);
		sprintf(napisXDATA ," %.2f %.2f",parametry_sygnalu.opadanie_t ,parametry_sygnalu.utrzymanie_t );
		UART_puts(napisXDATA);
		sprintf(napisXDATA ," %.2f",parametry_sygnalu.okres);
		UART_puts(napisXDATA);
		sprintf(napisXDATA ," %u",timerStart);
		UART_puts(napisXDATA);
    UART_puts("\r\n");
		wyslijFlaga=0;					//zerowanie flagi po wyslaniu danych
    for(i=0;i<6;i++)          
		{
		tablicaZnakow[i]=0;			//zerowanie tablicy po wyslaniu danych
		}
		}
    }
}