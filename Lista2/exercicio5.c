/*
  Nome: Reinaldo Apolinário Junior
  Compilador: Dev-C++ 4.9.9.2
  Data: 01/11/2016
*/
#include<stdio.h>
#include<stdlib.h>

char conceito(float nota){
     char c;
     if(nota < 4.9)
       c = 'D';
     else if(nota < 6.9)
       c = 'C';
     else if(nota < 8.9)
       c = 'B';
     else if(nota < 10)
       c = 'A';
     return c;
}

int main(){
    float x;
    puts("Digite a nota a ser conceituada:");
    scanf("%f", &x);
    printf("Conceito: %c.\n", conceito(x));
    system("pause");
}

