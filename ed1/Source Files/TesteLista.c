#include <stdio.h>
#include <stdlib.h>
#include <ConfigImpl.h>

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
	imprimir(l);
	printf("Posição 1: %d\n", ler_pos(l, 1));    
	imprimir(l);    

    destruir(l);
    
    system("pause");
}

#endif
