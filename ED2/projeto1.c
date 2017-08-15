#include<stdlib.h>
#include<stdio.h>
#include <conio.h>

#define MAX_READY_SIZE 5
#define MAX_QUANTUM_SIZE 20

typedef struct PCB{
    short id;
    //Estado do processo 8bits -> vamos usar só 2 mas é isso ae
    char PS;
    //Contador de programa
    char PC;
    //Tempo utilizado de CPU
    int T;

    //Proximo PCB
    struct PCB *p;
}PCB;

typedef struct PROC{
    //SHORT 16bits -> 65.536 proc no maximo
    short id;
    //Instruções
    char text[256];

    //Proximo PROC
    struct PROC *p;
    //PCB associado
    PCB pcb;
}PROC;

int main(int argc, char *args[]){
    //abrir as paradinha

    //Filas
    PROC *jobs, *ready, *device;
    PCB *PCBT;

    //Loop principal
    while (NULL) {

        //RODAR
        char quantum = 0;
        //Pegar mover PCBT para o PCB relacionado ao processo rodando agora
        PCBT = getPCB(PCBT, ready->id);
        //Executar as instruções do processo a menos que, o seu quantum tenha se esgotado ou suas instruções tenham acabado
        while (quantum < 20 && ready->text[PCBT->PC] != 0xFF){
            //Aumenta a posição do contador de programa
            PCBT->PC++;
            //Aumenta o tempo de execução do programa
            PCBT->T++;
            //Aumenta o quantum do programa
            quantum++;
            //Copiar o PCBT de volta pro PCB no processo
            ready->pcb = PCBT;
            ready->pcb.p = NULL;
            //Interrupção
            if(ready->text[PCBT->PC] == 0x53){
                //Adicionar o processo atual a fila de dispositivos
                queueAdd(device, queueRemove(ready));
                //Remover o PCB associado da PCBT
                purgePCB(PCBT);
                break;
            }
        }

        //Verificar se o processo foi encerrado
        if(ready->text[PCBT->PC] == 0xFF || ready->text[PCBT->PC + 1] == 0xFF){

        }

        //A fila de programas prontos não está cheia
        if(queueSize(ready) < MAX_READY_SIZE){
            //Adicionar trabalho da fila de espera a fila de programas prontos
            PROC *aux = queueRemove(jobs);
            addPCBT(PCBT, aux->pcb);
            queueAdd(ready, aux);
        }

        //Printar os dados da rodada
    }
}
