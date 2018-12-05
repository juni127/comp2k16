

#define MAX_ANIMACAO 32
#define MAX_CAMINHO 32

typedef struct VERTEX{
    float x, y;
}vertex;

vertex caminho[MAX_ANIMACAO][MAX_CAMINHO], pos[MAX_ANIMACAO];
float v_movimento[MAX_ANIMACAO], v_animacao[MAX_ANIMACAO], tempo[MAX_ANIMACAO], tempo_passado;
char flags[MAX_ANIMACAO], tamanho[MAX_ANIMACAO], passo[MAX_ANIMACAO];
int imagem[MAX_ANIMACAO];
clock_t start, end;

void inicia_animacao(){
	start = end = 0;
	int x;
	for(x = 0; x < MAX_ANIMACAO; x++)
		flags[x] &= 0x7F;
}

void setar_animacao(vertex * c, int size, float v, char f, char i, int img){
	int x;
	v_movimento[i] = v;
	flags[i] = f;
	tamanho[i] = size;
	tempo[i] = 0;
	passo[i] = 1;
	pos[i] = c[0];
	imagem[i] = img;
	for(x = 0; x < size; x++){
		caminho[i][x] = c[x];
	}
}

void parar_animacao(char i){
	flags[i] &= 0x7F;
}

void tocar_animacao(char i){
	flags[i] |= 0x80;
}

void animacoes(){
	int x;

	end = clock();
	tempo_passado = (end - start)*1000/CLOCKS_PER_SEC;

	for(x = 0; x < MAX_ANIMACAO; x++){
		if(flags[x]&0x80){
			tempo[x] += tempo_passado;
			if(tempo[x] > 1000.0/v_movimento[x]){
				tempo[x] = 0;
				if(pos[x].x == caminho[x][passo[x]].x && pos[x].y == caminho[x][passo[x]].y)
					if(passo[x] < tamanho[x]-1)
						passo[x]++;
					else{
						pos[x] = caminho[x][0];
						passo[x] = 0;
					}
				if(pos[x].x != caminho[x][passo[x]].x)
					pos[x].x = (pos[x].x < caminho[x][passo[x]].x)?pos[x].x+1:pos[x].x-1;
				if(pos[x].y != caminho[x][passo[x]].y)
					pos[x].y = (pos[x].y < caminho[x][passo[x]].y)?pos[x].y+1:pos[x].y-1;
			}
			escolher_imagem(imagem[x]);
    		desenhar_imagem(pos[x].x, pos[x].y);
    		//printf("%d: %f %f | %f %f\n", x, pos[x].x, pos[x].y, caminho[x][passo[x]].x, caminho[x][passo[x]].y);
		}
	}

	start = clock();
}