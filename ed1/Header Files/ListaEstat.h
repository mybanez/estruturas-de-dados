#ifdef IMPL_LISTA_ESTAT

#include <Lista.h>

#define TAM_MAX 50

struct lista {
  int itens[TAM_MAX];
  int ini, fim;
};

//Opera��es externas usadas pelas implementa��es de Lista Est�tica
int _posicao_valida(Lista * l, int p);

#endif