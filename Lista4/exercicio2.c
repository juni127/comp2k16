//Escrito no Atom
#include<stdio.h>
#include<stdlib.h>

//Função que multiplica as matrizes
void multiplica(int *mata, int *matb, int m, int n, int l, int *matc){
  int x, y, w;

  for(x = 0; x < m; x++){
    for(y = 0; y < l; y++){
      int soma = 0;
      for(w = 0; w < n; w++){
        soma += mata[(x*n)+w] * matb[(w*l)+y];
      }
      matc[x*l+y] = soma;
    }
  }
}

//Função que lê as matrizes
void scanm(int *matriz, int m, int n){
  int x, i, j;
  for(x = 0; x < m*n; x++){
    i = x/n;
    j = x - i*n;
    printf("Matriz[%i][%i] = ", i+1, j+1);
    scanf("%i", matriz+x);
  }
}

//Função que imprime matrizes
void printm(int *matriz, int m, int n){
  int x, y;

  for(x = 0; x < m; x++){
    printf(" |%4i", *(matriz+x*n));
    for(y = 1; y < n; y++){
      printf(", %4i", *(matriz+y+x*n));
    }
    printf("|\n");
  }
}

int main(){
  int m, n, l;
  printf("Digite as dimencoes das matrizes (m, n, l):");
  scanf("%i, %i, %i", &m, &n, &l);

  system("cls");

  int mata[m*n], matb[n*l];
  puts("Digite a primeira matriz:");
  scanm(mata, m, n);

  system("cls");

  puts("Digite a segunda matriz:");
  scanm(matb, n, l);

  system("cls");

  puts("Matriz resultante:");
  int matc[m*l];
  multiplica(mata, matb, m, n, l, matc);
  printm(matc, m, l);

  system("pause");
  return 0;
}
