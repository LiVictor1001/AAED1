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

void stringcpy(char* destino, char* origem){
    int i = 0,j=0;
    for(i=0;origem[i] != '\0';i++){
        destino[i] = origem[i];
    }
	destino[i] = '\0';
}

char* ret_name(Arv* no){
	if(strcmp(typeof(no->info), "Diretorio") == 0)
		return ((Diretorio*)no->info)->nome;
	else
		return ((Arquivo*)no->info)->nome;
}

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

Diretorio* alocarDiretorio(char* nome,int tam,char* data, char* hora){
		
		Diretorio* dir;
		dir = (Diretorio*)malloc(sizeof(Diretorio));
		stringcpy(dir->nome, nome);
		stringcpy(dir->data, data);
		stringcpy(dir->hora, hora);
		stringcpy(dir->dataModificacao, "00000000");
		stringcpy(dir->horaModificacao, "00:00");
		dir->numArqDir = tam;
		return dir;
}

Arquivo* alocarArquivo(char* nome, char tipo, int tam, char* data, char* hora){

		Arquivo* arq;

		arq = (Arquivo*) malloc(sizeof(Arquivo));
		stringcpy(arq->nome, nome);
		stringcpy(arq->data, data);
		stringcpy(arq->hora, hora);
		stringcpy(arq->dataModificacao, "00000000");
		stringcpy(arq->horaModificacao, "00:00");
		arq->tipo = tipo;
		arq->tam = tam;


		return arq;
}

Arv* criarNo(void* val,int tipo){

	Arv* novo = (Arv*) malloc(sizeof(Arv));
	novo->filho = NULL;
	novo->irmao = NULL;
	novo->info = val;
	novo->tipo = tipo;

	return novo;
}

Arv* busca(Arv* arvore, char* nome1)
{
	if(qual_tipo(arvore->tipo) == 0){
		if(strcmp(((Diretorio*)arvore->info)->nome, nome1) != 0 )
		{
			if(arvore->filho != NULL)
			{
				return busca(arvore->filho, nome1);
			}
			if(arvore->irmao != NULL)
			{
				return busca(arvore->irmao, nome1);
			}
		}
		else if(strcmp(((Diretorio*)arvore->info)->nome, nome1) == 0)
		{
			return arvore;
		}

	}
	
	if(qual_tipo(arvore->tipo) == 1 || qual_tipo(arvore->tipo) == 2){
		if(strcmp(((Arquivo*)arvore->info)->nome, nome1) != 0 )
		{
			if(arvore->filho != NULL)
			{
				return busca(arvore->filho, nome1);
			}
			if(arvore->irmao != NULL)
			{
				return busca(arvore->irmao, nome1);
			}
		}
		else if(strcmp(((Arquivo*)arvore->info)->nome, nome1) == 0)
		{
			return arvore;
		}
	}

	return NULL;
}

