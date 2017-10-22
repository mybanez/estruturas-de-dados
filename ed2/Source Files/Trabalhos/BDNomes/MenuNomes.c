#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Config.h>

#ifdef TRABALHO_BIN_1

///////////////////////////////////////////////////////////////////////////////

#define TAM_MENU 7

#define OPC_REC 1
#define OPC_LST 2
#define OPC_BSC 3
#define OPC_INS 4
#define OPC_REM 5
#define OPC_BSC_REM 6
#define OPC_FIM 7

char nome[TAM_MAX_NOME];

int ler_opcao() {
	int opc;
	do {
		fflush(stdin);
		system("cls");
		printf("ESCOLHA A OPCAO:\n");
		printf("(1) Recarregar\n");
		printf("(2) Listar\n");
		printf("(3) Buscar\n");
		printf("(4) Inserir\n");
		printf("(5) Remover\n");
		printf("(6) Buscar e remover\n");
		printf("(7) Sair\n");
		printf("\n");
		printf("Opcao: ");
		opc = getche()-'0';
		printf("\n");
	} while(opc < 1 || opc > TAM_MENU );
	return opc;
}

void ler_nome() {
	printf("Digite o nome: ");
	fgets(nome, TAM_MAX_NOME,stdin);
	nome[strlen(nome)-1] = '\0';
}

void opc_recarregar(Arvore * bd) {
	FILE * f;
	limpar(bd);
    f = fopen ("Nomes.txt", "rt");
    while(fgets(nome, TAM_MAX_NOME, f) != NULL) {
		nome[strlen(nome)-1] = '\0';
		inserir_nome(bd, nome);
	}
    fclose(f);
}

void opc_listar(Arvore * bd) {
	imprimir(bd);
	printf("\n");
}

void opc_buscar(Arvore * bd) {
	ler_nome();
	imprimir_nomes_pref(bd, nome);
	printf("\n");
}

void opc_inserir(Arvore * bd) {
	ler_nome();
	inserir_nome(bd, nome);
}

void opc_remover(Arvore * bd) {
	ler_nome();
	remover_nome(bd, nome);
}

void opc_buscar_remover(Arvore * bd) {
	ler_nome();
	remover_nomes_pref(bd, nome);
}

void opc_sair() {
	printf("\nTchau!\n");
}

void pausar() {
	printf("\n");
	system("pause");
}

void processar_menu() {
	int opc;
	Arvore * bd = criar();
	opc_recarregar(bd);
	do {
		opc = ler_opcao();
		switch(opc) {
			case OPC_REC: 
				opc_recarregar(bd);
				break;
			case OPC_LST: 
				opc_listar(bd);
				break;
			case OPC_BSC: 
				opc_buscar(bd);
				break;
			case OPC_INS:
				opc_inserir(bd);
				break;
			case OPC_REM:
				opc_remover(bd);
				break;
			case OPC_BSC_REM:
				opc_buscar_remover(bd);
				break;
			case OPC_FIM:
				opc_sair();
				break;
		}
		pausar();
	} while(opc != OPC_FIM);
	destruir(bd);
}

///////////////////////////////////////////////////////////////////////////////

void _testar() {
	processar_menu();	
}

#endif
