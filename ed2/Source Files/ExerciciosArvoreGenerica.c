#include <stdio.h>
#include <stdlib.h>
#include <Config.h>

#ifdef EXERCICIOS_GEN

////////////////////////////// PILHA / FILA ///////////////////////////////////

int _ini=0, _fim=0;
No * _itens[26];

void _limpar_fila_pilha() {
	_ini = _fim = 0;
}

void _enfileirar(No * no) {
	_itens[_fim++] = no;
}

No * _desenfileirar() {
	return _itens[_ini++];
}

void _empilhar(No * no) {
	_enfileirar(no);
}

No * _desempilhar() {
	return _itens[--_fim];
}

int _vazia() {
	return _ini == _fim;
}

//////////////////////////////// QUESTÃO 5 ////////////////////////////////////

void _imprimir_nivel(No * raiz, int nvl) {
	if (raiz != NULL) {
		if (nvl == 0) printf("%c ", raiz->inf);
		else _imprimir_nivel(raiz->filho, nvl-1);
		_imprimir_nivel(raiz->irmao, nvl);
	}
}

void imprimir_nivel(Arvore * arv, int nvl) {
	_imprimir_nivel(arv->raiz, nvl);
}

//////////////////////////////// QUESTÃO 6 ////////////////////////////////////

void caminhar_por_nivel(Arvore * arv) {
	_limpar_fila_pilha();
	_enfileirar(arv->raiz);
	while (!_vazia()) {
		No * no = _desenfileirar();
		No * filho = no->filho;
		printf("%c ", no->inf);
		while(filho != NULL) {
			_enfileirar(filho);
			filho = filho->irmao;
		}
	}
}

//////////////////////////////// QUESTÃO 7 ////////////////////////////////////

int _contar_folhas(No * raiz) {
	int folhas = 0;
	if (raiz != NULL) {
		folhas = raiz->filho == NULL ? 1 : _contar_folhas(raiz->filho);
		folhas += _contar_folhas(raiz->irmao);
	}
	return folhas;
}

int _contar_folhas2(No * raiz) {
	int folhas = 0;
	if (raiz != NULL) {
		No * filho = raiz->filho;
		if (filho == NULL) {
			return 1;
		}
		do {
			folhas += _contar_folhas2(filho);
			filho = filho->irmao;
		} while (filho != NULL);
	}
	return folhas;
}

int contar_folhas(Arvore * arv) {
	return _contar_folhas2(arv->raiz);
}

//////////////////////////////// QUESTÃO 8 ////////////////////////////////////

int _altura2(No * raiz) {
	int alt_filho = -1;
	if (raiz != NULL) {
		No * filho = raiz->filho;
		while (filho != NULL) {
			int aux = _altura2(filho);
			if (alt_filho < aux) {
				alt_filho = aux;
			}
			filho = filho->irmao;
		}
	}
	return alt_filho+1;
}

int altura2(Arvore * arv) {
	return _altura2(arv->raiz);
}

//////////////////////////////// QUESTÃO 9 ////////////////////////////////////

typedef struct _no _No;

struct _no {
	char inf;
	int grau;
};

void imprimir_descendentes(_No arv[], char c){
	int pos = 0, cont = 1;
	while (cont > 0) {
		if (arv[pos].inf == c) {
			break;
		}
		cont += arv[pos].grau-1;
		pos++; 
	} 
	if (cont == 0) {
		printf("Caractere não encontrado");
		return;
	} 
	cont = arv[pos].grau;
	pos++; 
	while (cont > 0) {
		printf(" %c %d", arv[pos].inf, arv[pos].grau);
		cont += arv[pos].grau-1;
		pos++; 
	}
}

///////////////////////////// QUESTÕES DE PROVAS //////////////////////////////

