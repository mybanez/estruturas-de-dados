#ifdef comum_PESQ_NARIA

typedef struct no No;

struct arvore {
	No * raiz;
};

//Opera��es comuns �s implementa��es de �rvore N-�ria
int _buscar_chave_no(No * no, int inf);

#endif

#ifdef _struct_PESQ_NARIA

#define ORDEM 7

struct no {
  int nfilhos;
  int chaves[ORDEM-1];
  No * filhos[ORDEM];
};

#endif