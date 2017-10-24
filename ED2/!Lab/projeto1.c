#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

#define HASH_SIZE 333
#define true 1
#define false 0

typedef struct ALUNO{
    char nome[100], sexo;
    int idade, matricula;
}aluno;

#define TYPE aluno
#include "../ed.h"
#undef TYPE

list_aluno * buffer[4];
int buffer_flags[4][3]; //0 -> pin_count 1 -> dirty 2 -> id da pagina

char * genFileName(int x){
    int y;
    char *file_name = (char*)malloc(sizeof(char)*8);
    file_name[0] = '0';
    file_name[1] = '0';
    file_name[2] = '0';
    for(y = 2; x > 0; y--, x/=10)
        file_name[y] = (char)((x%10)+48);
    y = 3;
    file_name[y] = '.';
    y++;
    file_name[y] = 't';
    y++;
    file_name[y] = 'x';
    y++;
    file_name[y] = 't';
    y++;
    file_name[y] = '\0';
    y++;
    return file_name;
}

list_aluno * carregarDoArquivo(FILE * arq){
    list_aluno * retorno = NULL;
    aluno * data = (aluno*)malloc(sizeof(aluno));
    while (fscanf(arq, "%[^#]# %c %i %i\n", data->nome, &data->sexo, &data->idade, &data->matricula) == 4) {
        retorno = add_end_aluno(retorno, data);
        removeNumero(data->matricula);
        data = (aluno*)malloc(sizeof(aluno));
    }
    free(data);
    return retorno;
}

void salvarProArquivo(list_aluno * alunos, int pin, int addr){
    char * file_name = genFileName(addr);
    FILE * alvo = fopen(file_name, "w+");
    pin--;
    fprintf(alvo, "%i\n", pin);
    for(; alunos != NULL; alunos = alunos->NEXT)
        fprintf(alvo, "%s# %c %i %i\n", alunos->DATA->nome, alunos->DATA->sexo, alunos->DATA->idade, alunos->DATA->matricula);
    fclose(alvo);
}

void carregarBuffer(int matricula){
    int addr = matricula%HASH_SIZE, x, y;
    for(x = 0; x < 4; x++)
        if(buffer_flags[x][2] == addr)
            x |= 8;
    x--;
    //Encontrado
    if(x & 8){
        x = x&3;
        list_aluno * aux = buffer[x];
        int aux2[3];
        aux2[0] = buffer_flags[x][0];
        aux2[1] = buffer_flags[x][1];
        aux2[2] = buffer_flags[x][2];
        for(y = x; y > 0; y--){
            buffer[y] = buffer[y-1];
            buffer_flags[y][0] = buffer_flags[y - 1][0];
            buffer_flags[y][1] = buffer_flags[y - 1][1];
            buffer_flags[y][2] = buffer_flags[y - 1][2];
        }
        buffer[0] = aux;
        buffer_flags[0][0] = aux2[0];
        buffer_flags[0][1] = aux2[1];
        buffer_flags[0][2] = aux2[2];
    }
    //Não Encontrado
    else{
        char * file_name = genFileName(addr);
        if(buffer_flags[3][1]){
            salvarProArquivo(buffer[3], buffer_flags[3][0]-1, buffer_flags[3][2]);
            for( ; buffer[3] != NULL; buffer[3] = purge_node_aluno(buffer[3]));
        }
        for(x = 3; x > 0; x--){
            buffer[x] = buffer[x - 1];
            buffer_flags[x][0] = buffer_flags[x - 1][0];
            buffer_flags[x][1] = buffer_flags[x - 1][1];
            buffer_flags[x][2] = buffer_flags[x - 1][2];
        }
        buffer_flags[0][1] = false;
        buffer_flags[0][2] = addr;
        FILE * page = fopen(file_name,"r");
        if(page == NULL){
            page = fopen(file_name, "w");
            buffer_flags[0][0] = 1;
            fprintf(page, "1\n");
            fclose(page);
            buffer[0] = NULL;
        }else{
            fscanf(page, "%i\n", &y);
            buffer_flags[0][0] = y + 1;
            buffer[0] = carregarDoArquivo(page);
            fclose(page);
            salvarProArquivo(buffer[0], y+1, addr);
        }
    }
}

