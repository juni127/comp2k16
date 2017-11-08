#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

typedef struct cliente{
    int codigo, idade;
    char nome[40], telefone[8], endereco[40];
}cliente;

cliente buffer[11];
int btop = 0;

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

#include"btree.h"

int main(){

    char instruction;
    int input, x;
    cliente c;
	node * root = NULL;

    system("mkdir data");
    system("cls");

    FILE * data = fopen("data/log", "r");
    int e[2];
    if(data != NULL){
        //Ler todo o conteudo e inserir na arvore
        while(fread(e, sizeof(int), 2, data) == 2)
            if(e[0])
                root = insert(root, e[1], e[1]);
            else
                root = delete(root, e[1]);
        fclose(data);
        data = fopen("data/log", "a");
    }else{
        fclose(data);
        data = fopen("data/log", "w");
    }



    do{
        system("cls");
        puts("------| M3nU |-------------------");
        puts("| Comando  | Acao               |");
        puts("|-------------------------------|");
        puts("|    d     | Apagar cliente     |");
        puts("|    i     | Inserir cliente    |");
        puts("|    p     | Pesquisar cliente  |");
        puts("|    l     | Listar clientes    |");
        puts("|    q     | Sair do programa   |");
        puts("---------------------------------");
        instruction = getch();
        switch (instruction) {
        case 'd':
            printf("Digite o codigo do cliente:");
            scanf("%d", &input);
            btop = 0;
            e[0] = 0;
            e[1] = input;
            fwrite(e, sizeof(int), 2, data);
            root = deleteFile(root, input);
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
            buffer[0] = c;
            btop = 0;
            e[0] = 1;
            e[1] = c.codigo;
            fwrite(e, sizeof(int), 2, data);
            root = insertFile(root, c.codigo, c.codigo);
            break;
        case 'p':
            printf("Digite o codigo do cliente:");
            scanf("%d", &input);
        	node * l = find_leaf(root, input, false);
            FILE * f = fopen(genFileName(((record *)l->pointers[0])->value), "r");
            while(fscanf(f, "%i %i %[^#]# %[^#]# %[^\n]\n", &c.codigo, &c.idade, c.nome, c.telefone, c.endereco) == 5 && c.codigo != input);
            fclose(f);
            if(c.codigo == input)
                printf("Codigo: %i\nNome: %s\nIdade: %i\nTelefone: %s\nEndereco: %s\n", c.codigo, c.nome, c.idade, c.telefone, c.endereco);
            else
                puts("Cliente nao encontrado.");
            break;
        case 'l':
            print_leaves(root);
            break;
        }
        puts("Qualquer tecla para continuar...");
        getch();
        fflush(stdin);
    }while(instruction != 'q');

    if(root != NULL)root = destroy_tree(root);
    fclose(data);

    return 0;
}
