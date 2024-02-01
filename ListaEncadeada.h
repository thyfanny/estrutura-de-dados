#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef LISTA_ENC
#define LISTA_ENC

typedef int ITEM;

typedef struct estrutura {
  ITEM item;
  struct estrutura *prox;
}NO;

typedef struct{
  NO* cabeca;
  long tamanho;
}LISTA;

/*
   Compara o item x com o y, retornando:
     1 caso x > y
     0 caso x = y
    -1 caso x < y
*/
char compare(ITEM x, ITEM y) {
  if (x > y)
    return 1;
  else if (x == y)
    return 0;
  else
    return -1;
}

// Retorna true se x = y e false caso contrario
bool igual(ITEM x, ITEM y) { return compare(x, y) == 0; }

// Inicializa a lista deixando-a pronta para ser utilizada.
void inicializar(LISTA *l){
  l->cabeca = NULL;
  l->tamanho = 0;
}

NO* criarNo(ITEM item, NO *prox)
{
    NO* pNovo = (NO*) malloc(sizeof(NO));
    if (pNovo == NULL)
    {
        printf("Nao foi possivel alocar memoria para pNovo\n");
        exit(EXIT_FAILURE);        
    }
    pNovo->item = item;
    pNovo->prox = prox;
    return pNovo;
}


// Retornar o tamanho da lista sequencial
long tamanho(LISTA *l) { return l->tamanho; }

// Retorna true se a lista esta cheia (Tamanho = MAX)
bool cheia(LISTA *l) { return false; }

// Retorna true se a lista esta vazia (Tamanho = 0)
bool vazia(LISTA *l) { return l->cabeca == NULL ? 0 : 1; }

/* 
  Objetivo: Insere o item passado como parametro na lista passada.
            Se o tamanho da lista ja for igual ao tamanho maximo,
            a funcao Inserir retorna false.
*/
bool inserir(ITEM item, LISTA *l){
  l->cabeca = criarNo(item, l->cabeca);
  l->tamanho++;
  return true;
}

/*
    Objetivo: Retorna o endereco do No contido na posicao informada.
              Caso a posicao seja invalida (negativa ou maior ou igual
              ao tamanho da lista, retorna NULL.
*/
NO* noNaPosicao(long n, LISTA *l){
  if (n < 0 || n >= tamanho(l))
    return NULL;

  NO *endereco = l->cabeca;
  for(int count = 0; count < n; count++){
    endereco = endereco->prox;
  }
  return endereco;
}

/*
  Objetivo: Busca na lista o item passado.
            Caso encontre, retorna a posicao (entre 0 e tamanho - 1).
            Caso nao encontre, retorna o valor -1.
*/

long buscar(ITEM item, LISTA *l){
  NO* noAtual = l->cabeca;
  for(int count = 0; count < tamanho(l); count++){
    if (item == noAtual->item)
      return count;
    noAtual = noAtual->prox;
  }
  return -1;
}

// Retornar o n-esimo elemento da lista sequencial
// Pre-condicao: 0 <= n < tamanho
ITEM enesimo(long n, LISTA *l){
  NO* pAtual = noNaPosicao(n, l);
  if (pAtual == NULL){
    printf("Posicao invalida\n");
    exit(EXIT_FAILURE);}
  return pAtual->item;
}

/*
  Objetivo: Altera o item contido em uma dada posicao da lista.
            Caso a posicao exista, retorna true. Caso nao exista,
            a alteracao nao sera feita e retorna false.
*/
bool alterar(ITEM item, long pos, LISTA *l){
  if(pos >= tamanho(l)-1 || pos < 0)
    return false;
  NO* pAtual = noNaPosicao(pos, l);
  pAtual->item = item;
  return true;
}

/*
  Objetivo: Inserir o item passado como parametro na posicao i da lista.
            Caso a lista nao esteja cheia e a posicao seja valida
            (0<=i<=tamanho), o item sera inserido e a funcao retorna
            true. 
            Caso contrario, a funcao retorna false para indicar que item
            nao foi inserido.
 */
bool inserirNaPos(ITEM item, long i, LISTA *l){
  if(cheia(l) || i >= tamanho(l) || i < 0)
    return false;
  if(i==0){
    l->cabeca = criarNo(item, l->cabeca);
    l->tamanho++;
  }
  else{
    NO* pAnterior = noNaPosicao(i-1, l);
    pAnterior->prox = criarNo(item, pAnterior->prox);
    l->tamanho++;
  }
  return true;
}

/*
  Objetivo: Remove o item passado da lista. Caso nao seja
            encontrato, retorna false. Se for removido, true.
*/
bool remover(ITEM item, LISTA *l){
  int pos = buscar(item, l);
  if (pos == -1){
    printf("Item não consta na lista\n");
    exit(EXIT_FAILURE);
    return false;
  }
  NO* pAnterior = noNaPosicao(pos-1, l);
  NO* pAtual = noNaPosicao(pos, l);
  pAnterior->prox = pAtual->prox;
  free(pAtual);
  l->tamanho--;
  return true;
}

// Exibicao de um item da lista
void exibirItem(ITEM i) { printf("%d", i); }

// Exibicao da lista sequencial
void exibirLista(LISTA *l) {
  printf("[");
  NO* pAtual = l->cabeca;
  for (int count = 0; count < tamanho(l); pAtual= pAtual->prox, count++) {
    exibirItem(pAtual->item);
    if (count < tamanho(l)-1)
      printf(",");
  }
  printf("]");
}

// Remove todos os valores da lista, deixando-a vazia
void limpar(LISTA *l){
  int pos = 0;
  NO* pAtual = l->cabeca;
  while(pAtual != NULL){
    NO* proximo = pAtual->prox;
    free(pAtual);
    pos++;
    pAtual = proximo;
    l->tamanho--;
  }
  l->cabeca = NULL;
  l->tamanho = 0;
}

// Destruicao da lista sequencial
void destruir(LISTA *l) { limpar(l); }

/*
Implementar uma função inserirNoFinal para incluir um item no final da lista. Para isso,
utilize um apontador que mantenha o endereço do último elemento da lista. Observe que
tendo este apontador, a inserção é rápida e fácil, já que o novo item será colocado após o
último e será o novo último da lista. Fique atento para a remoção do último valor de uma
lista. Neste caso, a remoção tem que ajustar o apontador último para o nó que
anteriormente era o penúltimo.*/

void inserirNoFinal(ITEM item, LISTA *l){
  NO* ultimo = noNaPosicao(tamanho(l)-1, l);
  ultimo->prox = criarNo(item, NULL);
  l->tamanho++;
}

/*
Implementar uma função para remover o item de uma certa posição da lista. A função
deve checar se a posição é válida, ou seja, se é referente a uma posição existente na lista.
Caso a remoção seja bem-sucedida, a função retorna true e o parâmetro item contém o
valor que foi removido da lista. Caso contrário, a função retorna false e a lista não será
alterada.*/

bool removerDaPos(ITEM *item, int i, LISTA *l){
  if(i > tamanho(l)-1 || i < 0)
    return false;
  NO* pAnterior = noNaPosicao(i-1, l);
  NO* pAtual = noNaPosicao(i, l);
  *item = pAtual->item;
  pAnterior->prox = pAtual->prox;
  free(pAtual);
  l->tamanho--;
  return true;
}

#endif // LISTA_ENC