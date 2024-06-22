#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct nod
{
	struct nod *ant, *prox;
	void *info;
};
typedef struct nod Nod;

struct listad
{
	struct nod *ini, *fim;
};
typedef struct listad Listad;

Nod *cria_nod(void *info);
Listad *cria_listad();
Listad *insere_inicio(Listad *lista, void *info);
Listad *insere_fim(Listad *lista, void *info);
Listad *divide_lista(Listad *lista, int qtde);
Nod *remove_fim(Listad *lista);

struct pagina
{
	int folha;
	int qtdeChaves;
	struct pagina *pai;
	Listad *listaChaves;
	struct pagina *direita;
};
typedef struct pagina Pagina;

struct arvoreb
{
	Pagina *raiz;
	int ordem;
	int altura;
};
typedef struct arvoreb Arvoreb;

struct chave
{
	int valorChave;
	Pagina *filho;
};
typedef struct chave Chave;
void insere_chave_arvoreb(Arvoreb *tree, int novo_valor_chave);
Arvoreb *cria_arvoreb(int ordem);
Pagina *cria_pagina();
Chave *cria_chave(int valorChave);
void imprime_arvoreb(Arvoreb *ab);
void imprime_pagina(Pagina *p);
Pagina *localiza_folha(Arvoreb *tree, int novo_valor_chave);
int get_valor_chave(Nod *no_lista);
Pagina *get_filho(Nod *no_lista);
void set_filho(Nod *no_lista, Pagina *novo_filho);
Pagina *divide_pagina(Pagina *pagina_a_dividir);
void insere_ordenado(Listad *lista, Chave *info);
Pagina *cria_nova_raiz(Chave *, Pagina *, Pagina *);
void insere_chave_pagina(Pagina *folha, Chave *ch);
Chave *remove_ultima_chave(Pagina *pagina);

int main()
{
	int ordem, N;

	scanf("%d", &ordem);
	Arvoreb *tree = cria_arvoreb(ordem);

	while (scanf("%d", &N), (N != -1))
		insere_chave_arvoreb(tree, N);

	imprime_arvoreb(tree);
	printf("\n");

	return 0;
}

Arvoreb *cria_arvoreb(int ordem)
{
	Arvoreb *nova = (Arvoreb *)malloc(sizeof(Arvoreb));
	nova->altura = 0;
	nova->ordem = ordem;
	nova->raiz = NULL;
	return nova;
}

Pagina *cria_pagina()
{
	Pagina *nova = (Pagina *)malloc(sizeof(Pagina));
	nova->folha = 1;
	nova->qtdeChaves = 0;
	nova->pai = NULL;
	nova->direita = NULL;
	nova->listaChaves = cria_listad();
	return nova;
}

Chave *cria_chave(int valorChave)
{
	Chave *ch = (Chave *)malloc(sizeof(Chave));
	ch->valorChave = valorChave;
	ch->filho = NULL;
	return ch;
}

void insere_chave_pagina(Pagina *folha, Chave *ch)
{
	insere_ordenado(folha->listaChaves, ch);
	folha->qtdeChaves++;
}

void insere_chave_arvoreb(Arvoreb *tree, int novo_valor_chave)
{
	Chave *ch = cria_chave(novo_valor_chave);
	Pagina *nova_pagina, *pagina_da_insercao;
	pagina_da_insercao = localiza_folha(tree, novo_valor_chave);
	int continua_insercao = 1;
	if (pagina_da_insercao == NULL)
	{
		tree->raiz = cria_pagina();
		insere_chave_pagina(tree->raiz, ch);
	}
	else
	{
		while (continua_insercao)
		{
			insere_chave_pagina(pagina_da_insercao, ch);
			if (pagina_da_insercao->qtdeChaves <= tree->ordem - 1)
			{
				// nao estorou a pagina folha
				continua_insercao = 0;
			}
			else
			{
				// estorou a pagina
				nova_pagina = divide_pagina(pagina_da_insercao);
				// remove a ultima chave de pagina_da_insercao
				ch = remove_ultima_chave(pagina_da_insercao);
				if (pagina_da_insercao->pai == NULL)
				{
					tree->raiz = cria_nova_raiz(ch, pagina_da_insercao, nova_pagina);
					continua_insercao = 0;
				}
				else
				{
					pagina_da_insercao = pagina_da_insercao->pai;
				}
			}
		}
	}
}

Pagina *localiza_folha(Arvoreb *tree, int novo_valor_chave)
{
	Pagina *aux_pagina = tree->raiz;
	Nod *aux_lista;

	if (aux_pagina != NULL)
	{
		while (aux_pagina->folha == 0) // enqto nao for folha
		{
			aux_lista = aux_pagina->listaChaves->ini;
			while (aux_lista != NULL && get_valor_chave(aux_lista) < novo_valor_chave)
			{
				aux_lista = aux_lista->prox;
			}
			if (aux_lista == NULL)
				aux_pagina = aux_pagina->direita;
			else
				aux_pagina = get_filho(aux_lista);
		}
	}
	return aux_pagina;
}

int get_valor_chave(Nod *no_lista)
{
	return ((Chave *)no_lista->info)->valorChave;
}
Pagina *get_filho(Nod *no_lista)
{
	return ((Chave *)no_lista->info)->filho;
}
void set_filho(Nod *no_lista, Pagina *novo_filho)
{
	((Chave *)no_lista->info)->filho = novo_filho;
}

