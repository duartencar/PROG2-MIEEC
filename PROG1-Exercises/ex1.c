#include <stdio.h>

#define MAXIMO_NUMERO_DE_ACESSOS 100

int ler_tempos(int *tempos)
{
  FILE *input;

  int entrada;
  int saida;
  int entradaAnterior;
  int saidaAnterior;
  int acessos = 1;

  input = fopen("dados.txt", "r");

  fscanf(input, "%d %d", &entradaAnterior, &saidaAnterior);

  tempos[0] = saidaAnterior - entradaAnterior; //primeiro acesso

  //enquanto ler dois valores
  while(fscanf(input, "%d %d", &entrada, &saida) == 2)
  {
    //printf("entrada = %d e saida= %d\n", entrada, saida);

    //printf("Durou %d segundos\n", entrada - saidaAnterior);

    //Se a diferença entre os tempos for menor que 120 s, nao se incrementa
    // os acessos e adiciona-se o tempo de estacionamento ao tempo anterior
    // (poderá haver formas melhores de fazer isto)
    if(entrada - saidaAnterior < 120)
    {
      printf("Tempo inferior a 2 minutos. Não será considerado acesso.\n");

      // vamos ao indice do estacionamento anterior e adicionamos este tempo
      tempos[acessos - 1] = saida - entrada;

      entradaAnterior = entrada;

      saidaAnterior = saida;
    }
    else
    {
      tempos[acessos] = saida - entrada;

      acessos++;

      entradaAnterior = entrada;

      saidaAnterior = saida;
    }

    //printf("Acessos: %d\n", acessos);
  }

  return acessos;
}

void stats(int *tempos, int n, int *min, int *max, float *med)
{
  // int i;
  //
  // printf(" %d valores\n", n);
  //
  // for(i = 0; i < n - 2; i++)
  //   printf("%d\n", tempos[i]);
  //
  // int minimo;// = tempos[0]; //Serve apenas para termos valores com que comparar
  //
  // int maximo;// = tempos[0]; //podemos começar por i = 1
  //
  //
  //
  // printf("%d %d", minimo, maximo);
  //
  // printf("calcular");
  //
  // float total = 0;
  //
  // // for(i = 1; i < n; i++)
  // // {
  // //   total += tempos[i]; //adicionamos o tempo tomado para depois calcular a media
  // //
  // //   if(tempos[i] < *min)
  // //     *min = tempos[i];
  // //   else if(tempos[i] > *max)
  // //     *max = tempos[i];
  // //   else
  // //     continue;
  // // }
  //
  //
  // min = &tempos[0];
  // max = &tempos[0];
  // *med = total / n;
}

int main()
{
  //Vetor de duas dimensões com espaço para 100 acessos.
  //tem dois índices para guardar uma entrada e uma saída.
  int t[MAXIMO_NUMERO_DE_ACESSOS];

  int numeroDeAcessos;
  int *minimo, *maximo;
  float *media;

  numeroDeAcessos = ler_tempos(t);

  int i = 0;

  printf("Número de acessos: %d\n", numeroDeAcessos);

  for(i = 0; i < numeroDeAcessos; i++)
    printf("%d\n", t[i]);

  stats(t, numeroDeAcessos, minimo, maximo, media);

  //printf("Min: %d | Max: %d | Med: %f", *minimo, *maximo, *media);

  return 0;
}
