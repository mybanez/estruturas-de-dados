#include <stdio.h>
#include <stdlib.h>
#include <Config.h>

////////////////////////////////////////////////////////////////////////////////

#ifdef comum_PESQ_B

void _compactar_no(No * no, int pos_chv, int pos_flh_rel) { //0 - Esquerda | 1 - Direita
	int i;
	if (pos_flh_rel == 0) {
		no->filhos[pos_chv] = no->filhos[pos_chv+1]; 
	}
	for(i = pos_chv+1; i < no->nfilhos-1; i++) {
		no->chaves[i-1] = no->chaves[i]; 
		no->filhos[i] = no->filhos[i+1]; 
	}
	no->nfilhos--;
}

void _descompactar_no(No * no, int pos_chv, int pos_flh_rel) { //0 - Esquerda | 1 - Direita
	int i;
	for(i = no->nfilhos-1; i > pos_chv; i--) {
		no->chaves[i] = no->chaves[i-1]; 
		no->filhos[i+1] = no->filhos[i]; 
	}
	if (pos_flh_rel == 0) {
		no->filhos[pos_chv+1] = no->filhos[pos_chv]; 
	}
	no->nfilhos++;
}

void _mover_conteudo_no(No * ori, int ini_ori, int fim_ori, No * des, int ini_des) {
	int i, nchaves = fim_ori-ini_ori+1;
	for(i=0; i < nchaves; i++) {
		des->chaves[ini_des+i] = ori->chaves[ini_ori+i];
		des->filhos[ini_des+i] = ori->filhos[ini_ori+i];
	}
	des->filhos[ini_des+nchaves] = ori->filhos[ini_ori+nchaves];
	des->nfilhos = ini_des+nchaves+1;
	ori->nfilhos -= nchaves; 
}

#endif

#ifdef _manter_no_PESQ_B

No * _criar_no(int inf, No * flh1, No * flh2) {
	No * no = (No *)malloc(sizeof(No));
	no->chaves[0] = inf;
	no->filhos[0] = flh1;
	no->filhos[1] = flh2;
	no->nfilhos = 2;
	return no;
}

void _inserir_chave_no(No * no, int pos_chv, int inf, No * flh, int * ptchv_div, No * * ptflh_div) {
	int chv_div = 0; No * flh_div = NULL;
	if (no->nfilhos < ORDEM) { //Deslocar
		_descompactar_no(no, pos_chv, 1);
		no->chaves[pos_chv] = inf;
		no->filhos[pos_chv+1] = flh;
	} else { //Dividir
		flh_div = _criar_no(0, NULL, NULL);
		if (pos_chv > ORDEM/2) {
			chv_div = no->chaves[ORDEM/2];
			_mover_conteudo_no(no, ORDEM/2+1, ORDEM-2, flh_div, 0);
			no->nfilhos--; //Retirar a chave que vai subir
			_inserir_chave_no(flh_div, pos_chv-ORDEM/2-1, inf, flh, ptchv_div, ptflh_div);
		} 
		else
		if (pos_chv < ORDEM/2) {
			chv_div = no->chaves[ORDEM/2-1];
			_mover_conteudo_no(no, ORDEM/2, ORDEM-2, flh_div, 0);
			no->nfilhos--; //Retirar a chave que vai subir
			_inserir_chave_no(no, pos_chv, inf, flh, ptchv_div, ptflh_div);
		} 
		else {
			chv_div = inf;
			_mover_conteudo_no(no, ORDEM/2, ORDEM-2, flh_div, 0);
			flh_div->filhos[0] = flh; 
		}
	}
	*ptchv_div = chv_div;
	*ptflh_div = flh_div;
}

No * _remover_chave_no(No * no, int pos_chv, No * pai_no, int pos_no, int * ptpos_jun);
void _remover_menor(No * raiz, int * ptchvmenor, No * pai_raiz, int pos_raiz, int * ptpos_jun);

void _trocar_sucessor_chave_no(No * no, int pos_chv, No * pai_no, int pos_no, int * ptpos_jun) {
	_remover_menor(no->filhos[pos_chv+1], no->chaves+pos_chv, no, pos_chv+1, ptpos_jun);
	if (*ptpos_jun >= 0) { //Ocorreu uma junção: compactar nó
		_remover_chave_no(no, *ptpos_jun, pai_no, pos_no, ptpos_jun);
	}
}

