//Versão 1.0
#include<stdio.h>
#include<math.h>

int parseInt(char * num){
	int x, res = 0;
	for(x = 0; *(num+x) != '\0'; x++){
		res += ((int)*(num+x)) - 48;
		res*=10;
	}
	return res/=10;
}

int main(int argc, char ** argv){
	switch(argv[1][0]){
		case '+':
			printf("%i\n", parseInt(argv[2]) + parseInt(argv[3]) );
			break;
	}
	return 0;
}
