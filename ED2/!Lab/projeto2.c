#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

typedef struct REG{
    int pos, matricula, page_id;
}reg;

#define TYPE reg
#include "../ed.h"
#undef TYPE

typedef struct ALUNO{
    char nome[100], sexo;
    int idade, matricula;
}aluno;

typedef struct PAGE{
    aluno alunos[3];
    int alunos_count, id;
}pagina;

int HASH_SIZE, last_page_id = 0, topo_pagina = 0, buffer_f[4][2]; // 0 -> pin_count // 1 -> dirty
list_reg ** hashing;
pagina ** paginas_incompletas, * paginas_completas[333], * buffer[4];

void carregarBuffer(int page_id){
    int x, y;
    pagina * aux;
    int aux2[2];
    for(x = 0; x < 4; x++){
        if(buffer[x] != NULL && buffer[x]->id == page_id){
            aux = buffer[x];
            aux2[0] = buffer_f[x][0];
            aux2[1] = buffer_f[x][1];
            buffer_f[0][0]--;
            x |= 8;
            break;
        }
    }
    if(x&8){
        x = x&3;
        for(y = x; y > 0; y--){
            buffer[y] = buffer[y - 1];
            buffer_f[y][0] = buffer_f[y - 1][0];
            buffer_f[y][1] = buffer_f[y - 1][1];
        }
        buffer[0] = aux;
        buffer_f[0][0] = aux2[0] + 1;
        buffer_f[0][1] = aux2[1];
    }else{
        buffer_f[0][0]--;
        for(x = 3; x > 0; x--){
            buffer[x] = buffer[x - 1];
            buffer_f[x][0] = buffer_f[x - 1][0];
            buffer_f[x][1] = buffer_f[x - 1][1];
        }
        for(x = 0; x < topo_pagina; x++){
            if(paginas_completas[x]->id == page_id){
                buffer[0] = paginas_completas[x];
                buffer_f[0][0] = 1;
                buffer_f[0][1] = 0;
                x |= 512;
                break;
            }
        }
        if(!(x&512)){
            for(x = 0; x < HASH_SIZE; x++){
                if(paginas_incompletas[x]->id == page_id){
                    buffer[0] = paginas_incompletas[x];
                    buffer_f[0][0] = 1;
                    buffer_f[0][1] = 0;
                    break;
                }
            }
        }
    }
}

void atualizarPaginas(){
    int x;
    for(x = 0; x < HASH_SIZE; x++){
        if(paginas_incompletas[x]->alunos_count >= 3){
            paginas_completas[topo_pagina] = paginas_incompletas[x];
            topo_pagina++;
            paginas_incompletas[x] = (pagina*)malloc(sizeof(pagina));
            paginas_incompletas[x]->id = last_page_id;
            last_page_id++;
            paginas_incompletas[x]->alunos_count = 0;
        }
    }
}

void adicionarAluno(aluno alvo){
    int addr = alvo.matricula%HASH_SIZE;
    int page_id = paginas_incompletas[addr]->id;
    carregarBuffer(page_id);
    int alunoc = buffer[0]->alunos_count;
    strcpy(buffer[0]->alunos[alunoc].nome, alvo.nome);
    buffer[0]->alunos[alunoc].sexo = alvo.sexo;
    buffer[0]->alunos[alunoc].idade = alvo.idade;
    buffer[0]->alunos[alunoc].matricula = alvo.matricula;
    alunoc++;
    reg * registro = (reg*)malloc(sizeof(reg));
    registro->pos = alunoc-1;
    registro->matricula = alvo.matricula;
    registro->page_id = page_id;
    hashing[addr] = add_end_reg(hashing[addr], registro);
    atualizarPaginas();
}

aluno buscarAluno(int matricula){
    int addr = matricula%HASH_SIZE;
    aluno retorno;
    retorno.matricula = -1;
    list_reg * lista_reg = hashing[addr];
    for( ; lista_reg != NULL && lista_reg->DATA->matricula != matricula; lista_reg = lista_reg->NEXT);
    if(lista_reg == NULL)
        return retorno;
    carregarBuffer(lista_reg->DATA->page_id);
    return buffer[0]->alunos[lista_reg->DATA->pos];
}

