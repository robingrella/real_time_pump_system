#ifndef timerdef						//ifndef dient zum einmaligen definieren einer Header-Datei
#define timerdef						//definieren der Header-Datei

#include <stdlib.h>						//Einbinden der benötigten Header-Dateien
#include "vxWorks.h"
#include "sysLib.h"
#include "tickLib.h"

typedef unsigned int  uint;				//definieren des "makros" uint als unsigned int
	
char *convertToString(unsigned int);	//definieren der Prototypen
int getNumberofElements();				

void * pulseTimerCreate();				
void pulseTimerDelete(void*);
int pulseTimer (struct timer *);


enum states {TIMER_OFF, TIMER_ON};		//die Zustände TIMER_OFF und TIMER_ON definieren

struct timer							//die Timer Struktur anlegen
{
	void * id;							//Timer id
	uint in;							//ein -oder ausschalten des Timers 1 = einschalten 0 = ausschalten
	uint time_in;						//laufzeit des Timers
	uint *r_time;						//restzeit des Timers
	uint reset;							//zurücksetzten des Timers 1 =  rücksetzten 
};

struct timerControl						//Kontrollstruktur des Timers
{
	enum states state;					//Zustände des Timers
	uint endtime;						//Zeitpunkt an dem der Timer ausgeschaltet werden soll
};

										//Zustandfunktionen des Timers, sowie deren Funktionspointer
int timerOff ( struct timer*);			
int timerOn ( struct timer*);
typedef int (*stateFunc) (struct timer* ptr);
static stateFunc funcPtrArray[] = { timerOff, timerOn };

#endif //timerdef
