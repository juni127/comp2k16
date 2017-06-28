#include<stdio.h>
#include<stdlib.h>
#include"arvore.h"

//1->sim->direita 0->não->esquerda

int main(int argc, char const *argv[]) {

  FILE *save = fopen("save.txt", "r");

  Tree *dados = leArvore(save);
  fclose(save);
  Tree *raiz = dados;
  int e;

  //Loop principal
  do{
    //Limpa tela -> Windows only
    system("cls");
    puts("Digite 1 pra sim e 0 pra nao.");
    //Raiz serve para armazenar o primeiro nó, já que eu uso dados para caminhar pela arvore
    dados = raiz;
    //Loop de perguntas para descobrir o nome do aluno
    while(1){ //while(1) executa o codigo indeterminadamente
      //Imprime o conteudo do nó (Como ele tem raiz ele é uma pergunta).
      printf("%s\n", dados->conteudo);
      //Lê a resposta do usuario
      scanf("%i", &e);
      //Se e = 0 -> dados->e é retornado se não dados->d é retornado
      dados = (e)?dados->d:dados->e;
      //Se o nó não possui raiz então ele é uma resposta e o loop tem que ser quebrado
      if(dados->e == NULL)
        break;
    }

    //Imprime o chute do programa
    printf("O nome do aluno eh %s?\n", dados->conteudo);
    //Lê a resposta do usuario
    scanf("%i", &e);
    //Se e = 0
    if(!e){
      //Se prepara para receber os novos dados
      char nome[500], questao[500];
      //Pergunta o nome do novo aluno
      printf("Digite o nome do aluno:");
      //Limpa a entrada
      fflush(stdin);
      //Lê o nome do aluno
      scanf("%499[^\n]", nome);
      //Pergunta a questão que diferencia os alunos
      printf("Digite uma pergunta que eh valida para %s e nao para %s:", nome, dados->conteudo);
      //Limpa a entrada
      fflush(stdin);
      //Lê a questão que discrimina os alunos
      scanf("%499[^\n]", questao);
      //Cria novos nós para manipular a lista
      Tree *novo = (Tree*)malloc(sizeof(Tree)), *antigo = (Tree*)malloc(sizeof(Tree));
      //Copia o nome entrado pro novo nó
      strcpy(novo->conteudo, nome);
      //Copia o nome do nó antigo pro novo nó
      strcpy(antigo->conteudo, dados->conteudo);
      //Seta os ponteiros dos nós resposta pra NULL
      novo->e = NULL;
      novo->d = NULL;
      antigo->e = NULL;
      antigo->d = NULL;
      //Copia a nova questão pro antigo nó
      strcpy(dados->conteudo, questao);
      //Atribui o endereço dos novos nós pros ponteiros do antigo
      dados->e = antigo;
      dados->d = novo;
    }else{
      puts("Sou um otimo advinho!");
    }
    puts("Deseja jogar novamente?");
    scanf("%i", &e);
  }while(e != 0);

  //Salva o arquivo
  save = fopen("save.txt", "w");
  salvaArvore(save, raiz);
  fclose(save);

  return 0;
}
