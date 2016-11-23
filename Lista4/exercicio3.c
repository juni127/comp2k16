//Escrito por Sandro
#include<stdio.h>
#include<stdlib.h>

//Como eu fiz
int maiorElemento(int *vet, int t, int max){
  if(t == 0)return max;
  if(*vet > max)max = *vet;
  return maiorElemento(vet+1, t-1, max);
}


//Como a Ines espera que seja feito
//Ta quebrado :[
int maximo(int *vet, int t){
  if(t == 1)return *vet;
  int max = maximo(vet, t-1);
  if(*(vet+t) > max)return *(vet+t);
  else return max;
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

  printf("O maior elemento foi: %i\n", maximo(vet, n));

  system("pause");
  return 0;
}
