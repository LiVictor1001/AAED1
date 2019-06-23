#include "gerenciamento.c"
#include <ctype.h>

int main(int argc, char const *argv[])
{
	
	FILE* arqDados = fopen("dados.txt","r");
	
	if(arqDados == NULL){
		printf("Erro ao abrir o arquivo\n");
		exit(1);
	}

	char* nomeArqDir, *nomePai, *tam, *dataCriacao, *horaCriacao, *dataModificacao, *horaModificacao; 

	char c;
	
	int barra = 0;

	Arv* minhaArv;
	
	Diretorio* dir;
	Arquivo* arq;
	
	char tamTotalArq[501];
	
	while(!feof(arqDados)){

		c = fgetc(arqDados);
		
		if(c == '/') barra++;
			
		if(c == '\n') barra = 0;	 

		if(c != '\n' && barra == 0){
			switch(c){
				case 'D':
					fgets(tamTotalArq,500,arqDados);

					nomeArqDir = strtok(tamTotalArq,"/ \0");//strtok separa a string com / e \0 de tamTotalArq
					nomePai = strtok(NULL,"/ \0");//NULL porque é pra continuar na mesma string
					tam = strtok(NULL,"/ \0");
					dataCriacao = strtok(NULL,"/ \0");
					horaCriacao = strtok(NULL,"/ \0");
					
					//tokenAux = atoi(tokenTam); ou (int) *tokenTam-48;
					
					dir = alocarDiretorio(nomeArqDir,atoi(tam),dataCriacao,horaCriacao);//aloca memória para um diretório
					minhaArv = criarNo(dir);//cria um nó da árvore de diretório

					/*printf("Nome do Diretório %s\n",((Diretorio*) minhaArv->info)->nome);
					printf("Nome do Pai %s\n",nomePai);
					printf("Quantidade de arquivos ou diretórios %d\n",((Diretorio*) minhaArv->info)->numArqDir);
					printf("Data %s\n",((Diretorio*) minhaArv->info)->dataCriacao);
					printf("Hora %s\n",((Diretorio*) minhaArv->info)->horaCriacao);*/
					

					break;
				case 'T':
					fgets(tamTotalArq,500,arqDados);

					nomeArqDir = strtok(tamTotalArq,"/ \0");
					nomePai = strtok(NULL,"/ \0");
					tam = strtok(NULL,"/ \0 ");
					dataCriacao = strtok(NULL,"/ \0");
					horaCriacao = strtok(NULL,"/ \0");

					arq = alocarArquivo(nomeArqDir,'T',atoi(tam),dataCriacao,horaCriacao);//aloca memória para um arquivo
					minhaArv = criarNo(arq);//cria um nó da árvore de arquivo texto

					/*printf("Nome do Arquivo %s\n",((Arquivo*) minhaArv->info)->nome);
					printf("Nome do Pai %s\n",nomePai);
					printf("Tipo %c\n",((Arquivo*) minhaArv->info)->tipo);
					printf("Tam %d\n",((Arquivo*) minhaArv->info)->tam);
					printf("Data %s\n",((Arquivo*) minhaArv->info)->dataCriacao);
					printf("Hora %s\n",((Arquivo*) minhaArv->info)->horaCriacao);*/
					
					break;
				case 'B':
					fgets(tamTotalArq,500,arqDados);

					nomeArqDir = strtok(tamTotalArq,"/ \0 \n");
					nomePai = strtok(NULL,"/ \0 \n");
					tam = strtok(NULL,"/ \0 \n");
					dataCriacao = strtok(NULL,"/ \0 \n");
					horaCriacao = strtok(NULL,"/ \0 \n");

					arq = alocarArquivo(nomeArqDir,'B',atoi(tam),dataCriacao,horaCriacao);//aloca memória para um arquivo
					minhaArv = criarNo(arq);//cria um nó da árvore de arquivo binário

					/*printf("Nome do Arquivo %s\n",((Arquivo*) minhaArv->info)->nome);
					printf("Nome do Pai %s\n",nomePai);
					printf("Tipo %c\n",((Arquivo*) minhaArv->info)->tipo);
					printf("Tam %d\n",((Arquivo*) minhaArv->info)->tam);
					printf("Data %s\n",((Arquivo*) minhaArv->info)->dataCriacao);
					printf("Hora %s\n",((Arquivo*) minhaArv->info)->horaCriacao);*/

					break;
				default:
					if(!(c == EOF)){//se não chegou ao fim do arquivo e é nenhum dos caracteres anteriores então
						printf("Caracter não permitido\n");
						exit(1);
					}
			}
		}		
	}

	fclose(arqDados);

	//Começa a interface com o usuário
	
	char numAcao;//Variável que recebe a opção desejada pelo usuário
	//dados do inserir
	char auxNumAcao[3];//Variável auxiliar para verificar caracteres com qtds maiores que 1 e que contém um número do menu como 1º símbolo
	char strInserir[101];//Para receber o que foi digitado na tela
	char* arqDir;//Tipo da inserção se é D, T, B

	printf("---------- Bem-vindo ao simulador de diretório ----------");
	
	while(1){	
    	inicio:
	        apresentacao();
			
			scanf("%[^\n]",auxNumAcao);//lê a linha com \n
			setbuf(stdin,NULL);//limpa o buffer do teclado
			
			
		if(strlen(auxNumAcao) > 1){//Se o que foi digitado é maior que 1 volta para o menu
			goto inicio;
		}else{
			
			numAcao = auxNumAcao[0]; //numAcao recebe o primeiro caracter de auxNumAcao

			if(isdigit(numAcao)){//É número?
				if((numAcao < '0' || numAcao > '6')){//Se for menor que 0 e maior que 6
					goto inicio;
				}else{
						
					if(numAcao == '6'){//6 é pra sair do programa
    					exit(1);
   					}

   					switch(numAcao){
			            //insere 
			            case '1':
			            	
			            	digitarCaminho:
				            	printf("Digite o caminho (Tipo, nome, nome do pai e tamanho): ");
				                fgets(strInserir,101,stdin);
				           		setbuf(stdin,NULL);

			                arqDir = strtok(strInserir,"/ \0");
			                nomeArqDir = strtok(NULL,"/ \0");
							nomePai = strtok(NULL,"/ \0");
							tam = strtok(NULL,"/ \0");
							dataCriacao = strtok(NULL,"/ \0");
							horaCriacao = strtok(NULL,"/ \0");

							time_t min;//variavel do tipo time_t para armazenar o tempo em minutos
							time(&min);//obtém o tempo em minutos

							char dataCriacao[9] = {0};
							char horaCriacao[6] = {0};
							
							//Pegar dia mes e ano
							char day[3], month[3], year[5];
							char hour[3], minuto[3];

							data_hora_atual = localtime(&min);//converte minutos para o tempo local
							
							//função snprintf() transforma int para string
							//pega a hora e minuto em inteiro e transforma pra string
							snprintf(hour,3,"%d",data_hora_atual->tm_hour);
							snprintf(minuto,3,"%d",data_hora_atual->tm_min);

							//concatena a hora com os minutos
							strcat(horaCriacao,hour);
							strcat(horaCriacao,":");
							strcat(horaCriacao,minuto);
							printf("horaCriacao %s\n",horaCriacao);
							//pega o dia o mês e o ano e transforma para string
							snprintf(day,3,"%d",data_hora_atual->tm_mday);
							snprintf(month,3,"%d",data_hora_atual->tm_mon+1);
							snprintf(year,5,"%d",data_hora_atual->tm_year+1900);
							
							//concatena a data com mês e ano
							strcat(dataCriacao,day);
							strcat(dataCriacao,month);
							strcat(dataCriacao,year);

							if(arqDir == NULL || nomeArqDir == NULL || nomePai == NULL || tam == NULL){
								printf("Caminho incompleto, tente novamente.\n");
								goto digitarCaminho;
							}

							switch(*arqDir){
								case 'D':
									dir = alocarDiretorio(nomeArqDir,atoi(tam),dataCriacao,horaCriacao);
									minhaArv = criarNo(dir);
									
									if(minhaArv != NULL) printf("Inserido com sucesso!\n");
									
								break;
								case 'T':
									arq = alocarArquivo(nomeArqDir,'T',atoi(tam),dataCriacao,horaCriacao);//aloca memória para um arquivo
									minhaArv = criarNo(arq);
									
									if(minhaArv != NULL) printf("Inserido com sucesso!\n");

								break;
								case 'B':
									arq = alocarArquivo(nomeArqDir,'B',atoi(tam),dataCriacao,horaCriacao);
									minhaArv = criarNo(arq);

									if(minhaArv != NULL) printf("Inserido com sucesso!\n");
									
								break;
								default:
									printf("Caracter não permitido\n");
							}
			            break;
			            default:
			            	printf("caracter não permitido\n");
			        }
				}
			}		
		}
	}
			

	return 0;
}