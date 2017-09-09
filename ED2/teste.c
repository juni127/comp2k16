#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

int main(){
    char a;
    do{
        a = getch();
        printf("%c: %i\n", a, a);
    }while(a != 8);
    return 0;
}
