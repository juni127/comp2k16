//Escrito no Atom
#include<stdio.h>
#include<stdlib.h>

//Função para calcular o numero de divisores e a soma dos mesmos
void divisores(int numero, int *numeroDeDivisores, int *somaDosDivisores){
  int x, count = 0, soma = 0;
  for(x = 1; x <= numero; x++){
    //!(algo % algo) é equivalente a algo % algo != 0
    if(!(numero%x)){
      count++;
      soma+=x;
    }
  }
  *somaDosDivisores = soma;
  *numeroDeDivisores = count;
}

int main(){
  int t, x;
  printf("Digite a quantidade de numeros:");
  scanf("%i", &t);

  int m[t], soma[t], numero[t];

  for(x = 0; x < t; x++){
    printf("Numero %i: ", x+1);
    scanf("%i", &m[x]);
    divisores(m[x], &soma[x], &numero[x]);
  }

  system("cls");
  printf("Numero    |Soma      |Quantidade\n");
  for(x = 0; x < t; x++)printf("%10i|%10i|%10i\n", m[x], soma[x], numero[x]);

  system("pause");
  return 0;
}
