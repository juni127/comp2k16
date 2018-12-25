// Tudo
#include"lib/cabeca.h"

//Declaração de variaveis

// Persistencia
FILE * savedata;

// Quadric obj
GLUquadricObj *quadratic;

// Imagens
GLuint txd_default; ILuint img_default; // Background 2d
GLuint texid_clouds; ILuint image_clouds; // Background 2d
GLuint texid_city; ILuint image_city; // Background 2d
GLuint texid_grass; ILuint image_grass; // Background 2d
GLuint texid_message; ILuint image_message; // Instrução do inicio
GLuint texid_gameover; ILuint image_gameover; // Gameover
GLuint texid_novo; ILuint image_novo; // Novo recorde
GLuint texid_bronze; ILuint image_bronze; // Medalha de bronze
GLuint texid_prata; ILuint image_prata; // Medalha de prata
GLuint texid_ouro; ILuint image_ouro; // Medalha de ouro
GLuint texid_numeros[10]; ILuint image_numeros[10]; // Gameover



// Status 0x1 - gamemode / 0x2 e 0x4 - gamestate / 0x8 novo recorde
char status = 0x0;

int pontos = 0, melhor = 0, apagar = 0;

clock_t start, end;
float tempo, taxa = 0;


void abrirDados(){
    savedata = fopen("save.dat", "rb");
    if(savedata == NULL){
        savedata = fopen("save.dat", "wb");
        fwrite(&melhor, sizeof(int), 1, savedata);
    }else{
        fread(&melhor, sizeof(int), 1, savedata);
        fclose(savedata);
    }
}

void salvarDados(){
    savedata = fopen("save.dat", "wb");
    fwrite(&melhor, sizeof(int), 1, savedata);
    fclose(savedata);
}

void atualizarPontos(){
    pontos++;
}

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

void printaNumero(int numero){
    int x;
    for(x = 0; numero > 0 || x == 0; numero /= 10, x++){
        selecionarImagem(texid_numeros[numero%10], image_numeros[numero%10]);
        glBegin(GL_QUADS);
            glTexCoord3i(0, 1, 0); glVertex3f( 0-(x*18), 0, 0);
            glTexCoord3i(0, 0, 0); glVertex3f( 0-(x*18), 16, 0);
            glTexCoord3i(1, 0, 0); glVertex3f( 16-(x*18), 16, 0);
            glTexCoord3i(1, 1, 0); glVertex3f( 16-(x*18), 0, 0);
        glEnd();
    }
}

void fundo2d(){
    selecionarImagem(texid_clouds, image_clouds);
    glBegin(GL_QUADS);
        glTexCoord3i(0, 1, 0); glVertex3f(-W/2.0,   -W+100, -102);
        glTexCoord3i(0, 0, 0); glVertex3f(-W/2.0,   W+100, -102);
        glTexCoord3i(1, 0, 0); glVertex3f(W/2.0, W+100, -102);
        glTexCoord3i(1, 1, 0); glVertex3f(W/2.0, -W+100, -102);
    glEnd();

    selecionarImagem(texid_city, image_city);
    glBegin(GL_QUADS);
        glTexCoord3i(0, 1, 0); glVertex3f(-W/2.0,   -W+100, -101);
        glTexCoord3i(0, 0, 0); glVertex3f(-W/2.0,   W+100, -101);
        glTexCoord3i(1, 0, 0); glVertex3f(W/2.0, W+100, -101);
        glTexCoord3i(1, 1, 0); glVertex3f(W/2.0, -W+100, -101);
    glEnd();

    selecionarImagem(texid_grass, image_grass);
    glBegin(GL_QUADS);
        glTexCoord3i(0, 1, 0); glVertex3f(-W/2.0,   -W+100, -100);
        glTexCoord3i(0, 0, 0); glVertex3f(-W/2.0,   W+100, -100);
        glTexCoord3i(1, 0, 0); glVertex3f(W/2.0, W+100, -100);
        glTexCoord3i(1, 1, 0); glVertex3f(W/2.0, -W+100, -100);
    glEnd();
}

