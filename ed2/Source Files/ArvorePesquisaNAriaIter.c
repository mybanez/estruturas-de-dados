#include <stdio.h>
#include <stdlib.h>
#include <Config.h>

////////////////////////////////////////////////////////////////////////////////

#ifdef IMPL_PESQ_NARIA_ITER

No * _criar_no(int inf);
void _inserir_chave_no(No * no, int pos_chv, int inf);
No * _remover_chave_no(No * no, int pos_chv);

void _trocar_sucessor_chave_no(No * no, int pos_chv) {
	No * pai = no;
	No * filho = no->filhos[pos_chv+1];
	while (filho->filhos[0] != NULL) {
		pai = filho;
		filho = filho->filhos[0];
	}
	no->chaves[pos_chv] = filho->chaves[0];
	pai->filhos[pai == no ? pos_chv+1 : 0] = 
		_remover_chave_no(filho, 0);
}

void _trocar_predecessor_chave_no(No * no, int pos_chv) {
	No * pai = no;
	No * filho = no->filhos[pos_chv];
	while (filho->filhos[filho->nfilhos-1] != NULL) {
		pai = filho;
		filho = filho->filhos[filho->nfilhos-1];
	}
	no->chaves[pos_chv] = filho->chaves[filho->nfilhos-2];
	pai->filhos[pai == no ? pos_chv : pai->nfilhos-1] = 
		_remover_chave_no(filho, filho->nfilhos-2);
}

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef buscar_PESQ_NARIA_ITER

int buscar(Arvore * arv, int inf) {
	No * raiz = arv->raiz;   
	while (raiz != NULL) {
	    int pos_chv = _buscar_chave_no(raiz, inf);
		if (pos_chv == raiz->nfilhos-1 || inf != raiz->chaves[pos_chv]) {
			raiz = raiz->filhos[pos_chv];
		} else {
			return 1;
		}
	}
	return 0;
}

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef inserir_PESQ_NARIA_ITER

void inserir(Arvore * arv, int inf) {
	No * pai = NULL, * raiz = arv->raiz;   
	int pos_chv; 
	while (raiz != NULL) {
		pai = raiz;
		pos_chv = _buscar_chave_no(raiz, inf);
		if (pos_chv == raiz->nfilhos-1 || inf != raiz->chaves[pos_chv]) {
			raiz = raiz->filhos[pos_chv];
		} else {
			return;
		}
	}
	if (pai != NULL) _inserir_chave_no(pai, pos_chv, inf); 
	else arv->raiz = _criar_no(inf);
}

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef remover_PESQ_NARIA_ITER

void remover(Arvore * arv, int inf) {
	No * pai = NULL, * raiz = arv->raiz;   
	int pos_pai;
	while (raiz != NULL) {
		int pos_chv = _buscar_chave_no(raiz, inf);
		if (pos_chv == raiz->nfilhos-1 || inf != raiz->chaves[pos_chv]) {
			pai = raiz;
			pos_pai = pos_chv;
			raiz = raiz->filhos[pos_chv];
		} else {
			if (pai == NULL) arv->raiz = _remover_chave_no(raiz, pos_chv);
			else pai->filhos[pos_pai] = _remover_chave_no(raiz, pos_chv);
			return;
		}
	}
}

#endif

////////////////////////////////////////////////////////////////////////////////
