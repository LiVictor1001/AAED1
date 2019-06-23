#ifndef _GERENCIAMENTO_H
#define _GERENCIAMENTO_H
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>//biblioteca para pegar a data e hora do sistema

    struct tm* data_hora_atual;//estrutura de data e hora do sistema

    struct diretorio{

        char nome[101];
        int numArqDir;
        char data[9];
        char hora[6];
        char dataModificacao[9];
        char horaModificacao[6];
        //int numDire;

    };

    struct arquivo{
        char nome[101];
        char tipo;
        int tam;
        char data[9];
        char hora[6];
        char dataModificacao[9];
        char horaModificacao[6];
    };

    struct arv{
    	char tipo;
        void* info;
        struct arv* filho;
        struct arv* irmao;
    };

    typedef struct diretorio Diretorio;
    typedef struct arquivo Arquivo;
    typedef struct arv Arv;

    Arv* criarNo(void* val,int tipo);
    Arv* removerNo(Arv* no);
    int qual_tipo(char val);
    Diretorio* alocarDiretorio(char* nome,int tam,char* dataCriacao, char* horaCriacao);
    Arquivo* alocarArquivo(char* nome,char tipo,int tam,char* dataCriacao, char* horaCriacao);
    void apagar(Arv* no);
	Arv* find_the_father(Arv* raiz, char* filho);



#endif
