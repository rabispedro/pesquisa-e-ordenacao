#include <stdio.h>
#include <string.h>

#define STR_MAX 1 << 6

struct camiseta
{
	char nome[STR_MAX];
	char cor[STR_MAX];
	char tamanho;
};
typedef struct camiseta Camiseta;

int compara_camisetas(Camiseta, Camiseta);
void printa_camiseta(Camiseta);
void bubble_sort(Camiseta[], int);

int N;

int main()
{

	while (scanf("%d", &N), N)
	{
		Camiseta camisetas[N];
		for (int i = 0; i < N; ++i)
		{
			scanf(" %[^\n]s", camisetas[i].nome);
			scanf(" %s %c", camisetas[i].cor, &camisetas[i].tamanho);
		}

		bubble_sort(camisetas, N);

		for (int i = 0; i < N; ++i)
			printa_camiseta(camisetas[i]);

		printf("\n");
	}

	return 0;
}

int compara_camisetas(Camiseta a, Camiseta b)
{
	int cor_comparacao = strcmp(a.cor, b.cor);
	if (cor_comparacao != 0)
	{
		return cor_comparacao;
	}

	if (a.tamanho != b.tamanho)
	{
		return b.tamanho - a.tamanho;
	}

	return strcmp(a.nome, b.nome);
}

void printa_camiseta(Camiseta camiseta)
{
	printf("%s %c %s\n", camiseta.cor, camiseta.tamanho, camiseta.nome);
}

void bubble_sort(Camiseta camisetas[], int tam)
{
	for (int i = 0; i < (tam - 1); i++)
	{
		for (int j = i + 1; j < tam; j++)
		{
			if (compara_camisetas(camisetas[i], camisetas[j]) > 0)
			{
				Camiseta aux = camisetas[i];
				camisetas[i] = camisetas[j];
				camisetas[j] = aux;
			}
		}
	}
}
