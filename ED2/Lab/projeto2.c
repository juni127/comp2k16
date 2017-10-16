#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct CLIENTE{
    int conta, cpf;
    char nome[100];
    float limite, saldo;
}cliente;

typedef struct HASHING{
    int cpf, linha, profundidade_local;
}hashing;

#define TYPE hashing
#include "../ed.h"
#undef TYPE

#define TYPE cliente
#include "../ed.h"
#undef TYPE

list_hashing * diretorio[16];
int profundidade_global = 2; //profundidade_local = 4;

//Converte de decimal para binario
int dec_bin(int dec){
    if(dec/2 == 0)return dec%2;
    return dec%2 + 10 * dec_bin(dec/2);
}

//Inserir hashing
void inserir_hash(int cpf, int linha){
    //Descobre o index utilizando os n bits menos significativos
    int addr = cpf%(int)pow(2, profundidade_global);
    //Cria nova estrutura para armazenar os dados
    hashing * data = (hashing*)malloc(sizeof(hashing));
    data->cpf = cpf;
    data->linha = linha;
    //Se o balde não está cheio
    if(size_hashing(diretorio[addr]) < 4){
        //Adicionamos os dados a ele
        data->profundidade_local = (diretorio[addr] != NULL)?diretorio[addr]->DATA->profundidade_local:profundidade_global;
        diretorio[addr] = add_end_hashing(diretorio[addr], data);
    }
    //Se o balde estiver cheio e a profundidade global já suportar outro
    else if(diretorio[addr]->DATA->profundidade_local < profundidade_global){
        int x, y;
        list_hashing * aux;
        //Pega os elementos do baldo com overflow para serem realocados
        aux = diretorio[addr];

        //"Esvasia os baldes"
        for(x = addr&0x3; x < 16; x+=4){
            if(aux == diretorio[x])
                diretorio[x] = NULL;
        }

        //"Re-enche os baldes vasios"
        do{
            aux->DATA->profundidade_local++;
            int new_addr = aux->DATA->cpf%(int)pow(2, aux->DATA->profundidade_local);
            diretorio[new_addr] = add_end_hashing(diretorio[new_addr], aux->DATA);
            aux = purge_node_hashing(aux);
        }while(aux != NULL);

        for(x = pow(2, diretorio[addr]->DATA->profundidade_local), y = 0; profundidade_global > diretorio[addr]->DATA->profundidade_local && x < pow(2, diretorio[addr]->DATA->profundidade_local+1); x++, y++)
            diretorio[x] = diretorio[y];

        //Iserir novo elemento
        diretorio[addr] = add_end_hashing(diretorio[addr], data);
    }else{
        //Aumentar profundidade global
        profundidade_global++;
        list_hashing * aux;
        int x, y;
        //Pega os elementos do baldo com overflow para serem inseridos de novo
        aux = diretorio[addr];
        //"Esvasia o balde"
        diretorio[addr] = NULL;
        //Apontamos os ponteiros para os baldes como se a profundidade global ainda fosse a mesma
        for(x = pow(2, profundidade_global-1), y = 0; x < pow(2, profundidade_global); x++, y++)
            diretorio[x] = diretorio[y];

        //Re-inserir dados do balde com overflow
        for(;aux != NULL; aux = purge_node_hashing(aux))
            inserir_hash(aux->DATA->cpf, aux->DATA->linha);

        addr = cpf%(int)pow(2, profundidade_global);
        diretorio[addr] = add_end_hashing(diretorio[addr], data);
    }
}

void deletar_hash(int cpf){
    int addr = cpf%(int)pow(2, profundidade_global);
    list_hashing * aux = diretorio[addr];
    for( ;aux != NULL && aux->DATA->cpf != cpf; aux = aux->NEXT);
    if(aux != NULL)
        diretorio[addr] = purge_node_hashing(aux);
}

void salvar(char * nome_arquivo, list_cliente * clientes){
    int line;
    FILE * alvo = fopen(nome_arquivo, "w");
    for(line = 0, clientes; clientes != NULL; clientes = clientes->NEXT, line++){
        if(clientes->DATA != NULL)
            fprintf(alvo, "%i %s# %i %f %f\n", clientes->DATA->conta, clientes->DATA->nome, clientes->DATA->cpf, clientes->DATA->limite, clientes->DATA->saldo);
        else
            fprintf(alvo, "%i\n", -1);
    }
    fclose(alvo);
}

list_cliente * abrir(char * nome_arquivo){
    FILE * alvo = fopen(nome_arquivo, "r");
    if(alvo == NULL)
        alvo = fopen(nome_arquivo, "w+");
    int linha = 0;
    list_cliente * retorno = NULL;
    cliente entrada;
    while(!feof(alvo)){
        for( ; fscanf(alvo, "%d ", &entrada.conta) > 0; linha++){
            if(entrada.conta < 0){
                retorno = add_end_cliente(retorno, NULL);
                fscanf(alvo, "\n");
            }else{
                //Ler resto
                fscanf(alvo, "%[^#]# %i %f %f\n", entrada.nome, &entrada.cpf, &entrada.limite, &entrada.saldo);
                //Popular hashing
                inserir_hash(entrada.cpf, linha);
                //Criar novo cliente
                cliente * aux = (cliente*)malloc(sizeof(cliente));
                //Popular cliente
                aux->conta = entrada.conta;
                strcpy(aux->nome, entrada.nome);
                aux->cpf = entrada.cpf;
                aux->limite = entrada.limite;
                aux->saldo = entrada.saldo;
                //Adicionar cliente na lista
                retorno = add_end_cliente(retorno, aux);
            }
        }
    }
    return retorno;
}

int main(){
    list_cliente * clientes = abrir("entrada.txt");

    char e;

    do{
        int x;
        system("cls");
        for(x = 0; x < pow(2, profundidade_global); x++){
            list_hashing * aux = diretorio[x];
            printf("\n---| BALDE %8i |---| DIR ADDRESS 0x%p |---| PROFUNDIDADE %i |----------\n", dec_bin(x), diretorio[x], (diretorio[x] != NULL)?diretorio[x]->DATA->profundidade_local:0);
            for ( ;aux != NULL; aux = aux->NEXT) {
                printf("CPF: %i LINHA: %i\n", aux->DATA->cpf, aux->DATA->linha);
            }
        }
        fflush(stdin);
        printf("Entre: ");
        scanf("%c", &e);
        fflush(stdin);
        switch (e) {
            case 'i':
                printf("Nome:");
                cliente * entrada = (cliente*)malloc(sizeof(cliente));
                fflush(stdin);
                scanf("%[^\n]", entrada->nome);
                printf("Conta:");
                scanf("%i", &entrada->conta);
                printf("CPF:");
                scanf("%i", &entrada->cpf);
                printf("Limmite:");
                scanf("%f", &entrada->limite);
                printf("Saldo:");
                scanf("%f", &entrada->saldo);
                clientes = add_end_cliente(clientes, entrada);
                inserir_hash(entrada->cpf, size_hashing(clientes));
                break;
            case 'd':
                printf("CPF:");
                int cpf;
                scanf("%i", &cpf);
                deletar_hash(cpf);
                list_cliente * aux = clientes;
                for( ; aux != NULL && aux->DATA->cpf != cpf; aux = aux->NEXT);
                if(aux != NULL)
                    aux->DATA = NULL;
                break;
        }
    }while(e != 's');

    salvar("entrada.txt", clientes);

    return 0;
}
