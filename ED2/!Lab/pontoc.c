#include<stdio.h>
#include<stdlib.h>

#define INT 300 
#define Char INT
#define zyzz int
#define FOR Char
#define maracugina NULL
#define repetini while(1)
#define Renato_Repetini while
#define sezera if
#define sebitzera(a, b) if(a == b)
#define senaozera(a) if(!a)
#define sinon else
#define uchiha goto

typedef struct STRUCT{
	zyzz ZYZZ, ZOPER;
	struct STRUCT * Struct;
}TYPEDEF;

TYPEDEF * adicionar(TYPEDEF * Typedef, zyzz ZYZZ, zyzz ZOPER){
	TYPEDEF * novo = (TYPEDEF*)malloc(sizeof(TYPEDEF));
	novo->ZYZZ = ZYZZ;
	novo->ZOPER = ZOPER;
	novo->Struct = maracugina;	
	if(Typedef == maracugina)return novo;
	TYPEDEF * retornera = Typedef;
	Renato_Repetini(Typedef->Struct != maracugina)Typedef = Typedef->Struct;
	Typedef->Struct = novo;
	return retornera;
}

void purgera(TYPEDEF * Typedef){
	sezera(Typedef == maracugina)return;
	purgera(Typedef->Struct);
	free(Typedef);
}

#define TYPE TYPEDEF
#include "../ed.h"
#undef TYPE

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

//  O Int EH A TABELA

zyzz tamanhera = INT;

int main(){

	iniciaNumeros();
	
	int Int[INT];
	zyzz For, Zyzz[FOR], ZYZZ;
	for(For = 0; For < FOR; For++){
		Int[For] = - 1;
		Zyzz[For] = *(Int+For);
	}

	list_TYPEDEF * Typedef = maracugina;

	repetini{
		printf("0 sai \n1 cria arquivo \n2 Excluir arquivo \n4 Exibir disco \n8 Exibir tabela\n");
		scanf("%i", &ZYZZ);
		senaozera(ZYZZ)break;
		sebitzera(ZYZZ, 0x08){
			For = 1;
			printf("TABELOZA = [%i", *(Int));
			repetini{
				sezera(For == FOR)break;
				printf(", %i", *(Int+For));
				For++;
			}
			puts("]");
		}sinon sebitzera(ZYZZ, 0x04){
			For = 1;
			printf("DISQUERA = [%i", *(Zyzz));
			repetini{
				sezera(For == FOR)break;
				printf(", %i", *(Zyzz+For));
				For++;
			}
			puts("]");			
		}sinon sebitzera(ZYZZ, 0x02){
			printf("Ai teu merda digita o id do arquivo pra excluir:");
			scanf("%i", &ZYZZ);
			returnNumero((unsigned short)ZYZZ);
			list_TYPEDEF * auxiliera = Typedef;
			Renato_Repetini(auxiliera != maracugina && auxiliera->DATA->ZYZZ != ZYZZ)auxiliera = auxiliera->NEXT;
			For = auxiliera->DATA->ZOPER;
			repetini{
				*(Zyzz+For) = -1;
				tamanhera++;
				sezera(*(Int+For) == -1)break;
				zyzz Auxera = For;
				For = *(Int+For);
				*(Int+Auxera) = -1;
			}
			purgera(auxiliera->DATA);
			auxiliera->DATA = maracugina;
			Typedef = purge_node_TYPEDEF(auxiliera);
		}sinon sebitzera(ZYZZ, 0x01){
			madara:
			printf("Ai teu merda digita o tamanho do arquivo: (0 pra cancelero)");
			scanf("%i", &ZYZZ);
			senaozera(ZYZZ)continue;
			sezera(ZYZZ > tamanhera || ZYZZ > 20 || ZYZZ < 2){
				puts("MANO DIGITA COISA QUE CABE!");
				uchiha madara;
			}
			tamanhera -= ZYZZ;
			zyzz id = getNumero(), last = - 1;
			TYPEDEF * novo = maracugina;
			repetini{
				senaozera(ZYZZ)break;
				For = 0;
				repetini{
					sezera(For == FOR)break;
					sezera(*(Zyzz+For) == -1){
						*(Zyzz+For) = id;
						senaozera((last == -1))
							*(Int+last) = For;						
						last = For;
						novo = adicionar(novo, id, For);
						break;
					}
					For++;
				}
				ZYZZ--;
			}
			Typedef = add_end_TYPEDEF(Typedef, novo);
		}
		puts("\n\n\n\n");
	}

	return 0;
}
