#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "tabdispersao.h"

#define LIMITE 55000

// #include & #define
// functions and procedures

void guarda_palavra(tabela_dispersao *tab, char *str)
{
	char aux[100];
	int i=0, j=0;	

	for(i=0; str[i]!='\0'; i++)
	{
		if((str[i]<'a' || str[i]>'z') && str[i]!='\'')
		{
			if(str[i]>='A' && str[i]<='Z')
			{
				aux[j]=tolower(str[i]);
				j++;
			}
			else
			{
				aux[j]='\0';
				tabela_adiciona(tab, aux, aux);
				j=0;
			}
		}
		else
		{
			aux[j]=str[i];
			j++;
		}
	}

	aux[j]='\0';
	tabela_adiciona(tab, aux, aux);
}

void imprime_sugestoes(tabela_dispersao* tab, char* str, long int* sugestoes)
{
	int i=0, a=0, b=0, c=1, d=1, j=0;
	elemento* e;	

	printf("Word not found: %s\n", str);

	printf("Perhaps you meant: ");
	for(e=tab->elementos[hash_djbm(str, tab->tamanho)]; e!=NULL; e=e->proximo)
	{
		if(strlen(e->obj->valor)==strlen(str))
		{
			for(i=0; e->obj->valor[i]!='\0'; i++)
			{
				a+=(int) str[i];
				b+=(int) e->obj->chave[i];
				c*=(int) str[i];
				d*=(int) e->obj->chave[i];
			}
			if(b==a && c==d)
			{
				for(i=0; str[i]!='\0'; i++)
				{
					if(str[i]!=e->obj->valor[i])
						j++;
				}
				if(j==2)
				{
					*sugestoes=*sugestoes+1;
					printf("%s ", e->obj->valor);
				}		
			}
			a=0;
			b=0;
			c=1;
			d=1;
			j=0;
		}
	}
	printf("\n");
}

void resultados(tabela_dispersao* tab, char* str, long int* sugestoes)
{
	int i=0, a=0, b=0, c=1, d=1, j=0;
	elemento* e;	

	for(e=tab->elementos[hash_djbm(str, tab->tamanho)]; e!=NULL; e=e->proximo)
	{
		if(strlen(e->obj->valor)==strlen(str))
		{
			for(i=0; e->obj->valor[i]!='\0'; i++)
			{
				a+=(int) str[i];
				b+=(int) e->obj->chave[i];
				c*=(int) str[i];
				d*=(int) e->obj->chave[i];
			}
			if(b==a && c==d)
			{
				for(i=0; str[i]!='\0'; i++)
				{
					if(str[i]!=e->obj->valor[i])
						j++;
				}
				if(j==2)
				{
					*sugestoes=*sugestoes+1;
				}
			}
			a=0;
			b=0;
			c=1;
			d=1;
			j=0;
		}
	}
}

