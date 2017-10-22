#ifdef comum_GEN_PNT

typedef struct no No;

struct arvore {
	No * raiz;
};

#endif

#ifdef IMPL_GEN_PNT

struct no {
	char inf;
	No * pai;
	No * filho;
	No * irmao;
};

#endif

#ifdef IMPL_GEN_PNT2

#define MAX_FILHOS 5

struct no {
	char inf;
	No * pai;
	No * filhos[MAX_FILHOS];
};

#endif

