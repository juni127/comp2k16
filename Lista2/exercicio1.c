/*
  Nome: Reinaldo Apolin�rio Junior
  Compilador: Dev-C++ 4.9.9.2
  Data: 01/11/2016
*/

#include<stdio.h>
#include<stdlib.h>

char soma(int n){
  int x, s = 0;
  for(x = 1; x <= n; x++){
    s += x;
  }
  return s;
}

int main(){
    int x;
    puts("Digite a quantidade de numeros a ser somada:");
    scanf("%i", &x);
    printf("Soma: %i.\n", soma(x));
    system("pause");
}
