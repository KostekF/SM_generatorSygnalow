#ifndef __operacjeBitowe
#define __operacjeBitowe

#define BitUstaw(bajt,nr_bitu) bajt=bajt|(0x0001<<nr_bitu)
#define BitKasuj(bajt,nr_bitu) bajt=bajt&~(0x0001<<nr_bitu)
#define BitSprawdz(bajt,nr_bitu) (bajt&(0x0001<<nr_bitu))
#define BitPrzelacz(bajt,nr_bitu) bajt=bajt^(0x0001<<nr_bitu)

#endif