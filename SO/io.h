#include"sys.h"
#include"mem.h"

//Endereço do dispositivo, quantidade de dados (em bytes), endereço da memoria
void p_input(unsigned int f, unsigned int s, unsigned int t){
    int i;
    for(i = t; i < s + t; i++){
        while(*(ES_STATUS_REG + f));//Teria que verificar se o dispositivo está pronto pra receber o byte
	write(i, DEVICE[f]);//Copia os dados do dispositivo para a memoria
        *(ES_STATUS_REG + f) = 1;//Confirma ao dispositivo que o byte foi recebido
    }
}

//Endereço da memoria, quantidade de dados (em bytes), endereço do dispositivo
void p_output(unsigned int f, unsigned int s, unsigned int t){
    int i;
    mem_cpy(f, s, BUFFER_START);//Copia os dados do espaço do usuario pro buffer para serem escritos no dispositivo
    for(i = 0; i < s; i++){
        while(*(ES_STATUS_REG + t));//Teria que verificar se o dispositivo está pronto pra receber o byte
        mem_cpy(BUFFER_START + i, 1, t);//Copia os dados do buffer para o dispositivo
        *(ES_STATUS_REG + f) = 1;//Confirma ao dispositivo que o byte foi enviado
    }
}

//Brilha Pedren

//Endereço do dispositivo, quantidade de dados (em bytes), endereço da memoria
void i_input(unsigned int f, unsigned int s, unsigned int t){

}

//Endereço da memoria, quantidade de dados (em bytes), endereço do dispositivo
void i_output(unsigned int f, unsigned int s, unsigned int t){

}

//Brilha Mitonato
