#include<stdio.h>
#include<stdlib.h>

int ocorrencias(int a, int *vet, int n){
  int x, r = 0;
  for(x = 0; x < n; x++){
    if(a == vet[x])r++;
  }
  return r;
}

int main(){
  int n, x, r, a;

  printf("Digite o tamanho do vetor:");
  scanf("%i", &n);

  int vet[n];

  for(x = 0; x < n; x++){
    printf("VET[%i]=", x+1);
    scanf("%i", &vet[x]);
  }

  printf("Digite um numero para checar sua ocorrencia:");
  scanf("%i", &a);

  r = ocorrencias(a, vet, n);

  printf("Resultado: %i\n", r);
  system("pause");
  return 0;
}
