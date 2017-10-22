#include <stdio.h>
#include <stdlib.h>
#include <Config.h>

#ifdef EXERCICIOS_BIN

///////////////////////////////////////////////////////////////

int _imprimir_pai;

void _imprimir_info(int inf, void * inf_ext) {
	No * no = (No *)inf_ext;
	_imprimir_pai == 0 || no->pai == NULL ? 
		printf(" %d", inf) : 
		printf(" %d(%d)", inf, no->pai->inf);
}

///////////////////////// QUESTÃO 3 ///////////////////////////

int _eh_pesq_bin(No * raiz, int * pme, int * pma) {
	if (raiz != NULL) {
		int ma_e, me_d;
		*pme = ma_e = raiz->inf;
		me_d = *pma = raiz->inf;
		return _eh_pesq_bin(raiz->esq, pme, &ma_e) &&
			   _eh_pesq_bin(raiz->dir, &me_d, pma) &&
			   raiz->inf >= ma_e &&
			   raiz->inf <= me_d;
	}
	return 1;
}

int eh_pesq_bin(Arvore * arv) {
	int me, ma;
	return _eh_pesq_bin(arv->raiz, &me, &ma);
}

///////////////////////// QUESTÃO 8 ///////////////////////////

/* Ver arquivos "ArvorePesquisaBinariaIter.c" e "ArvorePesquisaBinariaRec.c" */

////////////////////// QUESTÕES 9 E 14 ////////////////////////

void imprimir_caminho(Arvore * arv, int inf) {
	No * raiz = arv->raiz;
	int prof = 0;
	while (raiz != NULL && raiz->inf!= inf) {
		printf(" %d", raiz->inf);
		if (inf < raiz->inf) raiz = raiz->esq;        
		else raiz = raiz->dir;
		prof++;
	}
	if (raiz != NULL) {
	    printf(" %d", raiz->inf);
	}
	printf(", profundidade %d", prof);
}     

///////////////////////// QUESTÃO 10 ///////////////////////////

void _remover_todos(No * raiz) {
	if (raiz != NULL) {
		_remover_todos(raiz->esq);
		_remover_todos(raiz->dir);
		printf(" %d", raiz->inf);
		free(raiz);
	} 
}

void remover_todos(Arvore * arv) {
	_remover_todos(arv->raiz);
	arv->raiz = NULL; 
}

No * _remover_menores(No * raiz, int inf) {
	if (raiz != NULL) {
		if (raiz->inf < inf) {
			No * aux = raiz;
			_remover_todos(raiz->esq);
			raiz = _remover_menores(raiz->dir, inf);
			printf(" %d", aux->inf);
			free(aux);			
		} else {
			if (raiz->inf > inf) {
				raiz->esq = _remover_menores(raiz->esq, inf);
			} else {
				_remover_todos(raiz->esq);
				raiz->esq = NULL;
			}
		}
	}
	return raiz;
}

No * _remover_menores2(No * raiz, int inf) {
	if (raiz != NULL) {
		raiz->esq = _remover_menores2(raiz->esq, inf);
		if (raiz->inf < inf) {
			No * aux = raiz;
			raiz = _remover_menores2(raiz->dir, inf);
			printf(" %d", aux->inf);
			free(aux);			
		}
	}
	return raiz;
}

void remover_menores(Arvore * arv, int inf) {
	arv->raiz = _remover_menores2(arv->raiz, inf);
}

No * _remover_maiores(No * raiz, int inf) {
	if (raiz != NULL) {
		if (raiz->inf > inf) {
			No * aux = raiz;
			_remover_todos(raiz->dir);
			raiz = _remover_maiores(raiz->esq, inf);
			printf(" %d", aux->inf);
			free(aux);			
		} else {
			if (raiz->inf < inf) {
				raiz->dir = _remover_maiores(raiz->dir, inf);
			} else {
				_remover_todos(raiz->dir);
				raiz->dir = NULL;
			}
		}
	}
	return raiz;
}

void remover_maiores(Arvore * arv, int inf) {
	arv->raiz = _remover_maiores(arv->raiz, inf);
}

///////////////////////// QUESTÃO 12 ///////////////////////////

