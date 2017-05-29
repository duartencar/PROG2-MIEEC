#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "tabdispersao.h"
#include "lista.h"

void avl_imprime_ord(arvore_avl* avl, int ordem)
{
	if(avl == NULL)
		return;

	arvore_avl *b = avl_nova();

	if(ordem >= 0)
		for(b->raiz = avl->raiz; b->raiz != NULL; avl_remove(b, avl_min(b->raiz)))
			printf("%s ", avl_min(b->raiz));

	else
		for(b->raiz = avl->raiz; b->raiz != NULL; avl_remove(b, avl_max(b->raiz)))
			printf("%s ", avl_max(b->raiz));
}

void valida_passwds(FILE *f, lista *login, lista *passwd)
{
	if(f == NULL || login == NULL || passwd == NULL)
		return;

	char log[26], pw[26];

	elemento *l, *p;

	tabela_dispersao *a = tabela_nova(10, hash_djbm);

	while(fscanf(f, "%s %s", log, pw) == 2)
		tabela_adiciona(a, log, pw);

	for(l = login->inicio, p = passwd->inicio; l != NULL || p != NULL; l = l->proximo, p = p->proximo)
	{
		printf("Login: %s\n", l->str);

		printf("Password: %s\n", p->str);

		if(strcmp(tabela_valor(a, l->str), p->str) == 0)
			printf("Authentication succeeded\n");

		else
			printf("Authentication failed\n");
	}
}
/* Aqui começa o código de teste. Não modificar! */

int main()
{
	/* teste problema 1.1 */
	{
		arvore_avl *res;

		int i;

		char data[][4] = {"ENG", "BEL", "NED", "GER", "FRA", "RUS", "SUI", "CRO", "BIH", "ITA", "ESP", "POR", "GRE"};

		printf("* Problema 1.1 *\n");

		res = avl_nova();

		for(i = 0; i < 13; i++)
      avl_insere(res, data[i]);

		printf("Arvore original: ");

		avl_imprime(res->raiz);

		printf("Ordem alfabetica crescente: ");

		avl_imprime_ord(res, 1);

		printf("\n\n");
	}

	/* teste problema 1.2 */
	{
		FILE *f;

		lista *lg, *psswd;

		int i;

		char login[][TAMANHO_VALOR] = {"maria", "tiago", "ricardo"};

		char password[][TAMANHO_CHAVE] = {"contrary", "contrary", "sheeplost"};

		printf("* Problema 1.2 *\n");

		f = fopen("passwords.txt", "r");

		if (!f)
		{
			printf("Nao foi possivel abrir ficheiro!\n");

			return -1;
		}

		lg = lista_nova();

		for(i=0; i<3; i++)
			lista_insere(lg, login[i], NULL);

		psswd = lista_nova();

		for(i=0; i<3; i++)
			lista_insere(psswd, password[i], NULL);

		valida_passwds(f, lg, psswd);

		lista_apaga(lg);

		lista_apaga(psswd);

		fclose(f);
	}

	return 0;
}
