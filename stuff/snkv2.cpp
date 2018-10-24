/*
	JOGO DA COBRINHA v2

	TODO
	-[x] A atualização tá toda zoada (Funciona no lab) :V
	-[ ] Implementar logica para repor a comida
	-[ ] Implementar logica para a cobra colidir
	-[x] Implementar logica para a cobra atravessar a parede
*/



#include<stdio.h>
#include<time.h>

//Freeglut
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

typedef struct VECTOR{
	int x, y;
}vector;

typedef struct SQUARE{
	vector pos;
	struct COLOR{
		unsigned char r, g, b;
	}cor;
}sqr;

//ED related
#define TYPE sqr
#include"../ed/ed.h"
#undef TYPE

list_sqr * snk;
sqr food;
vector dir;
char block = 0, gameover = 0;

clock_t start = 0, end = 0;
double cpu_time_used, time_past = 0, speed = 500;
#define SPEED_FACTOR 1.0

sqr * novoBloco(int x, int y, int r, int g, int b){
	sqr * novo = (sqr*)malloc(sizeof(sqr));
	novo->pos.x = x;
	novo->pos.y = y;
	novo->cor.r = r;
	novo->cor.g = g;
	novo->cor.b = b;
	return novo;
}

void gameLogic(){
	cpu_time_used = ((double) end - start)/CLOCKS_PER_SEC;
	time_past += cpu_time_used;
	if(time_past > SPEED_FACTOR/speed){
		time_past = 0;

		//Upar todos os blocos da cobra
		list_sqr * aux, * prox;
		for(aux = snk; aux->NEXT != NULL; aux = aux->NEXT){
			prox = aux->NEXT;
			aux->DATA->pos.x = prox->DATA->pos.x;
			aux->DATA->pos.y = prox->DATA->pos.y;
		}
		if(dir.x != 0 || dir.y != 0){
			aux->DATA->pos.x += dir.x;
			aux->DATA->pos.y += dir.y;
			block = 0;
		}

		//Atravessar paredes
		if(aux->DATA->pos.x > 39)
			aux->DATA->pos.x = -40;
		if(aux->DATA->pos.x < -40)
			aux->DATA->pos.x = 39;
		if(aux->DATA->pos.y > 40)
			aux->DATA->pos.y = -39;
		if(aux->DATA->pos.y < -39)
			aux->DATA->pos.y = 40;

		//Checar se a cobra colidiu com ela mesma
		for(prox = snk; prox->NEXT != NULL; prox = prox->NEXT)
			if(prox->DATA->pos.x == aux->DATA->pos.x && prox->DATA->pos.y == aux->DATA->pos.y)
				gameover = 1;

		//Checar se a cobra comeu
		if(aux->DATA->pos.x == food.pos.x && aux->DATA->pos.y == food.pos.y){
			//Logica de fazer a cobra crescer
			sqr * novo = novoBloco(food.pos.x, food.pos.y, 0, 0, 255);
			snk = add_begin_sqr(snk, novo);

			//Logica de recolocar a comida
		}
	}
}

void dsply(){

	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-400, 400, -400, 400);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	end = clock();
	if(!gameover)gameLogic();
	start = clock();

	//Imprime a comida
	glColor3ub(food.cor.r, food.cor.g, food.cor.b);
	glBegin(GL_TRIANGLES);
	glVertex2d(food.pos.x*10, food.pos.y*10);
	glVertex2d(food.pos.x*10+10, food.pos.y*10);
	glVertex2d(food.pos.x*10+10, food.pos.y*10-10);
	glVertex2d(food.pos.x*10, food.pos.y*10);
	glVertex2d(food.pos.x*10+10, food.pos.y*10-10);
	glVertex2d(food.pos.x*10, food.pos.y*10-10);
	glEnd();

	//Imprime a cobra
	list_sqr * aux;
	for(aux = snk; aux != NULL; aux = aux->NEXT){
		glColor3ub(aux->DATA->cor.r, aux->DATA->cor.g, aux->DATA->cor.b);
		glBegin(GL_TRIANGLES);
		glVertex2d(aux->DATA->pos.x*10, aux->DATA->pos.y*10);
		glVertex2d(aux->DATA->pos.x*10+10, aux->DATA->pos.y*10);
		glVertex2d(aux->DATA->pos.x*10+10, aux->DATA->pos.y*10-10);
		glVertex2d(aux->DATA->pos.x*10, aux->DATA->pos.y*10);
		glVertex2d(aux->DATA->pos.x*10+10, aux->DATA->pos.y*10-10);
		glVertex2d(aux->DATA->pos.x*10, aux->DATA->pos.y*10-10);
		glEnd();
	}

	glutPostRedisplay();

	glutSwapBuffers();
}

void getKey(unsigned char key, int x, int y){
	switch(key){
		case 'w':
			if(dir.y != -1 && !block){
				dir.y = 1;
				dir.x = 0;
				block = 1;
			}
			break;
		case 's':
			if(dir.y != 1 && !block){
				dir.y = -1;
				dir.x = 0;
				block = 1;
			}
			break;
		case 'a':
			if(dir.x != 1 && !block){
				dir.y = 0;
				dir.x = -1;
				block = 1;
			}
			break;
		case 'd':
			if(dir.x != -1 && !block){
				dir.y = 0;
				dir.x = 1;
				block = 1;
			}
			break;
		case 'r':
			gameover = 0;
			snk = purge_all_sqr(snk);
			sqr * novo = novoBloco(0, 0, 0, 0, 255);
			snk = add_begin_sqr(snk, novo);
			food.pos.x = 3;
			food.pos.y = 0;
			dir.x = 0;
			dir.y = 0;
			break;
	}
	//glutPostRedisplay(); já to rechamando ela na display
}

int main(int argc, char **argv){

	//Variaveis iniciais do jogo
	//Inicia a comida
	food.pos.x = 3;
	food.pos.y = 0;
	food.cor.r = 255;
	food.cor.g = 0;
	food.cor.b = 0;
	//Inicia a cobra
	sqr * novo = novoBloco(0, 0, 0, 0, 255);
	snk = add_begin_sqr(snk, novo);
	//Inicia o controle de direção
	dir.x = 0;
	dir.y = 0;

	//Inicia o glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("R4G");

	glutDisplayFunc(dsply);
	glutKeyboardFunc(getKey);

	glutMainLoop();

	return 0;
}