void fundo3d(){
    selecionarImagem(texid_clouds, image_clouds);
    glBegin(GL_QUADS);
        glTexCoord3i(0, 1, 0); glVertex3f(4900, -2080, -2140);
        glTexCoord3i(0, 0, 0); glVertex3f(4900, 3480, -2140);
        glTexCoord3i(1, 0, 0); glVertex3f(4900, 3480, 2140);
        glTexCoord3i(1, 1, 0); glVertex3f(4900, -2080, 2140);
    glEnd();
    
    selecionarImagem(texid_city, image_city);
    glBegin(GL_QUADS);
        glTexCoord3i(0, 1, 0); glVertex3f(4400, -1980, -2040);
        glTexCoord3i(0, 0, 0); glVertex3f(4400, 3380, -2040);
        glTexCoord3i(1, 0, 0); glVertex3f(4400, 3380, 2040);
        glTexCoord3i(1, 1, 0); glVertex3f(4400, -1980, 2040);
    glEnd();
    
    selecionarImagem(texid_grass, image_grass);
    glBegin(GL_QUADS);
        glTexCoord3i(0, 1, 0); glVertex3f(4000, -1780, -1840);
        glTexCoord3i(0, 0, 0); glVertex3f(4000, 3180, -1840);
        glTexCoord3i(1, 0, 0); glVertex3f(4000, 3180, 1840);
        glTexCoord3i(1, 1, 0); glVertex3f(4000, -1780, 1840);
    glEnd();
}

void gameOver(){
    status ^= 0x6;
    if(pontos > melhor){
        status ^= 0x8;
        melhor = pontos;
        salvarDados();
    }
}

void novoJogo(){
    setAlturaPassaro(-85);
    pontos = 0;
    status &= 0x01;
}

void logicaInicio(){
    // inicio
}

void logicaJogo(){

    end = clock();
    tempo = (end - start)*100.0/CLOCKS_PER_SEC;
    start = clock();

    taxa += tempo;

    int x;

    //printf("s: %f\n", s);
    proximoCano();
    
    if(taxa > 0.01){
        // Fisica
        atualizarFisica();

        // Canos
        atualizarCanos();

        taxa = 0;
    }

    // Colisões

    // Chão
    if(colisaoChao())
        gameOver();

    // Teto
    colisaoTeto();

    // Cano
    if(colisaoCano(getDistanciaCano(), getAlturaCano()))
        gameOver();
}

