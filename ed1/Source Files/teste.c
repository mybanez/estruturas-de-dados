#include <stdio.h>
#include <stdlib.h>
#include <configImpl.h>

///////////////////////////////////////////////////////////////////////////////

#ifdef TESTE_PILHA_ESTAT

void _testar() {
    Pilha * p = criar();
    
    empilhar(p, 5);
    empilhar(p, 2);
    
    printf("Tamanho: %d\n", tamanho(p));
    
    desempilhar(p);
    
    printf("Topo: %d\n", topo(p));
    
    destruir(p);
    
    system("pause");
}

#endif

///////////////////////////////////////////////////////////////////////////////

#if defined(TESTE_FILA_ESTAT) || \
    defined(TESTE_FILA_ESTAT_CIRC)

void _testar () {
    Fila * f = criar();
    
    enfileirar(f, 5);
    enfileirar(f, 2);
    enfileirar(f, 6);
    enfileirar(f, 7);
    enfileirar(f, 1);
    enfileirar(f, 9);
    
    
    printf("Tamanho: %d\n", tamanho(f));
    
    desenfileirar(f);
    desenfileirar(f);
    desenfileirar(f);
    desenfileirar(f);    
    
    printf("Primeiro: %d\n", primeiro(f));

    enfileirar(f, 6);
    enfileirar(f, 7);
    enfileirar(f, 8);

    printf("Tamanho: %d\n", tamanho(f));
    
    desenfileirar(f);
    desenfileirar(f);
    
    printf("Primeiro: %d\n", primeiro(f));    
    
    destruir(f);
    
    system("pause");
}

#endif

///////////////////////////////////////////////////////////////////////////////

#if defined(TESTE_LISTA_ESTAT) || \
    defined(TESTE_LISTA_ENCAD) || \
    defined(TESTE_LISTA_ENCAD_SENT) || \
	defined(TESTE_LISTA_DUP_ENCAD_SENT)

void _testar() {
    Lista * l = criar();

    inserir_ultimo(l, 1);
    inserir_ultimo(l, 2);
    inserir_primeiro(l, 2);
    inserir_primeiro(l, 2);
    inserir_primeiro(l, 2);    
    inserir_ultimo(l, 5);
    inserir_ultimo(l, 2);
    imprimir(l);    

    remover_todos(l, 2);
    imprimir(l);    

    remover_primeiro(l);    
    remover(l, 5);
    imprimir(l);        

    inserir_pos(l, 0, 0);
    inserir_pos(l, 1, 4);
    inserir_pos(l, 1, 5);
    imprimir(l);    
    
    remover_todos(l, 0);
    imprimir(l);    

	escrever_pos(l, 1, 10);
	printf("Posição 1: %d\n", ler_pos(l, 1));    
	imprimir(l);    

    destruir(l);
    
    system("pause");
}

#endif

///////////////////////////////////////////////////////////////////////////////