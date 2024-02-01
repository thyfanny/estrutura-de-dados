#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef LISTA_DUPLAMENTE_ENC
#define LISTA_DUPLAMENTE_ENC

typedef int ITEM;

typedef struct estrutura
{
    ITEM item;
    struct estrutura *ant;
    struct estrutura *prox;
} NO;

typedef struct
{
    NO* cabeca;
    NO* cauda;
    long tamanho;
} LISTA;

char compare(ITEM x, ITEM y)
{
    return x > y ? 1 : (x < y ? -1 : 0);
}


bool igual(ITEM x, ITEM y)
{
    return compare(x,y) == 0;
}


void inicializar(LISTA *l){
    l->cabeca = NULL;
    l->cauda = NULL;
    l->tamanho = 0;
}

NO* criarNo(ITEM item,  NO *ant, NO *prox){
    NO* pNovo = (NO*) malloc(sizeof(NO));
    if (pNovo == NULL){
        printf("Nao foi possivel alocar memoria para pNovo\n");
        exit(EXIT_FAILURE);        
    }
    pNovo->item = item;
    pNovo->ant = ant;
    pNovo->prox = prox;
    return pNovo;
}

long tamanho(LISTA *l){
    return l->tamanho;
}

bool cheia(LISTA *l){
    return false;
}

bool vazia(LISTA *l){
    return tamanho(l) == 0;
}

NO* noNaPosicao(long n, LISTA *l){
  if(n<0 || n>=tamanho(l)) return NULL;
  NO* pAtual = l->cabeca;
  for(long pos = 0; pos < n; pos++){
    pAtual = pAtual->prox;
  }
  return pAtual;
}

NO* buscarNO(ITEM item, LISTA *l){
  NO* pAtual = l->cabeca;
  while(pAtual != NULL){
    if(pAtual->item == item)
      return pAtual;
    pAtual = pAtual->prox;
  }
  return NULL;
}

bool inserir(ITEM item, LISTA *l){
  NO* pAtual = l->cabeca;
  NO* novoNo = criarNo(item, NULL, pAtual);
  if(l->cabeca!=NULL)
    pAtual->ant = novoNo;
  l->cabeca = novoNo;
  if(l->cauda == NULL)
    l->cauda = novoNo;
  l->tamanho++;
  return true;
}

long buscar(ITEM item, LISTA *l){
  NO* pAtual = l->cabeca;
  int pos = 0;
  for(; pAtual != NULL; pAtual = pAtual->prox, pos++){
    if(pAtual->item == item)
      return pos;
  }
  return -1;
}

ITEM enesimo(long n, LISTA *l){
  NO* pAtual = noNaPosicao(n, l);
  if(pAtual)
    return pAtual->item;
  else{
    printf("Não foi possivel acessar o enesimo elemento, pois n eh valido");
    exit(EXIT_FAILURE);
  }
}

bool alterar(ITEM item, long pos, LISTA *l){
  if(pos<0 || pos>=tamanho(l))
    return false;
  NO* pAtual = noNaPosicao(pos, l);
  pAtual->item = item;
  return true;
}

bool inserirNaPos(ITEM item, long i, LISTA *l){
  if(i<0 || i>tamanho(l)){
    printf("Posição inválida.");
    exit(EXIT_FAILURE);
  }
  NO* novoNo = criarNo(item, NULL, NULL);
  NO* pAnterior = noNaPosicao(i-1, l);
  NO* pAtual = noNaPosicao(i, l);

  pAnterior->prox = novoNo;
  pAtual->ant = novoNo;

  novoNo->ant = pAnterior;
  novoNo->prox = pAtual;

  l->tamanho++;
  return true;
}

bool remover(ITEM item, LISTA *l){
  NO* pAtual = buscarNO(item, l);

  if(pAtual->ant == NULL){  //primeiro elemento da lista
    l->cabeca = pAtual->prox;
    pAtual->prox->ant = NULL;
  }
  else if(pAtual->prox == NULL){  //ultimo elemento da lista
    l->cauda = pAtual->ant;
    pAtual->ant->prox = NULL;
  }
  else{
    pAtual->ant->prox = pAtual->prox;
    pAtual->prox->ant = pAtual->ant;
  }
  free(pAtual);
  l->tamanho--;
  return true;
}

void limpar(LISTA *l){
  NO* pAtual = l->cabeca;
  while(pAtual != NULL){
    NO* prox = pAtual->prox;
    free(pAtual);
    l->tamanho--;
    pAtual=prox;
  }
  l->cabeca = NULL;
  l->cauda = NULL;
  l->tamanho = 0;
}

void destruir(LISTA *l){
  limpar(l);
}

void exibirItem(ITEM i){
    printf("%d", i);
}

void exibirLista(LISTA *l) {
  printf("[");
  for (int count = 0; count < tamanho(l); count++) {
    exibirItem(noNaPosicao(count, l)->item);
    if (count < tamanho(l)-1)
      printf(",");
  }
  printf("]");
}

/*
Implementar uma função inserirNoFinal para incluir um item no final da lista. Para isso,
utilize um apontador cauda que já está disponível. Observe que tendo este apontador, a
inserção é rápida e fácil, já que o novo item será colocado após o último e será a nova
cauda da lista.*/

void inserirNoFinal(ITEM item, LISTA *l){
  NO* novoNo = criarNo(item, l->cauda, NULL);
  l->cauda->prox = novoNo;
  l->tamanho++;
}



#endif