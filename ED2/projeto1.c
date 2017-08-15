#include<stdlib.h>
#include<stdio.h>
#include <conio.h>

#define MAX_READY_SIZE 5
#define MAX_QUANTUM_SIZE 20

typedef struct PCB{
    unsigned short id;
    //Estado do processo 8bits -> vamos usar só 2 mas é isso ae
    unsigned char PS;
    //Contador de programa
    unsigned char PC;
    //Tempo utilizado de CPU
    int T;

    //Proximo PCB
    struct PCB *p;
}PCB;

typedef struct PROC{
    //SHORT 16bits -> 65.536 proc no maximo
    unsigned short id;
    //Instruções
    unsigned char text[256];

    //Proximo PROC
    struct PROC *p;
    //PCB associado
    PCB pcb;
}PROC;

PCB *getPCB(PCB *PCBT, int id){
	while(PCBT->id != id)
		PCBT = PCBT->p;
	return PCBT;
}

void queueAdd(PROC *queue, PROC *target){
	//Salvar id do primeiro elemento
	int id = queue->id;
	//Iterar pela fila para adicionar no final
	while(queue->p != NULL){
		//Verificar se o primeiro elemento � o pr�ximo (caso de fila circular)
		if(queue->p->id == id)
			break;
		queue = queue->p;
	}
	//Anular o proximo do alvo (ou aponta-lo para o come�o no caso de fila circular)
	target->p = queue->p;
	//Apontar o fim da fila para o alvo
	queue->p = target;
}

PROC *queueRemove(PROC *target){
	//Salvar o primeiro elemento
	PROC *aux = target;
	//Checar por fila circular
	while(target->p != NULL){
		if(target->p == aux){
			target->p = aux->p;
			break;
		}
		target = target->p;
	}
	//Remover o primeiro da fila
	target = aux->p;
	aux->p = NULL;
	return target;
}

PCB *purgePCB(PCB *target){
	
}

int main(int argc, char *args[]){
    //FLAGS 0x01 : Processo removido / 0x02 : Processo interrompido
	unsigned char FLAGS = 0;

    //Filas
    PROC *jobs, *ready, *device;
	PCB *pcb, *PCBT;

    //Loop principal
    while (NULL) {

        //RODAR
        char quantum = 0;
        //Pegar mover PCBT para o PCB relacionado ao processo rodando agora
        PCBT = getPCB(pcb, ready->id);
        //Executar as instruções do processo a menos que, o seu quantum tenha se esgotado ou suas instruções tenham acabado
        while (quantum < 20 && ready->text[PCBT->PC] != 0xFF){
            //Aumenta a posição do contador de programa
            PCBT->PC++;
            //Aumenta o tempo de execução do programa
            PCBT->T++;
            //Aumenta o quantum do programa
            quantum++;
            //Copiar o PCBT de volta pro PCB no processo
            ready->pcb = *PCBT;
            ready->pcb.p = NULL;
            //Interrupção
            if(ready->text[PCBT->PC] == 0x53){
                //Adicionar o processo atual a fila de dispositivos
                PROC *aux = ready;
                ready = queueRemove(ready);
                queueAdd(device, aux);
                //Remover o PCB associado da PCBT
                PCBT = purgePCB(PCBT);
                //Setar flag
                FLAGS |= 0x02;
                break;
            }
        }

        //Verificar se o processo foi encerrado (somente se ele n�o foi interrompido)
        if(!(FLAGS & 0x02) && (ready->text[PCBT->PC] == 0xFF || ready->text[PCBT->PC + 1] == 0xFF)){
			queuePurge(ready);
			FLAGS |= 0x01;
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
