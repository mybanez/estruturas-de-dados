#include <stdio.h>
#include <stdlib.h>
#include <ConfigImpl.h>

///////////////////////////////////////////////////////////////////////////////

#ifdef comum_FILA_ESTAT

Fila * criar() {
    Fila * f = (Fila *)malloc(sizeof(Fila));      
    limpar(f);
    return f;
}      

void destruir(Fila * f) {
    if (f != NULL) {
       free(f);      
    }
}      

void limpar(Fila * f){
    f->ini = 0;
    f->fim = 0;
}

#endif
       
///////////////////////////////////////////////////////////////////////////////

#ifdef comum_FILA_ESTAT

int esta_vazia(Fila * f){
    return tamanho(f) == 0;
}

int primeiro(Fila * f){
    if (esta_vazia(f)){
		printf("Fila vazia\n");
		return -1;
    }
    return f->itens[f->ini];
}

#endif

#ifdef IMPL_FILA_ESTAT

int tamanho(Fila * f){
    return f->fim-f->ini;
}

int ultimo(Fila * f){
    if (esta_vazia(f)){
		printf("Fila vazia\n");
		return -1;
    }
    return f->itens[f->fim-1];
}

void imprimir(Fila * f) {
	int i;
    printf("\nFila: "); 
    for(i = f->ini; i < f->fim; i++) {     
		printf("%d ", f->itens[i]); 
    }
    printf("\n");     
}  

#endif

///////////////////////////////////////////////////////////////////////////////

#ifdef IMPL_FILA_ESTAT

void enfileirar(Fila * f, int v){
	int i, tam;
    if (tamanho(f) == TAM_MAX){
		printf("Fila cheia!\n");
		return;
    }
    if (f->fim == TAM_MAX) {
		tam = tamanho(f);
		for(i = 0; i < tam; i++) {
			f->itens[i] = f->itens[f->ini+i];
		}
		f->ini = 0;
		f->fim = tam;
	}
    f->itens[f->fim++] = v;
}

int desenfileirar(Fila * f){
	if (esta_vazia(f)){
		printf("Fila vazia!");
		return -1;
    }
    return f->itens[f->ini++];
}

#endif

///////////////////////////////////////////////////////////////////////////////
