#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

#define MEM_SIZE 128

struct PROCESSADOR{
    unsigned short MAR, MBR, PC, IR;
}PROC;

unsigned short mem[MEM_SIZE];
int mem_top = -1;

int correrPrograma(){
    do{
        PROC.IR = mem[PROC.PC];
        switch ((PROC.IR >> 7)&0x07) {
            case 0x00:
                //NOOP Provavelmente é um valor de memoria
                PROC.PC++;
                break;
            case 0x01:
                //Lê o valor contido no endereço x e o salva no MBR
                PROC.MAR = PROC.IR&0x7F;
                PROC.MBR = mem[PROC.MAR+mem_top];
                PROC.PC++;
                break;
            case 0x02:
                //Salva o valor contido no MBR no endereço x
                PROC.MAR = PROC.IR&0x7F;
                mem[PROC.MAR+mem_top] = PROC.MBR&0x7F;
                PROC.PC++;
                break;
            case 0x03:
                //Lê o valor contido no endereço x e soma ao valor contido no MBR. O valor da soma é armazenado no MBR
                PROC.MAR = PROC.IR&0x7F;
                PROC.MBR += mem[PROC.MAR+mem_top];
                PROC.PC++;
                break;
            case 0x04:
                //Lê o valor contido no endereço x e subtrai do valor contido no MBR (MBR - ‘x’) . O valor da subtração é armazenado no MBR
                PROC.MAR = PROC.IR&0x7F;
                PROC.MBR -= mem[PROC.MAR+mem_top];
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

int compilar(char str1[100], char str2[100]){
    FILE * f = fopen(str1, "r"), * o;
    if(f == NULL)
        return -2;
    int s, y;
    char in[7];
    for(s = 0; !feof(f); s++)
        fscanf(f, "%s %p", in, &y);
    y = 0;
    if(s >= MEM_SIZE)
        return -1;
    rewind(f);
    unsigned short x, codigo[1];
    o = fopen(str2, "w");
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
        else if(in[1] == 'M' || in[1] == 'm')
            codigo[0] = 0x280;
        else if(in[0] == 'S' || in[0] == 's')
            codigo[0] = 0x300;
        else
            codigo[0] = 0x380;
        fscanf(f, "%c", &in[0]);
        if(in[0] == '\n' && codigo[0] != 0x380){
            fclose(f);
            fclose(o);
            return 0x100 | y;
        }
        if(codigo[0] != 0x380 && fscanf(f, "%p", &x) < 1){
            fclose(f);
            fclose(o);
            return 0x100 | y;
        }
        if(x+s >= MEM_SIZE && !(codigo[0] == 0x380 || codigo[0] == 0x300)){
            fclose(f);
            fclose(o);
            return 0x80 | y;
        }
        if(codigo[0] != 0x380)
            codigo[0] |= x&0x7F;
        fwrite(codigo, sizeof(unsigned short), 1, o);
        if(codigo[0] != 0x380){
            fscanf(f, "%c", &in[0]);
            if(in[0] == '\n')y++;
        }else
            y++;
    }while(!feof(f));
    fclose(f);
    fclose(o);
    return 0;
}

int carregar(char str1[100]){
    FILE * f = fopen(str1, "r");
    if(f == NULL)
        return 0;
    unsigned short codigo[1];
    PROC.PC = 0;
    mem_top = 0;
    while(fread(codigo, sizeof(unsigned short), 1, f) == 1){
        mem[mem_top] = codigo[0];
        mem_top++;
    }
    fclose(f);
    return 1;
}

void descompilar(){
    int x;
    puts("INICIO:");
    for(x = 0; x < mem_top; x++){
        switch ((mem[x]>>7)&0xF) {
            case 0x0:
                printf(" 0x%p: MEM ", x);
                break;
            case 0x1:
                printf(" 0x%p: READ ", x);
                break;
            case 0x2:
                printf(" 0x%p: WRITE ", x);
                break;
            case 0x3:
                printf(" 0x%p: ADD ", x);
                break;
            case 0x4:
                printf(" 0x%p: SUB ", x);
                break;
            case 0x5:
                printf(" 0x%p: JMP ", x);
                break;
            case 0x6:
                printf(" 0x%p: SET ", x);
                break;
            case 0x7:
                printf(" 0x%p: END \n", x);
        }
        if(((mem[x]>>7)&0xF) != 0x7){
            if(mem[x]&0x8000)
                printf("%p <-| breakpoint |\n", mem[x]&0x7F);
            else
                printf("%p\n", mem[x]&0x7F);
        }
    }
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
    char e, str1[100], str2[100], a, b, x, y;
    guia();
    do{
        fflush(stdin);
        scanf("%c", &e);
        switch (e) {
            case 'q':
                break;
            case 'c':
                scanf(" %s %s", str1, str2);
                int r = compilar(str1, str2);
                if(!r)
                    puts(" Convertido com sucesso.");
                else if(r == -1)
                    puts(" ERRO NA LINHA 128: Programa maior que a memoria.");
                else if(r == -2)
                    puts(" ERRO: Arquivo de entrada nao encontrado.");
                else if(r&0x80)
                    printf(" ERRO NA LINHA %i: Endereco digitado corresponde a espaco inexistente.\n", (r&0x7F) + 1);
                else if(r&0x100)
                    printf(" ERRO NA LINHA %i: Erro de sintaxe.\n", (r&0x7F) + 1);
                break;
            case 'l':
                scanf("  %s", str1);
                if(carregar(str1))
                    puts(" Carregado com sucesso.");
                else
                    puts(" Arquivo nao encontrado.");
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
                printf("\n MBR: %p\n MAR: %p\n PC: %p\n IR: %p\n\n", PROC.MBR, PROC.MAR, PROC.PC, PROC.IR);
                break;
            case 's':
                scanf("%p", &a);
                x = a;
                char spc;
                scanf("%c", &spc);
                if(spc != '\n')
                    scanf("%p", &b);
                else
                    b = x;
                for(; x <= b; x++){
                    if(x < mem_top)
                        printf(" PRG 0x%p: HEX: %p BIN: (", x, mem[x]);
                    else
                        printf(" MEM 0x%p: HEX: %p BIN: (", x, mem[x]);
                    for(y = 9; y > 0; y--)
                        printf("%i", (mem[x]>>y)&1);
                    puts(")");
                }
                break;
            case 'd':
                descompilar();
                break;
            case 'h':
                scanf(" %c", &a);
                ajuda(a);
                break;
            case 'n':
                a = 0;
                FILE * f = fopen(".tmp", "w");
                do{
                    fflush(stdin);
                    printf(" 0x%p: ", a);
                    scanf("%[^\n]", str1);
                    fprintf(f, "%s\n", str1);
                    a++;
                }while(str1[0] != 'E' && str1[0] != 'e');
                fclose(f);
                a = compilar(".tmp", ".tmp_out");
                system("del .tmp");
                if(!a){
                    puts(" Convertido com sucesso.");
                    carregar(".tmp_out");
                    system("del .tmp_out");
                    puts(" Programa inserido na memoria com sucesso.");
                }else if(a == -1)
                    puts(" ERRO NA LINHA 128: Programa maior que a memoria.");
                else if(a == -2)
                    puts(" ERRO: Arquivo de entrada nao encontrado.");
                else if(r&0x80)
                    printf(" ERRO NA LINHA %i: Endereco digitado corresponde a espaco inexistente.\n", (r&0x7F) + 1);
                else if(r&0x100)
                    printf(" ERRO NA LINHA %i: Erro de sintaxe.\n", (r&0x7F) + 1);
                break;
            case 'e':
                printf(" EXEC: ");
                scanf("%s %p", str1, &a);
                if(str1[0] == 'R' || str1[0] == 'r'){
                    PROC.MAR = a&0x7F;
                    PROC.MBR = mem[PROC.MAR];
                }else if(str1[0] == 'W' || str1[0] == 'w'){
                    PROC.MAR = a&0x7F;
                    mem[PROC.MAR] &= 0x7<<0x7;
                    mem[PROC.MAR] |= PROC.MBR;
                }else if(str1[0] == 'A' || str1[0] == 'a'){
                    PROC.MAR = a&0x7F;
                    PROC.MBR += mem[PROC.MAR]&0x7F;
                }else if(str1[2] == 'B' || str1[2] == 'b'){
                    PROC.MAR = a&0x7F;
                    PROC.MBR -= mem[PROC.MAR]&0x7F;
                }else if(str1[1] == 'M' || str1[1] == 'm')
                    PROC.PC = a&0x7F;
                else if(str1[0] == 'S' || str1[0] == 's')
                    PROC.MBR = a;
                break;
            default:
                puts(" Utilize \"h a\" para listar todos os comandos.");
                break;
        }
    }while(e != 'q');
    return 0;
}
