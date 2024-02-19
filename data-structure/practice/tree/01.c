#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

typedef struct node{
	int data;
	struct node* left, * right;
}node;

node* getnode();
void putnode(node*);
node* makeTreeNode(int, node*, node*);
void printTreeNode(node*);

void main() {
	node* F8 = makeTreeNode(80, 0, 0); // 4
	node* F7 = makeTreeNode(130, 0, 0); // 4
	node* F6 = makeTreeNode(120, F7, F8); // 3
	node* F5 = makeTreeNode(90, 0, 0); // 3
	node* F4 = makeTreeNode(70, 0, 0); // 3
	node* F3 = makeTreeNode(50, 0, F6); // 2
	node* F2 = makeTreeNode(30, F4, F5);  // 2
	node* F1 = makeTreeNode(20, F2, F3); // 1

	int n;
	scanf("%d", &n);

	if (n == 1) printTreeNode(F1);
	else if (n == 2) printTreeNode(F2);
	else if (n == 3) printTreeNode(F3);
	else if (n == 4) printTreeNode(F4);
	else if (n == 5) printTreeNode(F5);
	else if (n == 6) printTreeNode(F6);
	else if (n == 7) printTreeNode(F7);
	else if (n == 8) printTreeNode(F8);
	else printf("-1");
}

node* getnode() {
	return (node*)calloc(1, sizeof(node));
}
void putnode(node* p) {
	free(p);
}
node* makeTreeNode(int data, node* left, node* right) {
	node* p = getnode();
	p->data = data;
	p->left = left;
	p->right = right;
	return p;
}
void printTreeNode(node* p) {
	printf("%d", p->data);
	if (!(p->left == 0)) printf(" %d", p->left->data);
	if (!(p->right == 0)) printf(" %d", p->right->data);
	printf("\n");
}
