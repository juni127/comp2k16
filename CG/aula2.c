
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
//#include <stdio.h>
//#include <GL/freeglut.h>

//Declaração de Variáveis Globais
int projecao=0; //Variável Lógica para Definir o Tipo de Projeção (Perspectiva ou Ortogonal)
int posx=0, posy=10, posz=20; //Variáveis que definem a posição da câmera
int oy=0,ox=0,oz=0;         //Variáveis que definem para onde a câmera olha
int lx=0, ly=1,  lz=0;         //Variáveis que definem qual eixo estará na vertical do monitor.

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
   
   // Inicializa parâmetros de rendering
    // Define a cor de fundo da janela de visualização como preta
   glClearColor(1.0, 0.0, 0.0, 0.0); 
   
   
   glMatrixMode(GL_PROJECTION);/*glMatrixMode()- define qual matriz será alterada. SEMPRE defina o tipo de apresentação 
                              (Ortogonal ou Perspectiva) na matriz PROJECTION.*/
   glLoadIdentity();//"Limpa" ou "transforma" a matriz em identidade, reduzindo possíveis erros.

   if (projecao==1)
      glOrtho(-150, 150, -150, 150, -150, 150); //Define a projeção como ortogonal
   else
      gluPerspective(45,1,1,150); //Define a projeção como perspectiva
   
   glMatrixMode(GL_MODELVIEW);/*glMatrixMode()- define qual matriz será alterada. SEMPRE defina a câmera 
                              (Ortogonal ou Perspectiva) na matriz MODELVIEW (onde o desenho ocorrerá).*/
   glLoadIdentity(); ////"Limpa" ou "transforma" a matriz em identidade, reduzindo possíveis erros.

   gluLookAt(posx,posy,posz,ox,oy,oz,lx,ly,lz); //Define a pos da câmera, para onde olha e qual eixo está na vertical.
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); /* "limpa" um buffer particular ou combinações de buffers, 
                                                         onde buffer é uma área de armazenamento para informações da imagem. 
                                                        Nesse caso, está "limpando os buffers para suportarem animações */
   //Chamada para Função  ou funções para desenhar o objeto/cena...
   //----------------------------------------------------------------
   //glPushMatrix(); //Salva o estado atual da cena. O que for desenhado após o Push não influenciará o já representado
      glColor3ub(100, 255, 40); //DEFINE cor (R, G, B e percentual de transparência para o objeto)
      glutWireTeapot(5.0);
  // glPopMatrix();  //Retorna ao estado anterior da cena. O que for desenhado após o Push não influenciou o já representado
   //----------------------------------------------------------------   
   
   glutSwapBuffers(); //Executa a Cena. SwapBuffers dá suporte para mais de um buffer, permitindo execução de animações sem cintilações. 
}

void Mouse(int botao, int estado, int x, int y)
{  //botão - recebe o código do botão pressionado
   //estado - recebe se está pressionado ou não
   //x, y - recebem respectivamente as posições do mouse na tela
   switch (botao)
   {
      case GLUT_LEFT_BUTTON:
      if (estado == GLUT_DOWN)
      {                  
         projecao=1;
         posx=0; posy=10; posz=20;
         ox=0,oy=0,oz=0;
         lx=0, ly=1,lz=0;
         glutPostRedisplay();
      }
      break;

      case GLUT_RIGHT_BUTTON:
      if(estado == GLUT_DOWN)
      {
         projecao=0;
         posx=0; posy=10; posz=20;
         oy=0; ox=0;  oz=0;
         lx=0, ly=1, lz=0;
         glutPostRedisplay();
      }
      break;
   }
}

void keyboard (unsigned char key, int x, int y)
{//Key - recebe o código ASCII da tecla
 //x, y - recebem as posições do mouse na tela (permite tratar os dois dispositivos)
      if (key=='d')
      {
         lz=0; ly=1; ox+=5;
      }
      else if (key=='e')
      {
         lz=0; ly=1; ox-=5;
      }
      else if (key=='c')
      {
         lz=0; ly=1; oy+=5;
      }
      else if (key=='b')    
      {
         lz=0; ly=1; oy-=5;
      }
      else if (key==27)
      {         
         exit(0);
      }
      glutPostRedisplay();
}

void TeclasEspeciais (int key, int x, int y)
{//Key - recebe o código ASCII da tecla
 //x, y - recebem respectivamente as posições mouse na tela (permite tratar os dois dispositivos)
      if (key==GLUT_KEY_RIGHT)
      {
         posx+=5; ox+=5;
      }
      else if (key==GLUT_KEY_PAGE_UP)
      {
         posy+=5; oy+=5;
      }
      else if (key==GLUT_KEY_UP)
      {
         posz-=5; oz-=5;
      }
      else if (key==GLUT_KEY_LEFT)    
      { 
         posx-=5; ox-=5;
      }
      else if (key==GLUT_KEY_PAGE_DOWN)
      {
         posy-=5; oy-=5;
      }
      else if (key==GLUT_KEY_DOWN)
      {      
         posz+=5; oz+=5;
      }
      glutPostRedisplay();
}


int main(int argc,char **argv)
{
   glutInit(&argc, argv); // Initializes glut
    
   
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); /*Define as características do espaço vetorial. 
                                                                           //  Nesse caso, permite animações (sem cintilações), cores compostas por Verm. Verde e Azul,
                                                                           //  Buffer que permite trablhar com profundidade e elimina faces escondidas.*/           
  
   glutInitWindowSize(300, 300);
   glutInitWindowPosition(10, 10);
   glutCreateWindow("Estrutura para uma Aplicação 3D");
   glutDisplayFunc(Display);
   glutMouseFunc(Mouse);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(TeclasEspeciais);
   glutMainLoop();
   return 0; 
}
