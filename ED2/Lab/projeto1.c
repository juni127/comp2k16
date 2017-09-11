
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

//Constantes
#define MAX_PROCESS_SIZE 128
#define MAX_READY_SIZE 5
#define MAX_QUANTUM_SIZE 20
#define PROBA_INTERRUPTION 25
#define GENERATION_FACTOR 5


//Declaração da estrutura PCB e inclusão das suas funções
typedef struct PCB{
    unsigned short id;
    //Estado do processo 8bits
    unsigned char PS;
    //Contador de programa
    unsigned char PC;
    //Quantum maximo
    unsigned char QM;
    //Tempo utilizado de CPU
    int T;
}pcb;

#define TYPE pcb
#include "../ed.h"
#undef TYPE

//Declaração da estrutura Proccess e inclusão das suas funções
typedef struct proc{
    //SHORT 16bits -> 65.536 proc no maximo
    unsigned short id;
    //Instruções
    unsigned char text[MAX_PROCESS_SIZE];
}proc;

#define TYPE proc
#include "../ed.h"
#undef TYPE

typedef struct mem{
    proc *DATA;
    unsigned short POS;
    unsigned short SIZE;
}mem;

#define TYPE mem
#include "../ed.h"
#undef TYPE

struct LAST_DATA{
    unsigned short id;
    unsigned char PS;
    unsigned char total;
    int T;
}dados;

//Miscellaneous
void printarFilas(queue_proc queue){
    list_proc *aux = queue.FIRST;
    printf("[");
    if(aux == NULL){
        puts("]");
        return;
    }
    for( ; aux->NEXT != NULL; aux = aux->NEXT)
        printf("%i, ", aux->DATA->id);
    if(aux != NULL)printf("%i]\n", aux->DATA->id);
}

void printMem(list_mem * mmem){
    printf("MEMORIA = [");
    for( ;mmem->NEXT != NULL; mmem = mmem->NEXT){
        printf("(%i - %i), ", mmem->DATA->POS,mmem->DATA->SIZE);
    }
    printf("(%i - %i)]\n", mmem->DATA->POS,mmem->DATA->SIZE);
}

unsigned char getSizeOfInstruction (proc *processo){
	unsigned char res;
	for(res = 0; processo->text[res] != 0xFF; res++);
	return res;
}

//Id related
unsigned short idDisponiveis[65536];

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
            a = c;
    for(i = c; i > a; i--)
        idDisponiveis[i] = idDisponiveis[i - 1];
    idDisponiveis[a] = id;
}


//PCB related
list_pcb *getPCB(list_pcb *PCB, int id){
    for(; PCB->DATA->id != id && PCB->NEXT != NULL; PCB = PCB->NEXT);
    if(PCB->NEXT == NULL && PCB->DATA->id != id)
        return NULL;
    return PCB;
}

int getPCBIndex(list_pcb *PCB, int id){
    int x;
    for(x = 0; PCB->DATA->id != id && PCB->NEXT != NULL; PCB = PCB->NEXT, x++);
    if(PCB->NEXT == NULL && PCB->DATA->id != id)
        return -1;
    return x;
}

int getPCBIndexByPCB(list_pcb *PCB, pcb *target){
    int x;
    for(x = 0; PCB->DATA != target && PCB->NEXT != NULL; PCB = PCB->NEXT, x++);
    if(PCB->NEXT == NULL && PCB->DATA != target)
        return -1;
    return x;
}

pcb *gerarPCB(proc *processo){
    pcb *novo = (pcb*)malloc(sizeof(pcb));
    novo->id = processo->id;
    novo->PC = 0;
    novo->PS = 2;
    novo->T = 0;
    int x;
    for(x = 0; processo->text[x] != 0xFF; x++);
    novo->QM = x;
    return novo;
}

//Estados: 1 inicio, 2 pronto, 3 em execução, 4 bloqueado, 5 encerrado

//Memory related
list_mem *iniciaMemoria(){
    list_mem *memoria = (list_mem*)malloc(sizeof(list_mem));
    memoria->DATA = (mem*)malloc(sizeof(mem));
    memoria->NEXT = NULL;
    memoria->PREV = NULL;
    get_first_data_mem(memoria)->DATA = NULL;
    get_first_data_mem(memoria)->POS = 0;
    get_first_data_mem(memoria)->SIZE = 512;
    return memoria;
}

