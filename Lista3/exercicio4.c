#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float somaDeVetores(int *a, int *b, int n){
  int x;
  float soma = 0, r;
  for(x = 0; x < n; x++){
    soma += (a[x] - b[x])*(a[x] - b[x]);
  }
  r = sqrt(soma);
  return r;
}

int main(){
  int s, x;
  printf("Digite o tamanho dos vetores:");
  scanf("%i", &s);
  int a[s], b[s];

  for(x = 0; x < s; x++){
    printf("VET-A[%i]=", x+1);
    scanf("%i", &a[x]);
  }

  system("cls");

  for(x = 0; x < s; x++){
    printf("VET-B[%i]=", x+1);
    scanf("%i", &b[x]);
  }

  system("cls");

  float resultado = somaDeVetores(a, b, s);
  printf("A distancia entre os vetores e: %f\n", resultado);

  system("pause");
  return 0;
}
