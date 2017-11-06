#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

#define MEM_SIZE 1000

struct PROCESSADOR{
    unsigned short MAR, MBR, PC, IR;
}PROC;

unsigned short mem[MEM_SIZE];
int mem_top = -1;

int correrPrograma(){
    do{
        PROC.IR = mem[PROC.PC];
        switch ((PROC.IR >> 7) & 0x07) {
            case 0x00:
                //NOOP Provavelmente é um valor de memoria
                PROC.PC++;
                break;
            case 0x01:
                //Lê o valor contido no endereço x e o salva no MBR
                PROC.MAR = PROC.IR&0x7F;
                PROC.MBR = mem[PROC.MAR];
                PROC.PC++;
                break;
            case 0x02:
                //Salva o valor contido no MBR no endereço x
                PROC.MAR = PROC.IR&0x7F;
                mem[PROC.MAR] = PROC.MBR&0x7F;
                PROC.PC++;
                break;
            case 0x03:
                //Lê o valor contido no endereço x e soma ao valor contido no MBR. O valor da soma é armazenado no MBR
                PROC.MAR = PROC.IR&0x7F;
                PROC.MBR += mem[PROC.MAR];
                PROC.PC++;
                break;
            case 0x04:
                //Lê o valor contido no endereço x e subtrai do valor contido no MBR (MBR - ‘x’) . O valor da subtração é armazenado no MBR
                PROC.MAR = PROC.IR&0x7F;
                PROC.MBR -= mem[PROC.MAR];
                PROC.PC++;
                break;
            case 0x05:
                //Move o Contador de Programa para a linha de endereço x
                PROC.PC = PROC.IR&0x7F;
                break;
            case 0x06:
                //Escreve o valor numérico y no MBR
                PROC.MBR = PROC.IR&0x7F;
                PROC.PC++;
                break;
            case 0x07:
                //Indica que o programa chegou ao fim
                break;
        }
        if(PROC.IR&0x8000){
            //Breakpoint set
            printf(" Breakpoint em: %p\n", PROC.PC-1);
            return 0;
        }
    }while(((PROC.IR >> 7) & 0x07) != 0x07);
    return 1;
}

void compilar(char str1[100], char str2[100]){
    FILE * f = fopen(str1, "r"), * o = fopen(str2, "w");
    char in[7];
    unsigned short x, codigo[1];
    do{
        fscanf(f, "%s", in);
        if(in[0] == 'R' || in[0] == 'r')
            codigo[0] = 0x80;
        else if(in[0] == 'W' || in[0] == 'w')
            codigo[0] = 0x100;
        else if(in[0] == 'A' || in[0] == 'a')
            codigo[0] = 0x180;
        else if(in[2] == 'B' || in[2] == 'b')
            codigo[0] = 0x200;
        else if(in[0] == 'J' || in[0] == 'j')
            codigo[0] = 0x280;
        else if(in[0] == 'S' || in[0] == 's')
            codigo[0] = 0x300;
        else
            codigo[0] = 0x380;
        fscanf(f, " %p", &x);
        codigo[0] |= x;
        fwrite(codigo, sizeof(unsigned short), 1, o);
    }while(!feof(f));
    fclose(f);
    fclose(o);
}

void carregar(char str1[100]){
    FILE * f = fopen(str1, "r");
    unsigned short codigo[1];
    PROC.PC = 0;
    mem_top = 0;
    while(fread(codigo, sizeof(unsigned short), 1, f) == 1){
        mem[mem_top] = codigo[0];
        mem_top++;
    }
    fclose(f);
}

void guia(){
        puts(" Guia rapido ");
        puts("1 - Utilize um editor de texto para escrever seu codigo em assembly.");
        puts("2 - Utilize a opcao c <diretorio do arquivo entrada> <diretorio do arquivo de saida> para compilar seu codigo.");
        puts("3 - Utilize a opcao l <diretorio do arquivo> para carregar o binario para a memoria.");
        puts("4 - Utilize a opcao b <endereco do breakpoint> para selecionar pontos de quebra (Opcional).");
        puts("5 - Utilize a opcao r para rodar o programa que esta carregado atualmente na memoria.");
        puts("6 - Utilize a opcao m para mostrar o estado atual do processador.");
        puts("\n Utilize h h para obter ajuda.");
}

