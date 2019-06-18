#include "gerenciamento.c"

int main(int argc, char const *argv[])
{
	
	FILE* arqDados = fopen("dados.txt","r");
	char nomeArqDir[101],nomePai[101];
	int tam;
	char data[9];
	char hora[6];

	char c;
	
	int barra = 0;

	Arv* minhaArv;
	
	Diretorio* dir;
	Arquivo* arq;
	

	while(!feof(arqDados)){

		c = fgetc(arqDados);
		
		if(c == '/') barra++;
			
		if(c == '\n') barra = 0;	 

		if(c != '\n' && barra == 0){
			switch(c){
				case 'D':
					printf("------- DIRETÓRIO --------\n");
					fseek(arqDados,+1,SEEK_CUR);
					fscanf(arqDados,"%[^/]",nomeArqDir);
					fseek(arqDados,+1,SEEK_CUR);
					fscanf(arqDados,"%[^/]",nomePai);
					fseek(arqDados,+1,SEEK_CUR);
					fscanf(arqDados,"%d[^/]",&tam);
					fseek(arqDados,+1,SEEK_CUR);
					fscanf(arqDados,"%[^/]",data);
					fseek(arqDados,+1,SEEK_CUR);
					fscanf(arqDados,"%[^\n]",hora);
					fseek(arqDados,+1,SEEK_CUR);
					
					

					dir = alocarDiretorio(nomeArqDir,tam,data,hora);//aloca memória para um diretório
					minhaArv = criarNo(dir);//cria um nó da árvore de diretório
					printf("Nome do Diretório %s\n",((Diretorio*) minhaArv->info)->nome);
					printf("Nome do Pai %s\n",nomePai);
					printf("Quantidade de arquivos ou diretórios %d\n",((Diretorio*) minhaArv->info)->numArqDir);
					printf("Data %s\n",((Diretorio*) minhaArv->info)->data);
					printf("Hora %s\n",((Diretorio*) minhaArv->info)->hora);
					break;
				case 'T':
					printf("------- ARQUIVO --------\n");
					fseek(arqDados,+1,SEEK_CUR);
					fscanf(arqDados,"%[^/]",nomeArqDir);
					fseek(arqDados,+1,SEEK_CUR);
					fscanf(arqDados,"%[^/]",nomePai);
					fseek(arqDados,+1,SEEK_CUR);
					fscanf(arqDados,"%d[^/]",&tam);
					fseek(arqDados,+1,SEEK_CUR);
					fscanf(arqDados,"%[^/]",data);
					fseek(arqDados,+1,SEEK_CUR);
					fscanf(arqDados,"%[^\n]",hora);
					fseek(arqDados,+1,SEEK_CUR);
					
					printf("%s\n",nomeArqDir);
					printf("%s\n",nomePai);
					printf("%d\n",tam);
					printf("%s\n",data);
					printf("%s\n",hora);

					
					break;
				case 'B':
					printf("------- ARQUIVO --------\n");
					fseek(arqDados,+1,SEEK_CUR);
					fscanf(arqDados,"%[^/]",nomeArqDir);
					fseek(arqDados,+1,SEEK_CUR);
					fscanf(arqDados,"%[^/]",nomePai);
					fseek(arqDados,+1,SEEK_CUR);
					fscanf(arqDados,"%d[^/]",&tam);
					fseek(arqDados,+1,SEEK_CUR);
					fscanf(arqDados,"%[^/]",data);
					fseek(arqDados,+1,SEEK_CUR);
					fscanf(arqDados,"%[^\n]",hora);
					fseek(arqDados,+1,SEEK_CUR);
					
					printf("%s\n",nomeArqDir);
					printf("%s\n",nomePai);
					printf("%d\n",tam);
					printf("%s\n",data);
					printf("%s\n",hora);


					break;
				default:
					printf("Why?\n");
			}
		}
}