#include<stdio.h>
#include<stdlib.h>

void calc(float a, float b, char c, float *r){
  switch(c){
    case '+':
      *r = a + b;
      break;
    case '-':
      *r = a - b;
      break;
    case '*':
      *r = a * b;
      break;
    case '/':
      *r = a / b;
      break;
  }
}

int main(){
  float a, b, r;
  char c;
  puts("Calculadora:");
  scanf("%f %c %f", &a, &c, &b);
  calc(a, b, c, &r);
  printf("Resultado: %f\n", r);
  system("pause");
  return 0;
}
