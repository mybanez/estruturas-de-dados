#include <stdio.h>
#include <stdlib.h>
#include <Config.h>

#ifdef imprimir_PESQ_NARIA

void _imprimir_info(int inf, void * inf_ext) {
	printf("%d(%d) ", inf, *((int *)inf_ext));
}

void _imprimir(No * raiz, int nivel) {
	if (raiz != NULL) {
		int i;
		for (i = 0; i < raiz->nfilhos - 1; i++) {
			_imprimir(raiz->filhos[i], nivel + 1);
			_imprimir_info(raiz->chaves[i], &nivel);
		}
		_imprimir(raiz->filhos[i], nivel + 1);
	}
}

void imprimir(Arvore * arv) {
	_imprimir(arv->raiz, 0);
	printf("\n");
}

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef comum_PESQ_NARIA

void _iniciar(Arvore * arv) {
	arv->raiz = NULL;
}

void _limpar(No * raiz) {
	int i;
	if (raiz != NULL) {
		for(i=0; i < raiz->nfilhos; i++) {  
			_limpar(raiz->filhos[i]);
		}
		free(raiz);
	}
}

void limpar(Arvore * arv) {
	_limpar(arv->raiz);
	_iniciar(arv);
}

int _buscar_chave_no(No * no, int inf) { //Busca binária
	int pini = 0, pfim = no->nfilhos-2, pos_chv;
	do {
		pos_chv = (pini + pfim) / 2;
		if (inf > no->chaves[pos_chv]) pini = pos_chv+1;
		else if (inf < no->chaves[pos_chv]) pfim = pos_chv-1;
		else return pos_chv;
	} while(pini <= pfim);
	return pini;
}

#endif

#ifdef _manter_no_PESQ_NARIA

void _trocar_sucessor_chave_no(No * no, int pos_chv);
void _trocar_predecessor_chave_no(No * no, int pos_chv);

No * _criar_no(int inf) {
	No * no = (No *)malloc(sizeof(No));
	no->chaves[0] = inf;
	no->filhos[0] = NULL;
	no->filhos[1] = NULL;
	no->nfilhos = 2;
	return no;
}

void _inserir_chave_no(No * no, int pos_chv, int inf) {
	int i;
	if (no->nfilhos < ORDEM) { //Deslocar
		for(i = no->nfilhos-1; i > pos_chv; i--) {
			no->chaves[i] = no->chaves[i-1]; 
		}
		no->chaves[pos_chv] = inf;
		no->filhos[no->nfilhos++] = NULL;
	} else { //Criar filho
		no->filhos[pos_chv] = _criar_no(inf);
	}
}

No * _remover_chave_no(No * no, int pos_chv) {
	int i;
	//Um dos filhos nulo
	if (no->filhos[pos_chv+1] != NULL) {
		_trocar_sucessor_chave_no(no, pos_chv);
	} else
	if (no->filhos[pos_chv] != NULL) {
		_trocar_predecessor_chave_no(no, pos_chv);
	} else { //Ambos os filhos nulos
		if (no->nfilhos == 2) { //Eliminar nó
			free(no);
			no = NULL;
		} else {
			//Procurar filho não nulo
			int pos_flh = (pos_chv+2) % no->nfilhos;
			while (pos_flh != pos_chv && no->filhos[pos_flh] == NULL) {
				pos_flh = (pos_flh+1) % no->nfilhos;
			} 
			if (pos_flh == pos_chv) { //Não encontrou: compactar
				for(i = pos_chv+1; i < no->nfilhos-1; i++) {
					no->chaves[i-1] = no->chaves[i]; 
				}
				no->nfilhos--;
			} else { //Encontrou: trocar chave
				if (pos_flh > pos_chv) { //Deslocar bloco para esquerda
					for(i = pos_chv; i < pos_flh-1; i++) {
						no->chaves[i] = no->chaves[i+1];
					}
					_trocar_sucessor_chave_no(no, pos_flh-1);
				} else { //Deslocar bloco para direita
					/* Deslocamento dos filhos é necessário porque a busca 
					   do filho não nulo é feita para a direita */
					for(i = pos_chv; i > pos_flh; i--) {
						no->chaves[i] = no->chaves[i-1];
						no->filhos[i+1] = no->filhos[i];
					}
					no->filhos[pos_flh+1] = NULL;  
					_trocar_predecessor_chave_no(no, pos_flh);
				}
			}
		}
	} 
	return no;
}

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef sucessor_PESQ_NARIA

int _sucessor(No * raiz, int inf) {
	int suc = INT_MIN;
	if (raiz != NULL) {
	    int pos_chv = _buscar_chave_no(raiz, inf);
		if (pos_chv == raiz->nfilhos-1 || inf != raiz->chaves[pos_chv]) {
			suc = _sucessor(raiz->filhos[pos_chv], inf);
			if (suc == INT_MIN && pos_chv < raiz->nfilhos-1) {
				suc = raiz->chaves[pos_chv];
			}
		} else {
			No * filho = raiz->filhos[pos_chv+1];
			if (filho != NULL) {
				while (filho->filhos[0] != NULL) {
					filho = filho->filhos[0];
				}
				suc = filho->chaves[0];
			} else {
				if (pos_chv < raiz->nfilhos-2) {
					suc = raiz->chaves[pos_chv+1];
				}	
			}
		}
	}
	return suc;
}

int sucessor(Arvore * arv, int inf) {
	return _sucessor(arv->raiz, inf);
}

#endif

////////////////////////////////////////////////////////////////////////////////