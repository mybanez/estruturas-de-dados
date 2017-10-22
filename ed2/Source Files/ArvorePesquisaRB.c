#include <stdio.h>
#include <stdlib.h>
#include <Config.h>

////////////////////////////////////////////////////////////////////////////////

#ifdef IMPL_PESQ_RB

No * _criar_folha() {
	No * folha = (No *)malloc(sizeof(No));
	folha->cor = 'P';
	folha->esq = NULL;
	folha->dir = NULL;
	return folha;
}

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef _iniciar_PESQ_RB

void _iniciar(Arvore * arv) {
	arv->raiz = _criar_folha();
}

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef _imprimir_info_PESQ_RB

void _imprimir_info(int inf, void * inf_ext) {
	No * no = (No *)inf_ext;
	if (!_eh_folha(no)) {
		printf("%d(%c) ",inf, no->cor);
	}
}      

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef IMPL_PESQ_RB

void _rotacionar_esq(Arvore * arv, No * raiz) {
	No * pai = raiz->pai;
	No * esq = raiz;
	if (pai == NULL) {
	    arv->raiz = raiz->dir;
	} else {
	    if (raiz == pai->esq) pai->esq = raiz->dir;
	    else pai->dir = raiz->dir;
	}
	raiz = raiz->dir;
	raiz->pai = pai;
	esq->pai = raiz;
	esq->dir = raiz->esq;
	esq->dir->pai = esq;
	raiz->esq = esq;
}      
     
void _rotacionar_dir(Arvore * arv, No * raiz) {
	No * pai = raiz->pai;
	No * dir = raiz;
	if (pai == NULL) {
		arv->raiz = raiz->esq;
	} else {
	    if (raiz == pai->esq) pai->esq = raiz->esq;
	    else pai->dir = raiz->esq;
	}
	raiz = raiz->esq;
	raiz->pai = pai;
	dir->pai = raiz;
	dir->esq = raiz->dir;
	dir->esq->pai = dir;
	raiz->dir = dir;
}     

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef inserir_PESQ_RB

void _balancear_ins(Arvore * arv, No * no) {
	No * pai = no->pai;
    while (pai != NULL && pai->cor == 'V') {
		No * avo = pai->pai; 
		if (pai == avo->esq) {
			if (avo->dir->cor == 'V') {
				avo->cor = 'V';
				avo->esq->cor = 'P';
				avo->dir->cor = 'P';
				no = avo;
			} else {
				if (no == pai->dir) _rotacionar_esq(arv, pai);
				avo->cor = 'V';
				avo->esq->cor = 'P';
				_rotacionar_dir(arv, avo);
			}
		} else {
			if (avo->esq->cor == 'V') {
				avo->cor = 'V';
				avo->esq->cor = 'P';
				avo->dir->cor = 'P';
				no = avo;
			} else {
				if (no == pai->esq) _rotacionar_dir(arv, pai);
				avo->cor = 'V';
				avo->dir->cor = 'P';
				_rotacionar_esq(arv, avo);
			}
		}
		pai = no->pai;
	}
	if (pai == NULL) {
		no->cor = 'P';
	}
}     

