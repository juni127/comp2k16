#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct no{
    int valor;
    struct no * prox;
}no;

no * add_no(no * lista, int valor){
    no * aux, * novo = (no*)malloc(sizeof(no));
    novo->valor = valor;
    novo->prox = NULL;
    for(aux = lista; aux != NULL && aux->prox != NULL; aux = aux->prox);
    if(aux == NULL)
        return novo;
    aux->prox = novo;
    return lista;
}

no * remove_no(no * lista){
    if(lista == NULL)
        return lista;
    no * aux = lista->prox;
    free(lista);
    return aux;
}

void printa_lista(no * lista){
    no * aux;

    printf("[");
    for(aux = lista; aux != NULL && aux->prox != NULL; aux = aux->prox){
        printf("%i, ", aux->valor);
    }
    if(aux != NULL)
        printf("%i]\n", aux->valor);
    else
        puts("]");
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}


void bubbleSort(int arr[], int n)
{
   int i, j, swapped;
   for (i = 0; i < n-1; i++)
   {
     swapped = 0;
     for (j = 0; j < n-i-1; j++)
     {
        if (arr[j] > arr[j+1])
        {
           swap(&arr[j], &arr[j+1]);
           swapped = 1;
        }
     }

     // IF no two elements were swapped by inner loop, then break
     if (!swapped)
        break;
   }
}


int main(){

    int x, y, z, mem[3], cs, carregou = 0, acabou = 0;
    FILE * in;
    no * fitas[6];
    for(x = 0; x < 6; x++)
        fitas[x] = NULL;

    loop:
        system("cls");
        puts("-----| Menu |-----------------------");
        puts("|   Comando   |        Acao        |");
        puts("|      l      | Carrega os numeros |");
        puts("|      p      | Passa uma vez      |");
        puts("|      m      | Mostra as fitas    |");
        puts("|      q      | Sai do programa    |");
        puts("------------------------------------");
        switch (getch()) {
            case 'l':
                in = fopen("entrada", "r");
                y = 0;
                cs = 3;
                while((x = fscanf(in, "%i %i %i ", mem, mem+1, mem+2)) > 0){
                    bubbleSort(mem, x);
                    for(z = 0; z < x; z++)
                        fitas[y] = add_no(fitas[y], mem[z]);
                    y = (y == 2)?0:y+1;
                }
                carregou = 1;
                acabou = 0;
                fclose(in);
                break;
            case 'p':
                if(!carregou){
                    puts(" Numeros nao carregados.");
                    break;
                }
                if(acabou){
                    puts(" Numeros já ordenados.");
                    break;
                }
                int f[3];
                for(x = 0; x < 3; x++)
                    if(fitas[x] != NULL){
                        mem[x] = fitas[x]->valor;
                        fitas[x] = remove_no(fitas[x]);
                        f[x] = 0;
                    }else{
                        mem[x] = 1000;
                        f[x] = cs;
                    }
                y = 3;
                z = 0;
                do{

                    if(mem[0] <= mem[1] && mem[0] <= mem[2] && mem[0] < 1000){
                        fitas[y] = add_no(fitas[y], mem[0]);
                        f[0]++;
                        if(f[0] >= cs)
                            mem[0] = 1000;
                        else if(fitas[0] == NULL){
                            mem[0] = 1000;
                            f[0] = cs;
                        }else{
                            mem[0] = fitas[0]->valor;
                            fitas[0] = remove_no(fitas[0]);
                        }
                    }else if(mem[1] <= mem[0] && mem[1] <= mem[2] && mem[1] < 1000){
                        fitas[y] = add_no(fitas[y], mem[1]);
                        f[1]++;
                        if(f[1] >= cs)
                            mem[1] = 1000;
                        else if(fitas[1] == NULL){
                            mem[1] = 1000;
                            f[1] = cs;
                        }else{
                            mem[1] = fitas[1]->valor;
                            fitas[1] = remove_no(fitas[1]);
                        }
                    }else if(mem[2] <= mem[1] && mem[2] <= mem[0] && mem[2] < 1000){
                        fitas[y] = add_no(fitas[y], mem[2]);
                        f[2]++;
                        if(f[2] >= cs)
                            mem[2] = 1000;
                        else if(fitas[2] == NULL){
                            mem[2] = 1000;
                            f[2] = cs;
                        }else{
                            mem[2] = fitas[2]->valor;
                            fitas[2] = remove_no(fitas[2]);
                        }
                    }

                    if(f[0] >= cs && f[1] >= cs && f[2] >= cs){
                        z++;
                        y = (y == 5)?3:y+1;
                        for(x = 0; x < 3; x++)
                            if(fitas[x] != NULL){
                                mem[x] = fitas[x]->valor;
                                fitas[x] = remove_no(fitas[x]);
                                f[x] = 0;
                            }else{
                                mem[x] = 1000;
                                f[x] = cs;
                            }

                    }

                }while(fitas[0] != NULL || fitas[1] != NULL || fitas[2] != NULL);
                if(z < 1)
                    acabou = 1;
                cs *= 3;
                fitas[0] = fitas[3];
                fitas[3] = NULL;
                fitas[1] = fitas[4];
                fitas[4] = NULL;
                fitas[2] = fitas[5];
                fitas[5] = NULL;
                break;
            case 'm':
                if(!carregou){
                    puts(" Fitas vazias.");
                    break;
                }
                for(x = 0; x < 3; x++){
                    printf("\n\n FITA %d: ", x+1);
                    printa_lista(fitas[x]);
                }
                break;
            case 'q':
                puts("\n Saindo do programa...");
                goto saida;
                break;
        }
        puts(" Qualquer tecla para continuar...");
        getch();
    goto loop;
    saida:
    system("pause");
    return 0;
}
