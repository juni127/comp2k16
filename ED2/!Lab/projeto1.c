#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

#define HASH_SIZE 2

typedef struct ALUNO{
    char nome[100], sexo;
    int idade, matricula;
}aluno;

#define TYPE aluno
#include "../ed.h"
#undef TYPE

aluno *buscarAluno(list_aluno *alunos, int matricula){
    aluno *r = NULL;
    for( ; alunos != NULL && alunos->DATA->matricula != matricula; alunos = alunos->NEXT);
    if(alunos != NULL)
        r = alunos->DATA;
    return r;
}

void iniciaHash(list_aluno **hash){
    int x;
    for(x = 0; x < HASH_SIZE; x++)
        hash[x] = NULL;
}

void adicionaHash(aluno *data, list_aluno **hash){
    int index = data->matricula%HASH_SIZE;
    hash[index] = add_begin_aluno(hash[index], data);
}

aluno *retornarHash(list_aluno **hash, int matricula){
    int index = matricula%HASH_SIZE;
    return buscarAluno(hash[index], matricula);
}

void removerHash(list_aluno **hash, int matricula){
    int index = matricula%HASH_SIZE;
    list_aluno * alunos = hash[index];
    if(alunos == NULL)
        return;
    for( ; alunos != NULL && alunos->DATA->matricula != matricula; alunos = alunos->NEXT);
    if(alunos != NULL)
        hash[index] = purge_node_aluno(alunos);
}

void printarTodos(list_aluno **hash){
    int x;
    list_aluno *aux;
    for(x = 0; x < HASH_SIZE; x++)
        if(hash[x] != NULL){
            aux = hash[x];
            for( ; aux != NULL; aux = aux->NEXT)
                printf("Nome: %s\nSexo: %c\nIdade: %i\nNumero da matricula: %i\n\n\n", aux->DATA->nome, aux->DATA->sexo, aux->DATA->idade, aux->DATA->matricula);
        }
}

//Numero de matricula related
unsigned short numerosDisponiveis[1001];

void iniciaNumeros(){
    int x;
    for(x = 0; x < 1001; x++)
        numerosDisponiveis[x] = x;
}

unsigned short getNumero(){
    unsigned short result = numerosDisponiveis[0], c, i;
    for(c = 0; numerosDisponiveis[c] != 1000; c++){
        numerosDisponiveis[c] = numerosDisponiveis[c + 1];
    }
    return result;
}

void returnNumero(unsigned short id){
    unsigned short a = 0, c, i;
    for(c = 0; numerosDisponiveis[c] != 1000; c++)
        if(numerosDisponiveis[c] < id)
            a = c;
    for(i = c; i > a; i--)
        numerosDisponiveis[i] = numerosDisponiveis[i - 1];
    numerosDisponiveis[a] = id;
}

int main(){
    char e;
    list_aluno *hash[HASH_SIZE];

    iniciaHash(hash);
    iniciaNumeros();

    do{
        int nm;
        puts("Aperte n para adicionar um novo aluno.\nAperte b para buscar um aluno.\nAperte l para listar os alunos.\nAperte r para remover um aluno.\nAperte s para sair.");
        e = getch();
        system("cls");
        switch (e) {
            case 'n':;
                //n
                aluno *novo = (aluno*)malloc(sizeof(aluno));
                printf("Nome: ");
                fflush(stdin);
                scanf("%[^\n]", novo->nome);
                fflush(stdin);
                printf("Sexo (m ou f): ");
                scanf("%c", &novo->sexo);
                fflush(stdin);
                printf("Idade: ");
                scanf("%i", &novo->idade);
                int nMatricula = getNumero();
                printf("Numero da matricula: %i\n\n\n", nMatricula);
                novo->matricula = nMatricula;
                adicionaHash(novo, hash);
                break;
            case 'b':
                //b
                printf("Numero da matricula: ");
                scanf("%i", &nm);
                aluno *buscado = retornarHash(hash, nm);
                printf("Nome: %s\nSexo: %c\nIdade: %i\nNumero da matricula: %i\n\n\n", buscado->nome, buscado->sexo, buscado->idade, buscado->matricula);
                break;
            case 'l':
                //l
                printarTodos(hash);
                break;
            case 'r':
                printf("Numero da matricula: ");
                scanf("%i", &nm);
                returnNumero(nm);
                removerHash(hash, nm);
                break;
        }
        puts("Qualquer tecla para continuar.");
        getch();
        system("cls");
    }while(e != 115);

    return 0;
}