void _inserir(Arvore * arv, int inf, void * inf_ext) {
	No * pai = NULL, * raiz = arv->raiz, * * ptno;
	while (!_eh_folha(raiz)) {
		pai = raiz;  
		if (inf < raiz->inf) 
			raiz = raiz->esq;        
		else 
		if (inf > raiz->inf) 
			raiz = raiz->dir;
		else
			return;
	}
	raiz = (No *)malloc(sizeof(No));
	raiz->inf = inf;
	raiz->cor = 'V';
	raiz->pai = pai;
	raiz->esq = _criar_folha();
	raiz->dir = _criar_folha();
#ifdef ARVORE_INFO_EXT
	raiz->inf_ext = inf_ext;
#endif
	if (pai == NULL)
		ptno = &arv->raiz;
	else 
	if (inf < pai->inf) 
		ptno = &pai->esq;
	else 		
		ptno = &pai->dir;
	free(*ptno); //Elimina folha nula
	*ptno = raiz;
	_balancear_ins(arv, raiz);
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

#ifdef remover_PESQ_RB

No * _substituir_por_predecessor(No * raiz, No * * ptpred, No * * ptfilho_pred) {
	No * pai_pred = raiz;        
	No * pred = raiz->esq;
	while (!_eh_folha(pred->dir)) {
	    pai_pred = pred;
	    pred = pred->dir;
	}
	*ptpred = pred;
	*ptfilho_pred = pred->esq;
	if (pai_pred == raiz) pai_pred->esq = pred->esq;
	else pai_pred->dir = pred->esq; 
	pred->esq->pai = pai_pred;
	//Substituição da raiz pelo predecessor, mantendo a cor da raiz
	raiz->inf = pred->inf;
	return raiz;
}

void _balancear_rem(Arvore * arv, No * no) {
	//O primeiro x sempre vai ser uma folha nula
	while (no != arv->raiz && no->cor == 'P') {
		No * pai = no->pai;
		if (no == pai->esq) {
			No * irmao = pai->dir;
			if (irmao->cor == 'V') { // CASO 1
				pai->cor = 'V';
				irmao->cor = 'P';
 				_rotacionar_esq(arv, pai); //rotação intermediária p/ chegar a caso 2
			} else {
				if (irmao->dir->cor == 'P') {
					if (irmao->esq->cor == 'P') { //CASO 2
						irmao->cor = 'V';
						no = pai; //se pai é preto, ainda não compensou altura de preto
					} else { //CASO 4
						irmao->cor = 'V';
						irmao->esq->cor = 'P';
						_rotacionar_dir(arv, irmao); //rotação intermediária p/ chegar a caso 3
					} 
				} else { //CASO 3
					irmao->cor = pai->cor;
					irmao->dir->cor = 'P';
					pai->cor = 'P';
					_rotacionar_esq(arv, pai);
					no = arv->raiz; //para finalizar
				}
			}
		} else {
			No * irmao = pai->esq;
			if (irmao->cor == 'V') {
				pai->cor = 'V';
				irmao->cor = 'P';
 				_rotacionar_dir(arv, pai);
			} else {
				if (irmao->esq->cor == 'P') {
					if (irmao->dir->cor == 'P') {
						irmao->cor = 'V';
						no = pai;
					} else {
						irmao->cor = 'V';
						irmao->dir->cor = 'P';
						_rotacionar_esq(arv, irmao);
					} 
				} else { 
					irmao->cor = pai->cor;
					irmao->esq->cor = 'P';
					pai->cor = 'P';
					_rotacionar_dir(arv, pai);
					no = arv->raiz; //para finalizar
				}
			}
		}
	}
	no->cor = 'P'; //Garantir raiz preta e CASO 2
}

void remover(Arvore * arv, int inf) {
	No * pai = NULL, * raiz = arv->raiz;
	while (!_eh_folha(raiz)) {
		if (inf != raiz->inf) { 
			pai = raiz;    
			if (inf < raiz->inf) raiz = raiz->esq;
			else raiz = raiz->dir;
		} else {
			No * no, * filho_no;
			if (!_eh_folha(raiz->esq) && !_eh_folha(raiz->dir)) {
				raiz = _substituir_por_predecessor(raiz, &no, &filho_no);
			} else { 
				/* OBS: código poderia ser otimizado considerando que, quando o grau é 1, 
				   sempre a raiz é preta, o filho é vermelho e os netos são folhas nulas */
				no = raiz;
				if (_eh_folha(raiz->esq) && _eh_folha(raiz->dir)) {
					raiz = _criar_folha();
				} else {
					if (!_eh_folha(raiz->esq)) raiz = raiz->esq; 
					else raiz = raiz->dir;                    
				}
				filho_no = raiz;
			}
			if (pai == NULL) {
				arv->raiz = raiz;
			} else {
				if (inf < pai->inf) pai->esq = raiz;        
				else pai->dir = raiz;
			}     
			raiz->pai = pai;
			if (no->cor == 'P') _balancear_rem(arv, filho_no);
			//Eliminação da(s) folha(s) e do nó
			if (_eh_folha(no->esq)) free(no->esq);
			if (_eh_folha(no->dir)) free(no->dir);
#ifdef ARVORE_INFO_EXT
			free (no->inf_ext);
#endif
			free(no);
			return;
		}
	}
} 

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef IMPL_PESQ_RB

int _verificar_RB(No * raiz) {
	int ap_e, ap_d;
	if (!_eh_folha(raiz)) {
		if (raiz == NULL) {
			printf("\nPonteiro nulo no lugar de folha");
		} else {
			if (raiz->pai == NULL && raiz->cor != 'P') {
				printf("\nNó raiz não é preto: %d", raiz->inf);
			}
			if (raiz->cor != 'P' && raiz->cor != 'V') {
				printf("\nNó não é preto nem vermelho: %d", raiz->inf);
			}
			if (raiz->cor == 'V' && (raiz->esq->cor == 'V' || raiz->dir->cor == 'V')) {
				printf("\nNó vermelho com filho vermelho: %d", raiz->inf);
			}
			ap_e = _verificar_RB(raiz->esq);
			ap_d = _verificar_RB(raiz->dir);
			if (ap_e != ap_d) {
				printf("\nNó com altura de preto errada: %d", raiz->inf);
				return -1;
			}
			return raiz->cor == 'P' ? ap_e + 1 : ap_e;
		}
	} else {
		if (raiz->cor != 'P') {
			printf("\nFolha não é preta");
		}
	}
	return 0;
}

int verificar_RB(Arvore * arv) {
	return _verificar_RB(arv->raiz);
}

#endif

////////////////////////////////////////////////////////////////////////////////