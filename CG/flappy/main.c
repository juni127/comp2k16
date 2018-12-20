
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

#define MAXIMO_CANOS 8
#define VELOCIDADE -5.0
#define DISTANCIA 800

//Declaração de variaveis

// Quadric obj
GLUquadricObj *quadratic;

// Imagens
GLuint txd_default; ILuint img_default; // Background 2d
GLuint texid_clouds; ILuint image_clouds; // Background 2d
GLuint texid_city; ILuint image_city; // Background 2d
GLuint texid_grass; ILuint image_grass; // Background 2d

//Prot?ipos das Fun?es
void Display();
void logicaJogo();
void keyboard (unsigned char key, int x, int y);
void TeclasEspeciais (int key, int x, int y);

void abrirImagem(GLuint * texid, ILuint * image, char * path);
void selecionarImagem(GLuint texid, ILuint image);

// Status 0x1 - gamemode
char status = 0;

// Fisica
float s = 0, v = 0, a = -10, t = 0.1, tempo, taxa = 0, pulo = 50;

float canos[MAXIMO_CANOS][2];

clock_t start, end;

void abrirImagem(GLuint * texid, ILuint * image, char * path){
    ilGenImages(1, image); /* Generation of one image name */
    glGenTextures(1, texid);


    ilBindImage(*image); /* Binding of image name */
    ilLoadImage(path); /* Loading of the image filename by DevIL */
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE); 
}

void selecionarImagem(GLuint texid, ILuint image){
    /* OpenGL texture binding of the image loaded by DevIL  */
    ilBindImage(image); /* Binding of image name */
    glBindTexture(GL_TEXTURE_2D, texid); /* Binding of texture name */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
    0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */
}

void fundo2d(){
    selecionarImagem(texid_clouds, image_clouds);
    glBegin(GL_QUADS);
        glTexCoord3i(0, 1, 0); glVertex3f(-W/2.0,   -H/2.0, -103);
        glTexCoord3i(0, 0, 0); glVertex3f(-W/2.0,   H/2.0, -103);
        glTexCoord3i(1, 0, 0); glVertex3f(W/2.0, H/2.0, -103);
        glTexCoord3i(1, 1, 0); glVertex3f(W/2.0, -H/2.0, -103);
    glEnd();

    selecionarImagem(texid_city, image_city);
    glBegin(GL_QUADS);
        glTexCoord3i(0, 1, 0); glVertex3f(-W/2.0,   -H/2.0, -102);
        glTexCoord3i(0, 0, 0); glVertex3f(-W/2.0,   H/2.0, -102);
        glTexCoord3i(1, 0, 0); glVertex3f(W/2.0, H/2.0, -102);
        glTexCoord3i(1, 1, 0); glVertex3f(W/2.0, -H/2.0, -102);
    glEnd();

    selecionarImagem(texid_grass, image_grass);
    glBegin(GL_QUADS);
        glTexCoord3i(0, 1, 0); glVertex3f(-W/2.0,   -H/2.0, -101);
        glTexCoord3i(0, 0, 0); glVertex3f(-W/2.0,   H/2.0, -101);
        glTexCoord3i(1, 0, 0); glVertex3f(W/2.0, H/2.0, -101);
        glTexCoord3i(1, 1, 0); glVertex3f(W/2.0, -H/2.0, -101);
    glEnd();
}

