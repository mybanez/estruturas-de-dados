#include <stdio.h>
#include <stdlib.h>
#include <ConfigImpl.h>

///////////////////////////////////////////////////////////////////////////////

#ifdef IMPL_LISTA_ENCAD

Lista * criar() {
    Lista * l = (Lista *)malloc(sizeof(Lista));   
    l->ini = NULL;
    l->fim = NULL;    
    l->tam = 0;
    return l;
}      

void destruir(Lista * l) {
    if (l != NULL) {
       limpar(l);   
       free(l);      
    }
}      

void limpar(Lista * l){
    No * aux = l->ini;
    while(aux != NULL) {
		No * aux2 = aux;        
		aux = aux->prox;
		free(aux2); 
    }
    l->ini = NULL;
    l->fim = NULL;    
    l->tam = 0;
}

#endif

///////////////////////////////////////////////////////////////////////////////

#ifdef IMPL_LISTA_ENCAD

No * _obter_no_pos(Lista * l, int p) {
    int i; No * aux = l->ini;
	for(i = 0; i < p; i++) {     
		aux = aux->prox;        
    }           
    return aux;
}

#endif

#ifdef comum_LISTA_ENCAD

int tamanho(Lista * l) {
	return l->tam;
}

int ler_pos(Lista * l, int p) {
    if (!_posicao_valida(l, p)) {
		printf("Posicao invalida!\n");
		return -1;        
    }   
	return _obter_no_pos(l, p)->info;
}

int buscar(Lista * l, int v) {
    int p = 0;
    No * aux = _obter_no_pos(l, 0);
    for(p = 0; p < tamanho(l); p++) {     
		if (aux->info == v) {
			return p;
		}
		aux = aux->prox;        
    }           
    return -1;
}

void imprimir(Lista * l) {
	int i; No * aux;
    printf("\nLista: "); 
    aux = _obter_no_pos(l, 0);
    for(i = 0; i < tamanho(l); i++) {     
		printf("%d ", aux->info); 
		aux = aux->prox;        
    }
    printf("\n");     
}  

#endif

///////////////////////////////////////////////////////////////////////////////

#ifdef comum_LISTA_ENCAD

void escrever_pos(Lista * l, int p, int v) {
    if (!_posicao_valida(l, p)) {
		printf("Posicao invalida!\n");
		return;        
    }   
	_obter_no_pos(l, p)->info = v;
}

#endif

#ifdef IMPL_LISTA_ENCAD

void inserir_pos(Lista * l, int p, int v) {
	No * ant, * aux;
	if (!(p == 0 || p == tamanho(l)) && !_posicao_valida(l, p)) {
		printf("Posicao invalida!\n");
		return;        
    }
	aux = (No *)malloc(sizeof(No));
	aux->info = v;
	if (p == 0) { //Inserir primeiro
		aux->prox = l->ini;
		l->ini = aux;
	} else {
		ant = _obter_no_pos(l, p-1);
		aux->prox = ant->prox;
		ant->prox = aux;
	}
	if (p == tamanho(l)) { //Inserir último
		l->fim = aux;
	}
	l->tam++;
}     

int remover_pos(Lista * l, int p) {
    int v;
	No * ant, * aux;
	if (!_posicao_valida(l, p)) {
		printf("Posicao invalida!\n");
		return -1;        
    }
	if (p == 0) { //Remover primeiro
		ant = NULL;
		aux = l->ini;
		l->ini = aux->prox;		
	} else {
		ant = _obter_no_pos(l, p-1);
		aux = ant->prox;
		ant->prox = aux->prox;
	}
	if (p == tamanho(l)-1) { //Remover último
		l->fim = ant;
	}
	v = aux->info;
	free(aux);
	l->tam--;
	return v;
}     

void remover_todos(Lista * l, int v) {
	No * ant = NULL, * aux = l->ini, * aux2;
	while (aux != NULL) {
        if (aux->info == v) {
			aux2 = aux;
			aux = aux->prox;
			if (aux2 == l->ini) { //Remover primeiro
				l->ini = aux;	
			} else {
				ant->prox = aux;
			}
			if (aux2 == l->fim) { //Remover último
				l->fim = ant;
			}
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