void deletarAluno(int matricula){
    int addr = matricula%HASH_SIZE, x;
    list_reg * lista_reg = hashing[addr];
    for( ; lista_reg != NULL && lista_reg->DATA->matricula != matricula; lista_reg = lista_reg->NEXT);
    if(lista_reg == NULL)
    return;
    carregarBuffer(lista_reg->DATA->page_id);
    for(x = lista_reg->DATA->pos; x < buffer[0]->alunos_count - 1; x++){
        buffer[0]->alunos[x] = buffer[0]->alunos[x + 1];
    }
    buffer[0]->alunos_count--;
    hashing[addr] = purge_node_reg(lista_reg);
}


//TODO -> Trabalhani nisso aqui
void editarAluno(int matricula, aluno alvo){
    int addr = matricula%HASH_SIZE, x;
    list_reg * lista_reg = hashing[addr];
    for( ; lista_reg != NULL && lista_reg->DATA->matricula != matricula; lista_reg = lista_reg->NEXT);
    if(lista_reg == NULL)
        return;
    carregarBuffer(lista_reg->DATA->page_id);
    if(!strcmp("", aluno.nome))
        strcpy(buffer[0]->alunos[lista_reg->DATA->pos].nome, aluno.nome);
}

int main(){
    printf("Digite o tamanho da hash:");
    scanf("%i", &HASH_SIZE);

    hashing = (list_reg**)malloc(sizeof(list_reg*)*HASH_SIZE);
    paginas_incompletas = (pagina**)malloc(sizeof(pagina*)*HASH_SIZE);
    int x;
    for(x = 0; x < 4; x++)buffer[x] = NULL;
    for(x = 0; x < HASH_SIZE; x++){
        paginas_incompletas[x] = (pagina*)malloc(sizeof(pagina));
        paginas_incompletas[x]->alunos_count = 0;
        paginas_incompletas[x]->id = last_page_id;
        last_page_id++;
        hashing[x] = NULL;
    }

    char e = 'n';
    aluno malcom;

    do{
        system("cls");
        printf("Menuzera\nn para adicionar\nb para buscar\nd para deletar\n\n\n\n");
        fflush(stdin);
        e = getch();
        switch (e) {
            case 'n':
                fflush(stdin);
                aluno novo;
                printf("Digite o nome do aluno:");
                scanf("%[^\n]", novo.nome);
                printf("Digite o sexo do aluno:");
                fflush(stdin);
                scanf("%c", &novo.sexo);
                fflush(stdin);
                printf("Digite a idade do aluno:");
                scanf("%i", &novo.idade);
                printf("Digite o numero da matricula:");
                scanf("%i", &novo.matricula);
                adicionarAluno(novo);
                break;
            case 'b':
                printf("Digite o numero da matricula do aluno:");
                scanf("%i", &x);
                malcom = buscarAluno(x);
                if(malcom.matricula >= 0)
                    printf("Nome: %s\nSexo: %c\nIdade: %i\nNumero da matricula: %i\n", malcom.nome, malcom.sexo, malcom.idade, malcom.matricula);
                else
                    puts("Aluno não encontrado!");
                break;
            case 'd':
                printf("Digite o numero da matricula do aluno:");
                scanf("%i", &x);
                deletarAluno(x);
                break;
            case 'e':
                printf("Digite o numero da matricula do aluno:");
                scanf("%i", &x);
                fflush(stdin);
                aluno novo1;
                printf("Digite o novo nome do aluno:");
                scanf("%[^\n]", novo1.nome);
                printf("Digite o novo sexo do aluno:");
                fflush(stdin);
                scanf("%c", &novo1.sexo);
                fflush(stdin);
                printf("Digite a nova idade do aluno:");
                scanf("%i", &novo1.idade);
                editarAluno(x, novo1);
                break;
        }
        puts("\n\n\n\nQualquer tecla para continuar.");
        fflush(stdin);
        getch();

    }while(e != 's');

    return 0;
}
