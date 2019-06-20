#include "gerenciamento.h"
#define typeof(var) _Generic( (var),\
Diretorio *: "Diretorio",\
Arquivo *: "Arquivo",\
char: "Char",\
int: "Integer",\
float: "Float",\
char *: "String",\
void *: "Pointer",\
default: "Undefined")

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

Diretorio* alocarDiretorio(char* nome){
		Diretorio* dir;

		dir = (Diretorio*) malloc(sizeof(Diretorio));
		dir->nome = nome;
		dir->numArqDir= 0;

		return dir;
}

Arquivo* alocarArquivo(char* nome, char tipo){

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
	if(strcmp(((Diretorio*)arvore->info)->nome, nome1) != 0)
	{
		if(arvore->filho != NULL)
		{
			busca(arvore->filho, nome1);
		}
		if(arvore->irmao != NULL)
		{
			busca(arvore->irmao, nome1);
		}
	}
	else
	{
		return arvore;
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

void* renomear(Arv* arvore, char* nome, char* novoNome,char* data, char* hora,char* noPai){
	Arv* noAux = busca(arvore,nome);
	Arv* noAux2 = busca(arvore,noPai);
	if(noAux == NULL || noAux2 == NULL){
		return NULL;
	}
	if(noAux->tipo == 1){
		(((Diretorio*)noAux->info)->nome) = novoNome;
		(((Diretorio*)noAux->info)->data) = data;
		(((Diretorio*)noAux->info)->hora) = hora;
	}
	
	if(noAux->tipo == 2){
		(((Arquivo*)noAux->info)->nome) = novoNome;
		(((Arquivo*)noAux->info)->data) = data;
		(((Arquivo*)noAux->info)->hora) = hora;
		(((Diretorio*)noAux2->info)->data) = data;
		(((Diretorio*)noAux2->info)->hora) = hora;
	}	
}

void* transformar(Arv* arvore, char tipo,char* data, char* hora,char* noPai,char* nome){
	Arv* noAux = busca(arvore,nome);
	Arv* noAux2 = busca(arvore,noPai);
	if(noAux == NULL || noAux == NULL){
		return NULL;
	}

	if( (((Arquivo*)noAux->info)->tipo) == tipo){
		printf("Arquivo ja e do tipo inserido.");
		return NULL;
	}

	else{	
		(((Arquivo*)noAux->info)->tipo) = tipo;
		(((Arquivo*)noAux->info)->data) = data;
		(((Arquivo*)noAux->info)->hora) = hora;
		(((Diretorio*)noAux2->info)->data) = data;
		(((Diretorio*)noAux2->info)->hora) = hora;
	}
}

Arv* find_the_father(Arv* raiz, char* filho){
	if(strcmp(typeof(raiz->info),"Diretorio") !=0)
		goto looknext;

	if(strcmp(raiz->filho->info->nome, filho))
		return raiz;
	else{
		Arv* aux1 = raiz->filho->irmao;
		while(aux1 != NULL){
			if(strcmp(aux1->info->nome, filho) == 0)
				return raiz;
			aux1 = aux1->irmao;
		}

		looknext:
		if(raiz->irmao != NULL){
			aux1 = find_the_father(raiz->irmao, filho);
			if(aux1 != NULL)
				return aux1;
		}

		if(strcmp(typeof(raiz->info),"Diretorio") == 0){
			if(raiz->filho != NULL){
				aux1 = find_the_father(raiz->filho, filho);
				if(aux1 != NULL)
					return aux1;
			}
		}
	}
	return NULL;
}

void mover(Arv* arvore, char* aam, char* dest){
	//aam -> nome do Arquivo A Mover
	//dest -> destinatario, precisa ser obrigatoriamente
	Arv* noAux = busca(arvore,aam);
	if(noAux == NULL){
		printf("Arquivo não encontrado.\n");
		return;
	}
	Arv* noAux2 = busca(arvore,dest);
	if(noAux2 == NULL){
		printf("Pasta-destino não encontrada.\n");
		return;
	}
	else if(strcmp(typeof(noAux2->info), "Diretorio") != 0){
		printf("Destinatário não é uma pasta.\n");
		return;
	}
	//proximo passo: se o AAM é diretorio, se o destinatario for subpasta de AAM, a ação é inválida
	if(strcmp(typeof(noAux->info), "Diretorio") == 0){
		if(noAux2 == busca(noAux->filho, dest)){
			printf("A ação a ser realizada é inválida, pois o destinatário é subpasta do diretório a ser movido.\n");
			return;
		}
	}
	//proximo passo: encontrar quem é o pai do AAM
	Arv* OPai = find_the_father(arvore, aam);
	if(OPai != NULL){
		if(OPai->filho == noAux){
			OPai->filho = noAux->irmao;
			noAux->irmao = NULL;
		}
		else{
			Arv* newAux = OPai->filho;
			while(newAux->irmao != noAux){
				newAux = newAux->irmao;
			}
			newAux->irmao = noAux->irmao;
			noAux->irmao = NULL;
		}
	}
	//o motivo dessa procura é poder ajustar devidamente a ordenação dos arquivos da pasta de onde foi retirado o AAM
	if(noAux2->filho == NULL){
		noAux2->filho = noAux;
	}
	else{
		Arv* bigAux = noAux2->filho;
		if(bigAux->irmao != NULL){
			while(bigAux->irmao != NULL){
				bigAux = bigAux->irmao;
			}
		}
		bigAux->irmao = noAux;
	}
}
