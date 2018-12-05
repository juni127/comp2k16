
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

//DeclaraÃ§Ã£o de variaveis


//Protótipos das Funções
void Display();
void logicaJogo();
void keyboard (unsigned char key, int x, int y);
void TeclasEspeciais (int key, int x, int y);

float s= 0, v = 0, a = -10, t = 0, tempo;

clock_t start, end;

void logicaJogo(){

    end = clock();
    tempo = (end - start)*100.0/CLOCKS_PER_SEC;
    start = clock();

    t += tempo;

    printf("t: %f\n", s);
    if(t > 0.1){
        s = s + v*t/10.0 + a*t*t/20.0;
        v = v + a*t/10.0;

        t = 0;
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


   glMatrixMode(GL_PROJECTION);/*glMatrixMode()- define qual matriz será alterada. SEMPRE defina o tipo de apresentação 
                              (Ortogonal ou Perspectiva) na matriz PROJECTION.*/
   glLoadIdentity();//"Limpa" ou "transforma" a matriz em identidade, reduzindo possíveis erros.


   gluPerspective(45,1,1,150);
   //glOrtho(-8, 8, -8, 8, -150, 150);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0); //Define a pos da câmera, para onde olha e qual eixo está na vertical.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glColor3ub(255, 255, 255);


   logicaJogo();

   glPushMatrix();
   glTranslatef(0, s, 0);
   glutWireCube(1);
   glPopMatrix();


    glutSwapBuffers(); //Executa a Cena. SwapBuffers dá suporte para mais de um buffer, permitindo execução de animações sem cintilações.
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
        v = 5;
}


int main(int argc,char **argv)
{
   glutInit(&argc, argv); // Initializes glut


   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

   glutInitWindowSize(W, H);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Flappy Bird");
   glutDisplayFunc(Display);
   glutSpecialFunc(TeclasEspeciais);
   glutKeyboardFunc(TeclasNormais);
   glutMainLoop();

   return 0; 
}
