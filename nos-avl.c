#include <stdio.h>
#include <stdlib.h>

struct no_avl
{
	int chave;
	struct no_avl *esq, *dir, *pai;
	int fb;
};
typedef struct no_avl No_avl;

struct avl
{
	No_avl *raiz;
	int altura;
	int qtde_chaves;
};
typedef struct avl Avl;

No_avl *cria_no_avl(int chave);
Avl *cria_avl();
void em_ordem_avl(Avl *t);
Avl *insercao_avl(Avl *t, int chave);
No_avl *colocar_no_avl(No_avl *raiz, int chave);
void recalcular_fb(No_avl *candidato, int chave);
No_avl *rotacao_geral(No_avl *candidato);

No_avl *rotacao_dir(No_avl *candidato);
No_avl *rotacao_esq(No_avl *candidato);
No_avl *rotacao_dir_esq(No_avl *candidato);
No_avl *rotacao_esq_dir(No_avl *candidato);

void em_ordem_avl(Avl *T);
void em_ordem_no_avl(No_avl *raiz);

void libera_avl(No_avl *raiz);

int quantidade_filhos(No_avl *raiz);

int main()
{
	int N;
	scanf("%d", &N);

	while (N--)
	{
		Avl *avl = NULL;
		int K;

		while (scanf("%d", &K), (K != -1))
			avl = insercao_avl(avl, K);

		em_ordem_avl(avl);
		printf("\n");

		libera_avl(avl->raiz);
		free(avl);
	}

	return 0;
}

Avl *cria_avl()
{

	Avl *nova = (Avl *)malloc(sizeof(Avl));
	nova->altura = nova->qtde_chaves = 0;
	nova->raiz = NULL;
	return nova;
}

No_avl *cria_no_avl(int chave)
{
	No_avl *novo = (No_avl *)malloc(sizeof(No_avl));
	novo->dir = novo->esq = novo->pai = NULL;
	novo->chave = chave;
	novo->fb = 0;
	return novo;
}

Avl *insercao_avl(Avl *t, int chave)
{
	No_avl *candidato = NULL;
	if (t == NULL)
	{
		t = cria_avl();
		t->raiz = cria_no_avl(chave);
		t->altura++;
		t->qtde_chaves++;
		return t;
	}
	else
	{
		candidato = colocar_no_avl(t->raiz, chave);
		recalcular_fb(candidato, chave);
		if (candidato->fb == -2 || candidato->fb == +2)
		{
			if (t->raiz == candidato)
				t->raiz = rotacao_geral(candidato);
			else if (candidato->pai->esq == candidato)
				candidato->pai->esq = rotacao_geral(candidato);
			else
				candidato->pai->dir = rotacao_geral(candidato);
		}
	}
	return t;
}

No_avl *colocar_no_avl(No_avl *raiz, int chave)
{
	No_avl *aux = raiz;
	No_avl *candidato = raiz;
	No_avl *pai = NULL;
	No_avl *novo = cria_no_avl(chave);
	while (aux != NULL)
	{
		if (aux->fb != 0)
			candidato = aux;
		pai = aux;
		if (chave < aux->chave)
			aux = aux->esq;
		else
			aux = aux->dir;
	}
	if (chave < pai->chave)
		pai->esq = novo;
	else
		pai->dir = novo;
	novo->pai = pai;
	return candidato;
}

void recalcular_fb(No_avl *candidato, int chave)
{
	No_avl *aux = candidato;
	while (aux->chave != chave)
	{
		if (chave < aux->chave)
		{
			aux->fb++;
			aux = aux->esq;
		}
		else
		{
			aux->fb--;
			aux = aux->dir;
		}
	}
}

No_avl *rotacao_geral(No_avl *candidato)
{
	No_avl *nova_raiz;
	if (candidato->fb == -2)
	{
		if (candidato->dir->fb == +1)
			nova_raiz = rotacao_dir_esq(candidato);
		else
			nova_raiz = rotacao_esq(candidato);
	}
	else //+2
	{
		if (candidato->esq->fb == -1)
			nova_raiz = rotacao_esq_dir(candidato);
		else
			nova_raiz = rotacao_dir(candidato);
	}
	return nova_raiz;
}

No_avl *rotacao_dir(No_avl *candidato)
{
	No_avl *filho = candidato->esq;
	No_avl *neto = filho->dir;

	filho->dir = candidato;
	candidato->esq = neto;

	if (neto != NULL)
		neto->pai = candidato;

	filho->pai = candidato->pai;
	candidato->pai = filho;

	candidato->fb = filho->fb = 0;

	return filho;
}

No_avl *rotacao_esq(No_avl *candidato)
{
	No_avl *filho = candidato->dir;
	No_avl *neto = filho->esq;

	filho->esq = candidato;
	candidato->dir = neto;

	if (neto != NULL)
		neto->pai = candidato;

	filho->pai = candidato->pai;
	candidato->pai = filho;

	candidato->fb = filho->fb = 0;

	return filho;
}

No_avl *rotacao_esq_dir(No_avl *candidato)
{

	No_avl *filho = candidato->esq;
	No_avl *neto = filho->dir;

	candidato->esq = rotacao_esq(filho);
	filho = rotacao_dir(candidato);

	if (neto->fb == 1)
	{
		candidato->fb = -1;
		filho->fb = neto->fb = 0;
	}
	else
	{
		if (neto->fb == -1)
		{
			candidato->fb = neto->fb = 0;
			filho->fb = 1;
		}
		else // neto->fb ==0
		{
			candidato->fb = neto->fb = filho->fb = 0;
		}
	}

	return filho;
}

No_avl *rotacao_dir_esq(No_avl *candidato)
{
	No_avl *filho = candidato->dir;
	No_avl *neto = filho->esq;

	candidato->dir = rotacao_dir(filho);
	filho = rotacao_esq(candidato);
	if (neto->fb == 1)
	{
		candidato->fb = -1;
		filho->fb = neto->fb = 0;
	}
	else
	{
		if (neto->fb == -1)
		{
			candidato->fb = neto->fb = 0;
			filho->fb = 1;
		}
		else // neto->fb ==0
		{
			candidato->fb = neto->fb = filho->fb = 0;
		}
	}

	return filho;
}

void em_ordem_avl(Avl *T)
{
	if (T == NULL)
		return;

	em_ordem_no_avl(T->raiz);
}

void em_ordem_no_avl(No_avl *raiz)
{
	if (raiz == NULL)
		return;

	em_ordem_no_avl(raiz->esq);
	printf("[%d]%d(%d) ", quantidade_filhos(raiz->esq), raiz->chave, quantidade_filhos(raiz->dir));

	em_ordem_no_avl(raiz->dir);
}

void libera_avl(No_avl *raiz)
{
	if (raiz == NULL)
		return;

	libera_avl(raiz->esq);
	libera_avl(raiz->dir);
	free(raiz);
}

int quantidade_filhos(No_avl *raiz)
{
	if (raiz == NULL)
		return 0;

	return (1 + quantidade_filhos(raiz->esq) + quantidade_filhos(raiz->dir));
}