void liberarMemoria(list_mem *memoria, proc * processo){
    for( ; memoria != NULL && memoria->DATA->DATA != processo; memoria = memoria->NEXT);
    if(memoria == NULL)
        return;
    //Limpar esse chunk
    memoria->DATA->DATA = NULL;
    //Juntar os chunks
    if(memoria->NEXT != NULL && memoria->NEXT->DATA->DATA == NULL){
        memoria->DATA->SIZE += memoria->NEXT->DATA->SIZE;
        list_mem *aux = memoria->NEXT;
        memoria->NEXT = memoria->NEXT->NEXT;
        free(aux);
        if(memoria->NEXT != NULL)
            memoria->NEXT->PREV = memoria;
    }
    if(memoria->PREV != NULL && memoria->PREV->DATA->DATA == NULL){
        memoria = memoria->PREV;
        memoria->DATA->SIZE += memoria->NEXT->DATA->SIZE;
        list_mem *aux = memoria->NEXT;
        memoria->NEXT = memoria->NEXT->NEXT;
        free(aux);
        if(memoria->NEXT != NULL)
            memoria->NEXT->PREV = memoria;
    }
}

unsigned char alocaProcesso(list_mem *memoria, proc * processo){
    unsigned char result = 0, size = getSizeOfInstruction(processo);
    for( ;memoria != NULL; memoria = memoria->NEXT){
        if(size <= memoria->DATA->SIZE && memoria->DATA->DATA == NULL){
            result = 1;
            memoria->DATA->DATA = processo;
            if(size != memoria->DATA->SIZE){
                list_mem *new_chunk = (list_mem*)malloc(sizeof(list_mem));
                new_chunk->DATA = (mem*)malloc(sizeof(mem));
                new_chunk->DATA->DATA = NULL;
                new_chunk->DATA->POS = memoria->DATA->POS + size;
                new_chunk->DATA->SIZE = memoria->DATA->SIZE - size;
                new_chunk->NEXT = memoria->NEXT;
                new_chunk->PREV = memoria;
                memoria->DATA->SIZE = size;
                memoria->NEXT = new_chunk;
            }
            break;
        }
    }
    return result;
}

