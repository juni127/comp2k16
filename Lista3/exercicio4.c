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
  int s, x, y, m;
  printf("Digite o tamanho dos vetores:");
  scanf("%i", &s);
  printf("Digite a quantidade de pares de vetores:");
  scanf("%i", &m);
  int v[m*2][s];
  float r[m];

  for(y = 0; y < m*2; y++){
    for(x = 0; x < s; x++){
      printf("VET-%i-%i[%i]=", y+1, 1, x+1);
      scanf("%i", &v[y][x]);
    }

    system("cls");
    y++;

    for(x = 0; x < s; x++){
      printf("VET-%i-%i[%i]=", y+1, 2, x+1);
      scanf("%i", &v[y][x]);
    }
    r[y/2] = somaDeVetores(v[y-1], v[y], s);
    system("cls");
  }

  for(x = 0; x < m; x++)printf("Resultado par %i: %f\n", x+1, r[x]);

  system("pause");
  return 0;
}
