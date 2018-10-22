#include<math.h>
#define PI 3.14159265

void circle(float raio, int x, int y){
        glBegin(GL_LINE_LOOP);
        float a;
        for(a = 0; a < 360; a++){
                glVertex2f(x + sin(a*PI/180)*raio, y + cos(a*PI/180)*raio);
        }
        glEnd();
}

void square(float raio, int x, int y){
	glBegin(GL_LINE_LOOP);
	glVertex2f(x+raio, y+raio);
	glVertex2f(x+raio, y-raio);
	glVertex2f(x-raio, y-raio);
	glVertex2f(x-raio, y+raio);
	glEnd();
}
