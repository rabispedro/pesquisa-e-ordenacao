#include <stdio.h>
#include <stdlib.h>

struct grafo
{
	int ordem;
	int **matriz;
};
typedef struct grafo Grafo;

Grafo *cria_grafo(int ordem);

void limpa_grafo(Grafo *g);
void profundidade_grafo(Grafo *g);
void dfs(Grafo *g, int src, int dst, int *visitados, int profundidade);

int main()
{
	int N, V, E, src, dst, caso;
	Grafo *g = NULL;

	scanf("%d", &N);
	caso = 1;

	while (caso <= N)
	{
		printf("Caso %d:\n", caso);
		scanf("%d %d", &V, &E);
		g = cria_grafo(V);

		for (int i = 0; i < E; i++)
		{
			scanf("%d %d", &src, &dst);
			g->matriz[src][dst] = 1;
		}
		profundidade_grafo(g);
		limpa_grafo(g);

		caso++;
	}

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
			if (g->matriz[i] != NULL)
				for (int j = 0; j < ordem; j++)
					g->matriz[i][j] = 0;
		}
	}

	return g;
}

void profundidade_grafo(Grafo *g)
{
	int *visitados = (int *)malloc(sizeof(int) * g->ordem);

	for (int j = 1; j < g->ordem; j++)
		visitados[j] = 0;

	for (int i = 0; i < g->ordem; i++)
	{
		for (int j = 0; j < g->ordem; j++)
		{
			if (g->matriz[i][j] && !visitados[j])
			{
				dfs(g, i, j, visitados, 1);
				printf("\n");
			}
		}
	}
}

void dfs(Grafo *g, int src, int dst, int *visitados, int profundidade)
{
	visitados[dst] = 1;
	for (int i = 0; i < g->ordem; i++)
		if (g->matriz[dst][i])
		{
			for (int j = 0; j < profundidade; j++)
				printf("  ");
			if (!visitados[i])
			{
				printf("%d-%d pathR(G,%d)\n", src, dst, dst);
				dfs(g, dst, i, visitados, profundidade + 1);
			}
			else
				printf("%d-%d\n", src, dst);
		}
}

void limpa_grafo(Grafo *g)
{
	if (g == NULL)
		return;

	for (int i = 0; i < g->ordem; i++)
		free(g->matriz[i]);

	g->ordem = 0;
	free(g->matriz);
	free(g);
	g = NULL;
}
