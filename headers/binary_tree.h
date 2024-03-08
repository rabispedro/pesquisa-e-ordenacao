#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdbool.h>

#include "adt.h";

struct binary_tree
{
	Node *root;
	int size, level;
};

typedef struct binary_tree BinaryTree;

BinaryTree *new_binary_tree();
void delete_binary_tree(BinaryTree *bt);
bool is_empty_binary_tree(BinaryTree *bt);
void insert_value_binary_tree(BinaryTree *bt, Node *n);
Node *remove_value_binary_tree(BinaryTree *bt, int value);
Node *find_value_binary_tree(BinaryTree *bt, int value);
void clear_binary_tree(BinaryTree *bt);
void print_binary_tree(BinaryTree *bt);
void test_binary_tree();

#endif