void imprimir_pred_suc(Arvore * arv) {
	No * pred, * suc, * raiz = arv->raiz;
	if (raiz != NULL) {
		pred = raiz->esq;
		if (pred == NULL) {
			printf(" -");
		} else {
			while (pred->dir != NULL) pred = pred->dir;
			printf(" %d", pred->inf);
		}
		suc = raiz->dir;
		if (suc == NULL) {
			printf(" -");
		} else {
			while (suc->esq != NULL) suc = suc->esq;
			printf(" %d", suc->inf);
		}
	} 
}

///////////////////////// QUESTÃO 13 ///////////////////////////

void _preencher_pai(No * raiz, No * pai) {
	if (raiz != NULL) {
		raiz->pai = pai;
		_preencher_pai(raiz->esq, raiz);
		_preencher_pai(raiz->dir, raiz);
	} 
}

void preencher_pai(Arvore * arv) {
	_preencher_pai(arv->raiz, NULL);
}

///////////////////////// QUESTÃO 15 ///////////////////////////

void _imprimir_tabulado(No * raiz, int num_tab, int tam_tab) {
	int n, desloc = num_tab*tam_tab;
	for (n=0; n<desloc; n++) {
	    printf(" ");
	}
	if (raiz != NULL) {
		printf("%d\n", raiz->inf);
		_imprimir_tabulado(raiz->dir, num_tab+1, tam_tab);
		_imprimir_tabulado(raiz->esq, num_tab+1, tam_tab);
	} else {
		printf("-\n");
	}	
}      

void imprimir_tabulado(Arvore * arv) {
  _imprimir_tabulado(arv->raiz, 0, 2);
}      

///////////////////////// QUESTÃO 16 ///////////////////////////

typedef struct contexto Contexto;

struct contexto {
	No * raiz;
	int alt_esq;
	int alt_dir;
} _pilha[100];

int _tp = -1;

void _empilhar(Contexto ctx) {
	_pilha[++_tp] = ctx;
}

Contexto _desempilhar() {
	return _pilha[_tp--];
}

Contexto _topo() {
	return _pilha[_tp];
}

Contexto * _pt_topo() {
	return _pilha+_tp;
}

int _vazia() {
	return _tp == -1;
}

int altura2(Arvore * arv) {
	int retornar=0, alt=-1;
	No * raiz = arv->raiz;
	Contexto ctx1 = {raiz, INT_MIN, INT_MIN}; 
	Contexto ctx2 = {NULL, INT_MIN, INT_MIN};
	Contexto * ptctx;
	if (raiz == NULL) {
		return 0;
	}
	_empilhar(ctx1);
	while (!_vazia()) {
	    ptctx = _pt_topo(); //Contexto em processamento
		if (ptctx->raiz != NULL) {
			if (ptctx->alt_esq == INT_MIN) { //Altura esq ainda não definida
  				if (retornar) { //Altura calculada
					ptctx->alt_esq = alt;
					retornar = 0;
				} else {
					ctx2.raiz = ptctx->raiz->esq;
					_empilhar(ctx2);
					continue;
				}
			}
			if (ptctx->alt_dir == INT_MIN) { //Altura dir ainda não definida
				if (retornar) { //Altura calculada
					ptctx->alt_dir = alt;
					retornar = 0;
				} else {
					ctx2.raiz = ptctx->raiz->dir;
					_empilhar(ctx2);
					continue;
   				}
			}
			if (ptctx->alt_esq > ptctx->alt_dir) alt = ptctx->alt_esq+1;
			else alt = ptctx->alt_dir+1;
	    } else {
			alt = -1;
		}  
		_desempilhar();
		retornar = 1;
	}
	return alt;
}      

//////////////////////// QUESTÕES DE PROVAS /////////////////////////

int _contar_menores(No * raiz, int v) {
	if (raiz != NULL) {
		if (v <= raiz->inf) return _contar_menores(raiz->esq, v);
		else return _contar_menores(raiz->esq, v) + 1 + _contar_menores(raiz->dir, v); 
	}
	return 0;
}

int contar_menores(Arvore * arv, int v) {
	return _contar_menores(arv->raiz, v);
}

