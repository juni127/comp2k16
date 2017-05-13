#include<stdio.h>
#include"ed.h"

int main(int argc, char *args[]){

  no *l1 = NULL, *l2 = NULL;
  int e;
  do{
    printf("Digite o numero a ser inserido na lista 1 (0 para parar de inserir):");
    scanf("%i", &e);
    if(e != 0){
      if(l1 == NULL)l1 = iniciaLista('p', e);
      else l1 = push(l1, e);
    }
  }while(e != 0);
  do{
    printf("Digite o numero a ser inserido na lista 2 (0 para parar de inserir):");
    scanf("%i", &e);
    if(e != 0){
      if(l2 == NULL)l2 = iniciaLista('f', e);
      else l2 = push(l2, e);
    }
  }while(e != 0);

  do{
    system("cls");
    printf("Pilha = ");
    mostrar(l1);
    printf("Fila = ");
    mostrar(l2);

    puts("----------------------------------------");
    puts("| Adicionar um elemento a pilha    (1) |");
    puts("| Adicionar um elemento a fila     (2) |");
    puts("| Remover um elemento a pilha      (3) |");
    puts("| Remover um elemento a fila       (4) |");
    puts("| Concatenar a fila a pilha        (5) |");
    puts("| Comparar se as listas sao iguais (6) |");
    puts("| Terminar o programa              (0) |");
    puts("----------------------------------------");
    scanf("%i", &e);
    if(e == 0)break;

    switch (e) {
      case 1:
        printf("Digite o numero a ser iserido na pilha:");
        scanf("%i", &e);
        l1 = push(l1, e);
        break;
      case 2:
        printf("Digite o numero a ser iserido na fila:");
        scanf("%i", &e);
        l2 = push(l2, e);
        break;
      case 3:
        puts("Elemento removido da pilha!");
        l1 = pop(l1);
        system("pause");
        break;
      case 4:
        puts("Elemento removido da fila!");
        l2 = pop(l2);
        system("pause");
        break;
      case 5:
        puts("A fila foi concatenada a pilha!");
        concatena(l1, l2);
        system("pause");
        break;
      case 6:
        if(listComp(l1, l2))
          puts("As listas sao iguais!");
        else
          puts("As listas nao sao iguais!");
        system("pause");
        break;
    }
  }while(e != 0);

  return 0;
}
