#include <stdio.h>
#include <stdlib.h>
#include <Config.h>

Arvore * _montar();

///////////////////////////////////////////////////////////////////////////////

/////////////////////// ÁRVORE DE TESTE /////////////////////////
//															   //	
//						    |A|								   //
//						 /   |   \							   //
//					   |B|  |D|   |E|						   //
//					    |       /  |  \ 					   //
//					   |C|    |F| |G| |H| 					   //
//								   |						   //
//								  |I| 						   //
/////////////////////////////////////////////////////////////////

#if defined(TESTE_GEN_PNT) || \
	defined(TESTE_GEN_PNT2)

No * _nos[26];
 
No * _no_letra(char c) {
    return _nos[c-'A']; 
} 

#endif

#ifdef TESTE_GEN_PNT

Arvore * _montar() {
	Arvore * arv = criar();
	int i;
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
    _no_letra('B')->filho = _no_letra('C');
    _no_letra('B')->irmao = _no_letra('D');
    _no_letra('C')->pai   = _no_letra('B');
	_no_letra('D')->pai   = _no_letra('A');
    _no_letra('D')->irmao = _no_letra('E');      
	_no_letra('E')->pai   = _no_letra('A');
    _no_letra('E')->filho = _no_letra('F');
    _no_letra('F')->pai   = _no_letra('E');
    _no_letra('F')->irmao = _no_letra('G');
	_no_letra('G')->pai   = _no_letra('E');
	_no_letra('G')->filho = _no_letra('I');
	_no_letra('I')->pai   = _no_letra('G');
	_no_letra('G')->irmao = _no_letra('H');      
	_no_letra('H')->pai   = _no_letra('E');
	arv->raiz = _no_letra('A');

	return arv;
}         

#endif

#ifdef TESTE_GEN_PNT2

Arvore * _montar() {
	Arvore * arv = criar();
	int i, j;
	for(i=0; i<26; i++) {
		_nos[i] = (No *)malloc(sizeof(No));
		_nos[i]->inf = 'A'+i;
		_nos[i]->pai = NULL;
		for(j=0; j<MAX_FILHOS; j++) {
			_nos[i]->filhos[j] = NULL;
		}
	}
    _no_letra('A')->pai		  = NULL;
	_no_letra('A')->filhos[0] = _no_letra('B');
    _no_letra('A')->filhos[1] = _no_letra('D');
    _no_letra('A')->filhos[2] = _no_letra('E');        
	_no_letra('B')->pai		  = _no_letra('A');     
    _no_letra('B')->filhos[0] = _no_letra('C');
    _no_letra('C')->pai		  = _no_letra('B');
	_no_letra('D')->pai		  = _no_letra('A');
	_no_letra('E')->pai		  = _no_letra('A');
    _no_letra('E')->filhos[0] = _no_letra('F');
    _no_letra('E')->filhos[1] = _no_letra('G');        
    _no_letra('E')->filhos[2] = _no_letra('H');
    _no_letra('F')->pai		  = _no_letra('E');
	_no_letra('G')->pai		  = _no_letra('E');
	_no_letra('G')->filhos[0] = _no_letra('I');
	_no_letra('I')->pai       = _no_letra('G');
    _no_letra('H')->pai		  = _no_letra('E');
	arv->raiz = _no_letra('A');

	return arv;
}         

#endif

#if defined(TESTE_GEN_PNT) || \
	defined(TESTE_GEN_PNT2)

void _testar() {
	Arvore * arv = _montar();

	preord(arv);
    printf("\n");
    inord(arv);
    printf("\n");
    posord(arv);
    printf("\n");

	printf("Altura: %d\n", altura(arv));
	destruir(arv);

	system("pause");
}         

#endif

///////////////////////////////////////////////////////////////////////////////
