#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ConfigImpl.h>
#include <Calculadora.h>

#ifdef TRABALHO_PILHA_1

///////////////////////////////////////////////////////////////////////////////

struct calculadora {
	Pilha * p;
	char * status;
};

///////////////////////////////////////////////////////////////////////////////

Calculadora * criar_calc() {
	Calculadora * calc = (Calculadora *)malloc(sizeof(Calculadora));
	calc->p = criar();
	calc->status = "Ok";
	return calc;
}

void destruir_calc(Calculadora * calc) {
	free(calc);
}

///////////////////////////////////////////////////////////////////////////////

int status_ok (Calculadora * calc) {
	return strcmp(calc->status, "Ok") == 0;
}

void imprimir_calc(Calculadora * calc) {
	printf("\n");
	imprimir(calc->p);
	printf("%s\n", calc->status);
	calc->status = "Ok";
}

///////////////////////////////////////////////////////////////////////////////

void limpar_calc(Calculadora * calc) {
	limpar(calc->p);
	calc->status = "Ok";
}

void empilhar_operando(Calculadora * calc, int operando) {
	empilhar(calc->p, operando);
	calc->status = "Ok";
}

void somar(Calculadora * calc) {
	if (tamanho(calc->p) >= 2) {
		empilhar(calc->p, desempilhar(calc->p)+desempilhar(calc->p));
		calc->status = "Ok";
		return;
	}
	calc->status = "Erro: +";
}

void subtrair(Calculadora * calc) {
	if (tamanho(calc->p) >= 2) {
		int sub2 = desempilhar(calc->p);
		empilhar(calc->p, desempilhar(calc->p)-sub2);
		calc->status = "Ok";
		return;
	}
	calc->status = "Erro: -";
}

void multiplicar(Calculadora * calc) {
	if (tamanho(calc->p) >= 2) {
		empilhar(calc->p, desempilhar(calc->p)*desempilhar(calc->p));
		calc->status = "Ok";
		return;
	}
	calc->status = "Erro: *";
}

void dividir(Calculadora * calc) {
	if (tamanho(calc->p) >= 2 && topo(calc->p) != 0) {
		int den = desempilhar(calc->p);
		empilhar(calc->p, desempilhar(calc->p)/den);
		calc->status = "Ok";
		return;
	}
	calc->status = "Erro: /";
}

///////////////////////////////////////////////////////////////////////////////

#endif
