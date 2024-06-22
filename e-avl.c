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

struct no_abb
{
	int chave;
	struct no_abb *esq, *dir;
};
typedef struct no_abb NoAbb;

struct abb
{
	struct no_abb *raiz;
	int altura;
	int qtde_chaves;
};
typedef struct abb Abb;

NoAbb *cria_no_abb(int chave);
void insere_no_abb(Abb *T, int chave);
void busca_no_abb(Abb *T, int chave);
int busca_no_abb_rec(NoAbb *raiz, int chave);

void pre_ordem_abb(Abb *T);
void pre_ordem_no_abb(NoAbb *raiz);
Abb *cria_arvore_abb();

void em_ordem_avl(Avl *T);
void em_ordem_no_avl(No_avl *raiz);

void libera_avl(No_avl *raiz);

int compara_arvores(NoAbb *raiz_abb, No_avl *raiz_avl);

int main()
{
	int N;
	scanf("%d", &N);

	while (N--)
	{
		Avl *avl = NULL;
		Abb *abb = cria_arvore_abb();
		int K;
		int result;

		while (scanf("%d", &K), (K != -1))
		{
			avl = insercao_avl(avl, K);
			insere_no_abb(abb, K);
		}

		result = compara_arvores(abb->raiz, avl->raiz);
		printf("%s\n", ((result == 1) ? "sim" : "nao"));

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
	// criar a arvore se necessÃ¡rio
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
	// colocar o nÃ³ na arvore corretamente
	// recalcular o fb
	// verifica desbalanceamento
	// balancear (rotacionar)
	// recalcular o fb
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
	if (T != NULL)
		em_ordem_no_avl(T->raiz);
}

void em_ordem_no_avl(No_avl *raiz)
{
	if (raiz != NULL)
	{
		em_ordem_no_avl(raiz->esq);
		printf("%d ", raiz->chave);
		em_ordem_no_avl(raiz->dir);
	}
}

void libera_avl(No_avl *raiz)
{
	if (raiz != NULL)
	{
		libera_avl(raiz->esq);
		libera_avl(raiz->dir);
		free(raiz);
	}
}

void pre_ordem_abb(Abb *T)
{
	if (T != NULL)
		pre_ordem_no_abb(T->raiz);
}

void pre_ordem_no_abb(NoAbb *raiz)
{
	if (raiz != NULL)
	{
		printf("%d ", raiz->chave);
		pre_ordem_no_abb(raiz->esq);
		pre_ordem_no_abb(raiz->dir);
	}
}

NoAbb *cria_no_abb(int chave)
{
	NoAbb *novo = (NoAbb *)malloc(sizeof(NoAbb));
	novo->chave = chave;
	novo->esq = novo->dir = NULL;
	return novo;
}
void insere_no_abb(Abb *T, int chave)
{
	NoAbb *novo = cria_no_abb(chave);
	NoAbb *aux;
	NoAbb *pai_aux = NULL;
	int alt = 0;
	if (T != NULL)
	{
		aux = T->raiz;
		if (T->raiz != NULL)
		{
			while (aux != NULL)
			{
				pai_aux = aux;
				if (chave > aux->chave)
				{
					aux = aux->dir;
					alt++;
				}
				else if (chave < aux->chave)
				{
					aux = aux->esq;
					alt++;
				}
				else
					aux = NULL;
			}
			if (chave > pai_aux->chave)
			{
				pai_aux->dir = novo;
				if (alt > T->altura)
					T->altura++;
				T->qtde_chaves++;
			}
			else if (chave < pai_aux->chave)
			{
				pai_aux->esq = novo;
				if (alt > T->altura)
					T->altura++;
				T->qtde_chaves++;
			}
		}
		else
		{
			T->raiz = cria_no_abb(chave);
			T->altura++;
			T->qtde_chaves++;
		}
	}
}

void busca_no_abb(Abb *T, int chave)
{
	int resposta = busca_no_abb_rec(T->raiz, chave);
	if (resposta)
		printf("existe!");
	else
		printf("nao existe!");
}

int busca_no_abb_rec(NoAbb *raiz, int chave)
{
	int aux = 0;
	if (raiz != NULL)
		if (raiz->chave != chave)
			if (chave < raiz->chave)
				aux = busca_no_abb_rec(raiz->esq, chave);
			else
				aux = busca_no_abb_rec(raiz->dir, chave);
		else
			aux = 1;
	else
		aux = 0;

	return aux;
}

Abb *cria_arvore_abb()
{
	Abb *T = (Abb *)malloc(sizeof(Abb));
	if (T != NULL)
	{
		T->raiz = NULL;
		T->altura = 0;
		T->qtde_chaves = 0;
	}
	return T;
}

int compara_arvores(NoAbb *raiz_abb, No_avl *raiz_avl)
{
	if (raiz_abb == NULL && raiz_avl == NULL)
		return 1;

	if (raiz_abb == NULL || raiz_avl == NULL)
		return 0;

	return (raiz_abb->chave == raiz_avl->chave) && compara_arvores(raiz_abb->dir, raiz_avl->dir) && compara_arvores(raiz_abb->esq, raiz_avl->esq);
}
