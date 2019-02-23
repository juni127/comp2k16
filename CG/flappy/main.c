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
GLuint texid_bird; ILuint image_bird; // Passarela marconi 
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

void desenhaPassaro(){

    glPushMatrix();
        selecionarImagem(texid_bird, image_bird);
        mostrarImagem(-28, 28, -28, 28, 0, 0);
    glPopMatrix();
    selecionarImagem(txd_default, img_default);
    /*
    glPushMatrix();
        glTranslatef(-12.5, 0, 0);
        glutSolidCube(35);
        glColor3ub(255, 0, 0);
    glPushMatrix();
    glPopMatrix();
        glTranslatef(12.5, 0, 0);
        glutSolidCube(35);
        glColor3ub(255, 255, 255);
    glPopMatrix();
    */
}

void atualizarPontos(){
    pontos++;
}

void printaNumero(int numero){
    int x;
    for(x = 0; numero > 0 || x == 0; numero /= 10, x++){
        selecionarImagem(texid_numeros[numero%10], image_numeros[numero%10]);
        mostrarImagem(0-(x*18), 16-(x*18), 0, 16, 0, 0);
    }
}

void fundo2d(){
    selecionarImagem(texid_clouds, image_clouds);
    mostrarImagem(-W/2.0, W/2.0, -W+100, W+100, -102, -102);

    selecionarImagem(texid_city, image_city);
    mostrarImagem(-W/2.0, W/2.0, -W+100, W+100, -101, -101);

    selecionarImagem(texid_grass, image_grass);
    mostrarImagem(-W/2.0, W/2.0, -W+100, W+100, -101, -100);
}

void fundo3d(){
    selecionarImagem(texid_clouds, image_clouds);
    mostrarImagem(4900, 4900, -2080, 3480, -2140, 2140);
    
    selecionarImagem(texid_city, image_city);
    mostrarImagem(4400, 4400, -1980, 3380, -2040, 2040);
    
    selecionarImagem(texid_grass, image_grass);
    mostrarImagem(4000, 4000, -1780, 3180, -1840, 1840);
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
        mostrarImagem(-150, 150, -240, 240, 76, 76);

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
                mostrarImagem(32, 64, -25, 7, 77, 77);
            }

            if(pontos >= GOLD)
                selecionarImagem(texid_ouro, image_ouro);
            else if(pontos >= SILVER)
                selecionarImagem(texid_prata, image_prata);
            else if(pontos >= BRONZE)
                selecionarImagem(texid_bronze, image_bronze);

            if(pontos >= BRONZE)
                mostrarImagem(-106, -38, -42, 27, 78, 78);
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

    // Textura padrão branca para os objetos ficarem opacos
    selecionarImagem(txd_default, img_default);

    glPushMatrix();
        glTranslatef(0, getAlturaPassaro(), 0);
        glPushMatrix();
            // Rotação
            glRotatef(getVelocidadePassaro()*90.0/150.0, 0, 0, 1);

            desenhaPassaro();

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
	//glutPostRedisplay();
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
            if(key == KEY_SPACE){
                setVelocidade(VELOCIDADE_PULO);
            }
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

    // Abrindo imagens
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
    abrirImagem(&texid_bird, &image_bird, "img/bird.png");

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
