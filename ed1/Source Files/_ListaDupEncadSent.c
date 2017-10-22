void inserir_primeiro(Lista * l, int v) {
	No * aux = (No *)malloc(sizeof(No));
    aux->info = v;
    aux->prox = l->ini->prox;
    aux->ant = l->ini;
    l->ini->prox = aux;
    aux->prox->ant = aux;
    l->tam++;
}     

void inserir_ultimo(Lista * l, int v) {
    No * aux = (No *)malloc(sizeof(No));
    aux->info = v;
    aux->prox = l->fim;
    aux->ant = l->fim->ant;
    l->fim->ant = aux;
    aux->ant->prox = aux;
    l->tam++;
}


int remover_primeiro(Lista * l) {
	int v; No * aux;
	if (esta_vazia(l)){
		printf("Lista vazia!");
		return -1;
    }
	aux = l->ini->prox;
    l->ini->prox = aux->prox;
    aux->prox->ant = l->ini;
	v = aux->info;
    free(aux);
    l->tam--;
	return v;
}
     
int remover_ultimo(Lista * l) {
	int v; No * aux;
	if (esta_vazia(l)){
		printf("Lista vazia!");
		return -1;
    }
    aux = l->fim->ant;
    l->fim->ant = aux->ant;
    aux->ant->prox = l->fim;
	v = aux->info;
    free(aux);
	l->tam--;
	return v;
}  
