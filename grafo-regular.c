#include <stdio.h>
#include <stdlib.h>

struct grafo
{
	int ordem;
	int **matriz;
};
typedef struct grafo Grafo;

Grafo *cria_grafo(int ordem);

void preenche_arestas(Grafo *g);
void mostra(Grafo *g);
int eh_regular(Grafo *g);

int main()
{
	Grafo *g = NULL;

	int N;
	scanf("%d", &N);

	g = cria_grafo(N);
	preenche_arestas(g);

	printf("%s\n", eh_regular(g) == 1 ? "sim" : "nao");

	return 0;
}

Grafo *cria_grafo(int ordem)
{
	Grafo *g = (Grafo *)malloc(sizeof(Grafo));

	if (g != NULL)
	{
		g->ordem = ordem;
		g->matriz = (int **)malloc(sizeof(int *) * ordem);
		for (int i = 0; i < ordem; i++)
		{
			g->matriz[i] = (int *)malloc(sizeof(int) * ordem);
			for (int j = 0; j < ordem; j++)
				g->matriz[i][j] = -1;
		}
	}

	return g;
}

void preenche_arestas(Grafo *g)
{
	for (int i = 0; i < g->ordem; i++)
		for (int j = 0; j < g->ordem; j++)
			scanf("%d", &g->matriz[i][j]);
}

void mostra(Grafo *g)
{
	for (int i = 0; i < g->ordem; i++)
	{
		for (int j = 0; j < g->ordem; j++)
			printf("%3d ", g->matriz[i][j]);
		printf("\n");
	}
}

int eh_regular(Grafo *g)
{
	int result = 1, qtd = 0;

	for (int i = 0; i < g->ordem; i++)
		if (g->matriz[0][i] == -1)
			qtd++;

	for (int i = 1; i < g->ordem && result; i++)
	{
		int qtdProx = 0;
		for (int j = 0; j < g->ordem && result; j++)
		{
			if (g->matriz[i][j] == -1)
				qtdProx++;
		}
		if (qtd != qtdProx)
			result = 0;
	}

	return result;
}
