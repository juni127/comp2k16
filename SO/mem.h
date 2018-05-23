#include"sys.h"

/*
	Checa se a pagina que contem o endereço addr está em um dos frames
	caso esteja: retorna o indice do frame que contem a pagina desejada
	caso não esteja: chama fifo(), mru(), lru() ou mfu() para pegar a
	pagina e retorna o indice do frame que contem a pagina desejada
*/
unsigned char get_page(unsigned int addr){

}

//Retorna o byte salvo no endereço addr 
unsigned char read(unsigned int addr){
	unsigned char r;

	return r;
}

//Salva o byte value no endereço addr
void write(unsigned int addr, unsigned char value){

}

//Copia s bytes de f a t
void mem_cpy(unsigned int f, unsigned int s, unsigned int t){
    //endereço f, tamanho, endereço t
	unsigned char i;
    do{
		s--;
		i = read(f + s);//Lê o byte s no espaço de memoria f + s e salva no "registrador" i
		write(t + s, i);//Escreve o byte em i no espaço de memoria t + s 
	}(s > 0);
}

//Algoritimos de substituição
void fifo(unsigned int addr){

}

void mru(unsigned int addr){

}

void lru(unsigned int addr){

}

void mfu(unsigned int addr){

}
