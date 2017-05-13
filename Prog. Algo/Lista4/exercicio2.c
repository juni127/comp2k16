//Escrito com Atom
#include<stdio.h>
#include<stdlib.h>

int somaRecursiva(int n){
  if(n == 1)return 1;
  return somaRecursiva(n-1)+(n*n);
}

int main(){
  int n;
  printf("Digite um numero:");
  scanf("%i", &n);
  printf("A soma dos %i primeiros quadrados e: %i\n", n, somaRecursiva(n));

  system("pause");
  return 0;
}
