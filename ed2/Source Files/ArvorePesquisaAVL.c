#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Config.h>

////////////////////////////////////////////////////////////////////////////////

#if _imprimir_info_PESQ_AVL

void _imprimir_info(int inf, void * inf_ext) {
	printf("%d(%d) ", inf, ((No *)inf_ext)->fb);
}      

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef IMPL_PESQ_AVL

No * _rotacionar_esq(No * raiz) {
	int fb_raiz, fb_esq;
	No * esq;
	if (raiz->dir->fb == 1) { //Remoção ou inserção
		fb_raiz = 0;
		fb_esq = 0;
	}  else { //Remoção ou árvore de 2 nós
		fb_raiz = -1; 
		fb_esq = raiz->dir->esq != NULL ? 1 : 0; // qtd nós > 2
	}
	esq = raiz;
	raiz = raiz->dir;
	esq->dir = raiz->esq;
	esq->fb = fb_esq;
	raiz->esq = esq;
	raiz->fb = fb_raiz; 
    return raiz;   
}      

No * _rotacionar_dir(No * raiz) {
	int fb_raiz, fb_dir;
	No * dir;
	if (raiz->esq->fb == -1) { //Remoção ou inserção
		fb_raiz = 0;
		fb_dir = 0;
	}  else { //Remoção ou árvore de 2 nós
		fb_raiz = 1; 
		fb_dir = raiz->esq->dir != NULL ? -1 : 0; // qtd nós > 2
	}
	dir = raiz;
	raiz = raiz->esq;
	dir->esq = raiz->dir;
	dir->fb = fb_dir;
	raiz->dir = dir;
	raiz->fb = fb_raiz; 
    return raiz;   
}      

No * _rotacionar_dir_esq(No * raiz) {
	int fb_esq, fb_dir;  
	if (raiz->dir->esq->fb == 1) { //Remoção ou inserção
		fb_esq = -1;
		fb_dir = 0;
	} else 
	if (raiz->dir->esq->fb == -1) { //Remoção ou inserção
		fb_esq = 0;
		fb_dir = 1;
	} else { //Remoção
		fb_esq = 0;
		fb_dir = 0;  
	}
	raiz->dir = _rotacionar_dir(raiz->dir);                
	raiz = _rotacionar_esq(raiz);
	raiz->fb = 0;
	raiz->esq->fb = fb_esq;
	raiz->dir->fb = fb_dir;  
	return raiz;
}     

No * _rotacionar_esq_dir(No * raiz) {
	int fb_dir, fb_esq;  
	if (raiz->esq->dir->fb == -1) { //Remoção ou inserção
		fb_dir = 1;
		fb_esq = 0;
	} else 
	if (raiz->esq->dir->fb == 1) { //Remoção ou inserção
		fb_dir = 0;
		fb_esq = -1;
	} else { //Remoção
		fb_dir = 0;
		fb_esq = 0;  
	}
	raiz->esq = _rotacionar_esq(raiz->esq);                
	raiz = _rotacionar_dir(raiz);
	raiz->fb = 0;
	raiz->dir->fb = fb_dir;
	raiz->esq->fb = fb_esq;  
	return raiz;
}     

No * _balancear(No * raiz, int oper, int fb_ant_filho) {
	if ((oper == INS_ESQ && /* Árvore esquerda aumentou */
		((fb_ant_filho == 0 && abs(raiz->esq->fb) == 1) || fb_ant_filho == FB_INDEF)) || /* ou */ 		
		(oper == REM_DIR && /* Árvore direita diminuiu */         
		((abs(fb_ant_filho) == 1 && raiz->dir->fb == 0) || (fb_ant_filho != FB_INDEF && raiz->dir == NULL)))) {
		if (raiz->fb == -1) {
			if (raiz->esq->fb == 1) raiz = _rotacionar_esq_dir(raiz); /* rotação dupla */
			else raiz = _rotacionar_dir(raiz); /* rotação simples */
		} else {
			raiz->fb--;
		} 
	} else 
	if ((oper == INS_DIR && /* Árvore direita aumentou */
		((fb_ant_filho == 0 && abs(raiz->dir->fb) == 1) || fb_ant_filho == FB_INDEF)) || /* ou */ 
		(oper == REM_ESQ && /* Árvore esquerda diminuiu */         
        ((abs(fb_ant_filho) == 1 && raiz->esq->fb == 0) || (fb_ant_filho != FB_INDEF && raiz->esq == NULL)))) {
		if (raiz->fb == 1) {
			if (raiz->dir->fb == -1) raiz = _rotacionar_dir_esq(raiz); /* rotação dupla */
			else raiz = _rotacionar_esq(raiz); /* rotação simples */
	    } else {
	      raiz->fb++;
		}
	}
	return raiz;                
}     

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef inserir_PESQ_AVL

