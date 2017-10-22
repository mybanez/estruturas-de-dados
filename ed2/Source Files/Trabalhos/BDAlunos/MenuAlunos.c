#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <Config.h>

#ifdef TRABALHO_BIN_2

///////////////////////////////////////////////////////////////////////////////

#define TAM_MENU 12
#define OPC_GAR 1
#define OPC_CAR 2
#define OPC_LST 3
#define OPC_BSC 4
#define OPC_BSL 5
#define OPC_INS 6
#define OPC_ALT 7
#define OPC_REM 8
#define OPC_REL 9
#define OPC_RET 10
#define OPC_SAL 11
#define OPC_FIM 12

int ler_opcao() {
	int opc;
	do {
		system("cls");
		printf("ESCOLHA A OPCAO:\n");
		printf("(1) Gerar arquivos\n");
		printf("(2) Carregar base\n");
		printf("(3) Listar\n");
		printf("(4) Buscar\n");
		printf("(5) Buscar em lote\n");
		printf("(6) Inserir\n");
		printf("(7) Alterar\n");
		printf("(8) Remover\n");
		printf("(9) Remover em lote\n");
		printf("(10) Remover todos\n");
		printf("(11) Salvar base\n");
		printf("(12) Sair\n");
		printf("\n");
		printf("Opcao: ");
		scanf("%d", &opc);
		printf("\n");
		fgetchar(); //Elimina '\n' de stdin
	} while (opc < 1 || opc > TAM_MENU);
	return opc;
}

int ler_confirmacao() {
	char c[2];
	printf("Confirma ? (S / N) ");
	scanf_s("%s", c, 2);
	printf("\n");
	return c[0] == 'S' || c[0] == 's';
}


///////////////////////////////////////////////////////////////////////////////

#define TAM_NOME_ARQ 19

char arq_alunos[TAM_NOME_ARQ];
char arq_mat[TAM_NOME_ARQ];

void ler_nome_arquivo(char * arq) {
	int manter_arq = 0;
	if (arq[0] != '\0') {
		printf("Arquivo atual: %s\n\n", arq);
		manter_arq = ler_confirmacao();
	}
	if (!manter_arq) {
		printf("Arquivo: ");
		scanf_s("%s", arq, TAM_NOME_ARQ);
		printf("\n");
	}
}

///////////////////////////////////////////////////////////////////////////////

#define TAM_MATRICULA 11
#define TAM_NOME 22
#define TAM_EMAIL 22
#define TAM_FONE 11

int mat;
struct info {
	char nome[TAM_NOME];
	char email[TAM_EMAIL];
	char fone[TAM_FONE];
} inf_ext, *pinf;

void ler_matricula() {
	char m[TAM_MATRICULA];
	printf("Matrícula: ");
	fgets(m, TAM_MATRICULA, stdin);
	m[strlen(m) - 1] = '\0';
	mat = atoi(m);
}

void ler_nome(char * nome) {
	printf("Nome: ");
	fgets(nome, TAM_NOME, stdin);
	nome[strlen(nome) - 1] = '\0';
}

void ler_email(char * email) {
	printf("Email: ");
	fgets(email, TAM_EMAIL, stdin);
	email[strlen(email) - 1] = '\0';
}

void ler_fone(char * fone) {
	printf("Fone: ");
	fgets(fone, TAM_FONE, stdin);
	fone[strlen(fone) - 1] = '\0';
}

///////////////////////////////////////////////////////////////////////////////

#define POT_MAX TAM_MATRICULA-3
#define N_SEQ 1
#define SEQ1 "0d1d2d3d4d5d6d7d8d9d"
#define SEQ2 "9e8e7e6e5e4e2e3e1e0e"
#define SEQ3 "4e3e2e1e0e5d6d7d8d9d"
#define SEQ4 "4e9d1e2d6e7d0e3d5e8d"
#define NME_ARQ1 "BDAlunos10e?v?.txt"
#define NME_ARQ2 "PesqAlunos10e?.txt"
#define FMT_REG1 "%.?ld|Aluno mat. %.?ld|%.?ld@ffb.edu.br|9%.3ld.%.4ld\n"
#define FMT_REG2 "%.?ld\n"

char fmt1[] = FMT_REG1;
char fmt2[] = FMT_REG2;

void conf_fmt1() {
	fmt1[2] = fmt1[19] = fmt1[25] = '0' + POT_MAX + 1;
}

void conf_fmt2() {
	fmt2[2] = '0' + POT_MAX + 1;
}

