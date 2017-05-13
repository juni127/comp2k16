/*
  Criado por: Reinaldo A. Junior
  Escrito com: Atom 1.16.0
  Compilado com: gcc 5.3.0
  Compilado em: Windows 7 64 Bits

  TODO Criar a struct HEADER para evitar o gasto de memoria com o tipo de estrutura
*/

//Necessaria para utilziar malloc() e sizeof(). I guess.
#include<stdlib.h>
//Necessaria para utilizar printf() e puts()
#include<stdio.h>

//Define true como 1 e false como 0 para poder usar essas palavras nos ifs.
#define true 1;
#define false 0;

/*
  Types know:
  s - Lista sem regras
  p - Lista com estrutura de pilha
  f - Lista com estrutura de fila
*/

typedef struct NO{
  int value, index;
  char type;
  struct NO *next, *prev;
}no;

//Prototipagem das funções (nunca pensei que faria isso).
//Cria uma lista sem cabeça do tipo type e atribui o valor value a seu primeiro elemento.
no *iniciaLista(char type, int value);
//Adiciona um nó no fim da lista l com o valor value.
void addEnd(no* l, int value);
//Adiciona um nó no começo da lista l com o valor value.
no *addStart(no* l, int value);
//Adiciona um nó na posição index da lista l com o valor value.
no *add(no *l, int value, int index);
//Remove o ultimo elemento da lista l.
no *removeEnd(no* l);
//Remove o primeiro elemento da lista l.
no *removeStart(no *l);
//Remove o nó na posição index da lista l.
no *rm(no *l, int index);
//Retorna o valor na posição index da lista l.
int valueOf(no *l, int index);
//Retorna o primeiro indice que contem o valor value na lista l ou o ultimo indice se o valor não for encontrado na lista.
int indexOf(no* l, int value);
//Adiciona o valor valor na lista l de acordo com seu tipo.
no *push(no *l, int valor);
//Remove um valor da lista l de acordo com seu tipo.
no *pop(no *l);
//Remove a lista l completamente.
void purge(no *l);
//Retorna um valor da lista l de acordo com seu tipo
int get(no* l);
//Retorna o tamanho da lista l
int getSize(no* l);
//Iguala o valor do nó na posição index da lista l a value
void set(no *l, int value, int index);
//Concatena a lista l2 a lista l1
void concatena(no* l1, no* l2);
//Compara se a lista l1 é igual a lista l2
int listComp(no *l1, no *l2);
//Imprime o conteudo da lista l no seguinte formato "[a1, a2, a3, ..., an]"
void mostrar(no* l);

no *iniciaLista(char type, int value){
    //Aloca memoria para o novo nó
    no *novo = (no*)malloc(sizeof(no));
    //Atribui o tipo de estrutura de dados especificado a lista
    novo->type = type;
    //Completa o circulo da lista
    novo->next = novo;
    //Completa o circulo da lista²
    novo->prev = novo;
    //Atribui o indice correto ao novo nó
    novo->index = 0;
    //Atribui o valor ao novo nó
    novo->value = value;
    //Retorna o novo elemento para ser o primeiro da lista
    return novo;
}

void addEnd(no* l, int value){
  //Move a lista l até o ultimo elemento
  while((l->next)->index != 0)l = l->next;
  //Aloca memoria pra um novo elemento
  no *novo = (no*)malloc(sizeof(no));
  //Atribui o tipo da estrutura da lista para este nó
  novo->type = l->type;
  //Aponta o ponteiro de próxmio do novo nó para o inicio da lista
  novo->next = l->next;
  //Aponta o antigo fim da lista para o novo nó
  l->next = novo;
  //Aponta o ponteiro de anterior do novo nó para o antigo fim da lista
  novo->prev = l;
  //Atribui o indice correto ao novo nó
  novo->index = l->index + 1;
  //Atribui o valor especificado ao novo nó
  novo->value = value;
}

no *addStart(no* l, int value){
  //Aloca memoria para um novo elemento
  no *novo = (no*)malloc(sizeof(no));
  //Insero o valor no nó
  novo->value = value;
  //Atribui o indice correto ao novo nó
  novo->index = 0;
  //Atribui o tipo correto ao novo nó
  novo->type = l->type;
  //Aponta o novo elemento pro antigo começo da lista
  novo->next = l;
  //Aponta o ponteiro de anterior do antigo começo para o novo.
  l->prev = novo;
  //Itera por todos os elementos da lista (menos o elemento com indice igual a 0) ajustando os indices
  while((l->next)->index != 0){
    l = l->next;
    l->index++;
  }
  //Ajusta o indice do elemento 0 da lista
  (novo->next)->index++;
  //Completa o circulo
  l->next = novo;
  novo->prev = l;
  //Retorna o novo nó para ser o novo incio da lista
  return novo;
}

