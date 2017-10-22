#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <ConfigImpl.h>
#include <Calculadora.h>

#ifdef TRABALHO_PILHA_1

#define TAM_MAX_LIN 100

///////////////////////////////////////////////////////////////////////////////

void ler_prompt(char * linha) {
	printf("\nCALC> ");
	fgets(linha, TAM_MAX_LIN, stdin);
}

void escrever_prompt(char * linha) {
	printf("\nCALC> %s\n", linha);
}

char * ler_item(char * linha, char * item_atual) {
	if (item_atual != NULL) {
		item_atual = strtok(NULL, " \n");
		if (item_atual != NULL) {
			return item_atual;
		}
	}
	ler_prompt(linha);
	return strtok(linha, " \n");
}

int eh_operando(char * item) {
    int i, tam = strlen(item);
    for(i=0; i < tam; i++) {
       if(!isdigit(item[i]))
		   return 0;
    }
    return 1;
}

int eh_operador(char * item) {
    return strlen(item) == 1 && 
		   (*item == '+' ||	*item == '-' ||	
		    *item == '*' ||	*item == '/');
}

///////////////////////////////////////////////////////////////////////////////

void processar_prompt() {
	char * item = NULL, linha_entrada[TAM_MAX_LIN], linha_saida[TAM_MAX_LIN];
	int sair = 0;
	Calculadora * calc = criar_calc();
	do {
		item = ler_item(linha_entrada, item);
		if (item == NULL) {
			if (sair) exit(0);
			limpar_calc(calc);
			sair = 1;
		} else {
			if (eh_operando(item)) {
				empilhar_operando(calc, atoi(item));
			} else 
			if (eh_operador(item)) {
				switch (item[0]) {
				case '+':
					somar(calc);
					break;
				case '-':
					subtrair(calc);
					break;
				case '*':
					multiplicar(calc);
					break;
				case '/':
					dividir(calc);
					break;
				}
				if (!status_ok(calc)) {
					item = NULL;
				}
			} else {
				sprintf(linha_saida, "%s?", item);
				escrever_prompt(linha_saida);
				item = NULL;
			}
			sair = 0;
		}
		imprimir_calc(calc);
	} while(1);
}

///////////////////////////////////////////////////////////////////////////////

void _testar() {
	setlocale(LC_ALL,"");
	processar_prompt();	
}

#endif
