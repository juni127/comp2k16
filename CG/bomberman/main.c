#include<stdio.h>
#include<time.h>

//Threads
#include<pthread.h>

//Glut
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

//DevIL - Imagens
#include<IL/il.h>

//mpg123 - Audio
#include <ao/ao.h>
#include <mpg123.h>

//Organizacional
#include"lib/texture.h"
#include"lib/audio.h"
#include"lib/animacao.h"

#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 480

int width  = DEFAULT_WIDTH;
int height = DEFAULT_HEIGHT;

int ESTADO = 0;

void menu_principal(){
    /* Draw a quad */
    abrir_imagem("img/fundo_titulo.png", 0);
    desenhar_imagem(0, 0);

    animacoes();
    
    abrir_imagem("img/titulo.png", 5);
    desenhar_imagem(0, -100);
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
    /* Comum */
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glMatrixMode(GL_MODELVIEW);     // Operate on model-view matrix
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    switch(ESTADO){
        case 0:
            //Menu principal
            menu_principal();
            break;
    }

    glutSwapBuffers();
}

void reshape(int width, int height) {
    // we ignore the params and do:
    glutReshapeWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}



/* Initialize OpenGL Graphics */
void initGL(int w, int h) 
{
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);   // Set the window's initial width & height
    glutCreateWindow("Bomberman");      // Create window with the name of the executable
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);
    glViewport(0, 0, w, h); // use a screen size of WIDTH x HEIGHT
    glEnable(GL_TEXTURE_2D);     // Enable 2D texturing
 
    glMatrixMode(GL_PROJECTION);     // Make a simple 2D projection on the entire window
    glLoadIdentity();
    glOrtho(0.0, w, h, 0.0, 0.0, 100.0);
 
    glMatrixMode(GL_MODELVIEW);    // Set the matrix mode to object modeling
 
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
    glClearDepth(0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window
}

 
int main(int argc, char **argv) {
    /* GLUT init */
    glutInit(&argc, argv);
    initGL(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    /* Inicialização do mpg123 */
    inicia_audio();
    abrir_audio("sng/main.mp3");
    pthread_t thread_musica, musica2;
    int arg = 0x01;
    pthread_create(&thread_musica, NULL, tocar_audio, &arg);


    /* Initialization of DevIL */
    inicia_textura();

    inicia_animacao();

    abrir_imagem("img/dirigivel_menor.png", 1);
    vertex c1[2];
    c1[0].x = -100; c1[0].y = 225;
    c1[1].x = 650; c1[1].y = 225;
    setar_animacao(c1, 2, 50.0, 0, 0, 1);
    tocar_animacao(0);

    abrir_imagem("img/dirigivel_maior.png", 2);
    vertex c2[2];
    c2[0].x = 650; c2[0].y = 180;
    c2[1].x = -200; c2[1].y = 180;
    setar_animacao(c2, 2, 100.0, 0, 1, 2);
    tocar_animacao(1);

    abrir_imagem("img/balao.png", 3);
    vertex c3[7];
    c3[0].x = -150; c3[0].y = 140;
    c3[1].x = -10; c3[1].y = 0;
    c3[2].x = 130; c3[2].y = 140;
    c3[3].x = 270; c3[3].y = 0;
    c3[4].x = 410; c3[4].y = 140;
    c3[5].x = 550; c3[5].y = 0;
    c3[6].x = 690; c3[6].y = 140;
    setar_animacao(c3, 7, 75.0, 0, 2, 3);
    tocar_animacao(2);


/*
    abrir_imagem("img/dirigivel_menor.png", 2);
    desenhar_imagem(0, 225);

    abrir_imagem("img/balao.png", 3);
    desenhar_imagem(50, 25);
*/
    /* Main loop */
    glutMainLoop();
 
    /* Delete used resources and quit */
    ilDeleteImages(1, &(image[0])); /* Because we have already copied image data into texture data we can release memory used by image. */
    glDeleteTextures(1, &(texid[0]));

    finaliza_audio();

    return 0;
}
