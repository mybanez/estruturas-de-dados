#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ConfigImpl.h>

#ifdef EXERCICIOS_FILA

////////////////////////////////// QUESTÃO 2 //////////////////////////////////
/*
struct fila {
	Pilha * pe;
	Pilha * pd;
};

Fila * criar() {
	Fila * f = (Fila *)malloc(sizeof(Fila));      
    f->pe = criar_pilha();
	f->pd = criar_pilha();
    return f;
}

void enfileirar(Fila * f, int v){
	while(!esta_vazia_pilha(f->pd)) {
		empilhar(f->pe, desempilhar(f->pd));
	}
	empilhar(f->pe, v);
}

int desenfileirar(Fila * f){
	while(!esta_vazia_pilha(f->pe)) {
		empilhar(f->pd, desempilhar(f->pe));
	}
	return desempilhar(f->pd);
}
*/
////////////////////////////////// QUESTÃO 3 //////////////////////////////////

void ordenar(Fila * f) {
	int i, v, tam = tamanho(f), troca = 1;
	while(troca) {
		troca = 0;
		v = desenfileirar(f);
		for (i=1; i<tam; i++) {
			if (v < primeiro(f)) { 
				enfileirar(f, v);
				v = desenfileirar(f);
			} else {
				enfileirar(f, desenfileirar(f));
				troca = 1;
			}
		}
		enfileirar(f, v);
	}
}

///////////////////////////// QUESTÕES DE PROVAS //////////////////////////////

#ifdef IMPL_FILA_ESTAT

void furar(Fila * f, int p, int v) {
    int i;
    if (tamanho(f) == TAM_MAX) {
		printf("Fila cheia!\n");
		return;                           
    }
    if (p < 1 || p > tamanho(f)) {
		printf("Posicao invalida!\n");
		return;        
    }   
	if (f->fim == TAM_MAX) {
		//Deslocar elementos
		for(i=0; i < tamanho(f); i++) {
			f->itens[i] = f->itens[i+f->ini]; 
		}
		f->ini = 0;
		f->fim = i;
	}
	p = f->ini + p - 1;
	for(i = f->fim; i > p; i--) {
		f->itens[i] = f->itens[i-1];
	}
	f->itens[i] = v;
	f->fim++;   
}

void furar_meio(Fila * f, int v) {
    int i, p;
    if (tamanho(f) == TAM_MAX) {
		printf("Fila cheia!\n");
		return;                           
    }
	p = f->ini + tamanho(f)/2;
	if (f->fim == TAM_MAX) {
		//Deslocar elementos p/ esquerda
		f->ini--;
		for(i=f->ini; i < p; i++) {
			f->itens[i] = f->itens[i+1]; 
		}
	} else {
		//Deslocar elementos p/ direita
		for(i=f->fim; i > p; i--) {
			f->itens[i] = f->itens[i-1]; 
		}
		f->fim++;
	}
	f->itens[p] = v;
}

#endif 

#ifdef IMPL_FILA_ESTAT_CIRC

int desenfileirar_maior(Fila * f) {
    int p, pm, m;
	if (esta_vazia(f)){
		printf("Fila vazia!");
		return -1;
    }
    p = f->ini;
	pm = p;
	m = f->itens[pm];
	while(p != f->fim) {
		p = (p + 1) % TAM_MAX;
		if (m < f->itens[p]) {
			pm = p;
			m = f->itens[pm];
		}
	}
	p = pm;
	f->fim = f->fim == 0 ? TAM_MAX-1 : f->fim-1;
	while(p != f->fim) {
		f->itens[p] = f->itens[(p + 1) % TAM_MAX];
		p = (p + 1) % TAM_MAX;
	}
	return m;
}

void desenfileirar_maiores_valor(Fila * f, int v) {
    int i, j;
	for(i = f->ini, j=f->fim; i != f->fim; i=(i+1)%TAM_MAX) {
		if (f->itens[i] <= v) {
			f->itens[j] = f->itens[i];
			j = (j+1) % TAM_MAX;
		}
	}
	f->ini = f->fim;
	f->fim = j;
}

void desenfileirar_faixa(Fila * f, int p, int q) {
	int i, j;
	if (p > q || p < 0 || p >= tamanho(f) || q < 0 || q >= tamanho(f)) {
		printf("Faixa inválida!\n");
		return;
	}
	i = (f->ini + p) % TAM_MAX;
	j= (f->ini + q + 1) % TAM_MAX;
	while(j != f->fim) {
		f->itens[i] = f->itens[j];
		i = (i+1) % TAM_MAX;
		j = (j+1) % TAM_MAX;
	}
	f->fim = i;
}

#endif 

///////////////////////////////////////////////////////////////////////////////

void _testar() {
	int i;
	Fila * f; 
	
	f = criar();
	enfileirar(f, 11);
	enfileirar(f, 2);
	enfileirar(f, 4);
	enfileirar(f, 5);
	furar(f, 3, 3);
	//desenfileirar(f);
	//desenfileirar(f);
	enfileirar(f, 10);
	enfileirar(f, 9);
	enfileirar(f, 8);
	enfileirar(f, 7);
	//desenfileirar_maior(f);
    ordenar(f);
	imprimir(f);
	furar_meio(f, 0);
	imprimir(f);
	desenfileirar(f);
	imprimir(f);
	furar_meio(f, 1);
	imprimir(f);
	//desenfileirar_faixa(f, 2, 5);
	//imprimir(f);
	destruir(f);

	printf("\n");

	system("pause");
}

#endif
