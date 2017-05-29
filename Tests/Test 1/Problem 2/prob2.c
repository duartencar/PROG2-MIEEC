#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "grafo.h"
#include "heap.h"

int proximas_n_chegadas(lista *tempos, lista *origens, lista *aeroportos, int n)
{
	if( n > 25 || tempos->tamanho == 0 || origens->tamanho == 0 || aeroportos->tamanho == 0 || n < 0 || tempos == NULL || origens == NULL || aeroportos == NULL)
		return 0;

	elemento *t, *o, *a;

	vetor *v;

	heap *h;

	h = heap_nova(25);

	v = vetor_novo();

	int i, k;

	for(i = 0, t = tempos->inicio, o = origens->inicio; i < h->tamanho_maximo; i++, t = t->proximo, o = o->proximo)
		heap_insere(h, o->str, atoi(t->str));

	for(i = 0; i < n; i++)
		vetor_insere(v,atoi(heap_remove(h)),0);

	for(i = n; i != 0; i--)
	{
		for(k = 0, a = aeroportos->inicio; k < v->elementos[i-1].val; k++)
				a = a->proximo;

		printf("%d: %s\n",n - (i-1), a->str);
	}

  return 1;
}

lista* pesquisa_destinos (grafo *rotas, lista *aeroportos, const char *origem)
{
	if(rotas == NULL || aeroportos == NULL || origem == NULL)
		return NULL;

	int i, k;

	elemento *a;

	vetor *suc;

	lista *su;

	su = lista_nova();

	for(i = 0, a = aeroportos->inicio; i < lista_tamanho(aeroportos); i++, a = a->proximo)
	{
		if(strcmp(a->str, origem) == 0)
		{
			suc = v_sucessores(rotas, i);

			break;
		}
	}

	for(i = 0; i < vetor_tamanho(suc); i++)
	{
		for(k = 0, a = aeroportos->inicio; k < suc->elementos[i].val; k++)
			a = a->proximo;

		lista_insere(su, a->str, NULL);
	}

	lista_ordena(su);

	vetor_apaga(suc);

	return su;
}

/* Aqui começa o código de teste. Não modificar! */

grafo* carrega_rotas (lista *aeroportos, const char *filename)
{
	if(!filename)
		return NULL;

	grafo* g = NULL;

	FILE *f;

	int origem, destino;

	f = fopen(filename, "r");

	if(!f)
	{
		printf("Erro na leitura do ficheiro: %s\n",filename);

		return NULL;
	}

	g = grafo_novo(lista_tamanho(aeroportos), NAODIRECIONADO);

	if(!g)
	{
		printf("Erro na criacao do grafo\n");

		return NULL;
	}

	while(fscanf(f, "%d\t%d", &origem, &destino) == 2)
		grafo_adiciona(g, origem, destino);

	fclose(f);

	return g;
}

int main()
{
	FILE *f;

	grafo *g = NULL;

	lista *aeroportos;

	char buff[50];

	size_t n;

	setvbuf(stdout, NULL, _IONBF, 0);

	f = fopen("aeroportos.txt", "r");

	aeroportos = lista_nova();

	n = 0;

	while(fgets(buff,50,f) != NULL)
	{
		buff[strlen(buff)-1]='\0';

		lista_insere(aeroportos,buff,NULL);
	}

	fclose(f);

	g = carrega_rotas(aeroportos, "rotas.txt");

	/* teste problema 2.1 */
	{
		FILE *f;

		char tempo[5], origem[10];

		lista *tempos, *origens;

		printf("* Problema 2.1 *\n");

		f = fopen("chegadas.txt", "r");

		tempos = lista_nova();

		origens = lista_nova();

		while(fscanf(f, "%s\t%s", tempo, origem) == 2)
		{
			lista_insere(tempos, tempo, NULL);

			lista_insere(origens, origem, NULL);
		}

		if(proximas_n_chegadas(tempos, origens, aeroportos, 5) != 1)
    		printf("Erro ao executar a funcao\n");

    lista_apaga(tempos);

		lista_apaga(origens);

		fclose(f);
	}

	/* teste problema 2.2 */
	{
		printf("\n* Problema 2.2 *\n");

		const char *origem = "Lille (FR)";

		elemento *elem;

		lista *l = pesquisa_destinos(g, aeroportos, origem);

		if(l == NULL)
			printf("Destinos diretos a partir de %s = 0\n", origem);
		else
		{
			printf("Destinos diretos a partir de %s = %d\n", origem, lista_tamanho(l));

			for(elem=l->inicio;elem!=NULL;elem=elem->proximo)
				printf("%s\n",elem->str);

			lista_apaga(l);
		}
	}

	grafo_apaga(g);

	lista_apaga(aeroportos);

	return 0;
}
