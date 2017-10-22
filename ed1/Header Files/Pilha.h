//TAD Pilha

typedef struct pilha Pilha;
        
Pilha * criar();
void destruir(Pilha * p);
void limpar(Pilha * p);

int tamanho(Pilha * p);
int esta_vazia(Pilha * p); 
int topo(Pilha * p);
void imprimir(Pilha * p);

void empilhar(Pilha * p, int v); 
int desempilhar(Pilha * p);
        
        