void adicionarAluno(aluno * data){
    carregarBuffer(data->matricula);
    buffer[0] = add_end_aluno(buffer[0], data);
    buffer_flags[0][1] = true;
}

aluno *buscarAluno(int matricula){
    carregarBuffer(matricula);
    if(buffer[0] == NULL)
        return NULL;
    list_aluno * aux;
    for(aux = buffer[0]; aux != NULL && aux->DATA->matricula != matricula; aux = aux->NEXT);
    if(aux == NULL)
        return NULL;
    return aux->DATA;
}

void printarTodos(){
    int x;
    for(x = 0; x < 333; x++){
        FILE * file = fopen(genFileName(x), "r");
        if(file != NULL){
            aluno data;
            fscanf(file, "%i\n");
            while (fscanf(file, "%[^#]# %c %i %i\n", data.nome, &data.sexo, &data.idade, &data.matricula) == 4)
                printf("Nome: %s\nSexo: %c\nIdade: %i\nNumero da matricula: %i\n\n\n", data.nome, data.sexo, data.idade, data.matricula);
        }
        fclose(file);
    }
}

void removerAluno(int matricula){
    carregarBuffer(matricula);
    if(buffer[0] == NULL)
        return;
    list_aluno * aux;
    for(aux = buffer[0]; aux != NULL && aux->DATA->matricula != matricula; aux = aux->NEXT);
    if(aux == NULL)
        return;
    free(aux->DATA);
    buffer[0] = purge_node_aluno(aux);
    buffer_flags[0][1] = true;
}


//--------              ----------              ----------              ----------              ----------              ----------

//Numero de matricula related
unsigned short numerosDisponiveis[1001];

void removeNumero(unsigned short id){
    int c, x;
    for(x = 0; numerosDisponiveis[x] != id && numerosDisponiveis[x] != 1000; x++);
    if(numerosDisponiveis[x] == 1000)return;
    for(c = x; numerosDisponiveis[c] != 1000; c++){
        numerosDisponiveis[c] = numerosDisponiveis[c + 1];
    }
}

void iniciaNumeros(){
    int x;
    for(x = 0; x < 1001; x++)
        numerosDisponiveis[x] = x;
    for(x = 0; x < 333; x++){
        FILE * file = fopen(genFileName(x), "r");
        if(file != NULL){
            aluno data;
            fscanf(file, "%i\n");
            while (fscanf(file, "%[^#]# %c %i %i\n", data.nome, &data.sexo, &data.idade, &data.matricula) == 4)
                removeNumero(data.matricula);
        }
        fclose(file);
    }
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
    int x;
    for(x = 0; x < 4; x++){
        buffer[x] = NULL;
        buffer_flags[x][1] = false;
        buffer_flags[x][2] = - 1;
    }
    char e;
    iniciaNumeros();

    do{
        int nm;
        puts("Aperte n para adicionar um novo aluno.\nAperte b para buscar um aluno.\nAperte l para listar os alunos.\nAperte r para remover um aluno.\nAperte e para editar um aluno.\nAperte g para gravar.\nAperte s para sair.");
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
                adicionarAluno(novo);
                break;
            case 'b':
                //b
                printf("Numero da matricula: ");
                scanf("%i", &nm);
                aluno * buscado = buscarAluno(nm);
                if(buscado != NULL)
                    printf("Nome: %s\nSexo: %c\nIdade: %i\nNumero da matricula: %i\n\n\n", buscado->nome, buscado->sexo, buscado->idade, buscado->matricula);
                else
                    puts("Aluno não encontrado.");
                break;
            case 'l':
                //l
                printf("----| Alunos cadastrados |--------------------------------\n");
                printarTodos();
                printf("----------------------------------------------------------\n");
                break;
            case 'r':
                printf("Numero da matricula: ");
                scanf("%i", &nm);
                returnNumero(nm);
                removerAluno(nm);
                break;
            case 'g':
                //Salvar todos
                for(nm = 0; nm < 4; nm++){
                    if(buffer_flags[nm][1])salvarProArquivo(buffer[nm], buffer_flags[nm][0], buffer_flags[nm][2]);
                }
                break;
            case 'e':
                //Edittar
                break;
        }
        puts("Qualquer tecla para continuar.");
        getch();
        system("cls");
    }while(e != 115);

    return 0;
}
