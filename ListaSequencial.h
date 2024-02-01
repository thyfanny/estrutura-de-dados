#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LISTA_SEQ_ESTATICA
#define LISTA_SEQ_ESTATICA

#define MAX 50

typedef int ITEM;

typedef struct {
  ITEM itens[MAX];
  long tamanho;
} LISTA;

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

void inicializar(LISTA *lista) { lista->tamanho = 0; }

// Retornar o tamanho da lista sequencial
long tamanho(LISTA *l) { return l->tamanho; }

// Retorna true se a lista esta cheia (Tamanho = MAX)
bool cheia(LISTA *l) { return tamanho(l) == MAX ? 0 : 1; }

// Retorna true se a lista esta vazia (Tamanho = 0)
bool vazia(LISTA *l) { return tamanho(l) == 0 ? 0 : 1; }

/*
  Objetivo: Insere o item passado como parametro na lista passada.
            Se o tamanho da lista ja for igual ao tamanho maximo,
            a funcao Inserir retorna false.
*/
bool inserir(ITEM item, LISTA *l) {
  if (tamanho(l) == MAX)
    return false;
  else {
    l->itens[l->tamanho++] = item;
    return true;
  }
}

/*
  Objetivo: Busca na lista o item passado.
            Caso encontre, retorna a posicao (entre 0 e tamanho - 1).
            Caso nao encontre, retorna o valor -1.
*/
long buscar(ITEM item, LISTA *l) {
  int count = 0;
  while (l != NULL) {
    if (igual(item, l->itens[count])) {
      return count;
    }
    count++;
  }
  return -1;
}

// Retornar o n-esimo elemento da lista sequencial
// Pre-condicao: 0 <= n < tamanho
ITEM enesimo(long n, LISTA *l) { 
  if (n >= 0 && n < tamanho(l)) 
    return l->itens[n-1];
  else
    exit(EXIT_FAILURE);
}

/*
  Objetivo: Altera o item contido em uma dada posicao da lista.
            Caso a posicao exista, retorna true. Caso nao exista,
            a alteracao nao sera feita e retorna false.
*/
bool alterar(ITEM item, long pos, LISTA *l) {
  if (pos < 0 || pos >= tamanho(l))
    return false;
  else {
    l->itens[pos] = item;
    return true;
  }
}

/*
  Objetivo: Inserir o item passado como parametro na posicao i da lista.
            Caso a lista nao esteja cheia e a posicao seja valida
            (0<=i<=tamanho), o item sera inserido e a funcao retorna true.
            Caso contrario, a funcao retorna false para indicar que o item
            nao foi inserido.
 */
bool inserirNaPos(ITEM item, long i, LISTA *l) {
  if (i < 0 || i >= tamanho(l) || tamanho(l)==MAX)
    return false;
  else {

    for (int count = tamanho(l); count > i; count--) {
      l->itens[count] = l->itens[count - 1];
    }

    l->itens[i] = item;
    l->tamanho++;
    return true;
  }
}

/*
  Objetivo: Remove o item passado da lista. Caso nao seja
            encontrato, retorna false. Se for removido, true.
*/
bool remover(ITEM item, LISTA *l) {
  if (buscar(item, l) == -1)
    return false;
  else {
    for (int pos = buscar(item, l); pos > tamanho(l); pos++) {
      l->itens[pos] = l->itens[pos + 1];
    }
    l->tamanho--;
    return true;
  }
}

// Exibicao de um item da lista
void exibirItem(ITEM i) { printf("%i", i); }

// Exibicao da lista sequencial
void exibirLista(LISTA *l) {
  printf("[");
  for (int count = 0; count < tamanho(l);) {
    exibirItem(l->itens[count++]);
    if (count < tamanho(l))
      printf(", ");
  }
  printf("]");
}

// Remove todos os valores da lista, deixando-a vazia
void limpar(LISTA *l) { l->tamanho = 0; }

// Destruicao da lista sequencial
void destruir(LISTA *l) { limpar(l); }

void exibirListaReversa(LISTA *l){
  printf("[");
  for (int count = tamanho(l)-1; count >= 0;) {
    exibirItem(l->itens[count--]);
    if (count >= 0)
      printf(", ");
  }
  printf("]");
}

/*
Implementar uma função para remover o item de uma certa posição da lista. A função
deve checar se a posição é válida, ou seja, se é referente a uma posição existente na lista.
Caso a remoção seja bem-sucedida, a função retorna true e o parâmetro item contém o
valor que foi removido da lista. Caso contrário, a função retorna false e a lista não será
alterada.
*/
bool removerDaPos(ITEM *item, int i, LISTA *l){
  item = &l->itens[i];
  if (i>=tamanho(l) || i<0)
    return false;

else{
  for (int count = i; count > tamanho(l)-1; count++) {
    l->itens[count] = l->itens[count + 1];
  }
  l->tamanho--;
  return true;
}
}

/*
Implementar uma função para buscarEm um item na lista começando de um ponto inicial
(inicio) e terminando no antecessor de fim, isto é, desconsiderando as posições menores
inicio e maiores ou iguais a fim. Caso não encontre, a função retorna o valor -1. Aproveite
e ajuste a função buscar padrão para utilizar esta mesma função, evitando assim
duplicação de código. A função deve ter a assinatura abaixo:
*/
int buscarEm(ITEM item, int inicio, int fim, LISTA *l){
  for(int count = inicio; count < fim; count++){
    if(item==l->itens[count])
      return count;
  }
  return -1;
}

/*Implementar uma função para inverter os itens de posição na lista, ou seja, trocar o
primeiro com o último, o segundo com o penúltimo e assim por diante. A função deve ter a
assinatura abaixo:*/

void reversa(LISTA *l){
  LISTA *listaInversa;
  inicializar(listaInversa);
  for(int count = tamanho(l)-1, count2 = 0; count >= 0; count--, count2++) {
    listaInversa->itens[count2] = l->itens[count];
    listaInversa->tamanho++;
  }
}

#endif // LISTA_SEQ_ESTATICA
