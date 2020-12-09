void* pumpenCreate()
{
	struct pumpenSteuerung *ptr;

	ptr = (struct pumpenSteuerung)malloc(sizeof(struct pumpenSteuerung*));

	if(ptr == NULL)
		return ptr;

	ptr->state = keine;
	ptr->sensoren = 0;
	ptr->pumpe = 0;
	ptr->statusWechsel = wechselErzeugen();

	return ptr;
}

void pumpenDelete(void*)
{

}

int pumpenFunktion (struct pumpenSteuerung* ptr)
{
	if(ptr == NULL)
		return ptr;
	readByteRegister(&ptr->sensoren);
	return (func_array_pump[ptr->status](ptr));
}

int beideAus (struct pumpenStruktur * ptr)
{
	if(ptr->pumpen != 0x00)
	{
        ptr->pumpen=0x00;
        writeByteRegister(ptr->pumpen);
    }

	if(ptr->sensoren == 0x02)
	{
		ptr->state = eine;
	}
}

int eineAn(struct pumpenStruktur * ptr)
{
	if(ptr == NULL)
		return ptr;

}

int beideAn(struct pumpenStruktur * ptr)
{

}
