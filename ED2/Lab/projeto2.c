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
    int cpf, linha;
}hashing;

#define TYPE hashing
#include "../ed.h"
#undef TYPE

#define TYPE cliente
#include "../ed.h"
#undef TYPE

list_hashing * diretorio[16];
int profundidade_global = 2, profundidade_local = 4;

int dec_bin(int dec){
    if(dec/2 == 0)return dec%2;
    return dec%2 + 10 * dec_bin(dec/2);
}

//Inserir hashing
void inserir_hash(int cpf, int linha){
    int addr = cpf%(int)pow(2, profundidade_global);
    hashing * data = (hashing*)malloc(sizeof(hashing));
    data->cpf = cpf;
    data->linha = linha;
    if(size_hashing(diretorio[addr]) < profundidade_local)
        diretorio[addr] = add_end_hashing(diretorio[addr], data);
    else if(diretorio[addr] == diretorio[cpf%(int)pow(2, profundidade_global-1)] && profundidade_global > 2)
        diretorio[addr] = add_end_hashing(NULL, data);
    else{
        //Aumentar profundidade global
        profundidade_global++;
        int x, y;
        for(x = pow(2, profundidade_global-1), y = 0; x < pow(2, profundidade_global); x++, y++)
            diretorio[x] = diretorio[y];
        addr = cpf%(int)pow(2, profundidade_global);
        diretorio[addr] = add_end_hashing(NULL, data);
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
            fprintf(alvo, "%i\n", line);
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
        for( ; fscanf(alvo, "%i %[^#]# %i %f %f\n", &entrada.conta, entrada.nome, &entrada.cpf, &entrada.limite, &entrada.saldo) > 1; linha++){
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
        if(!feof(alvo)){
            fscanf(alvo, "%i\n");
            linha++;
        }
    }
    return retorno;
}

int main(){

    list_cliente * clientes = abrir("entrada.txt");

    char e;

    do{
        int x;
        for(x = 0; x < pow(2, profundidade_global); x++){
            list_hashing * aux = diretorio[x];
            printf("---| BALDE %8i |----------------\n", dec_bin(x));
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
                    clientes = purge_node_cliente(aux);
                break;
        }
    }while(e != 's');

    salvar("entrada.txt", clientes);

    return 0;
}
