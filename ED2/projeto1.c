
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

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
#include "ed.h"
#undef TYPE

typedef struct proc{
    //SHORT 16bits -> 65.536 proc no maximo
    unsigned short id;
    //Instruções
    unsigned char text[256];
}proc;

#define TYPE proc
#include "ed.h"
#undef TYPE

struct LAST_DATA{
    unsigned short id;
    unsigned char PS;
    unsigned char total;
    int T;
}dados;

#define MAX_READY_SIZE 5
#define MAX_QUANTUM_SIZE 20
#define PROBA_INTERRUPTION 25
#define GENERATION_FACTOR 1000

unsigned short idDisponiveis[65536];

unsigned short getId(){
    unsigned short result = idDisponiveis[0], c, i;
    for(c = 0; idDisponiveis[c] != 65535; c++){
        idDisponiveis[c] = idDisponiveis[c + 1];
    }
    return result;
}


unsigned char getSizeOfInstruction (proc *processo){
	unsigned char res;
	for(res = 0; processo->text[res] != 0xFF; res++);
	return res;
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

int main(int argc, char *args[]){
    //Variavel para todos os usos
    int x;

    //Preparar a "aleatoriade"
    srand(time(NULL));

    //Gerar ids validos
    for(x = 0; x < 65536; x++)
        idDisponiveis[x] = x;

    //Filas
    queue_proc jobs, ready, device;
    jobs = queue_init_proc();
    ready = queue_init_proc();
    device = queue_init_proc();
    list_pcb *PCBT = NULL, *PCB = NULL;


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
        if(rand()%60000 < 60000-(queue_size_proc(jobs) * GENERATION_FACTOR)){
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
            }while(novo->text[pointer-1] != 0xFF && pointer < 255);
            if(pointer == 255)
                novo->text[pointer] = 0xFF;
            //Atribuir id valido
            novo->id = getId();
            printf("%i\n", novo->id);
            //Adicionar na fila de trabalhos
            queue_add_proc(&jobs, novo);
        }

        //A fila de programas prontos não está cheia
        if(queue_size_proc(ready) < MAX_READY_SIZE){
            //Verificar se alguma interrupção terminou
            if(queue_size_proc(device) > 0 && rand()%100 < PROBA_INTERRUPTION)
                queue_add_proc(&ready, queue_remove_proc(&device)->DATA);
            //Se não, adicionar trabalho da fila de espera a fila de programas prontos
            else{
                queue_add_proc(&ready, queue_remove_proc(&jobs)->DATA);
                //Gerar PCB para tabela
                PCBT = add_end_pcb(PCBT, gerarPCB(queue_get_last_proc(ready)));
            }
        }

        char quantum = 0;
        if(queue_size_proc(ready) > 0){
            //RODAR
            queue_add_proc(&ready, queue_remove_proc(&ready)->DATA);

            //Pegar pcb do processo atual
            PCB = getPCB(PCBT, queue_get_first_proc(ready)->id);
            //Executar as instruções do processo a menos que, o seu quantum tenha se esgotado ou suas instruções tenham acabado
            while (quantum < 20 && queue_get_first_proc(ready)->text[PCB->DATA->PC] != 0xFF){
                //Aumenta a posição do contador de programa
                PCB->DATA->PC++;
                //Aumenta o tempo de execução do programa
                PCB->DATA->T++;
                //Aumenta o quantum do programa
                quantum++;
                //Interrupção
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

            //Verificar se o processo foi encerrado (Caso ele não tenha ido pra fila de dispositivos)
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
                //Eliminar processo
                queue_purge_proc(&ready);
            }

        }
        
        int zyzz;

		do{

	        //Printar os dados da rodada
	        system("cls");
			puts("DADOS:");
	        printf("JOBS = ");
	        printarFilas(jobs);
	        printf("READY = ");
	        printarFilas(ready);
	        printf("DEVICES = ");
	        printarFilas(device);
	        
	        //1 proc 2 jobs 3  backspace = 8 a = 97 enter = 13
	        printf("Aperte:\n d para os dados do ultimo processo \nj para fila de Jobs \nr para a fila de Prontos \ns para fila de dispositivos \nQualquer outra tecla para continuar\n");
	        int i;
	        switch(getch()){
	        	case 100:
	        		printf("Dados do processo: \nId: %i\nStatus do processo: %i\nTempo total passado: %i\nTempo total: %i\nTempo restate: %i\nQuantum da ultima rodada: %i\n", dados.id,dados.PS,dados.T,dados.total,dados.total-dados.T,quantum);
					printf("Aperte backspace par voltar ou qualquer tecla para continuar\n");
					zyzz = getch();
	        		break;
	        	case 106:
	        		printf("\nLista de processor na fila JOBS:\n");
	        		printf("---------------------------------------------------------");
	        		for(i = 0; i < queue_size_proc(jobs);i++){
	        			printf("\nId do processo: %i\nTamanho do processo: %i\n", get_proc(jobs.FIRST, i)->DATA->id, getSizeOfInstruction(get_proc(jobs.FIRST, i)->DATA));
	        			printf("---------------------------------------------------------\n");	
					}
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
		}while(zyzz == 8);
    }
}