Arv* find_the_father(Arv* raiz, char* filho){
	if(strcmp(typeof(raiz->info),"Diretorio") !=0)
		goto looknext;

	if(strcmp(ret_name(raiz->filho), filho) == 0)
		return raiz;
	else{
		Arv* aux1 = raiz->filho->irmao;
		while(aux1 != NULL){
			if(strcmp(ret_name(aux1), filho) == 0)
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

void insereNo(Arv* noEntrada, Arv* arvore, char* pai){
    Arv* noPai = busca(arvore, pai);
    Arv* noAux;

    if(noPai->filho != NULL){
        noAux = noPai->filho;
        
		while(noAux->irmao){
            noAux = noAux->irmao;
        }
        noAux->irmao = noEntrada;

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

	if(qual_tipo(arvore->tipo) == 0){
		stringcpy((((Diretorio*)noAux->info)->nome), novoNome);
		stringcpy((((Diretorio*)noAux->info)->dataModificacao), data);
		stringcpy((((Diretorio*)noAux->info)->horaModificacao), hora);
	}
	
	if(qual_tipo(arvore->tipo) == 1 || qual_tipo(arvore->tipo) == 2){
		stringcpy((((Arquivo*)noAux->info)->nome), novoNome);
		stringcpy((((Arquivo*)noAux->info)->dataModificacao), data);
		stringcpy((((Arquivo*)noAux->info)->horaModificacao), hora);
		stringcpy((((Diretorio*)noAux2->info)->dataModificacao), data);
		stringcpy((((Diretorio*)noAux2->info)->horaModificacao), hora);
	}	
}

void* transformar(Arv* arvore, char tipo,char* data, char* hora,char* noPai,char* nome){
	Arv* noAux = busca(arvore,nome);
	Arv* noAux2 = busca(arvore,noPai);
	if(noAux == NULL && noAux == NULL){
		return NULL;
	}

	if( (((Arquivo*)noAux->info)->tipo) == tipo){
		printf("Arquivo ja e do tipo inserido.");
		return NULL;
	}

	else{
		int i = 0;
		while( (((Arquivo*)noAux->info)->nome)[i] != '.'){
			i++;
		}
		if(tipo == 'T'){
			(((Arquivo*)noAux->info)->nome)[i+2] = 't';
			(((Arquivo*)noAux->info)->nome)[i+4] = 't';
		}

		if(tipo == 'B'){
			(((Arquivo*)noAux->info)->nome)[i+2] = 'e';
			(((Arquivo*)noAux->info)->nome)[i+4] = 'e';
		}

		(((Arquivo*)noAux->info)->tipo) = tipo;
		stringcpy((((Arquivo*)noAux->info)->data), data);
		stringcpy((((Arquivo*)noAux->info)->hora), hora);
		stringcpy((((Diretorio*)noAux2->info)->data), data);
		stringcpy((((Diretorio*)noAux2->info)->hora), hora);
	}
}



void mover(Arv* arvore, char* aam, char* pai, char* dest){
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
	else if(strcmp(typeof(noAux2->info), "Diretorio") == 0){
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
	Arv* OPai = busca(arvore, pai);
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

void destruir(Arv* no,char c,char* nome, char* pai){

	if(c == '1'){   //destruir toda a árvore
		apagar(no);
		no = NULL;
	}
	
	else if(c == '2' || c == '3'){  // destruir um diretorio ou um arquivo
		Arv* noAux = busca(no,nome);
		Arv* noAux2 = busca(no,pai);
		if( strcmp(ret_name(noAux2->filho), nome) == 0){
			noAux2->filho = noAux->irmao;
			noAux->irmao = NULL;
		}

		else{
			Arv* noAux3 = noAux2->filho;
			while(noAux3->irmao != noAux){
				noAux3 = noAux3->irmao;
			}

			noAux3->irmao = noAux->irmao;
			noAux->irmao = NULL;
		}
		if(c == '2'){
			apagar(noAux);
		}
		if(c == '3'){
			free(noAux);
		}
	}

}

void apagar(Arv* no){

	if(no->filho != NULL){
		apagar(no->filho);
	}

	if(no->irmao != NULL){
		apagar(no->irmao);
	}

	free(no);
}

void imprimir(Arv* a){
    printf("<");
    if(qual_tipo(a->tipo) == 0){	

        printf("%s",((Diretorio*)a->info)->nome);

    }
    else if(qual_tipo(a->tipo) == 1 || qual_tipo(a->tipo) == 2){	

        printf("%s",((Arquivo*)a->info)->nome);
    }

    Arv* aux = a->filho;

    while(aux != NULL){
        imprimir(aux);
        aux = aux->irmao;
    }

    printf(">");
}

void apresentacao(void){
	
	printf("\nSelecione uma opção:\n");
	printf("1 - Inserir\n");
	printf("2 - Excluir\n");
	printf("3 - Buscar\n");
	printf("4 - Renomear\n");
	printf("5 - Transformar de um tipo para outro\n");
	printf("6 - Sair\n");

}