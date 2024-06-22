#include <stdio.h>
#include <stdlib.h>

struct no
{
	int valor, altura;
	struct no *esq, *dir;
};
typedef struct no No;

struct arvore_binaria
{
	int tamanho, altura;
	struct no *raiz;
};
typedef struct arvore_binaria ABB;

No *cria_no(const int valor, const int altura);

ABB *cria_abb();
void insere_valor_abb(ABB *abb, const int valor);
void printa_largura_abb(ABB *abb);

void pre_ordem_abb(ABB *abb);
void pre_ordem_no_abb(No *raiz);

int main()
{
	int N;
	ABB *abb = cria_abb();

	while (scanf("%d", &N), (N != -1))
	{
		insere_valor_abb(abb, N);
	}

	printa_largura_abb(abb);

	return 0;
}

No *cria_no(const int valor, const int altura)
{
	No *n = (No *)malloc(sizeof(No));

	if (n != NULL)
	{
		n->esq = NULL;
		n->dir = NULL;
		n->altura = altura;
		n->valor = valor;
	}

	return n;
}

ABB *cria_abb()
{
	ABB *abb = (ABB *)malloc(sizeof(ABB));

	if (abb != NULL)
	{
		abb->tamanho = abb->altura = 0;
		abb->raiz = NULL;
	}

	return abb;
}

void insere_valor_abb(ABB *abb, const int valor)
{
	if (abb == NULL)
		return;

	int altura = 0;
	No *aux = abb->raiz;
	No *pai = NULL;

	if (abb->raiz == NULL)
	{
		No *aux = cria_no(valor, altura);
		abb->raiz = aux;
		abb->tamanho++;
		abb->altura++;

		return;
	}

	while ((aux != NULL) && (aux->valor != valor))
	{
		altura++;
		pai = aux;

		if (aux->valor > valor)
			aux = aux->esq;
		else
			aux = aux->dir;
	}

	if (aux != NULL && aux->valor == valor)
		return;

	aux = cria_no(valor, altura);
	abb->tamanho++;

	if (altura > abb->altura)
		abb->altura = altura;

	if (pai->valor > valor)
	{
		pai->esq = aux;
	}
	else
	{
		pai->dir = aux;
	}
}

void printa_largura_abb(ABB *abb)
{
	if (abb == NULL || abb->raiz == NULL)
		return;

	const int TAMANHO = abb->tamanho;
	const int ALTURA = abb->altura;

	No **topologia = (No **)malloc(TAMANHO * sizeof(No *));
	int index = 0;

	topologia[index++] = abb->raiz;

	for (int i = 0; i < TAMANHO; i++)
	{
		if (topologia[i]->esq != NULL)
			topologia[index++] = topologia[i]->esq;
		if (topologia[i]->dir != NULL)
			topologia[index++] = topologia[i]->dir;
	}

	for (int i = 0; i < TAMANHO; i++)
	{
		if (i == 0)
		{
			printf("%d", topologia[i]->valor);
		}
		else
		{
			if (topologia[i - 1]->altura != topologia[i]->altura)
				printf("\n");
			printf("%d ", topologia[i]->valor);
		}
	}

	printf("\n");
}

void pre_ordem_abb(ABB *abb)
{
	if (abb == NULL || abb->raiz == NULL)
		return;

	pre_ordem_no_abb(abb->raiz);
	printf("\n");
}

void pre_ordem_no_abb(No *raiz)
{
	if (raiz != NULL)
	{
		printf("%d ", raiz->altura);
		pre_ordem_no_abb(raiz->esq);
		pre_ordem_no_abb(raiz->dir);
	}
}
