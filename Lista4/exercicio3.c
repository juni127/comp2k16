//Escrito com Atom
#include<stdio.h>
#include<stdlib.h>

int maiorElemento(int *vet, int t, int max){
  if(t == 0)return max;
  if(*vet > max)max = *vet;
  return maiorElemento(vet+1, t-1, max);
}

int main(){
  int n, x;
  printf("Digite o tamanho do vetor:");
  scanf("%i", &n);
  int vet[n];

  for(x = 0; x < n; x++){
    printf("Vetor[%i] = ", x+1);
    scanf("%i", &vet[x]);
  }

  printf("O maior elemento foi: %i\n", maiorElemento(vet, n, 0));

  system("pause");
  return 0;
}
