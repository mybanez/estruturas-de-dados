#include <stdio.h>
#include <stdlib.h>
#include <Config.h>

///////////////////////////////////////////////////////////////////////////////

#ifdef comum_GEN_PNT

void _iniciar(Arvore * arv) {
	arv->raiz = NULL;
}

#endif

#ifdef IMPL_GEN_PNT

void _limpar(No * raiz) {
    if (raiz != NULL) {
		_limpar(raiz->irmao);
		_limpar(raiz->filho);
		free(raiz);
    }
}

void limpar(Arvore * arv) {
	_limpar(arv->raiz);
	_iniciar(arv);
}

#endif

///////////////////////////////////////////////////////////////////////////////

#ifdef comum_GEN_PNT

void _imprimir_info(int inf, void * inf_ext) {
	printf("%c ", inf);
}

#endif

#ifdef IMPL_GEN_PNT

int _altura(No * raiz) {
	if (raiz != NULL) {
		int ar = _altura(raiz->filho)+1;
		int ai = _altura(raiz->irmao);
		return ar > ai ? ar : ai; 
	}
	return -1;
}

int altura(Arvore * arv) {
	return _altura(arv->raiz);
} 

void _imp_pre_ord(No * raiz) {
	if(raiz != NULL) {
		_imprimir_info(raiz->inf, raiz);
	    _imp_pre_ord(raiz->filho);
		_imp_pre_ord(raiz->irmao);
	}   
} 

void _imp_in_ord(No * raiz) {
    if(raiz != NULL) {
		_imp_in_ord(raiz->filho);
		_imprimir_info(raiz->inf, raiz);
		_imp_in_ord(raiz->irmao);
    }   
} 

void _imp_pos_ord(No * raiz) {
    if(raiz != NULL) {
		_imp_pos_ord(raiz->filho);
		_imp_pos_ord(raiz->irmao);
		_imprimir_info(raiz->inf, raiz);
    }   
} 

void imprimir(Arvore * arv) {
	_imp_in_ord(arv->raiz);
	printf("\n");
}

#endif

///////////////////////////////////////////////////////////////////////////////
