
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

//DevIL - Imagens
#include<IL/il.h>

#define W 480
#define H 640

#define MAXIMO_CANOS 4
#define VELOCIDADE -5.0
#define DISTANCIA 800

//Declaração de variaveis

// Quadric obj
GLUquadricObj *quadratic;


//Prot?ipos das Fun?es
void Display();
void logicaJogo();
void keyboard (unsigned char key, int x, int y);
void TeclasEspeciais (int key, int x, int y);

// Imagens
GLuint texid;
ILuint image;

// Status 0x1 - gamemode
char status = 1;

// Fisica
float s = 0, v = 0, a = -10, t = 0.01, tempo, taxa = 0, pulo = 5;

float canos[MAXIMO_CANOS][2];

clock_t start, end;

void logicaJogo(){

    end = clock();
    tempo = (end - start)*100.0/CLOCKS_PER_SEC;
    start = clock();

    taxa += tempo;

    int x;

    for(x = 0; x < MAXIMO_CANOS; x++){
        canos[x][0] += VELOCIDADE*tempo;
        if(canos[x][0] < -300){
            canos[x][0] = 1000;
            canos[x][1] = 0;
        }
    }
    
    if(taxa > 0.01){
        s = s + v*t + a*t*t/2.0;
        v = v + a*t;

        taxa = 0;
    }
}

void Display(){

    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_SMOOTH);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    //glClearDepth(0.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();//"Limpa" ou "transforma" a matriz em identidade, reduzindo poss?eis erros.

    if(status&0x1){
        gluPerspective(45,1,50,1100);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, s, 0, 30, s, 0, 0, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    }else{
        glOrtho(-W/2.0, W/2.0, -H/2.0, H/2.0, -5.0, 200);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 0 , 30, 0, 0, 0, 0, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    }

    logicaJogo();

    glColor3ub(255, 255, 255);

    // Planos de fundo (um pra visão "2d" e outro pra primeira pessoa)
    glBegin(GL_QUADS);
        glTexCoord3i(0, 1, 0); glVertex3f(-W/2.0,   -H/2.0, -100);
        glTexCoord3i(0, 0, 0); glVertex3f(-W/2.0,   H/2.0, -100);
        glTexCoord3i(1, 0, 0); glVertex3f(W/2.0, H/2.0, -100);
        glTexCoord3i(1, 1, 0); glVertex3f(W/2.0, -H/2.0, -100);
    glEnd();

    glBegin(GL_QUADS);
        glTexCoord3i(0, 1, 0); glVertex3f(1000,   -H, -W);
        glTexCoord3i(0, 0, 0); glVertex3f(1000,   H, -W);
        glTexCoord3i(1, 0, 0); glVertex3f(1000, H, W);
        glTexCoord3i(1, 1, 0); glVertex3f(1000, -H, W);
    glEnd();

    glPushMatrix();
    //glColor3ub(255, 255, 0);
    // Passaro
    glTranslatef(0, s, 0);
    glPushMatrix();
        // Rotação
        glRotatef(-5.0*v, 0, 0, 1);

        glutSolidCube(50);
    glPopMatrix();
    glTranslatef(0, -s, 0);
    glPopMatrix();

    // Canos 
    int x;
    glColor3ub(50, 255, 50);
    for(x = 0; x < MAXIMO_CANOS; x++){
        glPushMatrix();
            glTranslatef(canos[x][0], 0, 0);

            glPushMatrix();
                glTranslatef(0, canos[x][1]+80, 0);
                glRotatef(90.0, -1, 0, 0);
                gluCylinder(quadratic, 30.0f, 30.0f, 500.0, 32, 32);
                gluCylinder(quadratic, 35.0f, 35.0f, 30.0, 32, 32);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, canos[x][1]-80, 0);
                glRotatef(90.0, 1, 0, 0);
                gluCylinder(quadratic, 30.0f, 30.0f, 500.0, 32, 32);
                gluCylinder(quadratic, 35.0f, 35.0f, 30.0, 32, 32);
            glPopMatrix();

        glPopMatrix();
    }

    glutSwapBuffers(); //Executa a Cena. SwapBuffers d?suporte para mais de um buffer, permitindo execu?o de anima?es sem cintila?es.
    glutPostRedisplay(); //Executa novamente
}



void TeclasEspeciais (int key, int x, int y){
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
    glutCreateWindow("Flappy Bird");
    glutInitWindowPosition(100, 100);
    glutDisplayFunc(Display);

    quadratic = gluNewQuadric();

    int x;
    for(x = 0; x < MAXIMO_CANOS; x++){
        canos[x][0] += x*DISTANCIA+100;
        canos[x][1] = 0;
    }
    
    // Abrindo background
    /* Initialization of DevIL */
    ilInit(); 

    ilGenImages(1, &image); /* Generation of one image name */
    glGenTextures(1, &texid);


    ilBindImage(image); /* Binding of image name */
    ilLoadImage("img/background.png"); /* Loading of the image filename by DevIL */
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE); 
 
    /* OpenGL texture binding of the image loaded by DevIL  */
    glBindTexture(GL_TEXTURE_2D, texid); /* Binding of texture name */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
    0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */





    glutSpecialFunc(TeclasEspeciais);
    glutKeyboardFunc(TeclasNormais);
    glutMainLoop();

   return 0; 
}
