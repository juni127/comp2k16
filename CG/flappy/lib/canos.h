int pc = 0;
float canos[MAXIMO_CANOS][2];

void iniciaCanos(){
    int x;
    pc = 0;
    for(x = 0; x < MAXIMO_CANOS; x++){
        canos[x][0] = x*DISTANCIA+500;
        canos[x][1] = gerarAltura();
    }
}

void atualizarCanos(){
	int x;
	for(x = 0; x < MAXIMO_CANOS; x++){
        canos[x][0] += VELOCIDADE;
        if(canos[x][0] < -300){
            canos[x][0] = (DISTANCIA * MAXIMO_CANOS) - 300;
            canos[x][1] = gerarAltura();
        }
    }
}

void proximoCano(){
	if(canos[pc][0] < 0){
        atualizarPontos();
        pc = (pc == MAXIMO_CANOS-1)?0:pc+1;
    }
}

float gerarAltura(){
	return rand()%200 - 50;
}

float getAlturaCano(){
	return canos[pc][1];
}

float getDistanciaCano(){
	return canos[pc][0];
}