#include <stdio.h>
#include <stdlib.h>
#include <ConfigImpl.h>

///////////////////////////////////////////////////////////////////////////////

#ifdef IMPL_LISTA_ENCAD_SENT

Lista * criar() {
    Lista * l = (Lista *)malloc(sizeof(Lista));   
    l->ini = (No *)malloc(sizeof(No)); //sentinela ini
    l->fim = (No *)malloc(sizeof(No)); //sentinela fim
    l->ini->prox = l->fim;    
    l->fim->prox = NULL;    
    l->tam = 0;
    return l;
}      

void limpar(Lista * l){
    No * aux = l->ini->prox;
    while(aux != l->fim) {
		No * aux2 = aux;        
		aux = aux->prox;
		free(aux2); 
    }
    l->ini->prox = l->fim;    
    l->tam = 0;
}

#endif

#ifdef comum_LISTA_ENCAD_SENT

void destruir(Lista * l) {
    if (l != NULL) {
		limpar(l);   
		free(l->ini);
		free(l->fim);       
		free(l);      
    }
}      

#endif

///////////////////////////////////////////////////////////////////////////////

#ifdef IMPL_LISTA_ENCAD_SENT

No * _obter_no_pos(Lista * l, int p) {
    int i; No * aux = l->ini->prox;
	for(i = 0; i < p; i++) {     
		aux = aux->prox;        
    }           
    return aux;
}

#endif

///////////////////////////////////////////////////////////////////////////////

#ifdef IMPL_LISTA_ENCAD_SENT

void inserir_pos(Lista * l, int p, int v) {
    No * ant, * aux;
	if (!(p == 0 || p == tamanho(l)) && !_posicao_valida(l, p)) {
		printf("Posicao invalida!\n");
		return;        
    }
	aux = (No *)malloc(sizeof(No));
	aux->info = v;
	if (p == 0) { 
		ant = l->ini;
	} else {
		ant = _obter_no_pos(l, p-1);
	}
	aux->prox = ant->prox;
	ant->prox = aux;
	l->tam++;
}     

int remover_pos(Lista * l, int p) {
    int v;
    No * ant, * aux;
	if (!_posicao_valida(l, p)) {
		printf("Posicao invalida!\n");
		return -1;        
    }
	if (p == 0) { 
		ant = l->ini;
	} else {
		ant = _obter_no_pos(l, p-1);
	}
	aux = ant->prox;
	ant->prox = aux->prox;
	v = aux->info;
	free(aux);
	l->tam--;
	return v;
}     

void remover_todos(Lista * l, int v) {
	No * ant = l->ini, * aux = l->ini->prox, * aux2;
	while (aux != l->fim) {
        if (aux->info == v) {
			aux2 = aux;
			aux = aux->prox;
			ant->prox = aux;
			free(aux2);
			l->tam--;
		} else {
			ant = aux;
			aux = aux->prox;
		}
    }
}  

#endif

///////////////////////////////////////////////////////////////////////////////