int _remover_nivel(No * raiz, int n) {
	if (raiz != NULL) {
		_remover_nivel(raiz->esq, n-1);
		_remover_nivel(raiz->dir, n-1);
		if (n == 0) {
			raiz->esq = NULL;
			raiz->dir = NULL;
		} else {
			if (n < 0) {
				free(raiz);
			}
		}
	}
	return 0;
}

void remover_nivel(Arvore * arv, int n) {
	_remover_nivel(arv->raiz, n);
}

int _imprimir_menor_caminho_folha (No * raiz, int alt) {
	int ae, ad;
	if (raiz != NULL) {
		ad = _imprimir_menor_caminho_folha(raiz->dir, alt-1)+1;
		if (ad == alt && ad != 0) {
			printf(" %d", raiz->inf);
			return ad;
		}
		ae = _imprimir_menor_caminho_folha(raiz->esq, alt-1)+1;
		if (ae == alt) {
			printf(" %d", raiz->inf);
			return ae;
		}
		if (ae != 0 && ad != 0) {
			return ae < ad ? ae : ad;
		} else {
			return ae != 0 ? ae : ad;
		}
	}
	return -1;
}

void imprimir_menor_caminho_folha (Arvore * arv) {
	_imprimir_menor_caminho_folha(arv->raiz, _imprimir_menor_caminho_folha(arv->raiz, -1));
}

#define ALT_INV -2

int _eh_completa (No * raiz) {
	if (raiz != NULL) {
		int ae = _eh_completa(raiz->esq);
		int ad = _eh_completa(raiz->dir);
		if (ae != ad || ae == ALT_INV || ae == ALT_INV) {
			return ALT_INV;
		}
		return 1 + (ae > ad ? ae : ad);
	}
	return -1;
}

int eh_completa (Arvore * arv) {
	return _eh_completa(arv->raiz) != ALT_INV;
}

/////////////////////////////////////////////////////////////////////

////////////////// MONTAGEM DA ÁRVORE DE TESTE //////////////////
//															   //	
//							   |20|							   //
//							 /     \						   //
//						   |10|    |30|						   //
//						   /       /   \ 					   //
//						 |5|    |23|   |46|					   //
//						   \								   //	
//						   |8|								   //
//															   //
/////////////////////////////////////////////////////////////////

extern No * _no; //Último nó criado

void _montar(Arvore * arv) {
	inserir(arv, 20);
	inserir(arv, 10);
	inserir(arv, 30);
	inserir(arv, 5);
	inserir(arv, 23);
	inserir(arv, 46);
	inserir(arv, 8);
	//inserir(arv, 28);
	//_no->info = 4;
}

void _testar() {
	Arvore * arv = criar();
	_montar(arv);

	if (!eh_pesq_bin(arv)) {
		printf("Não é árvore de pesquisa binária\n");
	} else {
	    printf("Qtd de nós menores que 40: %d\n", contar_menores(arv, 40));
		
		printf("Árvore tabulada:\n");
		imprimir_tabulado(arv);

		preencher_pai(arv);
		printf("Árvore com pais:");
		_imprimir_pai = 1;
		imprimir(arv);
		_imprimir_pai = 0;
		printf("\n");

		printf("Altura: %d\n", altura2(arv));

		printf("É completa? %s\n", eh_completa(arv) ? "Sim" : "Não");

		printf("Caminho para 8:");
		imprimir_caminho(arv, 8);
		printf("\n");

		printf("Caminho para folha mais próxima:");
		imprimir_menor_caminho_folha(arv);
		printf("\n");

		printf("Predecessor e sucessor da raiz:");
		imprimir_pred_suc(arv);
		printf("\n");

		printf("Remover menores que 24:");
		remover_menores(arv, 24);
		printf("\n");

		printf("Remover todos:");
		remover_todos(arv);
		printf("\n");

		printf("Árvore resultante:");
		imprimir(arv);
		printf("\n");

		_montar(arv);

		printf("Remover maiores que 8:");
		remover_maiores(arv, 8);
		printf("\n");

		printf("Árvore resultante:");
		imprimir(arv);
		printf("\n");

	    limpar(arv);
		_montar(arv);

		printf("Remover a partir nível 1:\n");
		remover_nivel(arv, 1);

		printf("Árvore resultante:");
		imprimir(arv);
		printf("\n");
	}

	destruir(arv);

	system("pause");
}

///////////////////////////////////////////////////////////////

#endif