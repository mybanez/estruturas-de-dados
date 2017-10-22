#include <stdio.h>
#include <stdlib.h>
#include <Config.h>

////////////////////////////////////////////////////////////////////////////////

#ifdef IMPL_PESQ_NARIA_REC

No * _criar_no(int inf);
void _inserir_chave_no(No * no, int pos_chv, int inf);
No * _remover_chave_no(No * no, int pos_chv);

No * _remover_menor(No * raiz, int * ptchvmenor);
No * _remover_maior(No * raiz, int * ptchvmaior);

void _trocar_sucessor_chave_no(No * no, int pos_chv) {
	int chvmenor;
	no->filhos[pos_chv+1] = _remover_menor(no->filhos[pos_chv+1], &chvmenor);
	no->chaves[pos_chv] = chvmenor;
}

void _trocar_predecessor_chave_no(No * no, int pos_chv) {
	int chvmaior;
	no->filhos[pos_chv] = _remover_maior(no->filhos[pos_chv], &chvmaior);
	no->chaves[pos_chv] = chvmaior;
}

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef buscar_PESQ_NARIA_REC

int _buscar(No * raiz, int inf) {
	if (raiz != NULL) {
	    int pos_chv = _buscar_chave_no(raiz, inf);
		if (pos_chv == raiz->nfilhos-1 || inf != raiz->chaves[pos_chv]) {
			return _buscar(raiz->filhos[pos_chv], inf);
		}
		return 1;
	}
	return 0;
}

int buscar(Arvore * arv, int inf) {
	return _buscar(arv->raiz, inf);
}

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef inserir_PESQ_NARIA_REC

void _inserir(No * raiz, int inf) {
	int pos_chv = _buscar_chave_no(raiz, inf);
	if (pos_chv == raiz->nfilhos-1 || inf != raiz->chaves[pos_chv]) {
		if (raiz->filhos[pos_chv] != NULL) {
			_inserir(raiz->filhos[pos_chv], inf);
		} else {
			_inserir_chave_no(raiz, pos_chv, inf);
		}
	}
}

void inserir(Arvore * arv, int inf) {
	if (arv->raiz != NULL) _inserir(arv->raiz, inf);
	else arv->raiz = _criar_no(inf);
} 

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef remover_PESQ_NARIA_REC

No * _remover_menor(No * raiz, int * ptchvmenor) {
	if (raiz->filhos[0] != NULL) {
		raiz->filhos[0] = _remover_menor(raiz->filhos[0], ptchvmenor);
	} else {
		*ptchvmenor = raiz->chaves[0];
		raiz = _remover_chave_no(raiz, 0);
	}
	return raiz;
}

No * _remover_maior(No * raiz, int * ptchvmaior) {
	if (raiz->filhos[raiz->nfilhos-1] != NULL) {
		raiz->filhos[raiz->nfilhos-1] = _remover_maior(raiz->filhos[raiz->nfilhos-1], ptchvmaior);
	} else {
		*ptchvmaior = raiz->chaves[raiz->nfilhos-2];
		raiz = _remover_chave_no(raiz, raiz->nfilhos-2);
	}
	return raiz;
}

No * _remover(No * raiz, int inf) {
	if (raiz != NULL) {
		int pos_chv = _buscar_chave_no(raiz, inf);
		if (pos_chv == raiz->nfilhos-1 || inf != raiz->chaves[pos_chv]) {
			raiz->filhos[pos_chv] = _remover(raiz->filhos[pos_chv], inf);
		} else {
			raiz = _remover_chave_no(raiz, pos_chv);
		}
	}
	return raiz;
}

void remover(Arvore * arv, int inf) {
	arv->raiz = _remover(arv->raiz, inf);
} 

#endif

////////////////////////////////////////////////////////////////////////////////