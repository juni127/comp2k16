#include<stdlib.h>

unsigned short idDisponiveis[65536];

//1 inicio, 2 pronto, 3 em execução, 4 bloqueado, 5 encerrado

typedef struct PCB{
    unsigned short id;
    //Estado do processo 8bits
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

PROC *queueRemove(PROC *target){
    //Não existe o que remover
    if(target == NULL)
        return target;
    //Cria variavel auxiliar
    PROC *aux = target->p;
    //Desligar nó da fila
    target->p = NULL;
    return aux;
}

PROC *queueAdd(PROC *queue, PROC *target){
    //Queue vazio
    if(queue == NULL)
        return target;
    //Criar variavel auxiliar
    PROC *aux = queue;
    //Ir até o ultimo elemento da fila
    while (aux->p != NULL)
        aux = aux->p;
    //Adicionar o novo elemento
    target->p = aux->p;
    aux->p = target;
    return queue;
}

PROC *queuePurge(PROC *target){
    if(target == NULL)
        return NULL;
    if(target == target->p){
        free(target);
        return NULL;
    }
    PROC *aux = target->p;
    free(target);
    return aux;
}

int queueSize(PROC *queue){
    //Fila vazia
    if(queue == NULL)
        return 0;
    int result;
    for (result = 1; queue->p != NULL; result++)
        queue = queue->p;
    return result;
}

void queuePrintID(PROC *queue){
    printf("[");
    for ( ; queue->p != NULL; queue = queue->p)
        printf("%d, ", queue->id);
    printf("%d]\n", queue->id);
}

PCB *getPCB(PCB *pcb, unsigned short id){
    if(pcb == NULL)
        return NULL;
    if(pcb->id == id)
        return pcb;
    while(pcb != NULL){
        if(pcb->id == id)
            return pcb;
        pcb = pcb->p;
    }
    return pcb;
}

PCB *purgePCB(PCB *PCBT, PCB *pcb){
    if(PCBT == pcb){
        pcb = PCBT->p;
        free(PCBT);
        return pcb;
    }
    PCB *aux = pcb;
    while(aux->p != PCBT)
        aux = aux->p;
    aux->p = PCBT->p;
    free(PCBT);
    return pcb;
}

PCB *addPCB(PCB *pcb, PCB PCBT){
    PCB *novo = (PCB*)malloc(sizeof(PCB)), *aux = pcb;
    *novo = PCBT;
    //Isso eh igual a *novo = PCBT?
    novo->id = PCBT.id;
    novo->PS = PCBT.PS;
    novo->PC = PCBT.PC;
    novo->T = PCBT.T;
    novo->p = NULL;
    if(pcb == NULL)
        return novo;
    while(aux->p != NULL)
        aux = aux->p;
    aux->p = novo;
    return pcb;
}

unsigned short getId(){
    unsigned short result = idDisponiveis[0], c, i;
    for(c = 0; idDisponiveis[c] != 65535; c++){
        idDisponiveis[c] = idDisponiveis[c + 1];
    }
    return result;
}

void returnId(unsigned short id){
    unsigned short a = 0, c, i;
    for(c = 0; idDisponiveis[c] != 65535; c++)
        if(idDisponiveis[c] < id)
            a++;
    a++;
    for(i = c; i > a; i--)
        idDisponiveis[i] = idDisponiveis[i - 1];
    idDisponiveis[a] = id;
}
