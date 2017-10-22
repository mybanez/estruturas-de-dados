#include <stdio.h>
#include <stdlib.h>
#include <ConfigImpl.h>

#ifdef EXERCICIOS_LISTA

#ifdef IMPL_LISTA_ESTAT

Lista * unir (Lista * l1, Lista * l2) {
	int i, tam1 = tamanho(l1), tam2 = tamanho(l2);
    Lista * l3 = criar();
    for(i=0; i<tam1; i++) {
		l3->itens[i] = l1->itens[i]; 
    }
    for(i=0; i<tam2; i++) {
		l3->itens[i+tam1] = l2->itens[i]; 
    }
    l3->fim = tam1 + tam2;
    return l3;  
}      

void inverter (Lista * l) {
	int i, f, aux;
    for(i=0, f=tamanho(l)-1; i < f; i++,f--) {
		aux = l->itens[i]; 
		l->itens[i] = l->itens[f]; 
		l->itens[f] = aux;
    }
}

#endif

#ifdef IMPL_LISTA_DUP_ENCAD_SENT

void inverter (Lista * l) {
	int i; No * aux, * aux2 = l->ini; 
    for(i=0; i < tamanho(l)-1; i++) {
		aux = l->ini->prox;
		l->ini->prox = l->fim->prox;
		l->fim->prox = l->ini; 
		l->ini = aux;
    }
	l->fim = aux2;
}

#endif

///////////////////////////// QUESTÕES DE PROVAS //////////////////////////////

void remover_maior(Lista * l) {
	int i, v, mv;
	for(mv = primeiro(l), i = 1; i < tamanho(l); i++) {
		v = ler_pos(l,i);
		if (v > mv) {
			mv = v;
		}
	}
	for(i = 0; i < tamanho(l); i++) {
		v = ler_pos(l,i);
		if (v == mv) {
			remover_pos(l, i);
			i--;
		}
	}
}

#ifdef IMPL_LISTA_ESTAT

Lista * unir_ordenado (Lista * l1, Lista * l2) {
	int i, j, k;
    Lista * l3 = criar();
    for(i = l1->ini, j = l2->ini, k = 0; i < l1->fim && j < l2->fim; k++) {
		if (l1->itens[i] < l2->itens[j]) {
			l3->itens[k] = l1->itens[i++];
		} else {
			l3->itens[k] = l2->itens[j++];
		}
    }
    for(; i < l1->fim ; k++) {
		l3->itens[k] = l1->itens[i++];
    }
    for(; j < l2->fim ; k++) {
		l3->itens[k] = l2->itens[j++];
    }
	l3->fim = k;
    return l3;  
}      

#endif

#ifdef IMPL_LISTA_ENCAD

Lista * unir_ordenado (Lista * l1, Lista * l2) {
	No * aux1 = l1->ini, * aux2 = l2->ini, * aux3;
	Lista * l3 = criar();
    while(aux1 != NULL && aux2 != NULL) {
		aux3 = malloc(sizeof(No));
		aux3->prox = NULL;
		if (l3->ini == NULL) {
			l3->ini = aux3;
		}
		if (aux1->info < aux2->info) {
			aux3->info = aux1->info;
			aux1 = aux1->prox;
		} else {
			aux3->info = aux2->info;
			aux2 = aux2->prox;
		}
		if (l3->fim != NULL) {
			l3->fim->prox = aux3;
		}
		l3->fim = aux3;
    }
    while(aux1 != NULL) {
		aux3 = malloc(sizeof(No));
		aux3->prox = NULL;
		if (l3->ini == NULL) {
			l3->ini = aux3;
		}
		aux3->info = aux1->info;
		aux1 = aux1->prox;
		if (l3->fim != NULL) {
			l3->fim->prox = aux3;
		}
		l3->fim = aux3;
    }
    while(aux2 != NULL) {
		aux3 = malloc(sizeof(No));
		aux3->prox = NULL;
		if (l3->ini == NULL) {
			l3->ini = aux3;
		}
		aux3->info = aux2->info;
		aux2 = aux2->prox;
		if (l3->fim != NULL) {
			l3->fim->prox = aux3;
		}
		l3->fim = aux3;
    }
	l3->tam = l1->tam + l2->tam;
    return l3;  
}      

#endif

#ifdef IMPL_LISTA_DUP_ENCAD_SENT

Lista * unir_ordenado (Lista * l1, Lista * l2) {
	No * aux1 = l1->ini->prox, * aux2 = l2->ini->prox, * aux3;
	Lista * l3 = criar();
    while(aux1 != l1->fim && aux2 != l2->fim) {
		aux3 = malloc(sizeof(No));
		if (aux1->info < aux2->info) {
			aux3->info = aux1->info;
			aux1 = aux1->prox;
		} else {
			aux3->info = aux2->info;
			aux2 = aux2->prox;
		}
		aux3->ant = l3->fim->ant;
		l3->fim->ant = aux3;
		aux3->ant->prox = aux3;
		aux3->prox = l3->fim;
    }
    while(aux1 != l1->fim) {
		aux3 = malloc(sizeof(No));
		aux3->info = aux1->info;
		aux1 = aux1->prox;
		aux3->ant = l3->fim->ant;
		l3->fim->ant = aux3;
		aux3->ant->prox = aux3;
		aux3->prox = l3->fim;
    }
    while(aux2 != l2->fim) {
		aux3 = malloc(sizeof(No));
		aux3->info = aux2->info;
		aux2 = aux2->prox;
		aux3->ant = l3->fim->ant;
		l3->fim->ant = aux3;
		aux3->ant->prox = aux3;
		aux3->prox = l3->fim;
    }
	l3->tam = l1->tam + l2->tam;
    return l3;  
}      

#endif

///////////////////////////////////////////////////////////////////////////////

void _testar() {
	Lista * l = criar();
	Lista * l1 = criar();
	Lista * l2 = criar();

	inserir_ultimo(l, 1);
	inserir_ultimo(l, 4);
	inserir_ultimo(l, 3);
	inserir_ultimo(l, 4);
	inserir_ultimo(l, 1);
	//inverter(l);
	remover_maior(l);
	imprimir(l);
	destruir(l);

	inserir_ultimo(l1, 1);
	inserir_ultimo(l1, 3);
	inserir_ultimo(l1, 5);
	inserir_ultimo(l2, 2);
	inserir_ultimo(l2, 4);
	imprimir(unir_ordenado(l1, l2));
	destruir(l1);
	destruir(l2);

	system("pause");
}

#endif