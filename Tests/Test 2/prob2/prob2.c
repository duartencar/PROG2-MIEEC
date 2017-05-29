#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "grafo.h"
#include "lista.h"

lista* descobre_caminho (grafo *g, int origem, int destino, int obrigatorio)
{
	/* prob 2.1 - a implementar */
	
	return NULL;
}

int simula_acontecimentos(lista *acoes, lista *tempos, int n)
{
    /* prob 2.2 - a implementar */    

    return 0;
}

/* Aqui começa o código de teste. Não modificar! */ 

int main()
{
	/* teste problema 2.1 */
	{
		grafo *g=NULL;
		lista *l=NULL;
		int i;

		printf("* Problema 2.1 *\n");

		g = grafo_novo(8, DIGRAFO);

		grafo_adiciona(g, 1, 3);
		grafo_adiciona(g, 2, 3);
		grafo_adiciona(g, 2, 4);
		grafo_adiciona(g, 2, 5);
		grafo_adiciona(g, 3, 2);
		grafo_adiciona(g, 3, 4);
		grafo_adiciona(g, 4, 6);
		grafo_adiciona(g, 4, 7);
		grafo_adiciona(g, 5, 4);
		grafo_adiciona(g, 5, 6);
		grafo_adiciona(g, 5, 7);
		grafo_adiciona(g, 6, 7);

		l = descobre_caminho (g, 1, 7, 5);

		printf("Descobre caminho - Inicio 1, Fim 7, Passando por 5\nCaminho: ");
		for(i=0; i<lista_tamanho(l); i++)
			printf("%s", lista_elemento(l, i));
		printf("\n\n");

		grafo_apaga(g);
		lista_apaga(l);
	}

	/* teste problema 2.2 */
	{
		FILE *f;
		char acao[21], tempo[5];
		lista *acoes, *tempos;
		
		printf("* Problema 2.2 *\n");

		f = fopen("acoes.txt", "r");
		acoes = lista_nova();
		tempos = lista_nova();

		while(fscanf(f, "%s %s", acao, tempo) == 2)
		{
			lista_insere(acoes, acao, -1);
			lista_insere(tempos, tempo, -1);
		}

		if(simula_acontecimentos(acoes, tempos, 4) == 0)
    		printf("Erro ao executar a funcao\n");

    	lista_apaga(acoes);
    	lista_apaga(tempos);
    	fclose(f);
	}

	return 0;
}