No * _remover_chave_no(No * no, int pos_chv, No * pai_no, int pos_no, int * ptpos_jun) {
	int pos_jun = -1;
	No * irmao;
	//Não é folha e não há consolidação em andamento
	if (no->filhos[pos_chv+1] != NULL) {
		_trocar_sucessor_chave_no(no, pos_chv, pai_no, pos_no, &pos_jun);
	} else { 
		No * filho_esq, * filho_dir;
		if (no->nfilhos == 2) { //Eliminar nó
			filho_esq = no->filhos[0];
			free(no);
			no = filho_esq; //Caso esteja havendo uma consolidação
		} else {
			_compactar_no(no, pos_chv, 1);
			//Violou propriedade árvore B: procurar irmão com chave sobrando
			if (pai_no != NULL && no->nfilhos-1 < ORDEM/2) { 
				if (pos_no < pai_no->nfilhos-1 && 
					((irmao = pai_no->filhos[pos_no+1])->nfilhos-1) > ORDEM/2) {//À direita
					_descompactar_no(no, no->nfilhos-1, 1);
					no->filhos[no->nfilhos-1] = irmao->filhos[0];
					no->chaves[no->nfilhos-2] = pai_no->chaves[pos_no];
					pai_no->chaves[pos_no] = irmao->chaves[0];
					_compactar_no(irmao, 0, 0);
				} else
				if (pos_no > 0 && 
					(irmao = pai_no->filhos[pos_no-1])->nfilhos-1 > ORDEM/2) {//À esquerda
					_descompactar_no(no, 0, 0);
					no->filhos[0] = irmao->filhos[irmao->nfilhos-1];
					no->chaves[0] = pai_no->chaves[pos_no-1];
					pai_no->chaves[pos_no-1] = irmao->chaves[irmao->nfilhos-2];
					_compactar_no(irmao, irmao->nfilhos-2, 1);
				} else { //Não existe
					//Fazer junção no filho à esquerda e liberar filho à direita
					if (pos_no < pai_no->nfilhos-1) {
						pos_jun = pos_no;
						filho_esq = no;
						filho_dir = pai_no->filhos[pos_no+1];
						pai_no->filhos[pos_no+1] = NULL; //Consolidação em andamento 
					} else {
						pos_jun = pos_no-1;
						filho_esq = pai_no->filhos[pos_no-1];
						filho_dir = no;
						pai_no->filhos[pos_no] = NULL; //Consolidação em andamento
						no = NULL;
					}
					_descompactar_no(filho_esq, filho_esq->nfilhos-1, 1);
					filho_esq->chaves[filho_esq->nfilhos-2] = pai_no->chaves[pos_jun];
					_mover_conteudo_no(filho_dir, 0, filho_dir->nfilhos-2, filho_esq, filho_esq->nfilhos-1);
					free(filho_dir);
				}
			}
		}
	} 
	*ptpos_jun = pos_jun;
	return no;
}     

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef inserir_PESQ_B
	
void _inserir(No * raiz, int inf, int * ptchv_div, No * * ptflh_div) {
	int pos_chv = _buscar_chave_no(raiz, inf);
	if (pos_chv == raiz->nfilhos-1 || inf != raiz->chaves[pos_chv]) {
		if (raiz->filhos[pos_chv] != NULL) {
			_inserir(raiz->filhos[pos_chv], inf, ptchv_div, ptflh_div);
			//Subiu uma chave para a raiz
			if (*ptflh_div != NULL) {
				_inserir_chave_no(raiz, pos_chv, *ptchv_div, *ptflh_div, ptchv_div, ptflh_div);
			}
		} else {
			_inserir_chave_no(raiz, pos_chv, inf, NULL, ptchv_div, ptflh_div);
		} 
	}
}

void inserir(Arvore * arv, int inf) {
	int chv_div; No * flh_div;
	if (arv->raiz != NULL) {
		_inserir(arv->raiz, inf, &chv_div, &flh_div);
		//Subiu uma chave para a raiz
		if (flh_div != NULL) {
			arv->raiz = _criar_no(chv_div, arv->raiz, flh_div);
		}
	} else {
		arv->raiz = _criar_no(inf, NULL, NULL);
	}
} 

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef remover_PESQ_B

void _remover_menor(No * raiz, int * ptchvmenor, No * pai_raiz, int pos_raiz, int * ptpos_jun) {
	if (raiz->filhos[0] != NULL) {
		_remover_menor(raiz->filhos[0], ptchvmenor, raiz, 0, ptpos_jun);
		if (*ptpos_jun >= 0) { //Ocorreu uma junção: compactar raiz
			_remover_chave_no(raiz, *ptpos_jun, pai_raiz, pos_raiz, ptpos_jun);
		}
	} else {
		*ptchvmenor = raiz->chaves[0];
		_remover_chave_no(raiz, 0, pai_raiz, pos_raiz, ptpos_jun);
	}
}

No * _remover(No * raiz, int inf, No * pai_raiz, int pos_raiz, int * ptpos_jun) {
	if (raiz != NULL) {
		int pos_chv = _buscar_chave_no(raiz, inf);
		if (pos_chv == raiz->nfilhos-1 || inf != raiz->chaves[pos_chv]) {
			_remover(raiz->filhos[pos_chv], inf, raiz, pos_chv, ptpos_jun);
			if (*ptpos_jun >= 0) { //Ocorreu uma junção: compactar raiz
				raiz = _remover_chave_no(raiz, *ptpos_jun, pai_raiz, pos_raiz, ptpos_jun);
			}
		} else {
			raiz = _remover_chave_no(raiz, pos_chv, pai_raiz, pos_raiz, ptpos_jun);
		}
	}
	return raiz;
}

void remover(Arvore * arv, int inf) {
	int pos_jun;
	arv->raiz = _remover(arv->raiz, inf, NULL, -1, &pos_jun);
} 

#endif

////////////////////////////////////////////////////////////////////////////////