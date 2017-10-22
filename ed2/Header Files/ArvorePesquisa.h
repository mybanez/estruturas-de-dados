//TAD Árvore de Pesquisa

int antecessor(Arvore * arv, int inf);
int sucessor(Arvore * arv, int inf);
int maior(Arvore * arv);
int menor(Arvore * arv);
#ifdef ARVORE_INFO_EXT
typedef struct info Info;
Info * buscar(Arvore * arv, int inf);
void inserir(Arvore * arv, int inf, Info * inf_ext);
#else
int buscar(Arvore * arv, int inf);
void inserir(Arvore * arv, int inf);
#endif
void remover(Arvore * arv, int inf);