int main(int argc, char* argv[])
{
	FILE *input, *wordlist;
	clock_t inicio, fim;
  	double tempo;
	long int erros=0, sugestoes=0;
	tabela_dispersao *tab;
	char palavra[10000], aux[1000];
	int i=0, j=0, k=0;

	if(argc != 3)
	{
		printf("utilização: %s <nome_ficheiro> <modo>\n", argv[0]);
		printf("modo: verboso ou silencioso\n");
		return 1;
	}

	// processa lista de palavras
	wordlist = fopen("wordlist.txt", "r");
	if(!wordlist)
	{
		printf("erro ao abrir ficheiro com lista de palavras\n");
		return 2;
	}
	
	tab=tabela_nova(LIMITE, hash_djbm);

	if(!tab)
	{
		printf("erro ao criar lista de palavras");
		return 5;
	}
	tabela_adiciona(tab, "\0", "\0");
	
	// armazena lista de palavras em estrutura de dados adequada
	while(fscanf(wordlist, "%s", palavra)!=EOF)
	{
		guarda_palavra(tab, palavra);
	}
	// processa ficheiro de entrada
	input = fopen(argv[1], "r");
	if(!input)
	{
		printf("erro ao abrir ficheiro %s\n", argv[1]);
		return 3;
	}
	inicio = clock();
	if(!strcmp(argv[2],"verboso")){

		while((palavra[k]=fgetc(input))!=EOF)
		{	
			if(palavra[k]=='\n')
			{
				palavra[k]=' ';
				palavra[k+1]='\0';
				if(k!=1)
				{
					printf("\n");
					printf("%s\n", palavra);
					k=0;

					for(i=0; palavra[i]!='\0'; i++)
					{
						if((palavra[i]<'a' || palavra[i]>'z') && palavra[i]!='\'')
						{
							if(palavra[i]>='A' && palavra[i]<='Z')
							{
								aux[j]=tolower(palavra[i]);
								j++;
							}
							else
							{
								aux[j]='\0';
								if((tabela_existe(tab, aux))==TABDISPERSAO_NAOEXISTE)
								{
									imprime_sugestoes(tab, aux, &sugestoes);
									erros++;
								}
								j=0;
							}
						}	
						else
						{
							aux[j]=palavra[i];
							j++;
						}
					}
				}
			}
			else if(palavra[k]=='.'||palavra[k]=='?'||palavra[k]=='!'||palavra[k]==';'||palavra[k]=='\0')
			{
				printf("\n");
				palavra[k+1]='\0';
				printf("%s\n", palavra);
				k=0;	
			
				for(i=0; palavra[i]!='\0'; i++)
				{
					if((palavra[i]<'a' || palavra[i]>'z') && palavra[i]!='\'')
					{
						if(palavra[i]>='A' && palavra[i]<='Z')
						{
							aux[j]=tolower(palavra[i]);
							j++;
						}
						else
						{
							aux[j]='\0';
							if((strchr(aux, '\'')!=NULL) && j==1)
								aux[j-1]='\0';
							if((tabela_existe(tab, aux))==TABDISPERSAO_NAOEXISTE)
							{
								imprime_sugestoes(tab, aux, &sugestoes);
								erros++;
							}
							j=0;
						}
					}
					else
					{
						aux[j]=palavra[i];
						j++;
					}
				}
			}
			else
				k++;
		}

	}
	else if(!strcmp(argv[2],"silencioso")){

		while((palavra[k]=fgetc(input))!=EOF)
		{	
			if(palavra[k]=='\n')
			{
				palavra[k]=' ';
				palavra[k+1]='\0';
				if(k!=1)
				{
					k=0;

					for(i=0; palavra[i]!='\0'; i++)
					{
						if((palavra[i]<'a' || palavra[i]>'z') && palavra[i]!='\'')
						{
							if(palavra[i]>='A' && palavra[i]<='Z')
							{
								aux[j]=tolower(palavra[i]);
								j++;
							}
							else
							{
								aux[j]='\0';
								if((tabela_existe(tab, aux))==TABDISPERSAO_NAOEXISTE)
								{
									resultados(tab, aux, &sugestoes);
									erros++;
								}
								j=0;
							}
						}	
						else
						{
							aux[j]=palavra[i];
							j++;
						}
					}
				}
			}
			else if(palavra[k]=='.'||palavra[k]=='?'||palavra[k]=='!' || palavra[k] == ';' || palavra[k]=='\0')
			{
				palavra[k+1]='\0';
				k=0;	
			
				for(i=0; palavra[i]!='\0'; i++)
				{
					if((palavra[i]<'a' || palavra[i]>'z') && palavra[i]!='\'')
					{
						if(palavra[i]>='A' && palavra[i]<='Z')
						{
							aux[j]=tolower(palavra[i]);
							j++;
						}
						else
						{
							aux[j]='\0';
							if((strchr(aux, '\'')!=NULL) && j==1)
								aux[j-1]='\0';
							if((tabela_existe(tab, aux))==TABDISPERSAO_NAOEXISTE)
							{
								resultados(tab, aux, &sugestoes);
								erros++;
							}
							j=0;
						}
					}
					else
					{
						aux[j]=palavra[i];
						j++;
					}
				}
			}
			else
				k++;
		}
	} 
	
	else{
		printf("modo %s desconhecido\n", argv[2]);
		return 4;
	}
	fim = clock();
	printf("\n");
	tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
	printf("Tempo gasto na verificação (em segundos): %lf\n", tempo);
	printf("Número de palavras com ortografia errada encontradas: %li\n", erros);
	printf("Número de sugestões efetuadas: %li\n", sugestoes);

	fclose(input);
	fclose(wordlist);
	return 0;
}
