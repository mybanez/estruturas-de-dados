#ifdef comum_LISTA_ENCAD

#include <Lista.h>

typedef struct no No;

struct lista {
  No * ini;
  No * fim;  
  int tam;  
};

//Operações externas usadas pelas implementações de Lista Encadeada
int _posicao_valida(Lista * l, int p);
No * _obter_no_pos(Lista * l, int p);

#endif

#if defined(IMPL_LISTA_ENCAD) || defined(IMPL_LISTA_ENCAD_SENT)

struct no {
  int info;
  No * prox;
};

#endif

#ifdef IMPL_LISTA_DUP_ENCAD_SENT

struct no {
  int info;
  No * prox;
  No * ant;
};

#endif

