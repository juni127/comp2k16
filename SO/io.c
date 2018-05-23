#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#include"sys.h"

//TMP Usar a função do grupo 4 (eu acho)
void mem_cpy(unsigned int f, unsigned int s, unsigned int t){
    //address (from), size, address (to)
    for(s--; s >= 0; s--)
        *(MEM+s+t) = *(MEM+s+f);
}

//Endereço do dispositivo, quantidade de dados (em bytes), endereço da memoria
void p_input(unsigned int f, unsigned int s, unsigned int t){
    int i;
    for(i = t; i < s + t; i++){
        while(*(ES_STATUS_REG + f));//Teria que verificar se o dispositivo está pronto pra receber o byte
        mem_cpy(f, 1, i);//Copia os dados do buffer para o dispositivo
        *(ES_STATUS_REG + f) = 1;//Confirma ao dispositivo que o byte foi recebido
    }
}

//Endereço da memoria, quantidade de dados (em bytes), endereço do dispositivo
void p_output(unsigned int f, unsigned int s, unsigned int t){
    int i;
    mem_cpy((MEM + f), s, (MEM + BUFFER_START));//Copia os dados do espaço do usuario pro buffer para serem escritos no dispositivo
    for(i = 0; i < s; i++){
        while(*(ES_STATUS_REG + t));//Teria que verificar se o dispositivo está pronto pra receber o byte
        mem_cpy(BUFFER_START + i, 1, t);//Copia os dados do buffer para o dispositivo
        *(ES_STATUS_REG + f) = 1;//Confirma ao dispositivo que o byte foi recebido
    }
}

int main(){
    int x;
    for(x = 2048; x < 2058; x++){
        MEM[x] = x;
        printf("[%i] = %i\n", x, MEM[x]);
    }
    MEM[1014] = 0xFF;
    printf("%i\n", MEM[1024]);
    programmed_io(0, 1014, 10, 1024);
    printf("%i\n", MEM[1033]);

    return 0;
}