#include<stdio.h>
#include<stdlib.h> 
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

#define MAX_CANO 3

int width  = DEFAULT_WIDTH;
int height = DEFAULT_HEIGHT;

pthread_t thread_sfx;

vertex canos[MAX_CANO];
float acel = 120, vel = 0, posicao = 240, temp = 0.05, vel_cano = -3;
char gameover = 0, caindo = 0, gamemode = 0;


void jogo2d(){
    int x;
    escolher_imagem(0);
    desenhar_imagem(0, 0);

    for(x = 0; x < MAX_CANO; x++){
        escolher_imagem(3);
        desenhar_imagem(canos[x].x, canos[x].y+40);
        escolher_imagem(4);
        desenhar_imagem(canos[x].x, canos[x].y - 570);

        // Colisão com o cano
        //printf("pos: %f  x: %f y: %f\n", posicao, canos[x].x, canos[x].y);
        if(!caindo && 360 > canos[x].x && 300 < canos[x].x && (posicao < canos[x].y-90 || posicao > canos[x].y+20)){
            pthread_cancel(&thread_sfx);
            abrir_audio("sng/queda.mp3");
            pthread_create(&thread_sfx, NULL, tocar_audio, NULL);
            caindo = 1;
            vel = 0;
        }
    }

    // Colisão com o chão
    if(posicao + 25 > 400){
        gameover = 1;

        //pthread_cancel(&thread_sfx);
        //abrir_audio("sng/colisao.mp3");
        //pthread_create(&thread_sfx, NULL, tocar_audio, NULL);
    }

    // Colisão com o teto
    if(posicao < 0){
        vel = 0;
        posicao = 0;
    }

    escolher_imagem(2);
    //glRotatef(90.0*vel/250.0, 0, 0, 1);
    desenhar_imagem(340, posicao);

    escolher_imagem(1);
    desenhar_imagem(0, 400);

}

void jogo3d(){

}

void jogo1pessoa(){

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

    end = clock();
    tempo_passado += (end - start)*10000/CLOCKS_PER_SEC;
    start = clock();

    int x;

    switch(gamemode){
        case 0:
            jogo2d();
            break;
        case 1:
            jogo3d();
            break;
        case 2:
            jogo1pessoa();
            break;
    }


    if(tempo_passado > 1 && !gameover){
        tempo_passado = 0;

        posicao = posicao + vel * temp + acel * temp * temp/2;
        vel = vel + acel * temp;

        for(x = 0; x < MAX_CANO && !caindo; x++){
            canos[x].x += vel_cano;
            if(canos[x].x < -100){
                canos[x].x = 640;
                canos[x].y = rand()%300 + 100;
            }
        }
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
    glutCreateWindow("Flappy Bird");      // Create window with the name of the executable
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

void processKeys(unsigned char key, int x, int y){
    if(key == 32 && !caindo){
        vel = -150;
        
        // Tocar som da batida das asas
        //pthread_cancel(&thread_sfx);
        //abrir_audio("sng/batida.mp3");
        //pthread_create(&thread_sfx, NULL, tocar_audio, NULL);
    }
}

 
int main(int argc, char **argv) {
    /* GLUT init */
    glutInit(&argc, argv);
    initGL(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    glutKeyboardFunc( processKeys );

    /* Inicialização do mpg123 */
    inicia_audio();

    int x = 0;

    /* Initialization of DevIL */
    inicia_textura();

    inicia_animacao();

    srand (time(NULL));

    for(x = 0; x < MAX_CANO; x++){
        canos[x].x = 680 + x*(640/MAX_CANO);
        canos[x].y = rand()%320 + 80;
    }

    abrir_imagem("img/fundo.png", 0);
    abrir_imagem("img/chao.png", 1);
    abrir_imagem("img/bird.png", 2);
    abrir_imagem("img/cano.png", 3);
    abrir_imagem("img/cano2.png", 4);

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