int _menor_nivel_folha(No * raiz) {
	int nivel, menor_nivel = -1;
	if (raiz != NULL) {
		menor_nivel = _menor_nivel_folha(raiz->filho) + 1;
		nivel = _menor_nivel_folha(raiz->irmao);
		if (nivel >= 0 && nivel < menor_nivel) {
			menor_nivel = nivel;
		}
	}
	return menor_nivel;
}

int _menor_nivel_folha2(No * raiz) {
	int menor_nivel = -1;
	if (raiz != NULL) {
		No * filho = raiz->filho;
		menor_nivel = INT_MAX;
		while (filho != NULL) {
			int nivel = _menor_nivel_folha2(filho)+1;
			if (nivel < menor_nivel) {
				menor_nivel = nivel;
			}
			filho = filho->irmao;
		}
	}
	return menor_nivel % INT_MAX;
}

int menor_nivel_folha(Arvore * arv) {
	return _menor_nivel_folha(arv->raiz);
}

void _imprimir_folhas(No * raiz) {
	if (raiz != NULL) {
		if (raiz->filho != NULL) {
			_imprimir_folhas(raiz->filho);
		} else {
			_imprimir_info(raiz->inf, NULL);
		}
		_imprimir_folhas(raiz->irmao);
	}
}

void _imprimir_folhas2(No * raiz) {
	if (raiz != NULL) {
		No * filho = raiz->filho;
		if (filho != NULL) {
			do {
				_imprimir_folhas2(filho);
				filho = filho->irmao;
			} while (filho != NULL);
		} else {
			_imprimir_info(raiz->inf, NULL);
		}
	}
}

void imprimir_folhas(Arvore * arv) {
	_imprimir_folhas2(arv->raiz);
}

int _gerar_maior_caminho_folha(No * raiz, int alt) {
	if (raiz != NULL) {
		int ar, ai;
		ar = _gerar_maior_caminho_folha(raiz->filho, alt-1)+1;
		if (ar == alt) {
			printf("%c ", raiz->inf);
			return ar;
		}
		ai = _gerar_maior_caminho_folha(raiz->irmao, alt);
		return ar > ai ? ar : ai; 
	}
	return -1;
}

int _gerar_maior_caminho_folha2(No * raiz, int alt) {
	if (raiz != NULL) {
		int ar, ai;
		ar = _gerar_maior_caminho_folha2(raiz->filho, alt-1)+1;
		if (ar == alt) {
			_empilhar(raiz);
			return ar;
		}
		ai = _gerar_maior_caminho_folha2(raiz->irmao, alt);
		return ar > ai ? ar : ai; 
	}
	return -1;
}

void imprimir_maior_caminho_folha(Arvore * arv) {
	//_gerar_maior_caminho_folha(arv->raiz, _gerar_maior_caminho_folha(arv->raiz, -1));
	
	_limpar_fila_pilha();
	_gerar_maior_caminho_folha2(arv->raiz, _gerar_maior_caminho_folha2(arv->raiz, -1));
	while(!_vazia()) {
		printf("%c ", _desempilhar()->inf);
	}
}

int _buscar_nivel(No * raiz, char inf) {
	if (raiz != NULL) {
		int nf;
		if (raiz->inf == inf) {
			return 0;
		}
		nf = _buscar_nivel(raiz->filho, inf);
		return nf != -1 ? nf+1 : _buscar_nivel(raiz->irmao, inf);
	}
	return -1;
}

int buscar_nivel(Arvore * arv, char inf) {
	return _buscar_nivel(arv->raiz, inf);
}

int _maior_grau(No * raiz, int nf) {
	if (raiz != NULL) {
		int gf = _maior_grau(raiz->filho, 1);
		int gi = _maior_grau(raiz->irmao, nf+1);
		gi = gi > 0 ? gi : nf;
		return gf > gi ? gf : gi; 

	}
	return 0;
}

int maior_grau(Arvore * arv) {
	return _maior_grau(arv-> raiz, 0);
}

