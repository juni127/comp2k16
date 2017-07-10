#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Pra usar true ou false
#define true 1
#define false 0
//Probabilidade de nascer
#define prob 50 //50 = 50%
//Quantidade de gerações
#define gera 10
//Tamanho da matriz
#define i 20
#define j 20

void printaMapa(int mapa[i][j]){
	//system("cls"); se vc estiver no windows descomente essa linha
	int x, y;
	for(x = 0; x < i; x++){
		for(y = 0; y < j; y++)
			if(mapa[x][y])
				printf("X");
			else
				printf(" ");
		puts("");
	}
}


int main(){

	int atual[i][j], antiga[i][j], x, y, w;

	srand(time(NULL));

	for(x = 0; x < i; x++){
		for(y = 0; y < j; y++){
			if(rand()%100 >= prob)atual[x][y] = true;
			else atual[x][y] = false;
			antiga[x][y] = atual[x][y];
		}
	}

	for(w = 0; w < gera; w++){
		//Igualar a matriz antiga a nova
		for(x = 0; x < i; x++)
			for(y = 0; y < j; y++)
				antiga[x][y] = atual[x][y];

		//Aplica a regra as celulas
		for(x = 0; x < i; x++){
			for(y = 0; y < j; y++){
				//N marca o numero de vizinhas vivas
				int n = 0;
				//Os ifs a seguir verificam as regras do jogo
				//Retire os elses para não contar as celulas fora da matriz como vivas 
				if(x-1 >= 0 && y-1 >= 0){
					if(antiga[x-1][y-1])
						n++;
				}else n++;
				if(x-1 >= 0){
					if(antiga[x-1][y])
						n++;
				}else n++;
				if(x-1 >= 0 && y+1 < j){
					if(antiga[x-1][y+1])
						n++;
				}else n++;
				if(y-1 >= 0){
					if(antiga[x][y-1])
						n++;
				}else n++;
				if(y+1 < j){
					if(antiga[x][y+1])
						n++;
				}else n++;
				if(x+1 < i && y-1 >= 0){
					if(antiga[x+1][y-1])
						n++;
				}else n++;
				if(x+1 < i){
					if(antiga[x+1][y])
						n++;
				}else n++;
				if(x+1 < i && y+1 < j){
					if(antiga[x+1][y+1])
						n++;
				}else n++;

				//Decidir o estado atual da celula de acordo com n
				//Morte
				if(atual[x][y] && (n < 2 || n > 3))
					atual[x][y] = false;
				//Nascimento
				if(!atual[x][y] && n == 3)
					atual[x][y] = true;
				printaMapa(atual); 
			}
		}		
	}	

	//system("pause"); se for windows descomente essa linha

	return 0;
}
