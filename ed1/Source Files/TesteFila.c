#include <stdio.h>
#include <stdlib.h>
#include <ConfigImpl.h>

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
