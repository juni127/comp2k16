/*
  Nome: Reinaldo Apolin�rio Junior
  Compilador: Dev-C++ 4.9.9.2
  Data: 01/11/2016
*/

#include<stdio.h>
#include<stdlib.h>

//4a
int mdc(int a, int b){
  int x;
  do{
    if(a > b){
      x = b;
      a -= b;
    }
    else  {
      x = a;
      b -= a;
    }
  }while(a > 0 && b > 0);

  return x;
}

//4b
int mdcGeral(int *vet, int n){
	int x;
	if(n < 2)return 0;
	int resultado = mdc(vet[0], vet[1]);
	for(x = 2; x < n; x++){
		resultado = mdc(resultado, vet[x]);
	}
	
	return resultado;
}

int main(){
    int n, x;
    puts("Digite a quantidade de numeros a serem guardados:");
    scanf("%i", &n);
    int vet[n];
    system("cls");
    puts("Digite os numeros para obtermos o mdc:");
    for(x = 0; x < n; x++){
    	printf("\nNumero %i: ", x+1);
    	scanf("%i", &vet[x]);
	}
    printf("MDC: %i.\n", mdcGeral(vet, n));
    system("pause");
}
