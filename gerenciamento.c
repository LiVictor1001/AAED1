#include "gerenciamento.h"

int qual_tipo(char val){//estava usando essa função para descobrir se era arquivo ou diretório.

	switch(val){
		case 'D':
			return 0;
			break;
		case 'T':
			return 1;
			break;
		case 'B':
			return 2;
			break;
		default:
			exit(1);
	}
}

Diretorio* alocarDiretorio(char nome){
		Diretorio* dir;

		dir = (Diretorio*) malloc(sizeof(Diretorio));
		dir->nome = nome;
		dir->numArq = 0;
		dir->numDire = 0;

		return dir;
}

Arquivo* alocarArquivo(char nome, char tipo){

		Arquivo* arq;

		arq = (Arquivo*) malloc(sizeof(Arquivo));
		arq->nome = nome;
		arq->tipo = tipo;

		return arq;
}

Arv* criarNo(void* val){

	Arv* novo = (Arv*) malloc(sizeof(Arv));
	novo->filho = NULL;
	novo->irmao = NULL;
	novo->info = val;

	return novo;
}

Arv* busca(Arv* arvore, char* nome1)
{
	Arv* noAux = arvore;
	while(((Diretorio*)noAux->info)->nome != nome1)
	{
		Arv* noAux2 = noAux;
		
		while(strcmp(((Diretorio*)noAux->info)->nome, nome1) != 0 && noAux2 != NULL)
		{
			noAux2 = noAux2->irmao;
		}
		if(strcmp(((Diretorio*)noAux->info)->nome, nome1) == 0)
		{
			return noAux2;
		}
		noAux = noAux ->filho;
	}
	if(strcmp(((Diretorio*)noAux->info)->nome, nome1) == 0)
	{
		return noAux;
	}
}

void insereNo(Arv* noEntrada, Arv* arvore, char* nome){
	Arv* noPai = busca(arvore, nome);
	Arv* noAux;

	if(noPai->filho != NULL){
		for(noAux = noPai->filho->irmao; noAux != NULL; noAux = noAux->irmao){
			if(noAux == NULL){
				noAux->irmao = noEntrada;
			}
		}
	}
	else{
		noPai->filho = noEntrada; 
	}

}

void renomear(Arv* arvore, char* nome, char* novoNome,char* data, char* hora){
	Arv* noAux = busca(arvore,nome);
	if(noAux->tipo == 1){
		noAux->info->nome = novoNome;
		noAux->info->data = data;
		noAux->info->hora = hora;
	}
	
	if(noAux->tipo == 2){
		noAux->nome = novoNome;
		noAux->data = data;
		noAux->hora = hora;
		noAux->info->data = data;
		noAux->info->hora = hora;
	}	
}

void transformar(Arv* arvore, char tipo,char* data, char* hora){
	Arv* noAux = busca(arvore,nome);
	if(noAux->info->tipo == tipo){
		exit(1);
	}

	else{
		noAux->info->tipo = tipo;
		noAux->info->data = data;
		noAUx->info->hora = hora;
		noAux->data = data;
		noAux->hora = hora;
	}
}