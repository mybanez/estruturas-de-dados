#include <stdio.h>
#include <stdlib.h>
#include <Config.h>

#ifdef IMPL_GEN_PNT2

///////////////////////////////////////////////////////////////////////////////

void _limpar(No * raiz) {
	int i;
	for(i=0; i < MAX_FILHOS && raiz->filhos[i] != NULL; i++) {  
		_limpar(raiz->filhos[i]);
	}
	free(raiz);
}

void limpar(Arvore * arv) {
	if (arv->raiz != NULL) {
		_limpar(arv->raiz);
	}
	_iniciar(arv);
}

///////////////////////////////////////////////////////////////////////////////

int _altura(No * raiz, int ind_irmao) {
	if (raiz != NULL) {
		int ar = _altura(raiz->filhos[0], 1)+1, ai = -1;
		if (ind_irmao < MAX_FILHOS) {
			ai = _altura(raiz->pai->filhos[ind_irmao], ind_irmao+1);
		}
		return ar > ai ? ar : ai; 
	}
	return -1;
}

int altura(Arvore * arv) {
	return _altura(arv->raiz, MAX_FILHOS);
} 

void _imp_pre_ord(No * raiz, int ind_irmao) {
	if (raiz != NULL) {
		_imprimir_info(raiz->inf, raiz);
		_imp_pre_ord(raiz->filhos[0], 1);
		if (ind_irmao < MAX_FILHOS) {
			_imp_pre_ord(raiz->pai->filhos[ind_irmao], ind_irmao+1);
		}
	}
}

void _imp_in_ord(No * raiz, int ind_irmao) {
	if (raiz != NULL) {
		_imp_in_ord(raiz->filhos[0], 1);
		_imprimir_info(raiz->inf, raiz);
		if (ind_irmao < MAX_FILHOS) {
			_imp_in_ord(raiz->pai->filhos[ind_irmao], ind_irmao+1);
		}
	}
}

void _imp_pos_ord(No * raiz, int ind_irmao) {
	if (raiz != NULL) {
		_imp_pos_ord(raiz->filhos[0], 1);
		if (ind_irmao < MAX_FILHOS) {
			_imp_pos_ord(raiz->pai->filhos[ind_irmao], ind_irmao+1);
		}
		_imprimir_info(raiz->inf, raiz);
	}
}

void imprimir(Arvore * arv) {
	_imp_in_ord(arv->raiz, MAX_FILHOS);
	printf("\n");
}

///////////////////////////////////////////////////////////////////////////////

#endif