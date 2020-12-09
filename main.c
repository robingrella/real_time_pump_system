
#include <vxWorks.h>
#include <sysLib.h>
#include <tickLib.h>
#include <taskLib.h>
#include "sim_communication.h"

#define LAUFZEIT500   500											//Definieren von Variablen
#define LAUFZEIT10000  10000		
#define MIN_CLOCKRATE 10

int user_sysinit()													//Einstiegspunkt in vxWorks
{
	unsigned int next_cycle,restzeit1000,restzeit300;
	struct timer zaehler10000;										//Erzeugen einer Instanz der Struktur timer f�r den 10 Sekunden Z�hler
	struct timer zaehler500;										//Erzeugen einer Instanz der Struktur timer f�r den 0,3 Sekunden Z�hler
	void * zaehlerCTL10000;											//Erzeugen der Kontrollstruktur f�r den 10 Sekunden Timer
	void * zaehlerCTL500;											//Erzeugen der Kontrollstruktur f�r den 1 Sekunden Timer
	unsigned int zykluszeit10000,zykluszeit500;						//Variablen f�r die Zykluszeit
	int clockrate;													//Variable f�r die Clockrate

	clockrate = sysClkRateGet();									//Clockrate holen
	if(clockrate < 10) {
		sysClkRateSet(MIN_CLOCKRATE);								//Clockrate auf 10 Setzten
		clockrate = sysClkRateGet();								
	}

	
	zaehlerCTL10000 = pulseTimerCreate();							//Speicher f�r die Kontrollstruktur f�r den 1 Sekunden Timer reservieren
	if(zaehlerCTL10000 == NULL) return -1;							//Erfolgreiche reservierung �berpr�fen

	zaehlerCTL500 = pulseTimerCreate();								//Speicher f�r die Kontrollstruktur f�r den 0,3 Sekunden Timer reservieren
	if(zaehlerCTL500 == NULL) return -1;							//Erfolgreiche reservierung �berpr�fen

	zaehler10000.id = zaehlerCTL10000;								//Zuweisen der Kontrollstruktur f�r den 1 Sekunden Timer
	zaehler500.id = zaehlerCTL500;									//Zuweisen der Kontrollstruktur f�r den 0,3 Sekunden Timer

	zykluszeit10000 = clockrate * LAUFZEIT10000 / 100;				//Endzeit bzw. Zykluszeit f�r den 1 Sek. Timer berechnen
	zykluszeit500 = clockrate * LAUFZEIT500 / 1000;					//Endzeit bzw. Zykluszeit f�r den 0,3 Sek. Timer berechnen

	zaehler10000.time_in = zykluszeit10000;							//Speicher f�r die Restzeit reservieren
	zaehler500.time_in = zykluszeit500;
	
	zaehler10000.in = 1;												//Attribute zum Einsschalten der Timer setzten
	zaehler500.in = 1;
    
    initSimComm(55000);



	return 0;
}