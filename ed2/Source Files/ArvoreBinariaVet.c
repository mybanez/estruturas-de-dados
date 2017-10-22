#include <stdio.h>
#include <stdlib.h>
#include <Config.h>

#ifdef IMPL_BIN_IMP

///////////////////////////////////////////////////////////////////////////////

void _iniciar(Arvore * arv) {
	int i;
	for (i=0; i<TAM_MAX; i++) {
		arv->nos[i] = NO_NULO;
	}
}

///////////////////////////////////////////////////////////////////////////////

void limpar(Arvore * arv) {
	_iniciar(arv);
}

///////////////////////////////////////////////////////////////////////////////

void _imprimir_info(int inf, void * inf_ext) {
	printf("%c ", inf);
}

void _imp_pre_ord(int nos[], int raiz) {
     if(nos[raiz] != NO_NULO && raiz < TAM_MAX) {
		 _imprimir_info(nos[raiz], NULL);
        _imp_pre_ord(nos, 2*raiz+1);
        _imp_pre_ord(nos, 2*raiz+2);    
     }   
} 

void _imp_in_ord(int nos[], int raiz) {
     if(nos[raiz] != NO_NULO && raiz < TAM_MAX) {
        _imp_in_ord(nos, 2*raiz+1);
		_imprimir_info(nos[raiz], NULL);
        _imp_in_ord(nos, 2*raiz+2);    
     }   
} 

void _imp_pos_ord(int nos[], int raiz) {
     if(nos[raiz] != NO_NULO && raiz < TAM_MAX) {
        _imp_pos_ord(nos, 2*raiz+1);
        _imp_pos_ord(nos, 2*raiz+2);
		_imprimir_info(nos[raiz], NULL);
     }   
} 

void imprimir(Arvore * arv) {
	_imp_in_ord(arv->nos, 0);
	printf("\n");
}

///////////////////////////////////////////////////////////////////////////////

#endif