void interface(){

    // Salva o estado
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-W/2.0, W/2.0, -H/2.0, H/2.0, -80.0f, 200);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    if(!((status&0x02)>>1)){
        // Selecionar textura de gameover ou de inico
        if(!(status&0x04))selecionarImagem(texid_message, image_message);
        else selecionarImagem(texid_gameover, image_gameover);
        glBegin(GL_QUADS);
            glTexCoord3i(0, 1, 0); glVertex3f(-150,  -240, 76);
            glTexCoord3i(0, 0, 0); glVertex3f(-150,  240, 76);
            glTexCoord3i(1, 0, 0); glVertex3f(150, 240, 76);
            glTexCoord3i(1, 1, 0); glVertex3f(150, -240, 76);
        glEnd();
        // Se for gameover mostrar as informaçẽos 
        if(status&0x4){
            glPushMatrix();
                glTranslatef(90.0f, -35.0f, 77);
                printaNumero(melhor);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(90.0f, 10.0f, 77);
                printaNumero(pontos);
            glPopMatrix();

            if(status&0x8){
                selecionarImagem(texid_novo, image_novo);
                glBegin(GL_QUADS);
                    glTexCoord3i(0, 1, 0); glVertex3f(32,  -25, 77);
                    glTexCoord3i(0, 0, 0); glVertex3f(32,  7, 77);
                    glTexCoord3i(1, 0, 0); glVertex3f(64, 7, 77);
                    glTexCoord3i(1, 1, 0); glVertex3f(64, -25, 77);
                glEnd();
            }

            if(pontos >= GOLD)
                selecionarImagem(texid_ouro, image_ouro);
            else if(pontos >= SILVER)
                selecionarImagem(texid_prata, image_prata);
            else if(pontos >= BRONZE)
                selecionarImagem(texid_bronze, image_bronze);

            if(pontos >= BRONZE){
                glBegin(GL_QUADS);
                    glTexCoord3i(0, 1, 0); glVertex3f(-106,  -42, 78);
                    glTexCoord3i(0, 0, 0); glVertex3f(-106,  27, 78);
                    glTexCoord3i(1, 0, 0); glVertex3f(-38, 27, 78);
                    glTexCoord3i(1, 1, 0); glVertex3f(-38, -42, 78);
                glEnd();
            }
        }
    }else{
        glPushMatrix();
            glTranslatef(220.0f, 300.0f, 75);
            printaNumero(pontos);
        glPopMatrix();
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
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
        gluLookAt(0, getAlturaPassaro(), 0, 30, getAlturaPassaro(), 0, 0, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    }else{
        glOrtho(-W/2.0, W/2.0, -H/2.0, H/2.0, -80.0f, 200);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 0 , 30, 0, 0, 0, 0, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    }

    glColor3ub(255, 255, 255);

    switch((status&0x06)>>1){
        case 0:
            // Inicio
            logicaInicio();
            break;
        case 1:
            // Jogo
            logicaJogo();
            break;
        case 2:
            // Scoreboard
            break;
    }

    // Planos de fundo (um pra visão "2d" e outro pra primeira pessoa)
    if(status&0x1)
        fundo3d();
    else
        fundo2d();

    selecionarImagem(txd_default, img_default);

    glPushMatrix();
        glTranslatef(0, getAlturaPassaro(), 0);
        glPushMatrix();
            // Rotação
            glRotatef(getVelocidadePassaro()*90.0/104.0, 0, 0, 1);

            glutSolidCube(50);
        glPopMatrix();
        glTranslatef(0, -getAlturaPassaro(), 0);
    glPopMatrix();

    // Canos (somente se estiver no jogo)
    if(status&0x06){
        int x;
        glColor3ub(116, 191, 46);
        for(x = 0; x < MAXIMO_CANOS; x++){
            glPushMatrix();
                glTranslatef(canos[x][0], 0, 0);

                glPushMatrix();
                    glTranslatef(0, canos[x][1]+(ESPACO_CANO/2), 0);
                    glRotatef(90.0, -1, 0, 0);
                    gluCylinder(quadratic, RAIO_CANO - 5.0f, RAIO_CANO - 5.0f, 500.0, 32, 32);
                    gluCylinder(quadratic, RAIO_CANO, RAIO_CANO, 30.0, 32, 32);
                glPopMatrix();

                glPushMatrix();
                    glTranslatef(0, canos[x][1]-(ESPACO_CANO/2), 0);
                    glRotatef(90.0, 1, 0, 0);
                    gluCylinder(quadratic, RAIO_CANO - 5.0f, RAIO_CANO - 5.0f, 500.0, 32, 32);
                    gluCylinder(quadratic, RAIO_CANO, RAIO_CANO, 30.0, 32, 32);
                glPopMatrix();

            glPopMatrix();
        }
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

    glColor3ub(255, 255, 255);

    // HUD
    interface();

    glutSwapBuffers(); //Executa a Cena. SwapBuffers d?suporte para mais de um buffer, permitindo execu?o de anima?es sem cintila?es.
    glutPostRedisplay(); //Executa novamente
}

void TeclasEspeciais (int key, int x, int y){
	switch(key){
		case GLUT_KEY_RIGHT:
            status |= 0x1;
			break;
		case GLUT_KEY_UP:
            status |= 0x8;
			break;
		case GLUT_KEY_LEFT:
            status &= 0xFE;
			break;
		case GLUT_KEY_DOWN:
            status &= 0xfd;
            status |= 0x04;
			break;
	}
	glutPostRedisplay();
}

void TeclasNormais(unsigned char key, int x, int y){
    switch((status&0x06)>>1){
        case 0:
            // Inicio
            if(key == KEY_SPACE){
                iniciaCanos();
                pontos = 0;
                setVelocidade(VELOCIDADE_PULO);
                status ^= 0x02;
            }
            break;
        case 1:
            // Jogo
            if(key == KEY_SPACE)
                setVelocidade(VELOCIDADE_PULO);
            break;
        case 2:
            // Scoreboard
            if(key == KEY_ENTER)
                novoJogo();
            break;
    }
}


int main(int argc,char **argv){


    // Persistencia de dados
    abrirDados();

    glutInit(&argc, argv); // Initializes glut

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(W, H);
    glutCreateWindow("Flappy Bird");
    glutInitWindowPosition(100, 100);
    glutDisplayFunc(Display);

    quadratic = gluNewQuadric();

    srand(time(NULL));
    
    // Abrindo background
    /* Initialization of DevIL */
    ilInit();

    abrirImagem(&txd_default, &img_default, "img/default.png");
    abrirImagem(&texid_clouds, &image_clouds, "img/bg/clouds.png");
    abrirImagem(&texid_city, &image_city, "img/bg/city.png");
    abrirImagem(&texid_grass, &image_grass, "img/bg/grass.png");
    abrirImagem(&texid_message, &image_message, "img/menu/message.png");
    abrirImagem(&texid_gameover, &image_gameover, "img/menu/gameover.png");
    abrirImagem(&texid_bronze, &image_bronze, "img/menu/bronze.png");
    abrirImagem(&texid_prata, &image_prata, "img/menu/prata.png");
    abrirImagem(&texid_ouro, &image_ouro, "img/menu/ouro.png");
    abrirImagem(&texid_novo, &image_novo, "img/menu/novo.png");

    int x;
    char path[18] = "img/numeros/0.png";
    for(x = 0; x < 10; x++){
        path[12] = x+48;
        abrirImagem(texid_numeros+x, image_numeros+x, path);
    }

    glutSpecialFunc(TeclasEspeciais);
    glutKeyboardFunc(TeclasNormais);
    glutMainLoop();



    fclose(savedata);
    
    return 0; 
}
