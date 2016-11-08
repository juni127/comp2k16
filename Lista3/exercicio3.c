#include<stdio.h>
#include<stdlib.h>

void mistura(int *a, int as, int *b, int bs, int *c){
  int x, ta = 0, tb = 0;
  for(x = 0; x < as+bs; x++){
    if(a[ta] > b[tb]){
      c[x] = b[tb];
      tb++;
    }else{
      c[x] = a[ta];
      ta++;
    }
  }
}

int main(){
  int x, sa, sb;
  printf("Digite o tamanho do vetor A:");
  scanf("%i", &sa);
  int vetA[sa];

  for(x = 0; x < sa; x++){
    printf("VET-A[%i]=", x+1);
    scanf("%i", &vetA[x]);
  }

  system("cls");

  printf("Digite o tamanho do vetor B:");
  scanf("%i", &sb);
  int vetB[sb];

  for(x = 0; x < sb; x++){
    printf("VET-B[%i]=", x+1);
    scanf("%i", &vetB[x]);
  }

  system("cls");

  int vetC[sa+sb];
  mistura(vetA, sa, vetB, sb, vetC);

  printf("VET-C = [%i", vetC[0]);
  for(x = 1; x < sa+sb; x++)printf(", %i", vetC[x]);
  puts("]");

  system("pause");
  return 0;
}