Pagina *divide_pagina(Pagina *pagina_a_dividir)
{

	Pagina *nova_pagina = cria_pagina();
	int qtde = ceil(pagina_a_dividir->qtdeChaves / 2.0);
	Pagina *ultima_chave;
	Nod *aux_lista;
	Listad *nova_lista = divide_lista(pagina_a_dividir->listaChaves, qtde);

	nova_pagina->listaChaves = nova_lista;
	nova_pagina->qtdeChaves = pagina_a_dividir->qtdeChaves - qtde;
	nova_pagina->folha = pagina_a_dividir->folha;
	nova_pagina->pai = pagina_a_dividir->pai;
	nova_pagina->direita = pagina_a_dividir->direita;

	pagina_a_dividir->qtdeChaves = qtde;
	ultima_chave = get_filho(pagina_a_dividir->listaChaves->fim);
	set_filho(pagina_a_dividir->listaChaves->fim, pagina_a_dividir);

	// se nao for raiz
	if (pagina_a_dividir->pai != NULL)
	{
		aux_lista = pagina_a_dividir->pai->listaChaves->ini;

		while (aux_lista != NULL && get_filho(aux_lista) != pagina_a_dividir)
		{
			aux_lista = aux_lista->prox;
		}
		if (aux_lista != NULL)
			set_filho(aux_lista, nova_pagina);
		else
			pagina_a_dividir->pai->direita = nova_pagina;
	}

	// quando não for folha
	if (!pagina_a_dividir->folha)
	{
		aux_lista = nova_lista->ini;
		while (aux_lista != NULL)
		{
			get_filho(aux_lista)->pai = nova_pagina;
			aux_lista = aux_lista->prox;
		}
		nova_pagina->direita->pai = nova_pagina;
		pagina_a_dividir->direita = ultima_chave;
	}
	return nova_pagina;
}

void insere_ordenado(Listad *lista, Chave *ch)
{
	Nod *aux = NULL;
	Nod *novo = cria_nod(ch);
	if (lista->ini == NULL)
	{
		lista->ini = lista->fim = cria_nod(ch);
	}
	else
	{
		if (ch->valorChave < get_valor_chave(lista->ini))
			lista = insere_inicio(lista, ch);
		else if (ch->valorChave > get_valor_chave(lista->fim))
			lista = insere_fim(lista, ch);
		else
		{
			aux = lista->ini; // ou aux = lista->ini->prox
			while (ch->valorChave > get_valor_chave(aux))
				aux = aux->prox;

			novo->ant = aux->ant;
			novo->prox = aux;
			aux->ant->prox = novo;
			aux->ant = novo;
		}
	}
}

Pagina *cria_nova_raiz(Chave *ch, Pagina *pagina_dividida, Pagina *nova_pagina)
{
	Pagina *nova_raiz = cria_pagina();
	insere_chave_pagina(nova_raiz, ch);
	nova_raiz->direita = nova_pagina;
	set_filho(nova_raiz->listaChaves->ini, pagina_dividida);
	nova_raiz->folha = 0;
	pagina_dividida->pai = nova_raiz;
	nova_pagina->pai = nova_raiz;
	return nova_raiz;
}

Chave *remove_ultima_chave(Pagina *pagina)
{
	Nod *aux = remove_fim(pagina->listaChaves);
	Chave *ch = (Chave *)aux->info;
	free(aux);
	pagina->qtdeChaves--;
	return ch;
}

void imprime_arvoreb(Arvoreb *ab)
{
	if (ab == NULL || ab->raiz == NULL)
		return;

	imprime_pagina(ab->raiz);
}

void imprime_pagina(Pagina *p)
{
	if (p == NULL)
		return;

	Nod *aux_lista = p->listaChaves->ini;
	while (aux_lista != NULL)
	{
		Pagina *filho = (Pagina *)((Chave *)aux_lista->info)->filho;
		imprime_pagina(filho);
		int valorChave = (int)((Chave *)aux_lista->info)->valorChave;
		printf("%d ", valorChave);
		aux_lista = aux_lista->prox;
	}

	imprime_pagina(p->direita);
}

Nod *cria_nod(void *info)
{
	Nod *novo = (Nod *)malloc(sizeof(Nod));
	novo->ant = novo->prox = NULL;
	novo->info = info;
	return novo;
}

Listad *cria_listad()
{
	Listad *lista = (Listad *)
			malloc(sizeof(Listad));
	lista->ini = lista->fim = NULL;
	return lista;
}

Listad *insere_inicio(Listad *lista, void *info)
{
	Nod *novo = cria_nod(info);

	if (lista == NULL)
	{
		lista = cria_listad();
		lista->ini = lista->fim = novo;
	}
	else
	{
		novo->prox = lista->ini;
		lista->ini->ant = novo;
		lista->ini = novo;
	}
	return lista;
}

Listad *insere_fim(Listad *lista, void *info)
{
	Nod *novo = cria_nod(info);

	if (lista == NULL)
	{
		lista = cria_listad();
		lista->ini = lista->fim = novo;
	}
	else
	{
		novo->ant = lista->fim;
		lista->fim->prox = novo;
		lista->fim = novo;
	}
	return lista;
}

Listad *divide_lista(Listad *lista, int qtde)
{
	Nod *aux = lista->ini;
	Listad *nova_lista;
	while (qtde > 0)
	{
		aux = aux->prox;
		qtde--;
	}
	nova_lista = cria_listad();
	nova_lista->ini = aux;
	nova_lista->fim = lista->fim;
	lista->fim = aux->ant;
	lista->fim->prox = NULL;
	aux->ant = NULL;
	return nova_lista;
}

Nod *remove_fim(Listad *L)
{
	Nod *aux = NULL;
	if (L != NULL && L->ini != NULL)
	{
		aux = L->fim;
		if (L->ini != L->fim)
		{
			L->fim->ant->prox = NULL;
			L->fim = L->fim->ant;
			aux->ant = NULL;
		}
		else
		{
			L->fim = L->ini = NULL;
		}
	}
	return aux;
}
