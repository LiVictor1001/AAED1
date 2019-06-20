#ifndef _GERENCIAMENTO_H
#define _GERENCIAMENTO_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>//biblioteca para pegar a data e hora do sistema

	struct tm* data_hora_atual;//estrutura de data e hora do sistema

	struct diretorio{

		char* nome;
		int numArqDir;
		char* data;
		char* hora;
		//int numDire;

	};

	struct arquivo{
		char* nome;
		char tipo;
		int tam;
		char* data;
		char* hora;
		//time_t dia, mes, ano; 
		//time_t hora, min;
		/*time_t é tipo da variável para receber informações de data e hora*/
	};

	struct arv{
		int tipo;
		void* info;
		struct arv* filho;
		struct arv* irmao;
	};

	typedef struct diretorio Diretorio;
	typedef struct arquivo Arquivo;
	typedef struct arv Arv;

	Arv* criarNo(void* val);
	Arv* removerNo(Arv* no);
	int qual_tipo(char val);
	Diretorio* alocarDiretorio(char* nome);
	Arquivo* alocarArquivo(char nome,char tipo);
	void apagar(Arv* no);




#endif
