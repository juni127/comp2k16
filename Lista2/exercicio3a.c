#include<stdio.h>
#include<stdlib.h>

int isCousin(int a){
    int x, count = 0;
    if(a == 1)return 0;
    for(x = 1; x < a/2 + 1; x++){
             if(a%x == 0)count++;
    }
    if(count > 1)return 0;
    else return 1;
}

int main(){
    int x, r;
    puts("Digite o numero a ser testado:");
    scanf("%i", &x);
    r = isCousin(x);
    printf("Resultado = %i, portanto o numero ", r);
    if(r)puts("e primo.");
    else puts("nao e primo.");
    system("pause");
}
