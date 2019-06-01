#ifndef __timeryCountery
#define __timeryCountery

//Stale
#define F_OSC 11058000.0

//Zaleznosci ogólne
#define Tx_tau(dzielnik) (float)((float)dzielnik/F_OSC)
 //obliczenie okresu zegara programowalnego ukladu licznikowego
#define Tx_N(zadany_czas_ms, dzielnik) (unsigned int)((float)zadany_czas_ms/Tx_tau(dzielnik)/1000.0)

#define T1_dzielnik 12
#define T1_rozdzielczosc 16
#define T1_rejestr_wartosc_poczatkowa(czas_ms) ((0x000001ul<<T1_rozdzielczosc) - Tx_N(czas_ms, T1_dzielnik))
//wyznaczenie wartosci poczatkowej licznika programowalnego ukladu
//licznikowego dla podanego czasu
#define T1_ustaw_czas_ms(czas_ms) TL1 = T1_rejestr_wartosc_poczatkowa(czas_ms); TH1 = T1_rejestr_wartosc_poczatkowa(czas_ms)>>8

#define T0_dzielnik 12
#define T0_rozdzielczosc 16
#define T0_rejestr_wartosc_poczatkowa(czas_ms) ((0x000001ul<<T0_rozdzielczosc) - Tx_N(czas_ms, T0_dzielnik))
//Ustawienia T0
#define T0_GATE_ON (0x01<<3)
#define T0_GATE_OFF (0x00)
#define T0_COUNTER (0x01<<2)
#define T0_TIMER (0x00)
#define T0_MODE0 (0x00)
#define T0_16BIT (0x01<<0)
#define T0_MODE2 (0x01<<1)
#define T0_MODE3 (0x01<<0)|(0x01<<1)

#define T0_COUNTER_CONFIG T0_GATE_OFF|T0_COUNTER|T0_16BIT
#define T0_TIMER_CONFIG T0_GATE_OFF|T0_TIMER|T0_16BIT

 //Ustawienia T1
#define T1_GATE_ON (0x01<<7)
#define T1_GATE_OFF (0x00)
#define T1_COUNTER (0x01<<6)
#define T1_TIMER (0x00)
#define T1_MODE0 (0x00)
#define T1_16BIT (0x01<<4)

#define T1_MODE2 (0x01<<5)
#define T1_MODE3 (0x01<<4)|(0x01<<5)

#define T1_TIMER_CONFIG T1_GATE_OFF|T1_TIMER|T1_16BIT
#define T1_COUNTER_CONFIG T1_GATE_OFF|T1_COUNTER|T1_16BIT
#define T1_TIMER_MODE2_CONFIG T1_GATE_OFF|T1_TIMER|T1_MODE2




#endif