no *add(no *l, int value, int index){
  //Cria variavel para armazenar o inicio da lista
  no *inicio = l;
  //Se o indice for 0 então adicionamos no começo
  if(index == 0)return addStart(l, value);
  //Se o indice não existir dentro da lista retornamos ela como está
  if(!(index < getSize(l)))return inicio;
  //Se não movemos o nó l até o nó antes do indice desejado
  while((l->next)->index != index)l = l->next;
  //Criamos o novo nó
  no *novo = (no*)malloc(sizeof(no));
  //Apontamos o ponteiro de anterior do próximo nó de l para o novo
  (l->next)->prev = novo;
  //Apontamos o ponteiro de próximo do novo nó para o próximo de l
  novo->next = l->next;
  //Apontamos o ponteiro de anterior do novo para o l
  novo->prev = l;
  //Apontamos o ponteiro de próximo de l para o novo
  l->next = novo;
  //Atribuimos o valor correto ao indice de novo
  novo->index = index;
  //Atribuimos o valor ao novo nó
  novo->value = value;
  //Concertamos os outros indices
  for(l = novo->next; l->index != 0; l = l->next)l->index++;
  //Retornamos o inicio da lista
  return inicio;
}

no *removeEnd(no* l){
  //Cria uma variavel para salvar o inicio caso a lista tenha menos de dois elementos
  no* inicio = l;
  //Move a lista l até o penultimo ultimo elemento
  while(((l->next)->next)->index != 0)l = l->next;
  //Checa se essa lista não tem menos de dois elementos
  if(l->next == l){
    //Se ela tem menos de dois elementos
    //Libera a memoria
    free(inicio);
    //Retorna nulo
    return NULL;
  }
  //Se ela tem mais de dois elementos
  //Libera a memoria do ultimo elementos
  free(l->next);
  //Aponta o ponteiro de próximo do novo fim da lista para o primeiro elemento
  l->next = inicio;
  //Aponta o ponteiro de anterior do começo da lista para o novo ultimo elemento
  inicio->prev = l;
  //Retorna o começo da lista
  return inicio;
}

no *removeStart(no *l){
  //Itera por todos os elementos da lista (menos o elemento com indice igual a 0) ajustando os indices
  while((l->next)->index != 0){
    l = l->next;
    l->index--;
  }
  //O próximo elemento é o elemento 0
  //Cria uma variavel para guardar o novo começo da lista
  no *inicio = (l->next)->next;
  //Apaga o antigo começo da lista
  free(l->next);
  //Aponta o ponteiro de anterior do novo começo da lista para o fim dela
  inicio->prev = l;
  //Aponta o ponteiro de próximo do fim da lista para o novo começo
  l->next = inicio;
  //Retorna o novo inicio da lista
  return inicio;
}

no* rm(no *l, int index){
  //Cria variavel para armazenar o começo da lista
  no *inicio = l;
  //Se o indice for zero remove o inicio da lista
  if(index == 0)return removeStart(l);
  //Se o indice não existir dentro da lista retornamos ela como está
  if(!(index < getSize(l)))return inicio;
  //Se não movemos o nó l até o nó antes do indice desejado
  while((l->next)->index != index)l = l->next;
  //Apontamos o ponteiro de próximo de l para o próximo do nó que sera removido
  l->next = (l->next)->next;
  //Apagamos o nó que deve ser removido da memoria
  free((l->next)->prev);
  //Apontamos o ponteiro de anterior do novo próximo de l para l
  (l->next)->prev = l;
  //Consertamos os indices subsequentes
  for(l = l->next; l->index != 0; l = l->next)l->index--;
  //Retornamos o inicio
  return inicio;
}

int valueOf(no *l, int index){
  //Cria variavel para guardar o valor a ser retornado
  int retorno = 0;
  //Checa caso especial (-1 -> Ultimo elemento da lista)
  if(index == -1){
    //Move o nó l até o ultimo indice
    for( ;(l->next)->index != 0; l = l->next);
    //Atribui o valor do nó no indice a variavel retorno
    retorno = l->value;
  }
  //Se não for um caso especial checa se o indice está dentro da lista
  else if(index < getSize(l)){
    //Se ele está
    //Move o nó l até ele
    while(l->index != index)l = l->next;
    //Atribui o valor do nó no indice a variavel retorno
    retorno = l->value;
  }
  //Retorna o valor que deve ser retornado
  return retorno;
}

