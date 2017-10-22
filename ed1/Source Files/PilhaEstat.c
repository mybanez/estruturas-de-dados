#include <stdio.h>
#include <stdlib.h>
#include <ConfigImpl.h>

#ifdef IMPL_PILHA_ESTAT

///////////////////////////////////////////////////////////////////////////////

Pilha * criar() {
    Pilha * p = (Pilha *)malloc(sizeof(Pilha));      
    p->tam = 0;
    return p;
}      

void destruir(Pilha * p) {
    if (p != NULL) {
       free(p);      
    }
}      

void limpar(Pilha * p){
    p->tam = 0;
}
       
///////////////////////////////////////////////////////////////////////////////

int tamanho(Pilha * p){
    return p->tam;
}

int esta_vazia(Pilha * p){
    return p->tam == 0;
}

int topo(Pilha * p){
    if (esta_vazia(p)){
       printf("Pilha vazia");
       return -1;
    }
    return p->itens[p->tam-1];
}

void imprimir(Pilha * p){
    int i;
	printf("[ ");
	for(i=0; i<tamanho(p); i++) {
		printf("%d ", p->itens[i]);
	}
	printf("]\n");
}

///////////////////////////////////////////////////////////////////////////////

void empilhar(Pilha * p, int v){
	if (p->tam == TAM_MAX){
		printf("Pilha cheia!");
		return;
	}
    p->itens[p->tam++] = v;     
}

int desempilhar(Pilha * p){
    if (esta_vazia(p)){
		printf("Pilha vazia");
		return -1;
    }
    return p->itens[--p->tam];
}

///////////////////////////////////////////////////////////////////////////////

int esta_desordenado(Pilha * p) {
	if (tamanho(p) > 2) {
		int i, ord; // ord = -1 (menor) | 0 (neutro) | 1 (maior) 
		for (i = 0, ord = 0; i < tamanho(p) - 1; i++) {
			if (p->itens[i] > p->itens[i + 1]) {
				if (ord == -1) {
					return 1;
				}
				ord = 1;
			}
			else {
				if (p->itens[i] < p->itens[i + 1]) {
					if (ord == 1) {
						return 1;
					}
					ord = -1;
				}
			}
		}
	}
	return 0;
}

#endif

void __testar() {
	Pilha * p = criar();
	empilhar(p, 0);
	empilhar(p, 1);
	empilhar(p, 2);
	empilhar(p, 3);
	empilhar(p, 5);
	empilhar(p, 5);
	printf("Ordenado? %s\n", esta_desordenado(p) ? "Nao" : "Sim");
	destruir(p);
	system("pause");
}
