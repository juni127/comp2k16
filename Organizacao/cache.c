#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

int main(){
    char e;
    int addr, x, y;

    do{
        system("cls");
        puts("------| MeNu |-------------------------------------------");
        puts("| Comando | Acao                                        |");
        puts("|-------------------------------------------------------|");
        puts("|    d    | Calcular endereco direto                    |");
        puts("|    a    | Calcular endereco associativo p/ conjunto   |");
        puts("|    s    | Sair do programa                            |");
        puts("---------------------------------------------------------");
        fflush(stdin);
        e = getch();
        if(e == 's')break;
        puts("| Digite o endereco em hexadecimal                      |");
        puts("---------------------------------------------------------");
        scanf("%p", &addr);
        //Mesmo role pros dois
        int word = addr&0x3, tag;

        switch (e) {
            case 'd':
                //Direto
                tag = (addr>>13);
                int linha = (addr>>2)&0x7FF;
                puts("\n\nEm hexa:");
                printf("WORD: 0x%p\nLINHA: 0x%p\nTAG: 0x%p\n", word, linha, tag);
                puts("\n\nEm binario:");
                printf("\nWORD: ");
                for(x = 1; x >= 0; x--)printf("%i", (word>>x)&0x1);
                printf("\nLINHA: ");
                for(x = 10; x >= 0; x--)printf("%i", (linha>>x)&0x1);
                printf("\nTAG: ");
                for(x = 16; x >= 0; x--)printf("%i", (tag>>x)&0x1);
                printf("\n\nEndereco completo: \n");
                for(x = 31; x >= 0; x--)printf("%i", (addr>>x)&0x1);
                break;
            case 'a':
                //Associativo
                printf(" Digite o numero de conjuntos (potencia de dois):");
                int y, k;
                scanf("%i", &y);
                for(k = 0; (1<<k) < y; k++);
                int set = (addr>>2)&(y-1);
                tag = (addr>>2+k);
                puts("\n\nEm hexa:");
                printf("WORD: 0x%p\nCONJUNTO: 0x%p\nTAG: 0x%p\n", word, set, tag);
                puts("\n\nEm binario:");
                printf("\nWORD: ");
                for(x = 1; x >= 0; x--)printf("%i", (word>>x)&0x1);
                printf("\nCONJUNTO: ");
                for(x = k-1; x >= 0; x--)printf("%i", (set>>x)&0x1);
                printf("\nTAG: ");
                for(x = 29-k; x >= 0; x--)printf("%i", (tag>>x)&0x1);
                printf("\n\nEndereco completo: \n");
                for(x = 31; x >= 0; x--)printf("%i", ((addr>>x)&0x1));
                break;
        }
        puts("\n\n               | Qualquer tecla para continutar |");
        getch();
    }while(1);
    system("cls");
    puts("Obrigado por usar o programa. Volte sempre. (Qualquer tecla para continuar)");
    getch();
    return 0;
}
