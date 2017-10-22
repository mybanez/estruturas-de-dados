#include <stdio.h>
#include <stdlib.h>
#include <Config.h>

////////////////////////////////////////////////////////////////////////////////

#if defined(TESTE_PESQ_NARIA_ITER) || \
    defined(TESTE_PESQ_NARIA_REC) || \
    defined(TESTE_PESQ_B) || \
    defined(TESTE_PESQ_BMAIS)

void _testar() {
	int i;

	int ins[] = {30, 40, 35, 10, 31, 37, 50, 36, 38, 45, 99, 
		         80,  5, 15, 33, 39, 13, 20, 25, 18, 34, 32};

	int rem[] = {10, 40, 80, 45, 50, 99, 35, 39, 20, 25, 30,
		         18, 36, 32, 13, 38, 31, 37, 33, 15,  5, 34};

	Arvore * arv = criar();

	for (i = 0; i<22; i++) {
		printf("Inseriu: %d\n", ins[i]);
		inserir(arv, ins[i]);
		imprimir(arv);
		printf("\n");         
	}

	printf("\n");         
	printf("Achou 32: %c\n", buscar(arv, 32) ? 'S' : 'N');         
	printf("Achou 19: %c\n", buscar(arv, 19) ? 'S' : 'N');         
	printf("\n");         

	for (i = 0; i<22; i++) {
		printf("Sucessor de %d: %d\n", ins[i], sucessor(arv, ins[i]));
	}
	printf("Sucessor de 19: %d\n", sucessor(arv, 19));
	printf("\n");         

	for (i = 0; i<22; i++) {
		printf("Removeu: %d\n", rem[i]);
		remover(arv, rem[i]);
		imprimir(arv);
		printf("\n");         
	}

	printf("\n");         
	printf("Achou 32: %c\n", buscar(arv, 32) ? 'S' : 'N');         

	destruir(arv);

	system("pause");
}     

#endif

////////////////////////////////////////////////////////////////////////////////
