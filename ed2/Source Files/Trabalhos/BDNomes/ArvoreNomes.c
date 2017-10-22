#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Config.h>

#ifdef TRABALHO_BIN_1

////////////////////////////////////////////////////////////////////////////////

void _imprimir_no(No * no) {
	printf("\n%s", no->inf);
}

void _imprimir_iniciados(No * raiz, char * inf) {
	if (raiz != NULL) {
		int cmp = strcmp(raiz->inf, inf);
		if (cmp >= 0) {
			if (strstr(raiz->inf, inf) == raiz->inf) {
				_imprimir_iniciados(raiz->esq, inf);
				_imprimir_no(raiz);
				_imprimir_iniciados(raiz->dir, inf);
			} else {
				_imprimir_iniciados(raiz->esq, inf);
			}
		} else {
			_imprimir_iniciados(raiz->dir, inf);
		}
	}
}

void imprimir_nomes_pref(Arvore * arv, char * inf) {
	_imprimir_iniciados(arv->raiz, inf);
}
 
////////////////////////////////////////////////////////////////////////////////

void inserir_nome(Arvore * arv, char * inf) {
	No * pai = NULL, * raiz = arv->raiz;   
	while (raiz != NULL) {
		int cmp = strcmp(raiz->inf, inf);
		pai = raiz;  
	    if (cmp > 0) 
			raiz = raiz->esq;        
		else 
		if (cmp < 0) 
			raiz = raiz->dir;
		else
			return;
	}
	raiz = (No *)malloc(sizeof(No));
	strcpy(raiz->inf, inf);
	raiz->esq = NULL;
	raiz->dir = NULL;
	if (pai == NULL) {
	    arv->raiz = raiz;
	} else {
	    if (strcmp(pai->inf, inf) > 0) pai->esq = raiz;        
	    else pai->dir = raiz;
	}     
} 

////////////////////////////////////////////////////////////////////////////////

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

No * _remover(No * raiz, char * inf) {
	if (raiz != NULL) {
		int cmp = strcmp(raiz->inf, inf);
		if (cmp > 0) {
			raiz->esq = _remover(raiz->esq, inf);
		} else 
		if (cmp < 0) {
			raiz->dir = _remover(raiz->dir, inf);
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
			free(no);
		}
	}
	return raiz;
}  

void remover_nome(Arvore * arv, char * inf) {
	arv->raiz = _remover(arv->raiz, inf);
}

No * _remover_iniciados(No * raiz, char * inf) {
	if (raiz != NULL) {
		int cmp = strcmp(raiz->inf, inf);
		if (cmp >= 0) {
			if (strstr(raiz->inf, inf) == raiz->inf) {
				raiz->esq = _remover_iniciados(raiz->esq, inf);
				raiz->dir = _remover_iniciados(raiz->dir, inf);
				raiz = _remover(raiz, raiz->inf);
			} else {
				raiz->esq = _remover_iniciados(raiz->esq, inf);
			}
		} else {
			raiz->dir = _remover_iniciados(raiz->dir, inf);
		}
	}
	return raiz;
}

void remover_nomes_pref(Arvore * arv, char * inf) {
	arv->raiz = _remover_iniciados(arv->raiz, inf);
}

////////////////////////////////////////////////////////////////////////////////

#endif