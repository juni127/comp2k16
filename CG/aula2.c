
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
//#include <stdio.h>
//#include <GL/freeglut.h>

//DeclaraÃ§Ã£o de variaveis
int g1 = 45, g2 = 45, g0 = 45, s = 0;

//Protótipos das Funções
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

	//Codigo

	glTranslatef(0, -2, 0);
	glRotatef(g0, 0, 1, 0);

	glutWireCube(1);

	glPushMatrix();
	glTranslatef(0, 0.75, 0);
	glutWireSphere(0.5, 10, 10);
	glPopMatrix();

	glTranslatef(0, 0.75, 0);

	glPushMatrix();//First node start
	glRotatef(g1, 0, 0, 1);
	glTranslatef(0, -0.75,  0);

	glPushMatrix();
	glTranslatef(0, 2, 0);
	glScalef(1, 2, 1);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 3.25, 0);
	glutWireSphere(0.5, 10, 10);
	glPopMatrix();

	glTranslatef(0, 3.25, 0);

	glPushMatrix();//Second node start
	glRotatef(g2, 0, 0, 1);
	glTranslatef(0, -3.25, 0);

	glPushMatrix();
	glTranslatef(0, 4.5, 0);
	glScalef(1, 2, 1);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 5.75, 0);
	glutWireSphere(0.5, 10, 10);
	glPopMatrix();

	glTranslatef(0, 5.75, 0);

	glPopMatrix();//Second node end
	glPopMatrix();//First node end

   glutSwapBuffers(); //Executa a Cena. SwapBuffers dá suporte para mais de um buffer, permitindo execução de animações sem cintilações. 
}

void TeclasEspeciais (int key, int x, int y)
{
	switch(key){
		case GLUT_KEY_RIGHT:
			if(!s)g0--;
			if(s==1 && g1 > -45)g1--;
			if(s==2 && g2 > -45)g2--;
			break;
		case GLUT_KEY_UP:
			s = (s == 2)?0:s+1;
			break;
		case GLUT_KEY_LEFT:
			if(!s)g0++;
			if(s==1 && g1 < 45)g1++;
			if(s==2 && g2 < 45)g2++;
			break;
		case GLUT_KEY_DOWN:
			s = (!s)?2:s-1;
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
   glutCreateWindow("Estrutura para uma Aplicação 3D");
   glutDisplayFunc(Display);
   glutSpecialFunc(TeclasEspeciais);
   glutMainLoop();
   return 0; 
}