void opc_gerar_arquivos() {
	FILE * f1, *f2;
	char nome1[] = NME_ARQ1, nome2[] = NME_ARQ2;
	char *seq[] = { SEQ1, /*SEQ2, SEQ3, SEQ4*/ };
	int i, p, s, dig, dir, inc[] = { 1,-1 };
	long j, n, mat, cpl[] = { 1,1 };

	for (s = 0; s < N_SEQ; s++) {
		nome1[13] = '1' + s;
		for (p = 1, n = 1; p <= POT_MAX; p++, n *= 10) {
			nome1[11] = '0' + p;
			printf("%s\n", nome1);
			f1 = fopen(nome1, "w");
			for (i = 0, cpl[1] = n; i < 20; i += 2) {
				for (j = 0, dig = seq[s][i] - '0', dir = seq[s][i + 1] - 'd', mat = dig*n + cpl[dir]; j < n; j++, mat += inc[dir]) {
					fprintf(f1, fmt1, mat, mat, mat, mat / (long)1e4, mat % (long)1e4);
				}
			}
			fclose(f1);
		}
	}
	for (p = 1, n = 10; p < POT_MAX; p++, n *= 10) {
		nome2[13] = '0' + p;
		printf("%s\n", nome2);
		f2 = fopen(nome2, "w");
		for (i = 0, mat = 10; i < n; i++, mat += 10) {
			fprintf(f2, fmt2, mat);
		}
		fclose(f2);
	}
	printf("\nArquivos gerados\n");
}

///////////////////////////////////////////////////////////////////////////////

#define FMT_REG3 "%ld %*c %??[^|] %*c %??[^|] %*c %??[^\n]"

char fmt3[] = FMT_REG3;

void conf_fmt3() {
	fmt3[9] = '0' + (TAM_NOME - 1) / 10;
	fmt3[10] = '0' + (TAM_NOME - 1) % 10;
	fmt3[21] = '0' + (TAM_EMAIL - 1) / 10;
	fmt3[22] = '0' + (TAM_EMAIL - 1) % 10;
	fmt3[33] = '0' + (TAM_FONE - 1) / 10;
	fmt3[34] = '0' + (TAM_FONE - 1) % 10;
}

void opc_carregar(Arvore * bd) {
	FILE * f;
	clock_t tic, tac;

	limpar(bd);
	ler_nome_arquivo(arq_alunos);
	f = fopen(arq_alunos, "r");
	if (f != NULL) {
		tic = clock();
		while (!feof(f)) {
			pinf = malloc(sizeof(Info));
			if (pinf != NULL) {
				fscanf(f, fmt3, &mat, &pinf->nome, &pinf->email, &pinf->fone);
				inserir(bd, mat, pinf);
			}
			else {
				printf("Memória insuficiente\n\n");
				break;
			}
		}
		tac = clock();
		fclose(f);
		printf("Alunos carregados\n\n");
		printf("Tempo de carga: %f segundos\n", (double)(tac - tic) / CLOCKS_PER_SEC);
	} else {
		printf("Não foi possível abrir o arquivo\n");
	}
}

///////////////////////////////////////////////////////////////////////////////

#define FMT_REG4 "%.?ld | %s | %s | %s\n"
#define FMT_REG5 "%.?ld|%s|%s|%s\n"

char fmt4[] = FMT_REG4;
char fmt5[] = FMT_REG5;

void conf_fmt4() {
	fmt4[2] = '0' + POT_MAX + 1;
}

void conf_fmt5() {
	fmt5[2] = '0' + POT_MAX + 1;
}

FILE * saida;
char * fmt;

void _imprimir_info(int inf, void * inf_ext) {
	pinf = (Info *)inf_ext;
	fprintf(saida, fmt, inf, pinf->nome, pinf->email, pinf->fone);
}

void opc_listar(Arvore * bd) {
	saida = stdout;
	fmt = fmt4;
	imprimir(bd);
}

///////////////////////////////////////////////////////////////////////////////

void opc_buscar(Arvore * bd) {
	ler_matricula();
	printf("\n");
	pinf = buscar(bd, mat);
	if (pinf != NULL) {
		printf(fmt4, mat, pinf->nome, pinf->email, pinf->fone);
	} else {
		printf("Aluno inexistente\n");
	}
}

///////////////////////////////////////////////////////////////////////////////

#define FMT_REG6 "%ld\n"

void opc_buscar_lote(Arvore * bd) {
	FILE * f;
	clock_t tic, tac;

	ler_nome_arquivo(arq_mat);
	f = fopen(arq_mat, "r");
	if (f != NULL) {
		tic = clock();
		while (!feof(f)) {
			fscanf(f, FMT_REG6, &mat);
			pinf = buscar(bd, mat);
			if (pinf != NULL) {
				printf(fmt4, mat, pinf->nome, pinf->email, pinf->fone);
			}
		}
		tac = clock();
		fclose(f);
		printf("\nTempo de consulta: %f segundos\n", (double)(tac-tic)/CLOCKS_PER_SEC);
	} else {
		printf("Não foi possível abrir o arquivo\n");
	}
}