No * _criar_no(int inf, void * inf_ext) {
	No * no = (No *)malloc(sizeof(No));
	no->inf = inf;
	no->fb = 0;
	no->esq = NULL;
	no->dir = NULL;
#ifdef ARVORE_INFO_EXT
	no->inf_ext = inf_ext;
#endif
	return no;
}

/* Retorna raiz da nova árvore com o nó inserido*/
No * _inserir(No * raiz, int inf, int * ptfb_ant, void * inf_ext) { 
	int fb_ant_filho;
	if (raiz != NULL) {
		*ptfb_ant = raiz->fb;
		if (inf < raiz->inf) {
			raiz->esq = _inserir(raiz->esq, inf, &fb_ant_filho, inf_ext);
			raiz = _balancear(raiz, INS_ESQ, fb_ant_filho);   
		} else
		if (inf > raiz->inf) { 
			raiz->dir = _inserir(raiz->dir, inf, &fb_ant_filho, inf_ext);
			raiz = _balancear(raiz, INS_DIR, fb_ant_filho);    
		}
	} else {
		*ptfb_ant = FB_INDEF;
		raiz = _criar_no(inf, inf_ext);
	}
	return raiz;          
}  

#ifdef ARVORE_INFO_EXT
void inserir(Arvore * arv, int inf, Info * inf_ext) {
	int fb_ant;
	arv->raiz = _inserir(arv->raiz, inf, &fb_ant, inf_ext);          
} 
#else
void inserir(Arvore * arv, int inf) {
	int fb_ant;
	arv->raiz = _inserir(arv->raiz, inf, &fb_ant, NULL);
}
#endif

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef remover_PESQ_AVL

/* Retorna raiz da nova árvore com o nó de menor valor removido*/
No * _remover_menor(No * raiz, No * * ptmenor, int * ptfb_ant) {
    *ptfb_ant = raiz->fb;
	if(raiz->esq != NULL) {
		int fb_ant_filho;           
		raiz->esq = _remover_menor(raiz->esq, ptmenor, &fb_ant_filho);
		raiz = _balancear(raiz, REM_ESQ, fb_ant_filho);
	} else {
		No * menor = raiz;
		raiz = menor->dir;
		menor->dir = NULL;
		*ptmenor = menor;         
	}
	return raiz;       
}     
 
/* Retorna raiz da nova árvore, sendo esta raiz o sucessor da raiz original*/
No * _substituir_por_sucessor(No * raiz) {
	No * r_ant = raiz;        
	int fb_ant_filho;
	r_ant->dir = _remover_menor(r_ant->dir, &raiz, &fb_ant_filho);
	raiz->fb = r_ant->fb;  
	raiz->esq = r_ant->esq;
	raiz->dir = r_ant->dir;
	return _balancear(raiz, REM_DIR, fb_ant_filho);
}

No * _destruir_no(No * raiz) {
	No * no = raiz;
	if (raiz->esq == NULL && raiz->dir == NULL) {
		raiz = NULL;
	} else 
	if (raiz->esq != NULL && raiz->dir != NULL) {
	    raiz = _substituir_por_sucessor(raiz);
	} else {
	    if (raiz->esq != NULL) raiz = raiz->esq; 
	    else raiz = raiz->dir;                    
	}  
#ifdef ARVORE_INFO_EXT
	free(no->inf_ext);
#endif
	free(no);
	return raiz;
}      

/* Retorna raiz da nova árvore com o nó removido*/
No * _remover(No * raiz, int inf, int * ptfb_ant) {
	int fb_ant_filho;
	if (raiz != NULL) {
		*ptfb_ant = raiz->fb;
		if (inf < raiz->inf) {
			raiz->esq = _remover(raiz->esq, inf, &fb_ant_filho);
			raiz = _balancear(raiz, REM_ESQ, fb_ant_filho);   
		} else 
		if (inf > raiz->inf) {
			raiz->dir = _remover(raiz->dir, inf, &fb_ant_filho);
			raiz = _balancear(raiz, REM_DIR, fb_ant_filho);
		} else {
			raiz = _destruir_no(raiz);
		}
	} else {
		*ptfb_ant = FB_INDEF;
	}
	return raiz;
}  

void remover(Arvore * arv, int inf) {
	int fb_ant;	
	arv->raiz = _remover(arv->raiz, inf, &fb_ant);
} 

#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef IMPL_PESQ_AVL

int _verificar_AVL(No * raiz) {
	int alte, altd, fb;
	if (raiz != NULL) {
		alte = _verificar_AVL(raiz->esq);      
		altd = _verificar_AVL(raiz->dir);  
		fb = altd-alte;
		//printf("\nFB nodo %d: %d", raiz->info, fb);                   
		if (abs(fb) > 2) {
			printf("\nNodo %d viola a propriedade AVL", raiz->inf);                   
		}
		return (alte > altd ? alte : altd) + 1;                     
	}
	return -1;
}     

int verificar_AVL(Arvore * arv) {
	return _verificar_AVL(arv->raiz);
}     

#endif

////////////////////////////////////////////////////////////////////////////////