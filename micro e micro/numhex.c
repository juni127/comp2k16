#include<stdio.h>
#include<stdlib.h>

char a, b;

void toHex(int n){
	if(n/16 < 10){
		a = n/16 + 48;
	}else{
		a = n/16 + 55;	
	}
	if(n%16 < 10){
		b = n%16 + 48;
	}else{
		b = n%16 + 55;	
	}
}

int main(){

	FILE * in = fopen("primos.txt", "r"), * out = fopen("primoshex.txt", "w");
	int n;
	while(!feof(in)){
		fscanf(in, "%d, ", &n);
		toHex(n);		
		fprintf(out, "0X%c%c\n", a, b);
	}

	return 0;
}
