#include <stdio.h>
#include <stdlib.h>
#include <Config.h>

#ifdef comum_ARVORE

////////////////////////////////////////////////////////////////////////////////

Arvore * criar() {
    Arvore * arv = (Arvore *)malloc(sizeof(Arvore));
	_iniciar(arv);
    return arv;
}      

void destruir(Arvore * arv) {
    if (arv != NULL) {
	   limpar(arv);
       free(arv);      
    }
}

////////////////////////////////////////////////////////////////////////////////

#endif