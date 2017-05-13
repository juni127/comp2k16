//Escrito com Atom
#include<stdio.h>
#include<stdlib.h>

int contaDigitos(int numero){
  if(numero/10 == 0)return 1;
  else return contaDigitos(numero/10) + 1;
}

int main(){
  int numero;
  printf("Digite um numero:");
  scanf("%i", &numero);
  printf("O tamanho do numero e: %i\n", contaDigitos(numero));
  system("pause");
  return 0;
}
