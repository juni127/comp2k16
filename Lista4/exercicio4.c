//Escrito com Atom
#include <stdio.h>
#include <stdlib.h>

int somaDigitos(int n){
  if(n/10 == 0)return n%10;
  return (n%10)+somaDigitos(n/10);
}

int main() {
  int x;
  printf("Digite um numero:");
  scanf("%i", &x);

  printf("A soma dos digitos e igual a: %i\n", somaDigitos(x));

  system("pause");
  return 0;
}
