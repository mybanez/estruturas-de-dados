#include <stdio.h>
#include <stdlib.h>
#include <Config.h>

////////////////////////////////////////////////////////////////////////////////

#ifdef _iniciar_BIN_PNT

void _iniciar(Arvore * arv) {
	arv->raiz = NULL;
}

#endif

#ifdef comum_BIN_PNT

void _limpar(No * raiz) {
    if (raiz != NULL) {
		_limpar(raiz->esq);
		_limpar(raiz->dir);
		free(raiz);
    }
}

void limpar(Arvore * arv) {
	_limpar(arv->raiz);
	_iniciar(arv);
}

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef _imprimir_info_BIN_PNT

void _imprimir_info(int inf, void * inf_ext) {
	printf("%d ", inf);
}

#endif

#ifdef comum_BIN_PNT

int _altura(No * raiz) {
	if (raiz != NULL) {
		int ae = _altura(raiz->esq);
		int ad = _altura(raiz->dir);
		return 1 + (ae > ad ? ae : ad);
	}
	return -1;
}

int altura(Arvore * arv) {
	return _altura(arv->raiz);
}

void _imp_pre_ord(No * raiz) {
	if(raiz != NULL) {
#ifdef ARVORE_INFO_EXT
		_imprimir_info(raiz->inf, raiz->inf_ext);
#else
		_imprimir_info(raiz->inf, raiz);
#endif
		_imp_pre_ord(raiz->esq);
        _imp_pre_ord(raiz->dir);    
	}   
} 

void _imp_in_ord(No * raiz) {
    if(raiz != NULL) {
       _imp_in_ord(raiz->esq);
#ifdef ARVORE_INFO_EXT
	   _imprimir_info(raiz->inf, raiz->inf_ext);
#else
	   _imprimir_info(raiz->inf, raiz);
#endif
       _imp_in_ord(raiz->dir);
    }   
} 

void _imp_pos_ord(No * raiz) {
    if(raiz != NULL) {
       _imp_pos_ord(raiz->esq);
       _imp_pos_ord(raiz->dir);
#ifdef ARVORE_INFO_EXT
	   _imprimir_info(raiz->inf, raiz->inf_ext);
#else
	   _imprimir_info(raiz->inf, raiz);
#endif
    }   
} 

void imprimir(Arvore * arv) {
	_imp_in_ord(arv->raiz);
	printf("\n");
}

#endif

/////////////////////////////////////////////////////////////////

#ifdef comum_BIN_PNT

int _eh_folha(No * no) {
	return no != NULL && no->esq == NULL && no->dir == NULL;
}

#endif

///////////////////////////////////////////////////////////////////////////////