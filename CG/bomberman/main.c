#include<stdio.h>

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

#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 480

int width  = DEFAULT_WIDTH;
int height = DEFAULT_HEIGHT;

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() 
{
    // Clear color and depth buffers
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
       glMatrixMode(GL_MODELVIEW);     // Operate on model-view matrix
 
    /* Draw a quad */
       glBegin(GL_QUADS);
           glTexCoord2i(0, 0); glVertex2i(0,   0);
           glTexCoord2i(0, 1); glVertex2i(0,   height);
           glTexCoord2i(1, 1); glVertex2i(width, height);
           glTexCoord2i(1, 0); glVertex2i(width, 0);
       glEnd();
 
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

 
int main(int argc, char **argv) 
{
 
 
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
    initDevil();
    openAndBind("img/main.png", 0);
    //openAndBind("img/osama.png", 1);

    /* Main loop */
    glutMainLoop();
 
    /* Delete used resources and quit */
     ilDeleteImages(1, &(image[0])); /* Because we have already copied image data into texture data we can release memory used by image. */
     glDeleteTextures(1, &(texid[0]));

     finaliza_audio();

     return 0;
}
