#include <stdlib.h>
#include <Config.h>

////////////////////////////////////////////////////////////////////////////////

#ifdef inserir_PESQ_BIN_REC2

No * _no; //Último nó criado

void _criar_no(No * * ptraiz, int inf, void * inf_ext) {
	No * no = _no = (No *)malloc(sizeof(No));
	no->inf = inf;
	no->esq = NULL;
	no->dir = NULL;
#ifdef ARVORE_INFO_EXT
	no->inf_ext = inf_ext;
#endif
	*ptraiz = no;
}

void _inserir(No * * ptraiz, int inf, void * inf_ext) {
	No * raiz = *ptraiz;
	if (raiz != NULL) {
		if (inf < raiz->inf) {
			_inserir(&raiz->esq, inf, inf_ext);
		} else
		if (inf > raiz->inf) { 
			_inserir(&raiz->dir, inf, inf_ext);
		} 
	} else {
		_criar_no(ptraiz, inf, inf_ext);
	}     
}  

#ifdef ARVORE_INFO_EXT
void inserir(Arvore * arv, int inf, Info * inf_ext) {
	_inserir(&arv->raiz, inf, inf_ext);
}
#else
void inserir(Arvore * arv, int inf) {
	_inserir(&arv->raiz, inf, NULL);
}
#endif

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef remover_PESQ_BIN_REC2

void _remover_menor(No * * ptraiz, No * * ptmenor) {
	No * raiz = *ptraiz;
	if(raiz->esq != NULL) {
		_remover_menor(&raiz->esq, ptmenor);
	} else {
		*ptmenor = raiz;
		raiz = raiz->dir;
		(*ptmenor)->dir = NULL;
		*ptraiz = raiz;
	}
}     

void _substituir_por_sucessor(No * * ptraiz) {
	No * r_ant = *ptraiz;
	_remover_menor(&r_ant->dir, ptraiz);
	(*ptraiz)->esq = r_ant->esq;
	(*ptraiz)->dir = r_ant->dir;
}
 
void _destruir_no(No * * ptraiz) {
	No * raiz = *ptraiz;
	No * no = raiz;
	if (raiz->esq == NULL && raiz->dir == NULL) {
	    raiz = NULL;
	}  
	else 
	if (raiz->esq != NULL && raiz->dir != NULL) {
		_substituir_por_sucessor(&raiz);
	}
	else {
		if (raiz->esq != NULL) raiz = raiz->esq; 
		else raiz = raiz->dir;                    
	}  
#ifdef ARVORE_INFO_EXT
	free(no->inf_ext);
#endif
	free(no);
	*ptraiz = raiz;
}     

void _remover(No * * ptraiz, int inf) {
	No * raiz = *ptraiz;
	if (raiz != NULL) {
		if (inf < raiz->inf) {
			_remover(&raiz->esq, inf);
		} else 
		if (inf > raiz->inf) {
			_remover(&raiz->dir, inf);
		} else {
			_destruir_no(ptraiz);
		}
	}
}  

void remover(Arvore * arv, int inf) {
	_remover(&arv->raiz, inf);
} 

#endif

////////////////////////////////////////////////////////////////////////////////
