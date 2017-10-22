#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Config.h>

#ifdef EXERCICIOS_PESQ_AVL

/////////////////////////// QUESTÃO 1 /////////////////////////////////

/* Ver arquivo "ArvorePesquisaAVL.c" */

//////////////////////////// QUESTÕES 5 E 6 ///////////////////////////

int verificar_AVL(Arvore * arv);

//////////////////////////// QUESTÕES PROVAS ///////////////////////////

No * _rotacionar_esq(No * raiz);
No * _rotacionar_dir(No * raiz);
No * _rotacionar_dir_esq(No * raiz);
No * _rotacionar_esq_dir(No * raiz);

No * _rotacionar_AVL(No * raiz) {
	if (raiz->fb == 2) {
		if (raiz->dir->fb == -1) return _rotacionar_dir_esq(raiz);
		else return _rotacionar_esq(raiz);
	} else {
		if (raiz->esq->fb == 1) return _rotacionar_esq_dir(raiz);
		else return _rotacionar_dir(raiz);
	}
}     

No * rotacionar_AVL(Arvore * arv) {
	return _rotacionar_AVL(arv->raiz);
}     

////////////////////////////////////////////////////////////////////////////////

#endif