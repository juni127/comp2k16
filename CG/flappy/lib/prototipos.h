//Prot?ipos das Fun?es
void Display();
void logicaJogo();
void keyboard (unsigned char key, int x, int y);
void TeclasEspeciais (int key, int x, int y);

void abrirImagem(GLuint * texid, ILuint * image, char * path);
void selecionarImagem(GLuint texid, ILuint image);

void atualizarPontos();

// canos.h
void iniciaCanos();
void atualizarCanos();
void proximoCano();
float gerarAltura();
float getAlturaCano();
float getDistanciaCano();

// fisica.h
void atualizarFisica();
char colisaoCano(float pos, float altura);
char colisaoChao();
void colisaoTeto();
float getAlturaPassaro();
float getVelocidadePassaro();
void setAlturaPassaro(float altura);
void setVelocidade(float velocidade);
float max(float a, float b);
float min(float a, float b);
