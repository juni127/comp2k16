#include<stdio.h>

//Freeglut
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

#include"formas.h"

void dsply(){

	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-400, 400, -400, 400);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3ub(255,255,255);

	circle(50, 50, -50);
	circle(100, 25, -25);
	square(50, 50, -50);

	glutSwapBuffers();
}

void getKey(unsigned char key, int x, int y){
	printf("%c\n", key);

	//glutPostRedisplay();
}

int main(int argc, char **argv){

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
