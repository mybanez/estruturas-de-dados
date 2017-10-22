#include <stdio.h>
#include <stdlib.h>
#include <ConfigImpl.h>

#ifdef comum_LISTA

///////////////////////////////////////////////////////////////////////////////

Lista * clonar(Lista * l) {
	int i;
	Lista * cln = criar();
	for(i=0; i<tamanho(l); i++) {
		inserir_ultimo(cln, ler_pos(l, i));	
	}
	return(cln);
}

///////////////////////////////////////////////////////////////////////////////

int _posicao_valida(Lista * l, int p) {
	return p >= 0 && p < tamanho(l);
}

int esta_vazia(Lista * l) {
    return tamanho(l) == 0;     
}    

int primeiro(Lista * l) {
	return ler_pos(l, 0);
}

int ultimo(Lista * l) {
	return ler_pos(l, tamanho(l)-1);
}
    
///////////////////////////////////////////////////////////////////////////////

void inserir_primeiro(Lista * l, int v) {
    inserir_pos(l, 0, v);    
}     

void inserir_ultimo(Lista * l, int v) {
    inserir_pos(l, tamanho(l), v);    
}     

int remover_primeiro(Lista * l) {
    return remover_pos(l, 0);    
}     

int remover_ultimo(Lista * l) {
    return remover_pos(l, tamanho(l)-1);    
}     

int remover(Lista * l, int v) {
	return remover_pos(l, buscar(l, v));
}

///////////////////////////////////////////////////////////////////////////////

#endif