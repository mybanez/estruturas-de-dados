#include <stdio.h>
#include <stdlib.h>
#include <ConfigImpl.h>

#ifdef IMPL_LISTA_ESTAT

///////////////////////////////////////////////////////////////////////////////

Lista * criar() {
    Lista * l = (Lista *)malloc(sizeof(Lista));      
    l->ini = 0;
	l->fim = 0;
    return l;
}      

void destruir(Lista * l) {
    if (l != NULL) {
       free(l);      
    }
}      

void limpar(Lista * l) {
    l->ini = 0;
	l->fim = 0;
}

///////////////////////////////////////////////////////////////////////////////

int tamanho(Lista * l) {
    return l->fim - l->ini;     
}    

int ler_pos(Lista * l, int p) {
    if (!_posicao_valida(l, p)) {
		printf("Posicao invalida!\n");
		return -1;        
    }   
    return l->itens[l->ini+p];
}

int buscar(Lista * l, int v) {
    int i;
    for (i=l->ini; i < l->fim; i++) {
        if (l->itens[i] == v) {
			return i-l->ini;                
        }
    }       
    return -1;
}

void imprimir(Lista * l) {
    int i;
    printf("\nLista: "); 
	for(i = l->ini; i < l->fim; i++) {
		printf("%d ", l->itens[i]); 
    }
    printf("\n");     
}     
    
///////////////////////////////////////////////////////////////////////////////
    
void escrever_pos(Lista * l, int p, int v) {
    if (!_posicao_valida(l, p)) {
		printf("Posicao invalida!\n");
		return;        
    }   
    l->itens[l->ini+p] = v;
}

void inserir_pos(Lista * l, int p, int v) {
    int i, tam = tamanho(l);
    if (tam == TAM_MAX) {
		printf("Lista cheia!\n");
		return;                           
    }
    if (!(p == 0 || p == tam) && !_posicao_valida(l, p)) {
		printf("Posicao invalida!\n");
		return;        
    }
	if ((p > tam/2 && l->fim != TAM_MAX) || l->ini == 0) {
		for(i = l->fim; i > l->ini+p; i--) {
			l->itens[i] = l->itens[i-1]; 
		}
		l->fim++;
	} else {
		for(i = l->ini-1; i < l->ini+p; i++) {
			l->itens[i] = l->itens[i+1]; 
		}
		l->ini--;
	}
    l->itens[l->ini+p] = v;       
}     

int remover_pos(Lista * l, int p) {
    int i, v;
    if (!_posicao_valida(l, p)) {
		printf("Posicao invalida!\n");
		return -1;        
    }   
    v = l->itens[l->ini+p];
    if (p >= tamanho(l)/2) {
		for(i = l->ini+p; i < l->fim-1; i++) {
			l->itens[i] = l->itens[i+1]; 
		}
	    l->fim--;
	} else {
		for(i = l->ini+p; i > l->ini; i--) {
			l->itens[i] = l->itens[i-1]; 
		}
	    l->ini++;
	}
    return v;
}

void remover_todos(Lista * l, int v) {
	int i = l->ini, j;
	while (i < l->fim) {
        if (l->itens[i] == v) {
			for(j = i; j < tamanho(l)-1; j++) {
				l->itens[j] = l->itens[j+1]; 
			}
			l->fim--;
		} else {
			i++;
		}
    }
}

#endif

///////////////////////////////////////////////////////////////////////////////
