#include <stdio.h>
#include <stdlib.h>
#include <ConfigImpl.h>

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