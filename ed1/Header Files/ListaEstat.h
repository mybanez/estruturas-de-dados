#ifdef IMPL_LISTA_ESTAT

#include <Lista.h>

#define TAM_MAX 50

struct lista {
  int itens[TAM_MAX];
  int ini, fim;
};

//Operações externas usadas pelas implementações de Lista Estática
int _posicao_valida(Lista * l, int p);

#endif