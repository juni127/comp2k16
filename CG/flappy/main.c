
#include<stdio.h>
#include<stdlib.h>

// Tempo
#include<time.h>

// Glut
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

//Threads
#include<pthread.h>

#define W 480
#define H 640

#define MAXIMO_CANOS 2

//Declaração de variaveis


//Prot?ipos das Fun?es
void Display();
void logicaJogo();
void keyboard (unsigned char key, int x, int y);
void TeclasEspeciais (int key, int x, int y);

// Status 0x1 - gamemode
char status = 0;

// Fisica
float s = 0, v = 0, a = -10, t = 0.01, tempo, taxa = 0, pulo = 5;

float canos[MAXIMO_CANOS][2];

clock_t start, end;

void logicaJogo(){

    end = clock();
    tempo = (end - start)*100.0/CLOCKS_PER_SEC;
    start = clock();

    taxa += tempo;

    
    if(taxa > 0.01){
        printf("v: %f\n", v);
        s = s + v*t + a*t*t/2.0;
        v = v + a*t;

        taxa = 0;
    }
}

void Display()
{

   glEnable(GL_DEPTH_TEST);

   glEnable(GL_LINE_SMOOTH);
   glEnable(GL_POLYGON_SMOOTH);


   glEnable(GL_SMOOTH);
   glEnable(GL_BLEND);

   glClearColor(0.0, 0.0, 0.0, 0.0);


   glMatrixMode(GL_PROJECTION);/*glMatrixMode()- define qual matriz ser?alterada. SEMPRE defina o tipo de apresenta?o 
                              (Ortogonal ou Perspectiva) na matriz PROJECTION.*/
   glLoadIdentity();//"Limpa" ou "transforma" a matriz em identidade, reduzindo poss?eis erros.


    if(status&0x1)
        gluPerspective(45,1,1,150);
    else
        glOrtho(-8, 8, -8, 8, -150, 150);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0); //Define a pos da c?era, para onde olha e qual eixo est?na vertical.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glColor3ub(255, 255, 255);


    logicaJogo();

    // Passaro
    glTranslatef(0, s, 0);
    glPushMatrix();
        // Rotação
        glRotatef(-5.0*v, 0, 0, 1);

        glutSolidCube(1);
    glPopMatrix();
    glTranslatef(0, -s, 0);


    glutSwapBuffers(); //Executa a Cena. SwapBuffers d?suporte para mais de um buffer, permitindo execu?o de anima?es sem cintila?es.
    glutPostRedisplay(); //Executa novamente
}

void TeclasEspeciais (int key, int x, int y)
{
	switch(key){
		case GLUT_KEY_RIGHT:
			break;
		case GLUT_KEY_UP:
			break;
		case GLUT_KEY_LEFT:
			break;
		case GLUT_KEY_DOWN:
			break;
	}
	glutPostRedisplay();
}

void TeclasNormais(unsigned char key, int x, int y){
    if(key == 32)
        v = pulo;
}


int main(int argc,char **argv)
{
   glutInit(&argc, argv); // Initializes glut


   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

   glutInitWindowSize(W, H);
   glutInitWindowPosition(10, 10);
   glutCreateWindow("Flappy Bird");
   glutDisplayFunc(Display);
   glutSpecialFunc(TeclasEspeciais);
   glutKeyboardFunc(TeclasNormais);
   glutMainLoop();

   return 0; 
}
