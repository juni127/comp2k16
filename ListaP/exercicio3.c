#include<stdio.h>

void ler(){
	int x;
	printf("Digite um numero:");
	scanf("%i", &x);
	if(x != -0){
		ler();
		printf("%i, ", x);
	}
}

int main(){
	ler();

	return 0;
}
