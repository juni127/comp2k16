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



#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 480

#define MAX_CANO 3

int width  = DEFAULT_WIDTH;
int height = DEFAULT_HEIGHT;

GLuint texid;
ILuint image;


/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_SMOOTH);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
    //glClearDepth(0.0f);

    //glViewport(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT); // use a screen size of WIDTH x HEIGHT
    
 
    glMatrixMode(GL_PROJECTION);     // Make a simple 2D projection on the entire window
    glLoadIdentity();
    
    glOrtho(0.0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.0, 0.0, 100.0);
 
    glMatrixMode(GL_MODELVIEW);    // Set the matrix mode to object modeling
    glLoadIdentity();
    gluLookAt(0, 0 , 30, 0, 0, 0, 0, 1, 0); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);    

    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2f(0,   0);
        glTexCoord2i(0, 1); glVertex2f(0,   480);
        glTexCoord2i(1, 1); glVertex2f(640, 480);
        glTexCoord2i(1, 0); glVertex2f(640, 0);
    glEnd();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    // we ignore the params and do:
    glutReshapeWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}




void processKeys(unsigned char key, int x, int y){

}

 
int main(int argc, char **argv) {
    /* GLUT init */
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Enable double buffered mode
    glutInitWindowSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);   // Set the window's initial width & height
    glutCreateWindow("Flappy Bird");      // Create window with the name of the executable
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);
    



    int x = 0;

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


/*
    abrir_imagem("img/dirigivel_menor.png", 2);
    desenhar_imagem(0, 225);

    abrir_imagem("img/balao.png", 3);
    desenhar_imagem(50, 25);
*/
    /* Main loop */
    glutMainLoop();
 
    /* Delete used resources and quit */
    ilDeleteImages(1, &image); /* Because we have already copied image data into texture data we can release memory used by image. */
    glDeleteTextures(1, &texid);

    return 0;
}
