void * wechselErzeugen()
{
	struct Wechsel *ptr;

	ptr = (struct Wechsel)malloc(sizeof(struct Wechsel*));

	if(ptr == NULL)
		return ptr;
	
	ptr->status = pumpe1;
	ptr->timer = pulseTimerCreate();

	return ptr;
}

void wechselLoeschen(void* id)
{
	free((void)ptr->timer);
	free ((void*) id);		
}

int wechselRuecksetzten(void *id)
{
	struct Wechsel *ptr;
	ptr = (struct Wechsel) id;

	struct 

	
}

int wechseln(struct wechsel *ptr)
{
	if(ptr == NULL)
		return ptr;


	return (funktionsarray[ptr->state](ptr));
}

int funktionPumpe1(struct wechsel *ptr)
{
	if(ptr->pumpen ==
}

int funktionPumpe2(struct wechsel *ptr)
{

}