void ajuda(char e){
    switch (e) {
        case 'c':
            puts("\nUtilizacao:");
            puts("    c <diretorio do arquivo de entrada> <diretorio do arquivo de saida>");
            puts("Exemplo:");
            puts("    c entrada binario");
            puts("Funcionamento:");
            puts("    Converte o codigo escrito em assembly do arquivo de entrada em codigo de maquina e grava no arquivo de saida.");
            break;
        case 'l':
            puts("\nUtilizacao:");
            puts("    l <diretorio do arquivo>");
            puts("Exemplo:");
            puts("    c binario");
            puts("Funcionamento:");
            puts("    Carrega o codigo de maquina no arquivo para a memoria para execucao.");
            break;
        case 'b':
            puts("\nUtilizacao:");
            puts("    b <endereco da quebra>");
            puts("Exemplo:");
            puts("    b 0A");
            puts("Funcionamento:");
            puts("    Quebra a execucao do programa no momento especificado.");
            break;
        case 'r':
            puts("\nUtilizacao:");
            puts("    r");
            puts("Exemplo:");
            puts("    r");
            puts("Funcionamento:");
            puts("    Executa o programa carregado na memoria desde seu ultimo ponto (do inicio se o programa foi recem carregado ou terminado).");
            break;
        case 'm':
            puts("\nUtilizacao:");
            puts("    m");
            puts("Exemplo:");
            puts("    m");
            puts("Funcionamento:");
            puts("    Mostra o estado atual dos registradores do processador.");
            break;
        case 'q':
            puts("\nUtilizacao:");
            puts("    q");
            puts("Exemplo:");
            puts("    q");
            puts("Funcionamento:");
            puts("    Sai do programa.");
            break;
        case 'a':
            puts("\nComando            Acao");
            puts("  c             Converte o codigo do arquivo de entrada em codigo de maquina e grava no arquivo de saida.");
            puts("  l             Carrega o codigo de maquina do arquivo de entrada na memoria.");
            puts("  b             Cria ponto de quebra no endereco de memoria especificado.");
            puts("  r             Roda o programa que esta carregado atualmente na memmoria.");
            puts("  m             Mostra o estado atual do processador.");
            puts("  q             Finaliza o programa.");
            break;
        default:
            puts("\nUtilizacao:");
            puts("    h <comando>");
            puts("Exemplo:");
            puts("    h c");
            puts("Funcionamento:");
            puts("    Mostra a utilizacao, um exemplo e o funcionamento do comando desejado (utilize h a para listar os comandos).");
            break;
    }
}

int main(){
    char e, str1[100], str2[100], a;
    guia();
    do{
        fflush(stdin);
        scanf("%c", &e);
        switch (e) {
            case 'q':
                break;
            case 'c':
                scanf(" %s %s", str1, str2);
                compilar(str1, str2);
                puts(" Compilado com sucesso.");
                break;
            case 'l':
                scanf("  %s", str1);
                carregar(str1);
                puts(" Carregado com sucesso.");
                break;
            case 'r':
                if(correrPrograma())
                    puts(" Programa finalizado.");
                break;
            case 'b':
                scanf("%p", &a);
                mem[a] |= 0x8000;
                puts(" Breakpoint adicionado.");
                break;
            case 'm':
                printf("\nMBR: %p\nMAR: %p\nPC: %p\nIR: %p\n\n", PROC.MBR, PROC.MAR, PROC.PC, PROC.IR);
                break;
            case 'h':
                scanf(" %c", &a);
                ajuda(a);
                break;
            default:
                puts(" Utilize \"h a\" para listar todos os comandos.");
                break;
        }
    }while(e != 'q');
    return 0;
}
