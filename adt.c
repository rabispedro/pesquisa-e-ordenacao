#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "./headers/adt.h"

Node *new_node(int v)
{
	Node *n = (Node *)malloc(sizeof(Node));

	if (n != NULL)
	{
		n->left = NULL;
		n->right = NULL;
		n->value = v;
	}

	return n;
}

void delete_node(Node *n)
{
	if (n != NULL)
		free(n);
}

void print_node(Node *n)
{
	if (n != NULL)
		printf("Node@%p = [value: %d, left: %p, rigth: %p]\n", n, n->value, n->left, n->right);
}

void test_node()
{
	Node* n1 = new_node(-1);
	Node* n2 = new_node(-2);
	Node* n3 = new_node(1);
	Node* n4 = new_node(2);

	assert(n1 != NULL);
	assert(n2 != NULL);
	assert(n3 != NULL);
	assert(n4 != NULL);

	print_node(n1);
	print_node(n2);
	print_node(n3);
	print_node(n4);

	delete_node(n1);
	delete_node(n2);
	delete_node(n3);
	delete_node(n4);
}