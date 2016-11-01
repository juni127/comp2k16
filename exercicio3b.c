/*
  Nome: Reinaldo Apolinário Junior
  Compilador: Dev-C++ 4.9.9.2
  Data: 01/11/2016
*/
#include<stdio.h>
#include<stdlib.h>

int sumCousin(int a){
    int x, soma = 0, primos[a], w = 0;
    
    for(x = 1; w < a; x++){
          int count = 0, y;
          for(y = 0; y < w || primos[y] > x/2 + 1; y++){
                if(x%primos[y] == 0)count++;
          }
          if(count < 2){
                   primos[w] = x;
                   soma += primos[w];
                   w++;
          }
    }
    return soma;
}

int main(){
    int x, r;
    puts("Digite a quantidade a ser somada:");
    scanf("%i", &x);
    r = sumCousin(x);
    printf("Resultado = %i.", r);
    system("pause");
}

