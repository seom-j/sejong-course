#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)


typedef struct node {
	int data;
	struct node* left, * right;
}node;

node* mom;

node* getnode();
void putnode(node*);
node* makeTreeNode(node*, int, int, int);
void inOrder(node* p, int);

void main() {
	node* tree = getnode();
	node* p = tree;
	mom = tree;
	int n, m, l, r, f;
	char x[101] = { NULL };
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%d %d %d", &m, &l, &r);
		inOrder(tree, m);
		makeTreeNode(mom, m, l, r);
	}
	scanf("%d", &f);
	getchar();
	for (int i = 0; i < f; i++) {
		p = tree;
		scanf("%s", x);
		printf(" %d", p->data);
		for (int j = 0; j < strlen(x); j++) {
			if (x[j] == 'R') p = p->right;
			if (x[j] == 'L') p = p->left;
			printf(" %d", p->data);
		}
		printf("\n");
	}
	
}

node* getnode() {
	return (node*)calloc(1, sizeof(node));
}
void putnode(node* p) {
	free(p);
}

void inOrder(node* p, int data) {
	if (p->left != 0) {
		inOrder(p->left,data);
	}
	if (p->data == data) {
		mom = p;
	}
	if (p->right != 0) {
		inOrder(p->right, data);
	}
}
node* makeTreeNode(node* mom, int head, int left, int right) {
	node* l = getnode();
	node* r = getnode();
	mom->data = head;
	mom->left = l;
	mom->right = r;
	l->data = left;
	r->data = right;
}
