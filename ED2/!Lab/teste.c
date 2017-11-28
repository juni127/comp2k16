#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>


int main(){
    srand(time(NULL));
    int * a, b, * c = malloc(sizeof(int)*10), * d = malloc(sizeof(int)*10);
    for(b = 0; b < 10; b++){
        c[b] = rand()%10;
        d[b] = b;
    }

    a = c;
    c = d;
    d = a;

    for(b = 0; b < 10; b++){
        printf("C: %i D: %i\n", c[b], d[b]);
    }

    return 0;
}
