#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

struct node* ROOT = NULL;
struct node* NILL = NULL;

void initialization()
{
	NILL = (node*)malloc(sizeof(node));
	NILL->color = BLACK;
	ROOT = NILL;
}

node* tree_search(int key)
{
	node* x;

	x = ROOT;
	while (x != NILL && x->key != key) {
		if (key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}

	if (x == NILL)
		return NULL;
	else
		return x;
}

struct node* tree_minimum(node* x)
{
	while (x->left != NILL) {
		x = x->left;
	}
	return x;
}

void red_black_insert(int key)
{
	struct node* z, * x, * y;
	z =(node*)malloc(sizeof(node));

	z->key = key;
	z->color = RED;
	z->left = NILL;
	z->right = NILL;

	x = ROOT;
	y = NILL;

	while (x != NILL)
	{
		y = x;
		if (z->key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}

	if (y == NILL)
	{
		ROOT = z;
	}
	else if (z->key < y->key)
	{
		y->left = z;
	}
	else
	{
		y->right = z;
	}

	z->parent = y;

	red_black_insert_fixup(z);
}

void red_black_insert_fixup(node* z)
{
	while (z->parent->color == RED) 
	{

		if (z->parent == z->parent->parent->left) 
		{

			if (z->parent->parent->right->color == RED)
			{
				z->parent->color = BLACK;
				z->parent->parent->right->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}

			else
			{

				if (z == z->parent->right)
				{
					z = z->parent;
					left_rotate(z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				right_rotate(z->parent->parent);
			}
		}

		else 
		{

			if (z->parent->parent->left->color == RED)
			{
				z->parent->color = BLACK;
				z->parent->parent->left->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}


			else 
			{
				if (z == z->parent->left)
				{
					z = z->parent;
					right_rotate(z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				left_rotate(z->parent->parent);
			}
		}
	}

	ROOT->color = BLACK;
}

void left_rotate(node* x)
{
	 node* y;

	if (x->right != NILL)
	{
		y = x->right;
		x->right = y->left;
		if (y->left != NILL)
		{
			y->left->parent = x;
		}

		y->parent = x->parent;
		if (x->parent == NILL)
		{
			ROOT = y;
		}
		else if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}

		y->left = x;
		x->parent = y;
	}
}

void right_rotate( node* x)
{
	node* y;
	y = x->left;
	x->left = y->right;

	if (y->right != NILL)
	{
		y->right->parent = x;
	}

	y->parent = x->parent;
	if (y->parent == NILL)
	{
		ROOT = y;
	}
	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}
	else
	{
		x->parent->right = y;
	}

	y->right = x;
	x->parent = y;
}



void red_black_delete( node* z)
{
	 node* y, * x;
	int yOriginalColor;

	y = z;
	yOriginalColor = y->color;

	if (z->left == NILL)
	{
		x = z->right;
		red_black_transplant(z, z->right);
	}
	else if (z->right == NILL)
	{
		x = z->left;
		red_black_transplant(z, z->left);
	}
	else 
	{
		y = tree_minimum(z->right);
		yOriginalColor = y->color;

		x = y->right;

		if (y->parent == z)
		{
			x->parent = y;
		}
		else
		{
			red_black_transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		red_black_transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	if (yOriginalColor == BLACK)
	{
		red_black_delete_fixup(x);
	}
}

void red_black_delete_fixup(node* x)
{
	 node* w;

	while (x != ROOT && x->color == BLACK)
	{

		if (x == x->parent->left)
		{
			w = x->parent->right;

			if (w->color == RED) 
			{
				w->color = BLACK;
				x->parent->color = RED;
				left_rotate(x->parent);
				w = x->parent->right;
			}

			if (x != NILL && w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x->parent->color = BLACK;
				x = x->parent;
			}
			else 
			{

				if (x != NILL && w->right->color == BLACK)
				{
					w->color = RED;
					w->left->color = BLACK;
					right_rotate(w);
					w = x->parent->right;
				}
				
				if (x != NILL)
				{
					w->color = x->parent->color;
					x->parent->color = BLACK;
					x->right->color = BLACK;
				}
				
				left_rotate(x->parent);
				x = ROOT;

			}

		}
		else
		{
			w = x->parent->left;

			if (w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = BLACK;
				right_rotate(x->parent);
				w = x->parent->left;
			}

			if (w != NILL && w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				x->parent->color = BLACK;
				x = x->parent;
			}
			else
			{

				if (w->left->color == BLACK)
				{
					w->color = RED;
					w->right->color = BLACK;
					left_rotate(w);
					w = x->parent->left;
				}

				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				right_rotate(x->parent);
				x = ROOT;

			}
		}

	}

	x->color = BLACK;
}

void red_black_transplant(node* u, node* v) 
{
	if (u->parent == NILL)
	{
		ROOT = v;
	}
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}

	v->parent = u->parent;
}

void padding(char ch, int n)
{
	int i;

	for (i = 0; i < n; i++)
		putchar(ch);
}

void structure(node* root, int level)
{
	int i;

	if (root == NILL) 
	{
		padding('\t', level);
		puts("NILL");
	}
	else
	{
		structure(root->right, level + 1);
		padding('\t', level);
		printf("%d\n", root->key);
		structure(root->left, level + 1);
	}
}

void print()
{
	structure(ROOT, 0);
}