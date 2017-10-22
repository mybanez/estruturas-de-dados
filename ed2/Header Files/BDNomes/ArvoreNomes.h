#ifdef TRABALHO_BIN_1

#define TAM_MAX_NOME 51

void imprimir_nomes_pref(Arvore * arv, char * inf);
void inserir_nome(Arvore * arv, char * inf);
void remover_nome(Arvore * arv, char * inf);
void remover_nomes_pref(Arvore * arv, char * inf);

struct no {
	char inf[TAM_MAX_NOME];
	No * esq;
	No * dir;
};

#endif