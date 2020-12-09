#ifndef wechseldef
#define wechseldef

enum wechselstates {pumpe1,pumpe2};

struct wechsel
{
	enum wechselstates status;					//Zustand pumpe1 pumpe2
    void* timer;								// 10 Sek Timer
    unsigned char pumpen;                       //Kontrollsteuerung
}

void * wechselErzeugen();				
void wechselLoeschen(void *);
int wechselRuecksetzten(void  *);
int wechseln(struct wechsel *);

typedef (*wechselfunktionen) (struct wechsel *id);

int funktionPumpe1(struct wechsel *id);
int funktionPumpe2(struct wechsel *id);

static wechselfunktionen funktionsarray[] = {funktionPumpe1,funktionPumpe2};

#endif