#include <stdlib.h>
#include <Config.h>

////////////////////////////////////////////////////////////////////////////////

#ifdef buscar_PESQ_BIN_ITER

int maior (Arvore * arv) {
	No * raiz = arv->raiz;
	if (raiz != NULL) {
		while (raiz->dir != NULL) {
			raiz = raiz->dir;
		}
		return raiz->inf;
	}
	return -1;
}

void * _buscar(No * raiz, int inf) {
	while (raiz != NULL && raiz->inf != inf) {
		if (inf < raiz->inf) raiz = raiz->esq;        
		else raiz = raiz->dir;
	}
	return raiz;
}     

#ifdef ARVORE_INFO_EXT
Info * buscar(Arvore * arv, int inf) {
	No * no = (No *)_buscar(arv->raiz, inf);
	return no != NULL ? no->inf_ext : NULL;
}
#else
int buscar(Arvore * arv, int inf) {
	return _buscar(arv->raiz, inf) != NULL;
}
#endif

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef inserir_PESQ_BIN_ITER

No * _no; //Último nó criado

void _inserir(Arvore * arv, int inf, void * inf_ext) {
	No * pai = NULL, * raiz = arv->raiz;   
	while (raiz != NULL) {
	    pai = raiz;  
	    if (inf < raiz->inf) 
			raiz = raiz->esq;        
		else 
		if (inf > raiz->inf) 
			raiz = raiz->dir;
		else
			return;
	}
	raiz = _no = (No *)malloc(sizeof(No));
	raiz->inf = inf;
	raiz->esq = NULL;
	raiz->dir = NULL;
#ifdef ARVORE_INFO_EXT
	raiz->inf_ext = inf_ext;
#endif
	if (pai == NULL) {
	    arv->raiz = raiz;
	} else {
	    if (inf < pai->inf) pai->esq = raiz;        
	    else pai->dir = raiz;
	}     
} 

#ifdef ARVORE_INFO_EXT
void inserir(Arvore * arv, int inf, Info * inf_ext) {
	_inserir(arv, inf, inf_ext);
}
#else
void inserir(Arvore * arv, int inf) {
	_inserir(arv, inf, NULL);
}
#endif

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef remover_PESQ_BIN_ITER

No * _substituir_por_sucessor(No * raiz) {
	No * r_ant = raiz;        
	No * pai = raiz;
	raiz = raiz->dir;
	while (raiz->esq != NULL) {
	    pai = raiz;
	    raiz = raiz->esq;
	}
	if (pai == r_ant) pai->dir = raiz->dir;
	else pai->esq = raiz->dir; 
	raiz->esq = r_ant->esq;
	raiz->dir = r_ant->dir;
	return raiz;
}
 
void remover(Arvore * arv, int inf) {
	No * pai = NULL, * raiz = arv->raiz;
	while (raiz != NULL) {
		if (inf != raiz->inf) { 
			pai = raiz;    
			if (inf < raiz->inf) raiz = raiz->esq;
			else raiz = raiz->dir;
		} else {
			No * no = raiz;
			if (raiz->esq == NULL && raiz->dir == NULL) {
				raiz = NULL;
			}  
			else 
			if (raiz->esq != NULL && raiz->dir != NULL) {
				raiz = _substituir_por_sucessor(raiz);
			}
			else {
				if (raiz->esq != NULL) raiz = raiz->esq; 
				else raiz = raiz->dir;                    
			}  
			if (pai == NULL) {
				arv->raiz = raiz;
			} else {
				if (inf < pai->inf) pai->esq = raiz;        
				else pai->dir = raiz;
			}     
#ifdef ARVORE_INFO_EXT
			free(no->inf_ext);
#endif
			free(no);
			return;
		}
	}
} 

#endif

////////////////////////////////////////////////////////////////////////////////
