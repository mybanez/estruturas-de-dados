#include <stdio.h>
#include <stdlib.h>
#include <Config.h>

#ifdef EXERCICIOS_PESQ_RB

/////////////////////////// QUESTÃO 4 ///////////////////////////

void _colorir(No * raiz) {
	No * pai;
	if (!_eh_folha(raiz)) {
		_colorir(raiz->esq);
		_colorir(raiz->dir);
		pai = raiz->pai;
		if (pai == NULL) {
			raiz->cor = 'P';
		} else { 
			if (raiz->cor == 'V' && pai->cor == 'V') {
				No * avo = pai->pai;
				if (avo != NULL) {
					avo->cor = 'V';
					avo->esq->cor = 'P';
					avo->dir->cor = 'P';
				}
			}
		}  
	} else {
		raiz->cor = 'P';
	}
}

void colorir(Arvore * arv) {
	_colorir(arv->raiz);
}

/////////////////////////// QUESTÃO 5 ///////////////////////////

int _verificar_altura_preto(No * raiz) {
	if (!_eh_folha(raiz)) {
		int ap_e = _verificar_altura_preto(raiz->esq);
		int ap_d = _verificar_altura_preto(raiz->dir);
		if (ap_e != ap_d) {
			printf("\nAltura de preto violada no nó %d", raiz->inf);
			return -1;
		}
		return raiz->cor == 'P' ? ap_e + 1 : ap_e;
	}
	return 0;
}

int verificar_altura_preto(Arvore * arv) {
	return _verificar_altura_preto(arv->raiz);
}

/////////////////////////// QUESTÃO 6 ///////////////////////////

int verificar_RB(Arvore * arv);

/////////////////////////////////////////////////////////////////

///////////////// ÁRVORE DE TESTE //////////////////
//												  //	
//					   |20|						  //
//					 /     \					  //
//				   |10|    |30|					  //
//				  /       /    \ 				  //
//				 |5|    |23|  |46|				  //
//						    \					  //	
//					        |28|				  //
//												  //
////////////////////////////////////////////////////

int _ind = 0;
No * _nos[15];

No * _iniciar_RB(No * raiz, No * pai) {
	if (raiz != NULL) {
		_nos[_ind++] = raiz;
		raiz->pai = pai;
		raiz->esq = _iniciar_RB(raiz->esq, raiz);
		raiz->dir = _iniciar_RB(raiz->dir, raiz);
	} else {
		raiz = (No *)malloc(sizeof(No));
		raiz->esq = NULL;
		raiz->dir = NULL;
	}		
	raiz->cor = 'V';
	return raiz;
}

void _testar() {
	Arvore * arv = criar();

	//Monta arvore de teste
	inserir(arv, 20);
	inserir(arv, 10);
	inserir(arv, 30);
	inserir(arv, 5);
	inserir(arv, 23);
	inserir(arv, 46);
	inserir(arv, 28);
	_iniciar_RB(arv->raiz, NULL);

	printf("Árvore original: ");
	imprimir(arv);
	printf("\n");

	colorir(arv);
	//_nos[4]->cor = 'P';

	printf("Árvore colorida: ");
	imprimir(arv);
	printf("\n");

	printf("Altura: %d\n", verificar_RB(arv));

	destruir(arv);

	system("pause");
}

#endif