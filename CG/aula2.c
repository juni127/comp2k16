
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
//#include <stdio.h>
//#include <GL/freeglut.h>

//Declara��o de Vari�veis Globais
int projecao=0; //Vari�vel L�gica para Definir o Tipo de Proje��o (Perspectiva ou Ortogonal)
int posx=0, posy=10, posz=20; //Vari�veis que definem a posi��o da c�mera
int oy=0,ox=0,oz=0;         //Vari�veis que definem para onde a c�mera olha
int lx=0, ly=1,  lz=0;         //Vari�veis que definem qual eixo estar� na vertical do monitor.

//Prot�tipos das Fun��es
void Inicializa();
void Display();
void Mouse(int botao, int estado, int x, int y);
void keyboard (unsigned char key, int x, int y);
void TeclasEspeciais (int key, int x, int y);

void Display()
{

   glEnable(GL_DEPTH_TEST);

   glEnable(GL_LINE_SMOOTH);
   glEnable(GL_POLYGON_SMOOTH);


   glEnable(GL_SMOOTH);
   glEnable(GL_BLEND);

   glClearColor(0.0, 0.0, 0.0, 0.0);


   glMatrixMode(GL_PROJECTION);/*glMatrixMode()- define qual matriz ser� alterada. SEMPRE defina o tipo de apresenta��o 
                              (Ortogonal ou Perspectiva) na matriz PROJECTION.*/
   glLoadIdentity();//"Limpa" ou "transforma" a matriz em identidade, reduzindo poss�veis erros.


   //gluPerspective(45,1,1,150);
	glOrtho(-8, 8, -8, 8, -150, 150);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0, 0, 10, 0, 0, 0, lx, ly, lz); //Define a pos da c�mera, para onde olha e qual eixo est� na vertical.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glColor3ub(255, 255, 255);

	//Codigo

	glutWireCube(1);

	glPushMatrix();
	glTranslatef(0, 0.75, 0);
	glutWireSphere(0.5, 10, 10);
	glPopMatrix();

	glPushMatrix();//First node start
	glTranslatef(0, -1, 0);
	glRotatef(45, 0, 0, 1);

	glPushMatrix();
	glTranslatef(0, 2, 0);
	glScalef(1, 2, 1);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 3.25, 0);
	glutWireSphere(0.5, 10, 10);
	glPopMatrix();

	glPushMatrix();//Second node start

	glPushMatrix();
	glTranslatef(0, 4.5, 0);
	glScalef(1, 2, 1);
	glutWireCube(1);
	glPopMatrix();

	glPopMatrix();//Second node end
	glPopMatrix();//First node end

   glutSwapBuffers(); //Executa a Cena. SwapBuffers d� suporte para mais de um buffer, permitindo execu��o de anima��es sem cintila��es. 
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


int main(int argc,char **argv)
{
   glutInit(&argc, argv); // Initializes glut


   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

   glutInitWindowSize(300, 300);
   glutInitWindowPosition(10, 10);
   glutCreateWindow("Estrutura para uma Aplica��o 3D");
   glutDisplayFunc(Display);
   glutSpecialFunc(TeclasEspeciais);
   glutMainLoop();
   return 0; 
}
