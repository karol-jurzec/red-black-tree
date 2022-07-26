#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

struct node 
{
	int key;
	int color;
	struct node* parent;
	struct node* left;
	struct node* right;
};

void initialization();
void left_rotate( node* x);
void right_rotate(node* x);
void red_black_insert(int key);
void red_black_insert_fixup(node* z);
node* tree_search(int key);
node* tree_minimum(node* x);
void red_black_transplant(node* u, node* v);
void red_black_delete(node* z);
void red_black_delete_fixup(node* x);

void structure(node* root, int level);
void padding(char ch, int n);
void print();


