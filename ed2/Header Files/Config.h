///////////////////////////////////////////////////////////////////////////////

//#define TESTE_GEN_PNT
//#define TESTE_GEN_PNT2
//#define TESTE_BIN_VET
//#define TESTE_PESQ_BIN_ITER
#define TESTE_PESQ_BIN_REC
//#define TESTE_PESQ_AVL
//#define TESTE_PESQ_RB
//#define TESTE_PESQ_NARIA_ITER
//#define TESTE_PESQ_NARIA_REC
//#define TESTE_PESQ_B
//#define TESTE_PESQ_BMAIS

//#define EXERCICIOS_GEN
#define EXERCICIOS_BIN
//#define EXERCICIOS_PESQ_AVL
//#define EXERCICIOS_PESQ_RB
//#define TRABALHO_BIN_1
//#define TRABALHO_BIN_2

///////////////////////////////////////////////////////////////////////////////

#ifdef TESTE_GEN_PNT
#define IMPL_GEN_PNT
#endif

#ifdef TESTE_GEN_PNT2
#define IMPL_GEN_PNT2
#endif

#ifdef TESTE_BIN_VET
#define IMPL_BIN_IMP
#endif

#ifdef TESTE_PESQ_BIN_ITER
#define IMPL_PESQ_BIN_ITER
#endif

#ifdef TESTE_PESQ_BIN_REC
#define IMPL_PESQ_BIN_REC
#endif

#ifdef TESTE_PESQ_AVL
#define IMPL_PESQ_AVL
#endif

#ifdef TESTE_PESQ_RB
#define IMPL_PESQ_RB
#endif

#ifdef TESTE_PESQ_NARIA_ITER
#define IMPL_PESQ_NARIA_ITER
#endif

#ifdef TESTE_PESQ_NARIA_REC
#define IMPL_PESQ_NARIA_REC
#endif

#ifdef TESTE_PESQ_B
#define IMPL_PESQ_B
#endif

#ifdef TESTE_PESQ_BMAIS
#define IMPL_PESQ_BMAIS
#endif

///////////////////////////////////////////////////////////////////////////////

#ifdef IMPL_GEN_PNT
#define comum_ARVORE
#define comum_GEN_PNT
#endif

#ifdef IMPL_GEN_PNT2
#define comum_ARVORE
#define comum_GEN_PNT
#endif

#ifdef IMPL_BIN_IMP
#define comum_ARVORE
#endif

#ifdef IMPL_PESQ_BIN_ITER
#define comum_ARVORE
#define comum_BIN_PNT
#define _struct_BIN_PESQ
#define _iniciar_BIN_PNT
#define _imprimir_info_BIN_PNT 
#define buscar_PESQ_BIN_ITER
#define inserir_PESQ_BIN_ITER
#define remover_PESQ_BIN_ITER
#endif

#ifdef IMPL_PESQ_BIN_REC
#define comum_ARVORE
#define comum_BIN_PNT
#define _struct_BIN_PESQ
#define _iniciar_BIN_PNT
#define _imprimir_info_BIN_PNT 
#define buscar_PESQ_BIN_REC
#define inserir_PESQ_BIN_REC//2
#define remover_PESQ_BIN_REC//2
#endif

#ifdef IMPL_PESQ_AVL
#define comum_ARVORE
#define comum_BIN_PNT
#define _struct_PESQ_AVL
#define _iniciar_BIN_PNT
#define _imprimir_info_PESQ_AVL 
#define buscar_PESQ_BIN_ITER
#define inserir_PESQ_AVL
#define remover_PESQ_AVL
#endif

#ifdef IMPL_PESQ_RB
#define comum_ARVORE
#define comum_BIN_PNT
#define _struct_PESQ_RB
#define _iniciar_PESQ_RB
#define _imprimir_info_PESQ_RB
#define buscar_PESQ_BIN_ITER
#define inserir_PESQ_RB
#define remover_PESQ_RB
#endif

#ifdef IMPL_PESQ_NARIA_ITER
#define comum_ARVORE
#define comum_PESQ_NARIA
#define _struct_PESQ_NARIA
#define _manter_no_PESQ_NARIA
#define imprimir_PESQ_NARIA
#define sucessor_PESQ_NARIA
#define buscar_PESQ_NARIA_ITER
#define inserir_PESQ_NARIA_ITER
#define remover_PESQ_NARIA_ITER
#endif

#ifdef IMPL_PESQ_NARIA_REC
#define comum_ARVORE
#define comum_PESQ_NARIA
#define _struct_PESQ_NARIA
#define _manter_no_PESQ_NARIA
#define imprimir_PESQ_NARIA
#define sucessor_PESQ_NARIA
#define buscar_PESQ_NARIA_REC
#define inserir_PESQ_NARIA_REC
#define remover_PESQ_NARIA_REC
#endif

#ifdef IMPL_PESQ_B
#define comum_ARVORE
#define comum_PESQ_NARIA
#define comum_PESQ_B
#define _struct_PESQ_NARIA
#define _manter_no_PESQ_B
#define imprimir_PESQ_NARIA
#define sucessor_PESQ_NARIA
#define buscar_PESQ_NARIA_ITER
#define inserir_PESQ_B
#define remover_PESQ_B
#endif

#ifdef IMPL_PESQ_BMAIS
#define comum_ARVORE
#define comum_PESQ_NARIA
#define comum_PESQ_B
#define _struct_PESQ_BMAIS
#define _manter_no_PESQ_BMAIS
#define imprimir_PESQ_BMAIS
#define sucessor_PESQ_BMAIS
#define buscar_PESQ_BMAIS
#define inserir_PESQ_BMAIS
#define remover_PESQ_BMAIS
#endif

///////////////////////////////////////////////////////////////////////////////

#ifdef EXERCICIOS_GEN
#undef TESTE_GEN_PNT
#endif

#ifdef EXERCICIOS_BIN
#undef TESTE_PESQ_BIN_ITER
#undef TESTE_PESQ_BIN_REC
#undef _imprimir_info_BIN_PNT
#endif

#ifdef EXERCICIOS_PESQ_AVL
#undef TESTE_PESQ_AVL
#endif

#ifdef EXERCICIOS_PESQ_RB
#undef TESTE_PESQ_RB
#undef _iniciar_PESQ_RB
#define _iniciar_BIN_PNT
#undef inserir_PESQ_RB
#define inserir_PESQ_BIN_ITER
#endif

#ifdef TRABALHO_BIN_1
#define comum_ARVORE
#define comum_BIN_PNT
#define _iniciar_BIN_PNT
#endif

#ifdef TRABALHO_BIN_2
#undef TESTE_PESQ_BIN_ITER
#undef TESTE_PESQ_BIN_REC
#undef TESTE_PESQ_AVL
#undef _imprimir_info_PESQ_AVL 
#undef TESTE_PESQ_RB
#define ARVORE_INFO_EXT
#endif

///////////////////////////////////////////////////////////////////////////////

//TAD
#include <Arvore.h>
#include <ArvorePesquisa.h>
//Implementações
#include <ArvoreImpl.h>
#include <ArvoreGenericaPnt.h>
#include <ArvoreBinariaPnt.h>
#include <ArvoreBinariaVet.h>
#include <ArvorePesquisaBinaria.h>
#include <ArvorePesquisaAVL.h>
#include <ArvorePesquisaRB.h>
#include <ArvorePesquisaNAria.h>
#include <ArvorePesquisaB.h>
#include <ArvorePesquisaBMais.h>
//Implementações Trabalhos
#include <ArvoreNomes.h>

///////////////////////////////////////////////////////////////////////////////
