#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

int main(){
    int e;
    do{
        e = getch();
        printf("%c: %i\n", e, e);
    }while(e != 'q');

    return 0;
}
