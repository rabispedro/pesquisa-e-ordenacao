#ifndef ADT_H
#define ADT_H

struct node
{
	int value;
	struct node *left, *right;
};

typedef struct node Node;

Node *new_node(int v);
void delete_node(Node *n);
void print_node(Node *n);
void test_node();

#endif
