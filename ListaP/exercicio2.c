#include<stdio.h>

float pot(int x, int y){
	if(y > 0){
		if(y > 1)return (float)x*pot(x, y-1);
		return (float)x;
	}else{
		if(y < -1)return pot(x, y+1)*1.0f/(float)x;
		return 1.0f/(float)x;
	}
}

int main(){
	int x, y;
	scanf("%i**%i", &x, &y);
	printf("Resultado: %f\n", pot(x, y)); 

	return 0;
}