void fundo3d(){
    selecionarImagem(texid_clouds, image_clouds);
    glBegin(GL_QUADS);
        glTexCoord3i(0, 1, 0); glVertex3f(4800,   -H, -W);
        glTexCoord3i(0, 0, 0); glVertex3f(4800,   H, -W);
        glTexCoord3i(1, 0, 0); glVertex3f(4800, H, W);
        glTexCoord3i(1, 1, 0); glVertex3f(4800, -H, W);
    glEnd();
    
    selecionarImagem(texid_city, image_city);
    glBegin(GL_QUADS);
        glTexCoord3i(0, 1, 0); glVertex3f(4400,   -H, -W);
        glTexCoord3i(0, 0, 0); glVertex3f(4400,   H, -W);
        glTexCoord3i(1, 0, 0); glVertex3f(4400, H, W);
        glTexCoord3i(1, 1, 0); glVertex3f(4400, -H, W);
    glEnd();
    
    selecionarImagem(texid_grass, image_grass);
    glBegin(GL_QUADS);
        glTexCoord3i(0, 1, 0); glVertex3f(4000,   -H+100, -W);
        glTexCoord3i(0, 0, 0); glVertex3f(4000,   H+100, -W);
        glTexCoord3i(1, 0, 0); glVertex3f(4000, H+100, W);
        glTexCoord3i(1, 1, 0); glVertex3f(4000, -H+100, W);
    glEnd();
}

void logicaJogo(){

    end = clock();
    tempo = (end - start)*100.0/CLOCKS_PER_SEC;
    start = clock();

    taxa += tempo;

    int x;

    for(x = 0; x < MAXIMO_CANOS; x++){
        canos[x][0] += VELOCIDADE*tempo;
        if(canos[x][0] < -300){
            canos[x][0] = (DISTANCIA * MAXIMO_CANOS) - 300;
            canos[x][1] = rand()%200 - 100;
        }
    }
    
    if(taxa > 0.01){
        s = s + v*t + a*t*t/2.0;
        v = v + a*t;

        taxa = 0;
    }
}

void Display(){

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_SMOOTH);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    //glClearDepth(0.0f);
    glClearColor(0.41568627451f, 0.76862745098f, 0.81960784313f, 1.0f);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();//"Limpa" ou "transforma" a matriz em identidade, reduzindo poss?eis erros.

    if(status&0x1){
        gluPerspective(45,1,50,5000);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, s, 0, 30, s, 0, 0, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    }else{
        glOrtho(-W/2.0, W/2.0, -H/2.0, H/2.0, -50.0f, 200);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 0 , 30, 0, 0, 0, 0, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    }

    logicaJogo();

    glColor3ub(255, 255, 255);

    // Planos de fundo (um pra visão "2d" e outro pra primeira pessoa)
    if(status&0x1)
        fundo3d();
    else
        fundo2d();

    selecionarImagem(txd_default, img_default);

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
    glColor3ub(116, 191, 46);
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

    // Chão
    glColor3ub(158, 235, 94);
    glPushMatrix();
        glTranslatef(16, -200, 0);
        glScalef(128.0f, 0.3f, 3.0f);
        glutSolidCube(50);
    glPopMatrix();

    glColor3ub(211, 216, 148);
    glPushMatrix();
        glTranslatef(0, -300, 0);
        glScalef(16.0f, 4.0f, 2.5f);
        glutSolidCube(50);
    glPopMatrix();

    glutSwapBuffers(); //Executa a Cena. SwapBuffers d?suporte para mais de um buffer, permitindo execu?o de anima?es sem cintila?es.
    glutPostRedisplay(); //Executa novamente
}



void TeclasEspeciais (int key, int x, int y){
	switch(key){
		case GLUT_KEY_RIGHT:
            status = 1;
			break;
		case GLUT_KEY_UP:
			break;
		case GLUT_KEY_LEFT:
            status = 0;
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

    srand(time(NULL));

    int x;
    for(x = 0; x < MAXIMO_CANOS; x++){
        canos[x][0] += x*DISTANCIA+100;
        canos[x][1] = rand()%200 - 100;
    }
    
    // Abrindo background
    /* Initialization of DevIL */
    ilInit(); 


    abrirImagem(&txd_default, &img_default, "img/default.png");
    abrirImagem(&texid_clouds, &image_clouds, "img/clouds.png");
    abrirImagem(&texid_city, &image_city, "img/city.png");
    abrirImagem(&texid_grass, &image_grass, "img/grass.png");


    glutSpecialFunc(TeclasEspeciais);
    glutKeyboardFunc(TeclasNormais);
    glutMainLoop();

   return 0; 
}
