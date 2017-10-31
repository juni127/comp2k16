#include<stdio.h>
#include<stdlib.h>

typedef struct cliente{
    int codigo, idade;
    char nome[40], telefone[8], endereco[40], status;
}cliente;

char * genFileName(int x){
    int y;
    char *file_name = (char*)malloc(sizeof(char)*20);
    file_name[0] = 'd';
    file_name[1] = 'a';
    file_name[2] = 't';
    file_name[3] = 'a';
    file_name[4] = '/';
    for(y = 5; y < 15; y++)file_name[y] = '0';
    for(y = 14; x > 0; y--, x/=10)
        file_name[y] = (char)((x%10)+48);
    y = 15;
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

cliente getClienteData(int page_id){
    FILE * f = fopen(genFileName(page_id), "r");
    cliente c;
    if(f != NULL)fscanf(f, "%i\n%[^\n]\n%[^\n]\n%[^\n]\n%i\n%i", &c.codigo, c.nome, c.telefone, c.endereco, &c.status, &c.idade);
    else c.codigo = -1;
    fclose(f);
    return c;
}

void setClienteData(int page_id, void ** pointers, int num_keys){
    FILE * f = fopen(genFileName(page_id), "w");]
    void * pointer;
    int x;
    for(x = 0, pointer = pointers[x]; x < num_keys; x++, pointer = pointers[x])
        fprintf(f, "%i\n%s\n%s\n%s\n%i\n%i", pointer->codigo, pointer->nome, pointer->telefone, pointer->endereco, pointer->status, pointer->idade);
    fclose(f);
}

#include"../btree.h"

int main(){

    //remove("nomedoarquivo") <- para apagar arquivos

    system("mkdir data");
    system("cls");

    char instruction;
    int input, range2, input2;
	node * root = NULL;
    cliente c;

    while ((instruction = getch()) != 'q') {
        switch (instruction) {
        case 'd':
            scanf("%d", &input);
            root = delete(root, input);
            print_tree(root);
            break;
        case 'i':
            printf("Codigo:");
            scanf("%i", &c.codigo);
            printf("Nome:");
            fflush(stdin);
            scanf("%[^\n]", c.nome);
            printf("Telefone:");
            fflush(stdin);
            scanf("%[^\n]", c.telefone);
            printf("Endereco:");
            fflush(stdin);
            scanf("%[^\n]", c.endereco);
            printf("Idade:");
            scanf("%i", &c.idade);
            c.status = 0;
            root = insert(root, c.codigo, page_count);
            setClienteData(page_count, c);
            page_count++;
            break;
        case 'p':
            scanf("%d", &input);
            record * r = find(root, input, false);
            if(r != NULL){
                c = getClienteData(r->value);
                printf("Codigo: %i\nNome: %s\nTelefone: %s\nEndereco: %s\nStatus: %c\nIdade: %i\n", c.codigo, c.nome, c.telefone, c.endereco, c.status, c.idade);
            }else
                puts("Cliente nao encontrado.");
            break;
        case 'l':
            print_leaves(root);
            break;
        }
    }

    root = destroy_tree(root);
}
