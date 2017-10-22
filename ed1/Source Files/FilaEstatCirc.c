#include <stdio.h>
#include <ConfigImpl.h>

#ifdef IMPL_FILA_ESTAT_CIRC

///////////////////////////////////////////////////////////////////////////////

int tamanho(Fila * f){
    return (TAM_MAX + (f->fim - f->ini)) % TAM_MAX;
}

int ultimo(Fila * f){
    if (esta_vazia(f)){
		printf("Fila vazia\n");
		return -1;
    }
    return f->itens[f->fim == 0 ? TAM_MAX-1 : f->fim-1];
}

void imprimir(Fila * f) {
	int i;
    printf("\nFila: "); 
    for(i = f->ini; i != f->fim; i=(i+1)%TAM_MAX) {     
		printf("%d ", f->itens[i]); 
    }
    printf("\n");     
}  

///////////////////////////////////////////////////////////////////////////////

void enfileirar(Fila * f, int v){
    if (tamanho(f) == TAM_MAX-1){
		printf("Fila cheia!\n");
		return;
    }
	f->itens[f->fim] = v;     
	f->fim = (f->fim + 1) % TAM_MAX;
}

int desenfileirar(Fila * f){
	int v;
    if (esta_vazia(f)){
		printf("Fila vazia!");
		return -1;
    }
    v = f->itens[f->ini];
    f->ini = (f->ini + 1) % TAM_MAX; // incremento "circular"
    return v;
}

///////////////////////////////////////////////////////////////////////////////

#endif
