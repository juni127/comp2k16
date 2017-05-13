#include<stdio.h>
#include<stdlib.h>

int sumCousin(int a){
    int x, soma = 0, primos[a], w = 0;

    for(x = 2; w < a; x++){
          int count = 0, y;
          for(y = 0; y < w || primos[y] > x/2 + 1; y++){
                if(x%primos[y] == 0)count++;
          }
          if(count < 2){
                   primos[w] = x;
                   soma += primos[w];
                   w++;
          }
    }
    return soma;
}

//Essa fun��o � mais rapida.
int sumCousinMelhor(int a){
    //Se a for menor que 1 ent�o a soma vai ser 0
	if(a < 1)return 0;
	//Temos que colocar o 2 na lista de numeros primos pois s� testaremos os numeros impares
    int x, soma = 2, primos[a], w = 1;
    primos[0] = 2;

	//Mesmo algoritimo da fun��o original mas agora n�o testamos pares
    for(x = 3; w < a; x+=2){
          int count = 0, y;
          for(y = 0; y < w || primos[y] > x/2 + 1; y++){
                if(x%primos[y] == 0)count++;
          }
          if(count < 2){
                   primos[w] = x;
                   soma += primos[w];
                   w++;
          }
    }
    return soma;
}

int main(){
    int x, r;
    puts("Digite a quantidade a ser somada:");
    scanf("%i", &x);
    r = sumCousin(x);
    printf("Resultado = %i.\n", r);
    system("pause");
}
