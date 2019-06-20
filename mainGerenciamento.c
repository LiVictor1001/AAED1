	#include "gerenciamento.c"

int main(int argc, char const *argv[])
{
	
	FILE* arqDados = fopen("dados.txt","r");
	char nomeArqDir[101],nomePai[101], data[9], hora[6], hora[6], c;
	char barra, nomeArqBusca[30],nomeDestroi[30], arqdirtipo;
	int tam, numAcao, barra = 0;
	Diretorio* dir;
	Arquivo* arq;
	Arv *minhaArv;
    minhaArv = alocarDiretorio("raiz",0 ,01011969,23:59);
    criarNo(minhaArv);
	

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
					criarNo(dir);//cria um nó da árvore de diretório
					insereNo(dir, minhaArv, nomePai);

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
					
					arq = alocarArquivo(nomeArqDir, tam, data, hora);
					criarNo(arq);
					insereNo(arq, minhaArv, nomePai)

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

					arq = alocarArquivo(nomeArqDir, tam, data, hora);
					criarNo(arq);
					insereNo(arq, minhaArv, nomePai);
					
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
	
	printf("Bem vindo ao simulador de diretório\n\n1 - inserir\n");
    printf("2 - buscar\n3 - destruir\n");
    printf("4 - renomear\n5- transformar\n 6 - sair\n\n");
    while(exit != 1)
    {
        scanf("%d", numAcao);
        switch(numAcao)
        {
            //insere 
            case '1':
                scanf("%c", &c);
                scanf("%c", &barra);                
                scanf("%[^/]", nomeArqDir);
                scanf("%c", &barra);
                scanf("%[^/]", nomePai);
                scanf("%c", &barra);
                scanf("%d", &tam);
                scanf("%c", &barra);
                scanf("%[^/]", data);
                scanf("%c", &barra);
                scanf("%s", hora);
                    
                if(arqOUdir == 'D')
                {
                    dir = alocarDiretorio(nomeArqDir,tam,data,hora);//aloca memória para um diretório
					criarNo(dir);//cria um nó da árvore de diretório
					insereNo(dir, minhaArv, nomePai);
                }else
                {
                    arq = alocarArquivo(nomeArqDir, tam, data, hora);
                    criarNo(arq);
					insereNo(arq, minhaArv, nomePai);
                }
            case '2':
                printf("Digite o nome: ");
                scanf("%s", nomeArqBusca);
                printf("D ou A?");
                scanf("%s", arqdirtipo);
                
                if(arqdirtipo == 'D'){
                    Arv *NoBusca = busca(minhaArv, nomeArqBusca);
                    printf("%s", ((Diretorio*)Nobusca->info->nome));
                    printf("%s", ((Diretorio*)Nobusca->info->data));
                    printf("%s", ((Diretorio*)Nobusca->info->hora));
                    printf("%s", ((Diretorio*)Nobusca->info->numArqDir));
                }else{
                    Arv *NoBusca = busca(minhaArv, nomeArqBusca);
                    printf("%s", ((Arquivo*)Nobusca->info->nome));
                    printf("%s", ((Arquivo*)Nobusca->info->data));
                    printf("%s", ((Arquivo*)Nobusca->info->hora));
                    printf("%s", ((Arquivo*)Nobusca->info->numArqDir));
                }
            case '3':
                printf("Digite o nome: ");
                scanf("%s", nomeDestroi);
                destruir(busca(minhaArv, nomeDestroi));
            case '4':
        }
    }
}
