#include<stdio.h>
#include<stdlib.h>

int soma(int a, int b){
    int resultado;
    resultado = a + b;
    return resultado;
}
int sub(int a, int b){
    int resultado;
    resultado = a - b;
    return resultado;
}
int multi(int a, int b){
    int resultado;
    resultado = a * b;
    return resultado;
}
int divisao(int a, int b){
    int resultado;
    resultado = a / b;
    return resultado;
}

int main(){
    char ent;
    int a, b, result;
    puts("Escreva a operacao(Ex: a + b):");
    scanf("%i %c %i", &a, &ent, &b);
    switch(ent){
                case '+':
                      result = soma(a, b);
                      break;
                case '-':
                      result = sub(a, b);
                      break;
                case '*':
                      result = multi(a, b);
                      break;
                case '/':
                      result = divisao(a, b);
                      break;
    }
    printf("Resultado = %i\n", result);
    system("pause");
}
