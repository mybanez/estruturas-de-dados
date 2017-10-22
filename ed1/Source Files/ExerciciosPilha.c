#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ConfigImpl.h>

#ifdef EXERCICIOS_PILHA


////////////////////////////// QUESTÃO 3 ////////////////////////////////////////

Pilha * unir_ordenado(Pilha * p1, Pilha * p2) {
	Pilha * aux1 = criar(), * aux2 = criar();
	while(!esta_vazia(p1) && !esta_vazia(p2)) {
	    empilhar(aux1, topo(p1) > topo(p2) ? desempilhar(p1) : desempilhar(p2));
	}
	while(!esta_vazia(p1)) {
	    empilhar(aux1, desempilhar(p1));
	}
	while(!esta_vazia(p2)) {
	    empilhar(aux1, desempilhar(p2));
	} 
	while(!esta_vazia(aux1)) {
	    empilhar(aux2, desempilhar(aux1));
	} 
	destruir(aux1);
	return aux2;
}

////////////////////////////// QUESTÃO 6 ////////////////////////////////////////

char * inverter_letras(char * s) {
	int i = 0, inip = 0;   
	char c, * sinv = NULL;
	Pilha * p;
	if(s != NULL) {
	    sinv = (char *)malloc(strlen(s)+1);
	    p = criar();  
	    do {
			c = s[i++];    
			if (c == ' ' || c == '\0') {
				while(!esta_vazia(p)) {
					sinv[inip++] = desempilhar(p);     
				}
				sinv[inip++]=c;         
			} else {
				empilhar(p,c);             
			}       
		} while (c != '\0');  
		destruir(p);
	}           
	return sinv;
}

////////////////////////////// QUESTÃO 8 ////////////////////////////////////////

int eh_palindromo(char s[]) {
	char c; int i = 0;   
	Pilha * p;
	if(s != NULL) {
	    p = criar();
	    while ((c = s[i++]) != '\0') {
			empilhar(p, c);
		}
		i = 0;
	    while ((c = s[i++]) != '\0') {
			if (c != desempilhar(p)) {
				return 0;
			}
		}
		destruir(p);
	}           
	return 1;
}

///////////////////////////// QUESTÕES DE PROVAS //////////////////////////////

void empilhar_meio(Pilha * p, int v) {
	int tam_div = tamanho(p)/2;   
	Pilha * aux = criar();
	while (tamanho(aux) < tam_div) {
		empilhar(aux, desempilhar(p));
	}
	empilhar(p, v);
	while (!esta_vazia(aux)) {
		empilhar(p, desempilhar(aux));
	}
	destruir(aux);
}

void corrigir_hanoi(Pilha * p) {
	if (tamanho(p) > 1) {
		Pilha * aux = criar();
		empilhar(aux, desempilhar(p));
		while (!esta_vazia(p) && topo(p) > topo(aux)) {
			empilhar(aux, desempilhar(p));
		}
		if (!esta_vazia(p)) {
			int v = desempilhar(p);
			empilhar(p, desempilhar(aux));
			empilhar(p, v);
		}
		while (!esta_vazia(aux)) {
			empilhar(p, desempilhar(aux));
		}
		destruir(aux);
	}
}

void clonar_itens(Pilha * p) {
	Pilha * aux = criar();
	while (!esta_vazia(p)) {
		empilhar(aux, desempilhar(p));
	}
	while (!esta_vazia(aux)) {
		empilhar(p, topo(aux));
		empilhar(p, desempilhar(aux));
	}
	destruir(aux);
}

void retirar_repetidos(Pilha * p) {
	int nb, tam = tamanho(p);
	Pilha * aux = criar();
	for (nb = 0; nb < tam-1; nb++) {
		int i, base;
		for (i = 0; i < tam-nb-1; i++) {
			empilhar(aux, desempilhar(p));
		}
		base = topo(p);
		for (i = 0; i < tam-nb-1; i++) {
			int v = desempilhar(aux);
			if (v != base) {
				empilhar(p, v);
			}
		}
		tam = tamanho(p);
	}
	destruir(aux);
}

///////////////////////////////////////////////////////////////////////////////

void _testar() {
	Pilha * p1 = criar();
	//Pilha * p2 = criar();
	empilhar(p1, 5);
	empilhar(p1, 5);
	empilhar(p1, 2);
	empilhar(p1, 3);
	empilhar(p1, 1);
	empilhar(p1, 2);
	imprimir(p1);
	retirar_repetidos(p1);
	imprimir(p1);
	//corrigir_hanoi(p1);
	//imprimir(p1);
	//clonar_itens(p1);
	//imprimir(p1);
	//empilhar(p2, 2);
	//empilhar(p2, 4);
	//empilhar(p2, 7);
	//imprimir(unir_ordenado(p1, p2));
	//printf("Inverter letras: %s\n", inverter_letras("Este exercicio eh muito facil!"));
	//printf("'ARARA' eh palindromo? %c\n", eh_palindromo("ARARA") ? 'S' : 'N');
	//printf("'DADOS' eh palindromo? %c\n", eh_palindromo("DADOS") ? 'S' : 'N');
	system("pause");
}

#endif