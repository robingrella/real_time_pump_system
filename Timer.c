#include "Timer.h"	//einbinden der Header-Datei


static char *basis[] = { "Ausgabe1","Ausgabe2","Ausgabe3","Fehler"};				//Erzeugen des statischen Feldes zur Ausgabe



char* convertToString(unsigned int value)											//R�ckgabe eines Wertabh�ngigen Textes/Wort
{
	if(value > (getNumberofElements()-1)) return basis[getNumberofElements()-1];	//�berpr�fung des Wertebereichs
	return basis[value];															//R�ckgabe eines Textes/Wortes
}

int getNumberofElements()															//Berechnung der Arraygr��e
{
	return  sizeof(basis)/sizeof(char*);											//R�ckgabe der Arraygr��e
}	

void * pulseTimerCreate()															//Erzeugen bzw. reservieren des Speichers f�r den Timer
{
	struct timerControl *ptr;														
	ptr = (struct timerControl*)malloc(sizeof(struct timerControl));				//Reservieren des Speichers f�r den Timer

	ptr->state = TIMER_OFF;															//Timer Zustand auf TIMER_OFF setzten

	return (void*)ptr;																//R�ckgabe der Addresse 
}
void pulseTimerDelete(void * id)													//L�schen bzw. freigeben der Timer Struktur
{
	free ((void*) id);																//freigeben des erzeugten Speichers
	return;
}
int pulseTimer (struct timer *control)												//Dient zum Aufrufen der Zustandsfunktionen
{
	struct timerControl *mytimerControl;											//Pointer auf die Kontrollstruktur definieren
	
	if(control->id==NULL) return -1;												//�berpr�fung ob Speicher f�r den Timer reserviert wurde
	if(control->r_time==NULL) return -1;											//�berpr�fung ob Speicher f�r die Restzeit angelegt wurde

	mytimerControl = (struct timerControl*)control->id ;							

	return(funcPtrArray[mytimerControl->state](control));							//Aufrufen der Zustandsfunktionen und R�ckgabe des R�ckgabewertes der Zustandsfunktion
}

int timerOff (struct timer* ptr)													//Timer aus
{
	struct timerControl *mytimerControl;											
	mytimerControl = (struct timerControl*)ptr->id;
	
	if (ptr->in == 1)																//Pr�fen ob der Timer angeschaltet werden soll
	{				
		if(ptr->time_in > 0)
		{
			mytimerControl->endtime = ptr->time_in + tickGet();						//Endzeit setzten
			*ptr->r_time= ptr->time_in;													
			mytimerControl->state = TIMER_ON;										//Zustandswechsel auf TIMER_ON
			ptr->in = 0;															//Timer Einschaltswert auf 0 setzten
			return (unsigned int)ptr;												//R�ckgabe der Addresse des Timers
		}												
	}
	
	if (ptr->in == 0)																//Pr�fen ob der Timer ausgeschaltet werden soll
	{										
		return 0;																	//R�ckgabe 0 = Timer aus
	}
	return -1;
}

int timerOn (struct timer* ptr)														//Timer an
{
	struct timerControl *mytimerControl;
	mytimerControl = (struct timerControl*)ptr->id;
	
	mytimerControl->endtime = mytimerControl->endtime - tickGet();					//Berechnung der neuen Endzeit

	if(ptr->reset == 1)
	{
		*ptr->r_time = 0;
		mytimerControl->state = TIMER_OFF;
		return 0;
	}
	
	if(mytimerControl->endtime <= 0)												//Pr�fen ob die Zeit abgelaufen ist
	{
		mytimerControl->endtime = 0;												// 
		mytimerControl->state = TIMER_OFF;											//Zustandswechsel auf TIMER_OFF
		return 0;																	//R�ckgabe 0 = Timer aus
	}

	return 1;																		//R�ckgabe 1 = Timer an

}