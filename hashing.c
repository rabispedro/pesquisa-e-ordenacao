#include <stdio.h>
#include <stdlib.h>

struct tabela_hash
{
	int tamanho, **tabela;
};
typedef struct tabela_hash TabelaHash;

TabelaHash *cria_tabela_hash(int);
void insere_tabela_hash(TabelaHash *, int);
int hash(int, int);
void print_tabela_hash(TabelaHash *);
void destroi_tabela_hash(TabelaHash *);

int N, M, K, atual;
TabelaHash *tabelaHash;

int main()
{
	scanf("%d", &N);

	while (N--)
	{
		scanf("%d %d", &M, &K);
		tabelaHash = cria_tabela_hash(M);

		while (K--)
		{
			scanf("%d", &atual);
			insere_tabela_hash(tabelaHash, atual);
		}

		print_tabela_hash(tabelaHash);

		destroi_tabela_hash(tabelaHash);
		printf("\n");
	}

	return 0;
}

TabelaHash *cria_tabela_hash(int tamanho)
{
	TabelaHash *th = (TabelaHash *)malloc(sizeof(TabelaHash));

	if (th != NULL)
	{
		th->tamanho = tamanho;
		th->tabela = (int **)malloc(sizeof(int *) * th->tamanho);

		for (int i = 0; i < th->tamanho; i++)
		{
			th->tabela[i] = (int *)malloc(sizeof(int) * th->tamanho);
			for (int j = 0; j < th->tamanho; j++)
				th->tabela[i][j] = -1;
		}
	}

	return th;
}

void insere_tabela_hash(TabelaHash *th, int valor)
{
	if (th == NULL)
		return;

	int indice = hash(th->tamanho, valor);

	int aux = 0;
	while (aux < th->tamanho && th->tabela[indice][aux] != -1)
		aux++;

	if (aux == th->tamanho)
		return;

	th->tabela[indice][aux] = valor;
}

int hash(int chave, int valor)
{
	return valor % chave;
}

void print_tabela_hash(TabelaHash *th)
{
	if (th == NULL)
		return;

	for (int i = 0; i < th->tamanho; i++)
	{
		printf("%d -> ", i);

		for (int j = 0; j < th->tamanho && th->tabela[i][j] != -1; j++)
			printf("%d -> ", th->tabela[i][j]);

		printf("\\\n");
	}
}

void destroi_tabela_hash(TabelaHash *th)
{
	if (th == NULL)
		return;

	for (int i = 0; i < th->tamanho; i++)
		free(th->tabela[i]);

	free(th->tabela);
	free(th);

	th = NULL;
}