int main(int argc, char *args[]){
    //Variavel para todos os usos
    int x;

    //Preparar a "aleatoriade"
    srand(time(NULL));

    //Gerar ids validos
    for(x = 0; x < 65536; x++)
        idDisponiveis[x] = x;

    //Filas
    queue_proc ready, device;
    ready = queue_init_proc();
    device = queue_init_proc();
    //Listas
    list_pcb *PCBT = NULL, *PCB = NULL;
    list_mem *MMEM = iniciaMemoria();

    //Loop principal
    for (;;) {
        /*
            Flags
            0x01 -> Interrupção
            0x02 -> Encerrado
        */

        char f = 0;
        //ALEATORIEDADES
        //Adicionar um processo
        if(rand()%1000 < 1000 - ((size_mem(MMEM)-1)*GENERATION_FACTOR)){
            proc *novo = (proc*)malloc(sizeof(proc));
            //Criar instruções
            unsigned char pointer = 0;
            do{
                unsigned char teste = rand()%256;
                if(teste < 250)
                    novo->text[pointer] = teste;
                else if(teste < 253)
                    novo->text[pointer] = 0xFD;
                else
                    novo->text[pointer] = 0xFF;
                pointer++;
            }while(novo->text[pointer-1] != 0xFF && pointer < MAX_PROCESS_SIZE - 1);
            if(pointer == MAX_PROCESS_SIZE - 1)
                novo->text[pointer] = 0xFF;
            //Atribuir id valido
            novo->id = getId();
            if(alocaProcesso(MMEM, novo)){
                queue_add_proc(&ready, novo);
                PCBT = add_end_pcb(PCBT, gerarPCB(queue_get_last_proc(ready)));
                printf("Processo %i alocado na memoria com sucesso.\n", novo->id);
            }else{
                printf("Erro ao alocar o processo %i! Provavelmente nao ha espaco na memoria.\n", novo->id);
                returnId(novo->id);
                free(novo);
            }
        }

        if(queue_size_proc(device) > 0 && rand()%100 < PROBA_INTERRUPTION){
            queue_add_proc(&ready, queue_remove_proc(&device)->DATA);
            printf("Processo %i movido da fila de Dispositivos para a fila Prontos.\n", queue_get_last_proc(ready)->id);
        }

        char quantum = 0;
        if(queue_size_proc(ready) > 0){
            //RODAR
            queue_add_proc(&ready, queue_remove_proc(&ready)->DATA);

            //Pegar pcb do processo atual0
            PCB = getPCB(PCBT, queue_get_first_proc(ready)->id);
            //Executar as instru��es do processo a menos que, o seu quantum tenha se esgotado ou suas instru��es tenham acabado
            while (quantum < 20 && queue_get_first_proc(ready)->text[PCB->DATA->PC] != 0xFF){
                //Aumenta a posi��o do contador de programa
                PCB->DATA->PC++;
                //Aumenta o tempo de execu��o do programa
                PCB->DATA->T++;
                //Aumenta o quantum do programa
                quantum++;
                //Interrup��o
                if(queue_get_first_proc(ready)->text[PCB->DATA->PC] == 0xFD){
                    //Setar dados
                    dados.id = queue_get_first_proc(ready)->id;
                    dados.PS = 4;
                    dados.T = PCB->DATA->T;
                    dados.total = getSizeOfInstruction(queue_get_first_proc(ready));
                    //Setar flag
                    f |= 0x01;
                    //Adicionar o processo atual a fila de dispositivos
                    queue_add_proc(&device, queue_remove_proc(&ready)->DATA);
                    printf("Processo %i movido da fila de Prontos para a fila de Dispositivos.\n", queue_get_last_proc(device)->id);
                    break;
                }
            }

            if(!(f & 0x01)){
                //Setar dados
                dados.id = queue_get_first_proc(ready)->id;
                dados.PS = PCB->DATA->PS;
                dados.T = PCB->DATA->T;
                dados.total = getSizeOfInstruction(queue_get_first_proc(ready));
            }

            //Verificar se o processo foi encerrado (Caso ele n�o tenha ido pra fila de dispositivos)
            if(
                !(f & 0x01) &&
                (queue_get_first_proc(ready)->text[PCB->DATA->PC] == 0xFF ||
                    queue_get_first_proc(ready)->text[PCB->DATA->PC + 1] == 0xFF)
            ){
                //Setar flag
                f |= 0x02;
                //Setar status de encerrado
                dados.PS = 5;
                //Purge pcb
                purge_pcb(PCBT, getPCB(PCBT, queue_get_first_proc(ready)->id));
                //Retornar o id
                returnId(queue_get_first_proc(ready)->id);
                //Liberar memoria
                liberarMemoria(MMEM, queue_get_first_proc(ready));
                //Eliminar processo
                queue_purge_proc(&ready);
            }

        }

        int zyzz;

		do{

	        //Printar os dados da rodada
            printMem(MMEM);
            if(f & 0x01)
                printf("Processo %i interompido.\n", dados.id);
            else if(f & 0x02)
                printf("Processo %i finalizado.\n", dados.id);
            else
                printf("Processo %i movido para o final da fila.\n", dados.id);
			puts("DADOS:");
	        printf("READY = ");
	        printarFilas(ready);
	        printf("DEVICES = ");
	        printarFilas(device);

	        //1 proc 2 jobs 3  backspace = 8 a = 97 enter = 13
	        printf("Aperte:\n d para os dados do ultimo processo \nr para a fila de Prontos \ns para fila de dispositivos \nQualquer outra tecla para continuar\n");
	        int i;
	        switch(getch()){
	        	case 100:
	        		printf("Dados do processo: \nId: %i\nStatus do processo: %i\nTempo total passado: %i\nTempo total: %i\nTempo restate: %i\nQuantum da ultima rodada: %i\n", dados.id,dados.PS,dados.T,dados.total,dados.total-dados.T,quantum);
					printf("Aperte backspace par voltar ou qualquer tecla para continuar\n");
					zyzz = getch();
	        		break;
	        	case 114:
	        		printf("\nLista de processor na fila READY:\n");
	        		puts("---------------------------------------------------------");
	        		for(i = 0; i < queue_size_proc(ready);i++){
	        			printf("Id do processo: %i\nTamanho do processo: %i\n", get_proc(ready.FIRST, i)->DATA->id, getSizeOfInstruction(get_proc(ready.FIRST, i)->DATA));
	        			PCB = getPCB(PCBT, get_proc(ready.FIRST, i)->DATA->id);
						printf("Estado do programa: %i \nQuantum utilizado: %i\n", PCB->DATA->PS, PCB->DATA->T);
	        			printf("---------------------------------------------------------\n");
					}
					printf("Aperte backspace par voltar ou qualquer tecla para continuar\n");
					zyzz = getch();
	        		break;
	        	case 115:
	        		printf("\nLista de processor na fila DEVICE:\n");
	        		puts("---------------------------------------------------------");
	        		for(i = 0; i < queue_size_proc(device);i++){
	        			printf("Id do processo: %i\nTamanho do processo: %i\n", get_proc(device.FIRST, i)->DATA->id, getSizeOfInstruction(get_proc(device.FIRST, i)->DATA));
	        			PCB = getPCB(PCBT, get_proc(device.FIRST, i)->DATA->id);
						printf("Estado do programa: %i \nQuantum utilizado: %i\n", PCB->DATA->PS, PCB->DATA->T);
	        			printf("---------------------------------------------------------\n");
					}
					printf("Aperte backspace par voltar ou qualquer tecla para continuar\n");
					zyzz = getch();
	        		break;
        		default:
        			zyzz = 0;
        			break;
			}
            system("cls");
		}while(zyzz == 8);
    }
}
