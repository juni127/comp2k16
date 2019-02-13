// Fisica
float s = -85, v = 0, a = -50, t = 0.1, raio = 30;

void atualizarFisica(){
    s = s + v*t + a*t*t/2.0;
    v = v + a*t;
}

char colisaoCano(float pos, float altura){
	/* 
		Acha o ponto pertencente aos retangulos (os canos) mais proximo do circulo (o passaro) e se a distancia do ponto ao centro
		do circulo for menor que o raio do mesmo temos uma colisão.
	*/
	float DeltaX = 0 - max(pos - RAIO_CANO, min(0, pos + RAIO_CANO));
	float DeltaHY = s - max(altura + (ESPACO_CANO/2), min(s, altura + (ESPACO_CANO/2) + 500));
	float DeltaLY = s - max(altura - (ESPACO_CANO/2) - 500, min(s, altura - (ESPACO_CANO/2)));
	return ((DeltaX * DeltaX + DeltaHY * DeltaHY) < (raio * raio)) || ((DeltaX * DeltaX + DeltaLY * DeltaLY) < (raio * raio));
}

char colisaoChao(){
	return s - raio <= -200;
}

void colisaoTeto(){
	if(s > 340 - raio){
        v = 0;
        s = 340 - raio;
    }
}

float getAlturaPassaro(){
	return s;
}

float getVelocidadePassaro(){
	return v;
}

void setAlturaPassaro(float altura){
	s = altura;
}

void setVelocidade(float velocidade){
	v = velocidade;
}

float max(float a, float b){
	if(a > b) return a;
	else return b;
}

float min(float a, float b){
	if(a < b) return a;
	else return b;
}