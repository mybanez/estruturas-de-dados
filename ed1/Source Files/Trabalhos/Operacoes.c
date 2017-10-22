#include <stdio.h>
#include <stdlib.h>
#include <ConfigImpl.h>

#ifdef TRABALHO_LISTA_1

///////////////////////////////////////////////////////////////////////////////
 
// PRE: tamanho(op1) >= tamanho(op2))
// POS: op1 += op2
void acumular(Lista * op1, Lista * op2) {
	int i, sobe, soma, tam1, tam2;
	tam1 = tamanho(op1);
	tam2 = tamanho(op2);
	for(i=0, sobe=0; i < tam2; i++) {
		soma = ler_pos(op1,i) + ler_pos(op2,i) + sobe;
		if (soma > 9) {
			soma -= 10;
			sobe = 1;
		} else {
			sobe = 0;
		}
		escrever_pos(op1, i, soma); 
	}
	for(; i < tam1; i++) {
		soma = ler_pos(op1,i) + sobe;
		if (soma > 9) {
			soma -= 10;
			sobe = 1;
		} else {
			sobe = 0;
		}
		escrever_pos(op1, i, soma); 
	}
	if (sobe == 1) {
		inserir_ultimo(op1, 1);
	}
}

///////////////////////////////////////////////////////////////////////////////

// PRE: tamanho(op1) >= tamanho(op2))
// POS: resultado = op1 + op2
Lista * somar(Lista * op1, Lista * op2) {
	Lista * res;
	res = clonar(op1);
	acumular(res, op2);
	return res;
}

// POS: resultado = op1 * op2
Lista * multiplicar(Lista * op1, Lista * op2) {
	int i, j, k, sobe, mult, tam1, tam2;
	Lista * res = criar(), * res_par = criar(), * aux;
	tam1 = tamanho(op1);
	tam2 = tamanho(op2);
	for(i=0; i < tam2; i++) {
		limpar(res_par);
		for(j=0, sobe=0; j < tam1; j++) {
			mult = ler_pos(op1,j) * ler_pos(op2,i) + sobe;
			if (mult > 9) {
				sobe = mult/10;
				mult %= 10;
			} else {
				sobe = 0;
			}
			inserir_ultimo(res_par, mult); 
		}
		if (sobe > 0) {
			inserir_ultimo(res_par, sobe);
		}
		for(k=0; k<i; k++) {
			inserir_primeiro(res_par, 0);
		}
		aux = res;
		res = res_par;
		res_par = aux;
		acumular(res, aux);
	}
	destruir(res_par);
	return res;
}

///////////////////////////////////////////////////////////////////////////////

#endif
