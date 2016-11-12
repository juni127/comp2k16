#include<stdio.h>
#include<stdlib.h>

//Função original
void mistura(int *a, int as, int *b, int bs, int *c){
  int x, ta = 0, tb = 0;
  for(x = 0; x < as+bs; x++){
    if(a[ta] > b[tb] && tb < bs || ta >= as){
      c[x] = b[tb];
      tb++;
    }else{
      c[x] = a[ta];
      ta++;
    }
  }
}

//Ideia do jhon
void misturaJ(int *a, int as, int *b, int bs, int *c){
  //A variavel topoC serve para marcar onde paramos no vetor C, a topoB para marcar no vetor B
  int x, y, topoC, topoB = 0;
  //Coloca a em c
  for(x = 0; x < as; x++){
    c[x] = a[x];
  }
  topoC = as;
  for(x = 0; topoC <= as+bs; x++){
    //Se o valor de b teria que vir nessa posição em c
    if(b[topoB] < c[x]){
      //Adianta todos os valores de c na frente de x em uma casa
      for(y = topoC; y > x; y--)c[y] = c[y-1];
      //Coloca o valor de b em c
      c[x] = b[topoB];
      topoB++;
      topoC++;
    }
    //Se não não fazemos nada
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
