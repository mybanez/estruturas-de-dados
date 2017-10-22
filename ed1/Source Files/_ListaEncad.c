void inserir_primeiro(Lista * l, int v) {
    No * aux = (No *)malloc(sizeof(No));
    aux->info = v;
    aux->prox = l->ini;
	if (esta_vazia(l)) {
		l->fim = aux;
    }     
	l->ini = aux;
    l->tam++;
}     

void inserir_ultimo(Lista * l, int v) {
    No * aux =(No *)malloc(sizeof(No));
    aux->info = v;
    aux->prox = NULL;
    if (esta_vazia(l)) {
		l->ini = aux;	
    } else {
		l->fim->prox = aux;
	}
	l->fim = aux;
    l->tam++;
}

int remover_primeiro(Lista * l) {
	No * aux; int v;
	if (esta_vazia(l)){
		printf("Lista vazia!");
		return -1;
    }
	v = l->ini->info;
	aux = l->ini->prox;
	free(l->ini);     
	l->ini = aux;           
	l->tam--;
	if (esta_vazia(l)) {
		l->fim = NULL;           
	} 
	return v;
}
     
int remover_ultimo(Lista * l) {
	int i, v;
	if (esta_vazia(l)) {
		printf("Lista vazia!");
		return -1;
    }
	v = l->fim->info;
	free(l->fim);
	l->tam--;           
	if (esta_vazia(l)) {
		l->ini = NULL; 
		l->fim = NULL;           
	} else {                 
		l->fim = _obter_no_pos(l, tamanho(l)-1);
	}
	return v;
}  

