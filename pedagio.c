#include <stdio.h>
#include <stdlib.h>

struct no
{
	int valor;
	struct no *ant, *prox;
} typedef No;

No *cria_no(int valor);
void printa_no(No *no);
void destroi_no(No *no);

struct lista
{
	int tamanho;
	No *inicio, *fim;
} typedef Lista;

Lista *cria_lista();
void printa_lista(Lista *lista);
void insere_fim(Lista *lista, No *no);
void insere_ordenado(Lista *lista, No *no);
No *remove_inicio(Lista *lista);
No *pega_no(Lista *lista, int posicao);
void destroi_lista(Lista *lista);

struct grafo
{
	int ordem;
	int **vertices;
} typedef Grafo;

Grafo *cria_grafo(int ordem);
void insere_aresta_grafo(Grafo *grafo, int origem, int destino);
void printa_grafo(Grafo *grafo);
void destroi_grafo(Grafo *grafo);

void percorre_cidades(Grafo *grafo, int origem, int credito);
void heuristica(Grafo *grafo, int *visitados, int origem, int credito, Lista *memo);
void limpa_visitados(int *visitados, int tamanho);

int main()
{
	int C, E, L, P, src, dst, casos = 1;
	Grafo *grafo;

	while ((scanf("%d %d %d %d", &C, &E, &L, &P)), ((C | E | L | P)))
	{
		grafo = cria_grafo(C);
		printf("Teste %d\n", casos++);

		for (int i = 0; i < E; i++)
		{
			scanf("%d %d", &src, &dst);
			insere_aresta_grafo(grafo, src - 1, dst - 1);
		}

		percorre_cidades(grafo, L - 1, P);
		printf("\n");

		destroi_grafo(grafo);
	}

	return 0;
}

No *cria_no(int valor)
{
	No *no = (No *)malloc(sizeof(No));

	if (no != NULL)
	{
		no->ant = no->prox = NULL;
		no->valor = valor;
	}

	return no;
}

void printa_no(No *no)
{
	if (no == NULL)
		return;

	printf("%d ", no->valor);
}

void destroi_no(No *no)
{
	if (no == NULL)
		return;

	no->ant = no->prox = NULL;
	free(no);
	no = NULL;
}

Lista *cria_lista()
{
	Lista *lista = (Lista *)malloc(sizeof(Lista));

	if (lista != NULL)
	{
		lista->tamanho = 0;
		lista->inicio = lista->fim = NULL;
	}

	return lista;
}

void printa_lista(Lista *lista)
{
	if (lista == NULL)
		return;

	for (No *aux = lista->inicio; aux != NULL; aux = aux->prox)
		printa_no(aux);
}

void insere_fim(Lista *lista, No *no)
{
	if (lista == NULL)
		return;

	if (lista->inicio == NULL && lista->fim == NULL)
	{
		lista->inicio = lista->fim = no;
	}
	else
	{
		lista->fim->prox = no;
		no->ant = lista->fim;
		lista->fim = no;
	}
	lista->tamanho++;
}

void insere_ordenado(Lista *lista, No *no)
{
	if (lista == NULL)
		return;

	if (lista->inicio == NULL && lista->fim == NULL)
	{
		lista->inicio = lista->fim = no;
	}
	else if (no->valor < lista->inicio->valor)
	{
		lista->inicio->ant = no;
		no->prox = lista->inicio;
		lista->inicio = no;
	}
	else if (no->valor > lista->fim->valor)
	{
		lista->fim->prox = no;
		no->ant = lista->fim;
		lista->fim = no;
	}
	else
	{
		No *aux = lista->inicio;
		while (aux != lista->fim && aux->valor > no->valor)
			aux = aux->prox;

		aux->ant->prox = no;
		no->ant = aux->ant;
		aux->ant = no;
		no->prox = aux;
	}
	lista->tamanho++;
}

No *remove_inicio(Lista *lista)
{
	if (lista == NULL)
		return NULL;

	No *aux = lista->inicio;
	if (lista->inicio != NULL)
	{
		lista->inicio->prox->ant = NULL;
		lista->inicio = lista->inicio->prox;
		lista->tamanho--;
	}

	return aux;
}

No *pega_no(Lista *lista, int posicao)
{
	if (lista == NULL)
		return NULL;

	No *aux = lista->inicio;
	int i = 0;
	while (aux != NULL && i < posicao)
	{
		i++;
		aux = aux->prox;
	}

	return aux;
}

void destroi_lista(Lista *lista)
{
	if (lista == NULL)
		return;

	No *auxFree;
	No *aux = lista->inicio;
	while (aux != NULL)
	{
		auxFree = aux;
		aux = aux->prox;
		destroi_no(auxFree);
	}

	lista->inicio = lista->fim = NULL;
	free(lista);
	lista = NULL;
}

Grafo *cria_grafo(int ordem)
{
	Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));

	if (grafo != NULL)
	{
		grafo->ordem = ordem;
		grafo->vertices = (int **)malloc(sizeof(int *) * ordem);

		for (int i = 0; i < ordem; i++)
		{
			grafo->vertices[i] = (int *)malloc(sizeof(int) * ordem);
			for (int j = 0; j < ordem; j++)
				grafo->vertices[i][j] = 0;
		}
	}

	return grafo;
}

void insere_aresta_grafo(Grafo *grafo, int origem, int destino)
{
	if (grafo == NULL)
		return;

	if (origem >= 0 && origem < grafo->ordem && destino >= 0 && destino < grafo->ordem)
		grafo->vertices[origem][destino] = grafo->vertices[destino][origem] = 1;
}

void printa_grafo(Grafo *grafo)
{
	if (grafo == NULL)
		return;

	for (int i = 0; i < grafo->ordem; i++)
	{
		for (int j = 0; j < grafo->ordem; j++)
			printf("%d ", grafo->vertices[i][j]);
		printf("\n");
	}
}

void destroi_grafo(Grafo *grafo)
{
	if (grafo == NULL)
		return;

	for (int i = 0; i < grafo->ordem; i++)
		free(grafo->vertices[i]);

	grafo->vertices = NULL;
	free(grafo);
	grafo = NULL;
}

void percorre_cidades(Grafo *grafo, int origem, int credito)
{
	Lista *cidades = cria_lista();
	int *visitados = (int *)malloc(sizeof(int) * grafo->ordem);

	for (int i = 0; i < grafo->ordem; i++)
		if (grafo->vertices[origem][i])
			insere_fim(cidades, cria_no(i + 1));

	for (int i = 0; i < cidades->tamanho; i++)
	{
		Lista *memo = cria_lista();
		No *aux = pega_no(cidades, i);
		limpa_visitados(visitados, grafo->ordem);
		visitados[origem] = 1;
		heuristica(grafo, visitados, aux->valor - 1, credito - 1, memo);
		printa_lista(memo);
		destroi_lista(memo);
	}
	printf("\n");

	destroi_lista(cidades);
	free(visitados);
}

void heuristica(Grafo *grafo, int *visitados, int origem, int credito, Lista *memo)
{
	No *aux = cria_no(origem + 1);
	if (!visitados[origem])
		insere_ordenado(memo, aux);

	visitados[origem] = 1;

	if (credito > 0)
	{
		for (int i = 0; i < grafo->ordem; i++)
		{
			if (grafo->vertices[origem][i] && !visitados[i])
				heuristica(grafo, visitados, i, credito - 1, memo);
		}
	}
}

void limpa_visitados(int *visitados, int tamanho)
{
	if (visitados == NULL)
		return;

	for (int i = 0; i < tamanho; i++)
		visitados[i] = 0;
}
