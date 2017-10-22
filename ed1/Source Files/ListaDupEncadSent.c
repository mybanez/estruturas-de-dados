#include <stdio.h>
#include <stdlib.h>
#include <ConfigImpl.h>

#ifdef IMPL_LISTA_DUP_ENCAD_SENT

///////////////////////////////////////////////////////////////////////////////

Lista * criar() {
	Lista * l = (Lista *)malloc(sizeof(Lista));   
    l->ini = (No *)malloc(sizeof(No)); //sentinela ini
    l->fim = (No *)malloc(sizeof(No)); //sentinela fim
    l->ini->prox = l->fim;    
    l->ini->ant = NULL;
    l->fim->prox = NULL;    
    l->fim->ant = l->ini;
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
    l->fim->ant = l->ini;
    l->tam = 0;
}

///////////////////////////////////////////////////////////////////////////////

No * _obter_no_pos(Lista * l, int p) {
    int i, tam = tamanho(l); No * aux;
	if (p < tam/2) {
		aux = l->ini->prox;
		for(i = 0; i < p; i++) {     
			aux = aux->prox;        
		}
	} else {
		aux = l->fim->ant;
		for(i = tam-1; i > p; i--) {     
			aux = aux->ant;        
		}
	}
    return aux;
}

///////////////////////////////////////////////////////////////////////////////

void inserir_pos(Lista * l, int p, int v) {
    No * ant, * aux; 
	if (!(p == 0 || p == tamanho(l)) && !_posicao_valida(l, p)) {
		printf("Posicao invalida!\n");
		return;        
    }
	if (p == 0) { 
		ant = l->ini;
	} else {
		ant = _obter_no_pos(l, p-1);
	}
    aux = (No *)malloc(sizeof(No));
    aux->info = v;
	aux->prox = ant->prox;
    aux->ant = ant;
    ant->prox = aux;    
	aux->prox->ant = aux;
    l->tam++;
}     

int remover_pos(Lista * l, int p) {
    int v;  No * aux;
    if (!_posicao_valida(l, p)) {
		printf("Posicao invalida!");
		return -1;        
    }   
    aux = _obter_no_pos(l, p);
    aux->prox->ant = aux->ant;
    aux->ant->prox = aux->prox;    
	v = aux->info;
    free(aux);
    l->tam--;    
    return v;
}

void remover_todos(Lista * l, int v) {
	No * aux = l->ini->prox, * aux2;
	while (aux != l->fim) {
        if (aux->info == v) {
			aux2 = aux;
			aux->ant->prox = aux->prox;
			aux->prox->ant = aux->ant;
			aux = aux->prox;
			free(aux2);
			l->tam--;
		} else {
			aux = aux->prox;
		}
    }
}     
   
///////////////////////////////////////////////////////////////////////////////

#endif