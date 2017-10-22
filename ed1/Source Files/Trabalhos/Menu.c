#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <ConfigImpl.h>

#ifdef TRABALHO_LISTA_1

///////////////////////////////////////////////////////////////////////////////

typedef Lista * (Operacao)(Lista *, Lista *); 

Lista * somar(Lista * op1, Lista * op2);
Lista * multiplicar(Lista * l1, Lista * l2);

///////////////////////////////////////////////////////////////////////////////

void imprimir_numero(Lista * num, int ncar) {
	int i, tam = tamanho(num), nesp;
	for(i=0, nesp=ncar-tam; i < nesp; i++) {
		printf(" ");
	}
	for(i=tam-1; i >= 0; i--) {
		printf("%d", ler_pos(num,i));
	}
}

int operandos_definidos(Lista * op1, Lista * op2) {
	if (esta_vazia(op1) || esta_vazia(op2)) {
		printf("> Operando(s) nao definido(s)!\n");
		return 0;
	}
	return 1;
}

///////////////////////////////////////////////////////////////////////////////

#define TAM_MENU 6

#define OPC_LER_OP1 1
#define OPC_LER_OP2 2
#define OPC_IMP_OPS 3
#define OPC_IMP_SOMA 4
#define OPC_IMP_MULT 5
#define OPC_SAIR 6

int ler_opcao() {
	int opc;
	do {
		fflush(stdin);
		system("cls");
		printf("ESCOLHA A OPCAO:\n");
		printf("(1) Ler operando 1\n");
		printf("(2) Ler operando 2\n");
		printf("(3) Imprimir operandos\n");
		printf("(4) Somar\n");
		printf("(5) Multiplicar\n");
		printf("(6) Sair\n");
		printf("\n");
		printf("> Opcao: ");
		opc = getche()-'0';
		printf("\n");
	} while(opc < 1 || opc > TAM_MENU );
	return opc;
}

void opc_ler_numero(Lista * num) {
	int i, valido;
	char str[1000];
	limpar(num);
	do {
		i = 0;
		valido = 1;
		printf("> Digite o numero: ");
		scanf_s("%s", str, 1000);
		while (str[i] != '\0') {
			if (isdigit(str[i])) {
				inserir_primeiro(num, str[i]-'0');
				i++;
			} else {
				valido = 0;
				printf("> Valor invalido!\n");
				break;
			}
		}
	} while (!valido);
}

void opc_imprimir_operandos(Lista * op1, Lista * op2) {
	printf("> Operando 1: ");
	imprimir_numero(op1, 0);
	printf("\n> Operando 2: ");
	imprimir_numero(op2, 0);
	printf("\n");
}

void opc_imprimir_operacao(Lista * op1, Lista * op2, char soper, Operacao * oper) {
	int i, ncar;
	Lista * res, * aux;
	if (operandos_definidos(op1, op2)) {
		if (tamanho(op2) > tamanho(op1)) {
			aux = op1;
			op1 = op2;
			op2 = aux;
		}
		res = (*oper)(op1, op2);
		ncar = tamanho(res)+1;
		printf(">  ");
		imprimir_numero(op1, ncar);
		printf("\n> %c", soper);
		imprimir_numero(op2, ncar);
		printf("\n>  ");
		for (i=0; i < ncar; i++) {
			printf("%c", 196);
		}
		printf("\n>  ");
		imprimir_numero(res, ncar);
		printf("\n");
		destruir(res);
	}
}

void opc_sair() {
	printf("> Tchau!\n");
}

void pausar() {
	printf("\n");
	system("pause");
}

void processar_menu() {
	int opc;
	Lista * op1 = criar(); 
	Lista * op2 = criar();
	do {
		opc = ler_opcao();
		switch(opc) {
			case OPC_LER_OP1: 
				opc_ler_numero(op1);
				break;
			case OPC_LER_OP2: 
				opc_ler_numero(op2);
				break;
			case OPC_IMP_OPS: 
				opc_imprimir_operandos(op1, op2);
				break;
			case OPC_IMP_SOMA:
				opc_imprimir_operacao(op1, op2, '+', &somar);
				break;
			case OPC_IMP_MULT:
				opc_imprimir_operacao(op1, op2, 'x', &multiplicar);
				break;
			case OPC_SAIR:
				opc_sair();
				break;
		}
		pausar();
	} while(opc != OPC_SAIR);
	destruir(op1);
	destruir(op2);
}

///////////////////////////////////////////////////////////////////////////////

void _testar() {
	processar_menu();	
}

#endif