int indexOf(no* l, int value){
  //Itera por todos os elementos pelo menos uma vez checando seus valores.
  for(; (l->next)->index != 0 && l->value != value; l = l->next);
  //Retorna o index do valor procurado. Ou o valor do ultimo elemento caso a lista não possua o valor procurado.
  return l->index;
}

no *push(no *l, int valor){
  //Cria uma variavel para armazenar o começo da lista
  no *inicio = l;
  if(inicio == NULL)return iniciaLista('s', valor);
  //Checa o tipo de estrutura utilizada
  switch (l->type) {
    //Caso não seja estruturada
    case 's':
      //Adiciona no fim pq eu quero :V
      addEnd(l, valor);
      break;
    //Caso a estrutura seja em forma de pilha
    case 'p':
      //Adiciona no fim da lista
      addEnd(l, valor);
      break;
    //Caso a estrutura seja em forma de fila
    case 'f':
      //Adiciona no começo da lista
      inicio = addStart(l, valor);
      break;
  }
  //Retorna o potencialmente novo inicio
  return inicio;
}

no *pop(no *l){
  /*
    Essa parte é tricky.
    Como eu estabeleci que nas pilhas os valores seriam adicionados no fim e nas listas no começo (vide a função push()) eu vou remover de ambas as estruturas no fim.
    E como eu gosto de adicionar e remover no fim em listas desestruturadas agora a função pop fica simples assim:
  */
  return removeEnd(l);
}

void purge(no *l){
  if((l->next)->index == 0)free(l);
  purge(l->next);
  free(l);
}

int get(no* l){
  /*
    Novamente essa parte é tricky.
    Como eu estabeleci que nas pilhas os valores seriam adicionados no fim e nas listas no começo (vide a função push()) eu vou retornar de ambas as estruturas no fim.
    E como eu gosto de adicionar e remover no fim em listas desestruturadas agora a função get fica simples assim:
  */
  return valueOf(l, -1);
}

int getSize(no* l){
  //Inicia a variavel tamanho com o valor 0
  int size = 0;
  //Itera entre todos os elementos da lista
  while((l->next)->index != 0){
    //Aumenta a variavel tamanho em 1 pra cada elemento existente
    size++;
    //Passa pro próximo elemento
    l = l->next;
  }
  //Retorna o tamanho da lista
  return size;
}

void set(no *l, int value, int index){
  //Cria variavel para armazenar o inicio da lista
  no *inicio = l;
  //Se não movemos o nó l até o indice desejado
  while(l->index != index)l = l->next;
  //Modificamos o valor do indice desejado
  l->value = value;
}

void concatena(no* l1, no* l2){
  //Salva o inicio pra manter a lista circular
  no *inicio = l1;
  //Move a lista 1 até o fim
  while((l1->next)->index != 0)l1 = l1->next;
  //Aponta o fim da lista 1 pro começo da lista 2
  l1->next = l2;
  //Aponta o começo da lista 2 pro fim da lista 1
  l2->prev = l1;
  //Salva o ultimo indice a adiciona 1 para ajustar os indices de l2
  int k = l1->index + 1;
  //Itera por todos os elementos de l2 (menos o elemento com indice igual a 0) ajustando os indices e os tipos.
  while((l2->next)->index != 0){
    l2 = l2->next;
    l2->index += k;
    l2->type = l1->type;
  }
  //Ajusta o indice e o tipo do elemento 0 da lista 2.
  (l2->next)->index += k;
  (l2->next)->type = l1->type;
  //Completa o circulo
  l2->next = inicio;
  inicio->prev = l2;
}

int listComp(no *l1, no *l2){
  //Se as listas não tem o mesmo tamanho com certeza não serão iguais.
  if(getSize(l1) != getSize(l2))return false;
  //Itera entre as duas listas.
  for( ; (l1->next)->index != 0 && (l2->next)->index != 0; l1 = l1->next, l2 = l2->next)
    //Se algum elemento delas não é igual ao seu par na outra retornamos falso.
    if(l1->value != l2->value)return false;
  //Se ainda não retornamos falso então as listas são iguais.
  return true;
}

void mostrar(no* l){
  //Isso tudo foi só para ficar bonitinho :P
  int teste = false;
  printf("[");
  for( ; l->index != 0 || !teste; l = l->next){
    printf("%i", l->value);
    teste = true;
    if((l->next)->index != 0)printf(", ");
  }
  puts("]");
}
