#ifndef pumpendef
#define pumpendef
   
enum pumpenStatus{keine,eine,zwei};

struct pumpenStruktur{
    enum pumpenStatus status;                   
    char sensoren;                     
    char pumpen;              
    void* statusWechsel;                   
};

void* pumpenCreate();     
void pumpenDelete(void *);  
int pumpenFunktion (struct pumpenStruktur *);

typedef int (*pumpenFunktionen)(struct pumpenStruktur * id); 

int beideAus (struct pumpenStruktur * id);
int eineAn(struct pumpenStruktur * id);
int beideAn(struct pumpenStruktur * id);

static pumpenFunktionen func_array_pump[] = {beideAus, eineAn, beideAn};     

#endif