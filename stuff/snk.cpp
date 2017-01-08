/*
TO DO LIST ->
	*CONSERTAR O LOSE E O WIN

*/
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>


#define lrow1 "  /$$$$$$   /$$$$$$ /$$      /$$ /$$$$$$$$"
#define lrow2 " /$$__ $$ /$$__  $$| $$$    /$$$| $$_____/"
#define lrow3 "| $$  \\__/| $$  \\  $$| $$$$  /$$$$| $$      "
#define lrow4 "| $$ /$$$| $$$$$$$$| $$ $$/$$ $$| $$$$$   "
#define lrow5 "| $$|_ $$| $$__  $$| $$  $$$| $$| $$__/   "
#define lrow6 "| $$  \\ $$| $$  | $$| $$\\   $ | $$| $$      "
#define lrow7 "|  $$$$$/| $$  | $$| $$ \\ /  | $$| $$$$$$$$"
#define lrow8 " \\______/ |__/  |__/|__/     |__/|________/"

#define MAX_X 25
#define MAX_Y 25

// 0 => Nada, 1 => Barreiras, 2 => Cobra, 3 => Comida;

int maps[MAX_X][MAX_Y], pontos = 0;

//COORD é uma struct + ou - assim:
/*
typedef struct coord{
        int X, Y;        
}COORD;
*/

void cxy(COORD point){
	SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), point);
}

void title(int x, int y){
    //HWND console = GetConsoleWindow();
    //RECT r;
    //GetWindowRect(console, &r); //stores the console's current dimensions
    //MoveWindow(console, r.left, r.top, 700, 500, TRUE);
    system("title snake");
    
	COORD title;
	title.X = x;
	title.Y = y;
	cxy(title);
	puts("  /$$$$$  /$$  / $  /$$$$$$  /$$   /$$ /$$$$$$$$");
	title.Y = y + 1;
	cxy(title);
	puts(" /$$__  $| $$$| $$ /$$__  $$| $$  /$$/| $$_____/");
	title.Y = y + 2;
	cxy(title);
	puts("| $$  \\__/| $$$| $$| $$   \\ $$| $$ /$$/ | $$      ");
	title.Y = y + 3;
	cxy(title);
	puts("|  $$$$$ | $$ $$$$| $$$$$$$$| $$$$$/  | $$$$$   ");
	title.Y = y + 4;
	cxy(title);
	puts(" \\____  $$| $$  $$$| $$__  $$| $$  $$  | $$__/   ");
	title.Y = y + 5;
	cxy(title);
	puts(" /$$  \\ $$| $$\\  $$$| $$  | $$| $$\\  $$  | $$      ");
	title.Y = y + 6;
	cxy(title);
	puts("|  $$$$$/| $$ \\  $$| $$  | $$| $$ \\  $$ | $$$$$$$$");
	title.Y = y + 7;
	cxy(title);
	puts(" \\______/ |__/  \\__/|__/  |__/|__/  \\__/ |________/");
	title.Y = y + 8;
	cxy(title);
	system("pause");
	system("cls");
}

void end(bool w, int x, int y){
	system("cls");
	if(w){
	COORD title;
	title.X = x;
	title.Y = y;
	cxy(title);
	printf("%s", lrow1);
	title.Y = y + 1;
	cxy(title);
	printf("%s", lrow2);
	title.Y = y + 2;
	cxy(title);
	printf("%s", lrow3);
	title.Y = y + 3;
	cxy(title);
	printf("%s", lrow4);
	title.Y = y + 4;
	cxy(title);
	printf("%s", lrow5);
	title.Y = y + 5;
	cxy(title);
	printf("%s", lrow6);
	title.Y = y + 6;
	cxy(title);
	printf("%s", lrow7);
	title.Y = y + 7;
	cxy(title);
	printf("%s", lrow8);
	title.Y = y + 8;
	title.X = x + 15;
	cxy(title);
	printf("Pontuacao : %i", pontos);
	title.Y = y + 9;
	title.X = x;
	cxy(title);
	puts("  /$$$$$$  /$$    /$$ /$$$$$$$$ /$$$$$$$   ");
	title.Y = y + 10;
	cxy(title);
	puts(" /$$__  $$| $$   | $$| $$_____/| $$__  $$  ");
	title.Y = y + 11;
	cxy(title);
	puts("| $$    $$| $$   | $$| $$      | $$  \\ $$  ");
	title.Y = y + 12;
	cxy(title);
	puts("| $$  | $$|  $$ / $$/| $$$$$   | $$$$$$$/  ");
	title.Y = y + 13;
	cxy(title);
	puts("| $$  | $$ \\  $$ $$/ | $$__/   | $$__  $$  ");
	title.Y = y + 14;
	cxy(title);
	puts("| $$  | $$  \\  $$$/  | $$      | $$  \\ $$  ");
	title.Y = y + 15;
	cxy(title);
	puts("|  $$$$$$/   \\  $/   | $$$$$$$$| $$  | $$  ");
	title.Y = y + 16;
	cxy(title);
	puts(" \\______/      \\_/    |________/|__/  |__/  ");
	system("pause");
	system("pause");
	}else{
		
	}
}

