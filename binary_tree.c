#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "./headers/adt.h"
#include "./headers/binary_tree.h"

BinaryTree *new_binary_tree()
{
	BinaryTree *bt = (BinaryTree *)malloc(sizeof(BinaryTree));

	if (bt != NULL)
	{
		bt->level = 0;
		bt->root = NULL;
		bt->size = 0;
	}

	return bt;
}

void delete_binary_tree(BinaryTree *bt);

bool is_empty_binary_tree(BinaryTree *bt)
{
	return bt->size > 0;
}

void insert_value_binary_tree(BinaryTree *bt, Node *n);

Node *remove_value_binary_tree(BinaryTree *bt, int value);

Node *find_value_binary_tree(BinaryTree *bt, int value)
{
	if (bt == NULL || is_empty_binary_tree(bt))
		return NULL;

	Node *aux = bt->root;
	Node *foundedNode = NULL;

	while (aux != NULL)
	{
		if (value > aux->value)
			aux = aux->right;
		else if (value < aux->value)
			aux = aux->left;
		else
		{
			foundedNode = aux;
			aux = NULL;
		}
	}

	return foundedNode;
}

void clear_binary_tree(BinaryTree *bt);

void print_binary_tree(BinaryTree *bt)
{
}

void test_binary_tree()
{
	BinaryTree *bt1 = new_binary_tree();

	assert(bt1 != NULL);

	assert(is_empty_binary_tree(bt1) == true);

	Node *n1 = new_node(1);
	Node *n2 = new_node(2);
	Node *n3 = new_node(3);
	Node *n4 = new_node(4);
	Node *n5 = new_node(5);

	assert(find_value_binary_tree(bt1, 1) == NULL);

	insert_value_binary_tree(bt1, n3);
	insert_value_binary_tree(bt1, n3);
	insert_value_binary_tree(bt1, n3);
	insert_value_binary_tree(bt1, n3);
	insert_value_binary_tree(bt1, n3);

	assert(is_empty_binary_tree(bt1) == false);
	assert(find_value_binary_tree(bt1, 1) == n1);
	assert(find_value_binary_tree(bt1, 2) == n2);
	assert(find_value_binary_tree(bt1, 3) == n3);
	assert(find_value_binary_tree(bt1, 4) == n4);
	assert(find_value_binary_tree(bt1, 5) == n5);

	insert_value_binary_tree(bt1, n3);
	insert_value_binary_tree(bt1, n3);
	insert_value_binary_tree(bt1, n3);
	insert_value_binary_tree(bt1, n3);
	insert_value_binary_tree(bt1, n3);

	assert(1 != 0);

	delete_binary_tree(bt1);
}