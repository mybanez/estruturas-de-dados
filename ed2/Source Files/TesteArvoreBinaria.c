#include <stdio.h>
#include <stdlib.h>
#include <Config.h>

///////////////////////////////////////////////////////////////////////////////

#ifdef TESTE_BIN_VET

void _testar() {
	Arvore * arv = criar();
	arv->nos[0] = 'A';
	arv->nos[1] = 'B';
	arv->nos[2] = 'C';	
	arv->nos[3] = 'D';	
	arv->nos[5] = 'E';	
	arv->nos[6] = 'F';	
	arv->nos[8] = 'G';	
	arv->nos[12] = 'H';	
	imprimir(arv);
	printf("\n");
	system("pause");
}         

#endif

///////////////////////////////////////////////////////////////////////////////

#if defined(TESTE_PESQ_BIN_ITER) || \
	defined(TESTE_PESQ_BIN_REC)

void _testar() {
	int i;
    int arr[] = {50, 20, 39, 8, 79, 26, 58, 15, 88, 4, 85, 96, 71, 42, 53};
	Arvore * arv = criar();
    for (i = 0; i<15; i++) {
       inserir(arv, arr[i]);    
    }
	imprimir(arv);
    printf("\n");
	printf("Buscar 39: %c\n", buscar(arv, 39) ? 'S' : 'N');
	printf("Buscar 99: %c\n", buscar(arv, 99) ? 'S' : 'N');
    remover(arv, 53);
    remover(arv, 58);
    remover(arv, 20);
    remover(arv, 50);
    imprimir(arv);
    printf("\n");
	destruir(arv);
    system("pause");
}     
                     
#endif

///////////////////////////////////////////////////////////////////////////////

#ifdef TESTE_PESQ_AVL

int verificar_AVL(Arvore * arv);

void _testar() {
	int i;
	int ins[] = {30, 40, 35, 10, 31, 37, 50, 36, 38, 45, 99, 
                 80,  5, 15, 33, 39, 13, 20, 25, 18, 34, 32};
    int rem[] = {40, 39, 50, 38, 36, 99, 30, 25, 20, 15, 13, 1};

	Arvore * arv = criar();
/*
	for (int i = 1; i<=10000000; i++) {
		inserir(arv, i);
	}
	imprimir(arv);
	printf("\n");
*/
    for (i = 0; i<22; i++) {
        inserir(arv, ins[i]);
        imprimir(arv);
        printf("\n");         
    }

    printf("\nAltura da árvore: %d\n\n", verificar_AVL(arv));

    for (i = 0; i<12; i++) {
        remover(arv, rem[i]);    
        imprimir(arv);
        printf("\n");
    }
     
    printf("\nAltura da árvore: %d\n\n", verificar_AVL(arv));

	destruir(arv);

    system("pause");
}     

#endif

///////////////////////////////////////////////////////////////////////////////

#ifdef TESTE_PESQ_RB

int verificar_RB(Arvore * arv);

void _testar() {
	int i;
	int ins[] = {18, 15, 22, 13, 20, 27};
    int rem[] = {15};
 
	Arvore * arv = criar();
/*  
	for (int i = 1; i<=10000000; i++) {
       inserir(arv, i);
    }
    imprimir(arv);
    printf("\n"); 
*/       	
    for (i = 0; i<6; i++) {
        inserir(arv, ins[i]);
        imprimir(arv);
        printf("\n");         
    }

    printf("\nAltura da árvore: %d\n\n", verificar_RB(arv));
    for (i = 0; i<1; i++) {
        remover(arv, rem[i]);    
	    imprimir(arv);
		printf("\n");
	}

	printf("\nAltura da árvore: %d\n\n", verificar_RB(arv));

	destruir(arv);

	system("pause");
}     
                     
#endif

////////////////////////////////////////////////////////////////////////////////