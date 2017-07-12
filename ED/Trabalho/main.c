#include<stdio.h>
#include<stdlib.h>
#include"arvore.h"

//1->sim->direita 0->não->esquerda

int trataResposta(char e){
	if(e < 50)e -= 48;
	//Sim
	else if (e == 83)e = 1;
	else if (e == 115)e = 1;
	//Oui
	else if (e == 79)e = 1;
	else if (e == 111)e = 1;
	//Yes
	else if (e == 89)e = 1;
	else if (e == 121)e = 1;
	//Hai
	else if (e == 72)e = 1;
	else if (e == 104)e = 1;
	//Ja
	else if (e == 74)e = 1;
	else if (e == 106)e = 1;
	//Não - Non - No - Nein
	else if (e == 110)e = 0;
	else if (e == 78)e = 0;
	//Iie
	else if (e == 73)e = 0;
	else if (e == 105)e = 0;
	else e = 0;
	return e;
}

int main(int argc, char const *argv[]) {

  FILE *save = fopen("save.txt", "r");

  Tree *dados = leArvore(save);
  fclose(save);
  Tree *raiz = dados;
  int e;
  char in[50];

  //Loop principal
  do{
    //Limpa tela -> Windows only
    system("cls");
    //puts("Digite 1 pra sim e 0 pra nao.");
    //Raiz serve para armazenar o primeiro nó, já que eu uso dados para caminhar pela arvore
    dados = raiz;
    //Loop de perguntas para descobrir o nome do aluno
    while(dados->e != NULL){ //while(1) executa o codigo indeterminadamente
      //Imprime o conteudo do nó (Como ele tem raiz ele é uma pergunta).
      printf("%s\n", dados->conteudo);
      //Lê a resposta do usuario
      scanf("%s", in);
	  e = trataResposta(in[0]);
      //Se e = 0 -> dados->e é retornado se não dados->d é retornado
      dados = (e)?dados->d:dados->e;
    }

    //Imprime o chute do programa
    printf("O nome do aluno eh %s?\n", dados->conteudo);
    //Lê a resposta do usuario
    scanf("%s", in);
	e = trataResposta(in[0]);
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
    scanf("%s", in);
	e = trataResposta(in[0]);
  }while(e != 0);

  //Salva o arquivo
  save = fopen("save.txt", "w");
  salvaArvore(save, raiz);
  fclose(save);

  return 0;
}
