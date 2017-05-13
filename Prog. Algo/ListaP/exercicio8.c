#include<stdio.h>

int soma(int n){
	if(n/10 == 0)return n;
	return n%10 + soma(n/10);
}

int main(){
	int x;
	printf("Digite um numero:");
	scanf("%i", &x);
	printf("A soma dos algarismos e: %i\n", soma(x));
	return 0;
}
