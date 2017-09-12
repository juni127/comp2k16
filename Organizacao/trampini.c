#include<stdio.h>
#include<stdlib.h>

#define MEM_SIZE 100

unsigned short mem[MEM_SIZE];

void runInstruction(unsigned short instruction){
    switch ((instruction >> 7) & 0x07) {
        case 0x01:
            //Lê o valor contido no endereço x e o salva no MBR
            break;
        case 0x02:
            //Salva o valor contido no MBR no endereço x
            break;
        case 0x03:
            //Lê o valor contido no endereço x e soma ao valor contido no MBR. O valor da soma é armazenado no MBR
            break;
        case 0x04:
            //Lê o valor contido no endereço x e subtrai do valor contido no MBR (MBR - ‘x’) . O valor da subtração é armazenado no MBR
            break;
        case 0x05:
            //Move o Contador de Programa para a linha de endereço x
            break;
        case 0x06:
            //Escreve o valor numérico y no MBR
            break;
        case 0x07:
            //Indica que o programa chegou ao fim
            break;
    }
}

int main(){

    system("pause");

    return 0;
}
