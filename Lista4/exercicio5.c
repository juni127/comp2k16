//Escrito com Atom
#include <stdio.h>
#include <stdlib.h>

int decToBin(int n){
  if(!(n/2))return 0;
  return n%2 + decToBin(n/2)*10;

}

int main() {
  int x;
  printf("Digite um numero:");
  scanf("%i", &x);
  printf("Sua versao binaria e: %i\n", decToBin(x));

  system("pause");
  return 0;
}