void brd(){
	for(int x = 0; x < MAX_X; x++){
		printf("X");
		maps[x][0] = 1;
	}
	printf("\n");
	for(int y = 0; y < MAX_Y - 2; y++){
		for(int x = 0; x < MAX_X; x++){
			if(x > 0 && x < MAX_X - 1){
				printf(" ");
				maps[x][y] = 0;
			}else{
				printf("X");
				maps[x][y] = 1;
			}
		}
		printf("\n");}
		for(int x = 0; x < MAX_X; x++){
			printf("X");
			maps[x][MAX_Y-1] = 1;
		}
	printf("\n");
}

void foodPut(){
	//Cria um vetor de coordenadas possiveis excluindo o limite e a cobra
	COORD possiveis[MAX_X*MAX_Y];
	int cp = 0, escolhido = 0;
	
	for(int x = 1; x < MAX_X - 1; x++){
		for(int y = 1; y < MAX_Y - 1; y++){
			if(maps[x][y] != 1 && maps[x][y] != 2 && x != 0 && x != MAX_X){
				possiveis[cp].X = x;
				possiveis[cp].Y = y;
				cp++;
			}
		}
	}
	
	srand (time(NULL));
	escolhido = rand()%cp;
	
	maps[possiveis[escolhido].X][possiveis[escolhido].Y] = 3;
	cxy(possiveis[escolhido]);
	printf("O");
}

int main () {
	system("cls");
	clock_t firstTime = clock();
	clock_t timeSU;
	
	title(10,5);
	
	//Preenche a borda
	brd();
	
	//Cria o vetor cobra e o preenche com zeros
	COORD snake[2250];
	for(int x = 0; x < 2250; x++){
		snake[x].X = 0;
		snake[x].Y = 0;
	}
	
	snake[0].X = (MAX_X-2)/2;
	snake[0].Y = (MAX_Y-2)/2;
	
	//Cria a variavel que gerencia a direção
	COORD dir, trava;
	dir.X = 0;
	dir.Y = 0;
	trava.X = 2;
	trava.Y = 2;
	
	bool gameover = false;
	int timeC, c = 1, oldc = 1;
	float speed = 100;
	
	foodPut();
	
	while(!gameover){		
		//Atualiza o relogio
		timeSU = clock() - firstTime;
		firstTime += timeSU;
		timeC += timeSU;
		
		//Pega a direção da seta
		//A comparação com -128 e -127 é para não pegar os valores dos Bits superiores
		if((GetKeyState(VK_UP) == -128 || GetKeyState(VK_UP) == -127) &&  trava.Y != -1){
			dir.Y = 1;
			dir.X = 0;
		}
		if((GetKeyState(VK_DOWN) == -128 || GetKeyState(VK_DOWN) == -127) && trava.Y != 1){
			dir.Y = -1;
			dir.X = 0;		
		}
		if((GetKeyState(VK_RIGHT) == -128 || GetKeyState(VK_RIGHT) == -127) && trava.X != -1){
			dir.X = 1;
			dir.Y = 0;
		}
		if((GetKeyState(VK_LEFT) == -128 || GetKeyState(VK_LEFT) == -127) && trava.X != 1){
			dir.X = -1;
			dir.Y = 0;		
		}
		
		if(timeC > speed){
			trava = dir;
			timeC = 0;
			//Apagar o ultimo pedaço
			if(c == oldc){
				cxy(snake[c-1]);
				maps[snake[c-1].X][snake[c-1].Y] = 0;
				printf(" ");
			}
			
			//Mover os pedaços da cobra no vetor
			for(int i = c - 1; i > 0; i--){
				snake[i].X = snake[i-1].X;
				snake[i].Y = snake[i-1].Y;
			}
			
			switch(dir.Y){
				case 1:
					//Transportar para o outro lado
					if(snake[0].Y - 1 == 0){
						snake[0].Y = MAX_Y - 2;
					}else{
						snake[0].Y -= 1;
					}
					break;
				case -1:
					//Transportar para o outro lado
					if(snake[0].Y + 1 == MAX_Y - 1){
						snake[0].Y = 1;
					}else{
						snake[0].Y += 1;
					}
					break;
			}
			switch(dir.X){
				case 1:
					//Transportar para o outro lado
					if(snake[0].X + 1 == MAX_X - 1){
						snake[0].X = 1;
					}else{
						snake[0].X += 1;
					}
					break;
				case -1:
					//Transportar para o outro lado
					if(snake[0].X - 1 == 0){
						snake[0].X = MAX_X - 2;
					}else{
						snake[0].X -= 1;
					}
					break;
			}
			
			oldc = c;
			
			//Se a cobra encontrar o corpo
			if(maps[snake[0].X][snake[0].Y]==2){
				gameover = true;
			}
			
			//Comer
			if(maps[snake[0].X][snake[0].Y]==3){
				if(speed > 50){speed-=1;}
				pontos++;
				c++;
				foodPut();
				maps[snake[0].X][snake[0].Y]=2;
				printf("\7");
			}
			
			//Colocar o primeiro pedaço
			cxy(snake[0]);
			maps[snake[0].X][snake[0].Y] = 2;
			printf("S");
		}
		
	}
	end(true,10,5);
	COORD end;
	end.X = MAX_X + 1;
	end.Y = MAX_Y + 1;
	cxy(end);
	return 0;
}
