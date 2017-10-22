//TAD Fila

typedef struct fila Fila;

//Configuração
Fila * criar();
void destruir(Fila * f);
void limpar(Fila * f);

//Consultas
int tamanho(Fila * f);
int esta_vazia(Fila * f);
int primeiro(Fila * f);
int ultimo(Fila * f);
void imprimir(Fila * f);

//Manutenção
void enfileirar(Fila * f, int v);
int desenfileirar(Fila * f); 
