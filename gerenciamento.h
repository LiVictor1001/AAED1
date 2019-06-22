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
		char* dataCriacao;
		char* horaCriacao;
		char* dataModificacao;
		char* horaModificacao;
		//int numDire;

	};

	struct arquivo{
		char* nome;
		char tipo;
		int tam;
		char* dataCriacao;
		char* horaCriacao;
		char* dataModificacao;
		char* horaModificacao;
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
	Diretorio* alocarDiretorio(char* nome,int tam,char* dataCriacao, char* horaCriacao);
	Arquivo* alocarArquivo(char* nome,char tipo,int tam,char* dataCriacao, char* horaCriacao);
	void apagar(Arv* no);




#endif
