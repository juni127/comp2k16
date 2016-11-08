#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void subSequencias(int *a, int n){
  int x;
  for(x = 0; x < n; x++){
    printf("%i ", a[x]);
    if(x != n-1)if(a[x] > a[x+1])puts("");
  }
  puts("");

}

int main(){
  int n, x;
  printf("Digite o tamanho do vetor:");
  scanf("%i", &n);
  int v[n];

  for(x = 0; x < n; x++){
    printf("vet[%i] = ", x+1);
    scanf("%i", &v[x]);
  }

  subSequencias(v, n);

  system("pause");
  return 0;
}
