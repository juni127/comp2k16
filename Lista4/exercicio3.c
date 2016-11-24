//Escrito por Sandro
#include<stdio.h>
#include<stdlib.h>

/*
Como eu fiz
Essa função checa cada elemento do vetor e compara ele com o maximo até o ponto atual
bem parecido com o que seria feito com uma estrutura de repetição.
*/
int maiorElemento(int *vet, int t, int max){
  if(t == 0)return max;
  if(*vet > max)max = *vet;
  return maiorElemento(vet+1, t-1, max);
}


//Como a Ines espera que seja feito (Realmente essa função tem mais a ver com recursividade)
int maximo(int *vet, int t){
  t--;
  if(t == 1)return *vet;
  int max = maximo(vet, t);
  if(vet[t] > max)return vet[t];
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
