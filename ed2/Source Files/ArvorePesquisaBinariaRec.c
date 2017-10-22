#include <stdlib.h>
#include <Config.h>

////////////////////////////////////////////////////////////////////////////////

#ifdef buscar_PESQ_BIN_REC

void * _buscar(No * raiz, int inf) {
	if (raiz != NULL) {
		if (inf < raiz->inf) return _buscar(raiz->esq, inf);        
		if (inf > raiz->inf) return _buscar(raiz->dir, inf);
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

#ifdef inserir_PESQ_BIN_REC

No * _no; //Último nó criado

No * _criar_no(int inf, void * inf_ext) {
	No * no = _no = (No *)malloc(sizeof(No));
	no->inf = inf;
	no->esq = NULL;
	no->dir = NULL;
#ifdef ARVORE_INFO_EXT
	no->inf_ext = inf_ext;
#endif
	return no;
}

No * _inserir(No * raiz, int inf, void * inf_ext) {
	if (raiz != NULL) {
		if (inf < raiz->inf) {
			raiz->esq = _inserir(raiz->esq, inf, inf_ext);
		} else
		if (inf > raiz->inf) { 
			raiz->dir = _inserir(raiz->dir, inf, inf_ext);
		} 
	} else {
		raiz = _criar_no(inf, inf_ext);
	}     
	return raiz;
}  

#ifdef ARVORE_INFO_EXT
void inserir(Arvore * arv, int inf, Info * inf_ext) {
	arv->raiz = _inserir(arv->raiz, inf, inf_ext);
}
#else
void inserir(Arvore * arv, int inf) {
	arv->raiz = _inserir(arv->raiz, inf, NULL);
}
#endif

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef remover_PESQ_BIN_REC

No * _remover_menor(No * raiz, No * * ptmenor) {
	if(raiz->esq != NULL) {
		raiz->esq = _remover_menor(raiz->esq, ptmenor);
	} else {
		No * menor = raiz;
		raiz = raiz->dir;
		menor->dir = NULL;
		*ptmenor = menor;
	}
	return raiz;       
}     

No * _substituir_por_sucessor(No * raiz) {
	No * r_ant = raiz;        
	r_ant->dir = _remover_menor(r_ant->dir, &raiz);
	raiz->esq = r_ant->esq;
	raiz->dir = r_ant->dir;
	return raiz;
}
 
No * _destruir_no(No * raiz) {
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
#ifdef ARVORE_INFO_EXT
	free(no->inf_ext);
#endif
	free(no);
	return raiz;
}     

No * _remover(No * raiz, int inf) {
	if (raiz != NULL) {
		if (inf < raiz->inf) {
			raiz->esq = _remover(raiz->esq, inf);
		} else 
		if (inf > raiz->inf) {
			raiz->dir = _remover(raiz->dir, inf);
		} else {
			raiz = _destruir_no(raiz);
		}
	}
	return raiz;
}  

void remover(Arvore * arv, int inf) {
	arv->raiz = _remover(arv->raiz, inf);
} 

#endif

////////////////////////////////////////////////////////////////////////////////
