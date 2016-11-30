

//Feito no nano
#include<stdio.h>

void lerNomes(int i, char matriz[][100]){
	int x;
	for(x = 0; x < i; x++){
		printf("Digite o %i nome:", x+1);
		scanf("%s", matriz[x]);
	}
}

void apagaDepois(char *vet, int pos, int n){
	int x;
	for(x = pos; x < n+pos; x++)vet[x] = vet[x+n];
}

int primeiraOcorrencia(char *vet, char *palavra){
	int i = -1;
	

	return i;
}

void printNomes(char matriz[][100], int x){
	int i;
	for(i = 0; i < x; i++){
		printf("%s", matriz[i]);
		puts("");
	}
}

int main(){
	int x;
	scanf("%i", &x);
	char nomes[x][100];
	lerNomes(x, nomes);
	apagaDepois(nomes[0], 3, 3);
	printNomes(nomes, x);
	
	puts("");
	return 0;
}
