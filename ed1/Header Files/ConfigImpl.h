///////////////////////////////////////////////////////////////////////////////

//#define TESTE_PILHA_ESTAT
//#define TESTE_FILA_ESTAT
//#define TESTE_FILA_ESTAT_CIRC
//#define TESTE_LISTA_ESTAT
//#define TESTE_LISTA_ENCAD
//#define TESTE_LISTA_ENCAD_SENT
//#define TESTE_LISTA_DUP_ENCAD_SENT

#ifdef TESTE_PILHA_ESTAT
#define IMPL_PILHA_ESTAT
#endif

#ifdef TESTE_FILA_ESTAT
#define IMPL_FILA_ESTAT
#endif

#ifdef TESTE_FILA_ESTAT_CIRC
#define IMPL_FILA_ESTAT_CIRC
#endif

#ifdef TESTE_LISTA_ESTAT
#define IMPL_LISTA_ESTAT
#endif

#ifdef TESTE_LISTA_ENCAD
#define IMPL_LISTA_ENCAD
#endif

#ifdef TESTE_LISTA_ENCAD_SENT
#define IMPL_LISTA_ENCAD_SENT
#endif

#ifdef TESTE_LISTA_DUP_ENCAD_SENT
#define IMPL_LISTA_DUP_ENCAD_SENT
#endif

///////////////////////////////////////////////////////////////////////////////

#define EXERCICIOS_PILHA
//#define EXERCICIOS_FILA
//#define EXERCICIOS_LISTA
//#define EXERCICIOS_REC
//#define TRABALHO_LISTA_1
//#define TRABALHO_PILHA_1

#ifdef EXERCICIOS_PILHA
#define IMPL_PILHA_ESTAT
#endif

#ifdef TRABALHO_PILHA_1
#define IMPL_PILHA_ESTAT
#endif

#ifdef EXERCICIOS_FILA
#define IMPL_FILA_ESTAT
//#define IMPL_FILA_ESTAT_CIRC
#endif

#ifdef EXERCICIOS_LISTA_ESTAT
#define IMPL_LISTA_ESTAT
//#define IMPL_LISTA_ENCAD
//#define IMPL_LISTA_ENCAD_SENT
//#define IMPL_LISTA_DUP_ENCAD_SENT
#endif

#ifdef TRABALHO_LISTA_1
#define IMPL_LISTA_DUP_ENCAD_SENT
#endif

///////////////////////////////////////////////////////////////////////////////

#ifdef IMPL_FILA_ESTAT
#define comum_FILA_ESTAT
#endif

#ifdef IMPL_FILA_ESTAT_CIRC
#define comum_FILA_ESTAT
#endif

#ifdef IMPL_LISTA_ESTAT
#define comum_LISTA
#endif

#ifdef IMPL_LISTA_ENCAD
#define comum_LISTA
#define comum_LISTA_ENCAD
#endif

#ifdef IMPL_LISTA_ENCAD_SENT
#define comum_LISTA
#define comum_LISTA_ENCAD
#define comum_LISTA_ENCAD_SENT
#endif

#ifdef IMPL_LISTA_DUP_ENCAD_SENT
#define comum_LISTA
#define comum_LISTA_ENCAD
#define comum_LISTA_ENCAD_SENT
#endif

///////////////////////////////////////////////////////////////////////////////

#include <pilhaEstat.h>
#include <filaEstat.h>
#include <listaEstat.h>
#include <listaEncad.h>

///////////////////////////////////////////////////////////////////////////////

//Operações comuns às implementações
void _testar();