///////////////////////////////////////////////////////////////////////////////

void opc_inserir(Arvore * bd) {
	pinf = malloc(sizeof(Info));
	mat = maior(bd)+1;
	if (mat == 0) mat++;
	printf("Matrícula: %ld\n", mat);
	ler_nome(pinf->nome);
	ler_email(pinf->email);
	ler_fone(pinf->fone);
	printf("\n");
	if (ler_confirmacao()) {
		inserir(bd, mat, pinf);
		printf("Aluno inserido\n");
	}
}

///////////////////////////////////////////////////////////////////////////////

void opc_alterar(Arvore * bd) {
	opc_buscar(bd);
	if (pinf != NULL) {
		printf("\n");
		ler_nome(inf_ext.nome);
		ler_email(inf_ext.email);
		ler_fone(inf_ext.fone);
		if (inf_ext.nome[0] != '\0' || 
			inf_ext.email[0] != '\0' || 
			inf_ext.fone[0] != '\0') {
			printf("\n");
			if (ler_confirmacao()) {
				if (inf_ext.nome[0] != '\0' ) {
					strcpy(pinf->nome, inf_ext.nome);
				}
				if (inf_ext.email[0] != '\0') {
					strcpy(pinf->email, inf_ext.email);
				}
				if (inf_ext.fone[0] != '\0') {
					strcpy(pinf->fone, inf_ext.fone);
				}
				printf("Aluno alterado\n");
			}
		}
	} 
}

///////////////////////////////////////////////////////////////////////////////

void opc_remover(Arvore * bd) {
	opc_buscar(bd);
	printf("\n");
	if (ler_confirmacao()) {
		remover(bd, mat);
		printf("Aluno removido\n");
	}
}

///////////////////////////////////////////////////////////////////////////////

void opc_remover_lote(Arvore * bd) {
	FILE * f;
	clock_t tic, tac;

	ler_nome_arquivo(arq_mat);
	f = fopen(arq_mat, "r");
	if (f != NULL) {
		tic = clock();
		while (!feof(f)) {
			fscanf(f, FMT_REG6, &mat);
			remover(bd, mat);
		}
		tac = clock();
		fclose(f);
		printf("Tempo de remoção: %f segundos\n", (double)(tac - tic) / CLOCKS_PER_SEC);
    } else {
		printf("Não foi possível abrir o arquivo\n");
	}
}

///////////////////////////////////////////////////////////////////////////////

void opc_remover_todos(Arvore * bd) {
	if (ler_confirmacao()) {
		limpar(bd);
		printf("Alunos removidos\n");
	}
}

///////////////////////////////////////////////////////////////////////////////

void opc_salvar(Arvore * bd) {
	ler_nome_arquivo(arq_alunos);
	saida = fopen(arq_alunos, "w");
	fmt = fmt5;
	if (saida != NULL) {
		imprimir(bd);
		fclose(saida);
		printf("Alunos salvos\n");
	} else {
		printf("Não foi possível abrir o arquivo\n");
	}
}

///////////////////////////////////////////////////////////////////////////////

void opc_sair() {
	printf("Tchau!\n");
}

///////////////////////////////////////////////////////////////////////////////

void pausar() {
	printf("\n");
	system("pause");
}

///////////////////////////////////////////////////////////////////////////////

void configurar() {
	conf_fmt1();
	conf_fmt2();
	conf_fmt3();
	conf_fmt4();
	conf_fmt5();
}

void processar_menu() {
	int opc;
	Arvore * bd = criar();
	configurar();
	do {
		opc = ler_opcao();
		switch (opc) {
		case OPC_GAR:
			opc_gerar_arquivos();
			break;
		case OPC_CAR:
			opc_carregar(bd);
			break;
		case OPC_LST:
			opc_listar(bd);
			break;
		case OPC_BSC:
			opc_buscar(bd);
			break;
		case OPC_BSL:
			opc_buscar_lote(bd);
			break;
		case OPC_ALT:
			opc_alterar(bd);
			break;
		case OPC_INS:
			opc_inserir(bd);
			break;
		case OPC_REM:
			opc_remover(bd);
			break;
		case OPC_REL:
			opc_remover_lote(bd);
			break;
		case OPC_RET:
			opc_remover_todos(bd);
			break;
		case OPC_SAL:
			opc_salvar(bd);
			break;
		case OPC_FIM:
			opc_sair();
			break;
		}
		pausar();
	} while (opc != OPC_FIM);
	destruir(bd);
}

///////////////////////////////////////////////////////////////////////////////

void _testar() {
	processar_menu();
}

#endif
