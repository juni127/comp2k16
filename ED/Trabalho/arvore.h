#include<string.h>

//Isso eh uma struct
typedef struct TREE{
    char conteudo[500];
    struct TREE *e, *d;
}Tree;

//Lê a arvore do arquivo
Tree *leArvore(FILE *save){
  //Cria variaveis para armazenar os dados do próximo nó
  char conteudo[500];
  //e = 0 se não existir raiz e = 1 se existir
  int e = 0;
  //Lê os dados do nó no arquivo
  fscanf(save, "%[^;];%i;\n", conteudo, &e);
  //Cria o novo nó
  Tree* raiz = (Tree*)malloc(sizeof(Tree));
  //Copia a string que foi lida do arquivo para o nó
  strcpy(raiz->conteudo, conteudo);
  //Lê os nós raiz se existirem
  raiz->e = (e)?leArvore(save):NULL;
  raiz->d = (e)?leArvore(save):NULL;
  return raiz;
}

//Salva a arvore pro arquivo
void salvaArvore(FILE *save, Tree *arvore){
  //Verifica se o nó atual tem raizes
  //Se ele tem raizes e = 1 se não e = 0
  int e = (arvore->e == NULL)?0:1;
  //Printa no arquvio os dados do nó atual
  fprintf(save, "%s;%i;\n", arvore->conteudo, e);
  //Verifica se o nó tem raizes
  if(e){
    //Faz a chamada dessa função pra salvar cada nó 
    salvaArvore(save, arvore->e);
    salvaArvore(save, arvore->d);
  }
}
