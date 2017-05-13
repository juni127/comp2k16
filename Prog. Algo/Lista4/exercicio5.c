//Escrito com Nano (Linux) 
//Compilado com gcc (Linux)
#include<stdio.h>

int decToBin(int n){
	if(n/2 == 0)return n%2;
	else return n%2 + decToBin(n/2)*10;
}

float progMaluca(int n){
	if(n == 1)return 0.5f;
	return (float)((n*n)+1)/(float)(n+3) + progMaluca(n-1);
}

int main(){
	int n;
	printf("Digite um numero:");
	scanf("%i", &n);
	printf("Binario: %i\nSoma: %f\n", decToBin(n), progMaluca(n));
	

	return 0;
}