//////////////////////////////////////////////////////////////////////////////

////////////////// MONTAGEM DAS ÁRVORES DE TESTE //////////////////
//															     //	
//	Árvore 1				   |A|							     //
//							 /  |  \						     //
//						   |B| |C|  |D|						     //
//						    |      / | \					     //
//						   |E|  |F| |G| |H|					     //
//						    |								     //	
//						   |I|								     //
//															     //
//	Árvore 2				   |A|							     //
//							/   |   \						     //
//						 |B|   |C|   |D|					     //
//						       / \    | 					     //
//						     |E| |F| |G| 					     //
//						   									     //
///////////////////////////////////////////////////////////////////

No * _nos[26];
 
No * _no_letra(char c) {
    return _nos[c-'A']; 
}    

void _testar() {
	int i;
	Arvore * arv1;
	_No arv2[7];

	arv1 = criar();

	for(i=0; i<26; i++) {
		_nos[i] = (No *)malloc(sizeof(No));
		_nos[i]->inf = 'A'+i;
		_nos[i]->pai = NULL;
		_nos[i]->filho = NULL;  
		_nos[i]->irmao = NULL;
	}
    _no_letra('A')->pai	  = NULL;
    _no_letra('A')->filho = _no_letra('B');
	_no_letra('B')->pai   = _no_letra('A');     
    _no_letra('B')->filho = _no_letra('E');
    _no_letra('B')->irmao = _no_letra('C');
    _no_letra('C')->pai   = _no_letra('A');
	_no_letra('C')->irmao = _no_letra('D');      
	_no_letra('D')->pai   = _no_letra('A');
    _no_letra('D')->filho = _no_letra('F');
	//_no_letra('D')->irmao = _no_letra('J');
	//_no_letra('J')->pai   = _no_letra('A');
	_no_letra('E')->pai   = _no_letra('B');
    _no_letra('E')->filho = _no_letra('I');
    _no_letra('F')->pai   = _no_letra('D');
    _no_letra('F')->irmao = _no_letra('G');
	_no_letra('G')->pai   = _no_letra('D');
    //_no_letra('G')->filho = _no_letra('I');
    _no_letra('G')->irmao = _no_letra('H');      
    _no_letra('H')->pai   = _no_letra('D');
    _no_letra('I')->pai   = _no_letra('E');
    //_no_letra('I')->pai   = _no_letra('G');
	arv1->raiz = _no_letra('A');

	printf("Altura: %d\n", altura(arv1));
	
	printf("Nível 2: ");
	imprimir_nivel(arv1, 2);
	printf("\n");

	printf("Caminhamento por nível: ");
	caminhar_por_nivel(arv1);
	printf("\n");

	printf("Maior grau: %d\n", maior_grau(arv1));
	printf("Qtd de folhas: %d\n", contar_folhas(arv1));
	printf("Menor nivel c/ folha: %d\n", menor_nivel_folha(arv1));
	printf("Nível do nó %c: %d\n", 'G', buscar_nivel(arv1, 'G'));
	printf("Folhas: ");
	imprimir_folhas(arv1);
	printf("\n");
	printf("Maior caminho p/ folha: ");
	imprimir_maior_caminho_folha(arv1);
	printf("\n");

	destruir(arv1);

	arv2[0].inf = 'A';
	arv2[0].grau = 3;
	arv2[1].inf = 'B';
	arv2[1].grau = 0;
	arv2[2].inf = 'C';
	arv2[2].grau = 2;
	arv2[3].inf = 'E';
	arv2[3].grau = 0;
	arv2[4].inf = 'F';
	arv2[4].grau = 0;
	arv2[5].inf = 'D';
	arv2[5].grau = 1;
	arv2[6].inf = 'G';
	arv2[6].grau = 0;

	printf("Descendentes de 'C': ");
	imprimir_descendentes(arv2,'C');
	printf("\n");

	system("pause");
}

#endif