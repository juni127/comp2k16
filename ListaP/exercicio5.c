#include<stdio.h>

void maxmin(int vet[], int x, int *max, int *min){
	if(x != 0)maxmin(vet, x-1, max, min);
	else{
		*max = vet[0];
		*min = vet[0];
	}
	if(vet[x] > *max)*max = vet[x];
	if(vet[x] < *min)*min = vet[x];
}

int main(){
	int x, y;
	printf("Digite o tamanho do vetor:");
	scanf("%i", &x);
	int vet[x];
	for(y = 0; y < x; y++){
		printf("Vet[%i]=", y+1);
		scanf("%i", &vet[y]);
	}
	int max, min;
	maxmin(vet, x-1, &max, &min);
	printf("Maior numero: %i\nMenor numero: %i\n", max, min);
	
	return 0;
}
