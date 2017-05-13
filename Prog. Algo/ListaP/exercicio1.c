#include<stdio.h>

int procurar(int n, int vet[], int t){
	if(t == 0)return -1;
	if(vet[t] == n)return t;
	return procurar(n,  vet, t-1); 
}

int main(){
	int x, t;
	printf("Digite o tamanho do vetor:");
	scanf("%i", &t);
	int vet[t];
	for(x = 0; x < t; x++){
		printf("Vet[%i]=", x+1);
		scanf("%i", &vet[x]);
	}
	printf("Digite o numero a ser achado:");
	scanf("%i", &x);
	printf("O numero foi encontrado na posicao %i.\n", procurar(x, vet, t));

	return 0;
}
