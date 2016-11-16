//Escrito no Atom
#include<stdio.h>
#include<stdlib.h>

//Função que checa se existe um numero em um vetor
int busca(int valor, int *vet, int tVet){
  int x;
  for(x = 0; x < tVet; x++)if(valor == *(vet+x))return 1;
  return 0;
}

//Função que pega a interseccao
int interseccao(int *va, int ta, int *vb, int tb, int *vr){
  //O vetor R sempre vai ser menor ou igual ao menor vetor.
  int s = 0, x;
  for(x = 0; x < ta; x++){
    if(busca(va[x], vb, tb)){
      vr[s] = va[x];
      s++;
    }
  }
  //Retorna o tamanho real do vetor r.
  return s;
}

//Função que lê os vetores
void scanv(int *vet, int t){
  int x;
  for(x = 0; x < t; x++){
    printf("Vet[%i] = ", x+1);
    scanf("%i", vet+x);
  }
}

//Função que imprime vetores
void printv(int *vet, int t){
  int x;
  printf("[%i", *vet);
  for(x = 1; x < t; x++)printf(", %i", *(vet+x));
  printf("]");
}

int main(){
  int ta, tb, x;

  printf("Digite o tamanho do vetor A:");
  scanf("%i", &ta);
  int va[ta];
  scanv(va, ta);

  printf("Digite o tamanho do vetor B:");
  scanf("%i", &tb);
  int vb[tb];
  scanv(vb, tb);

  system("cls");

  int inter[ta];
  int tinter = interseccao(va, ta, vb, tb, inter);

  printf("Vetor A = ");
  printv(va, ta);
  puts("");

  printf("Vetor B = ");
  printv(vb, tb);
  puts("");

  printf("Vetor C = ");
  printv(inter, tinter);
  puts("");

  system("pause");

}
