#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

typedef struct node {
	int data, id;
	struct node* left, * right;
}node;

node* getnode();
void putnode(node*);
node* makeTreeNode(int, int);
void binaryPreOrder(node*);
void binaryPostOrder(node*);
void inOrder(node*);
void FindPrint(int com, int id, node*);

void main() {
	node* p = makeTreeNode(1, 20);
	node* tree = p;
	tree->left = makeTreeNode(2, 30);
	tree->right = makeTreeNode(3, 50);
	tree->left->left = makeTreeNode(4, 70);
	tree->left->right = makeTreeNode(5, 90);
	tree->right->right = makeTreeNode(6, 120);
	tree->right->right->left = makeTreeNode(7, 130);
	tree->right->right->right = makeTreeNode(8, 80);
	
	int n, m;
	scanf("%d %d", &n, &m);
	if (m > 8) printf("-1");
	FindPrint(n, m, tree);
}

node* getnode() {
	return (node*)calloc(1, sizeof(node));
}
void putnode(node* p) {
	free(p);
}
node* makeTreeNode(int id,int data) {
	node* p = getnode();
	p->id = id;
	p->data = data;
	p->right = 0;
	p->left = 0;
	return p;
}
void binaryPreOrder(node* p) {
	printf("%d ", p->data);
	if (p->left != 0) {
		binaryPreOrder(p->left);
	}
	if (p->right != 0) {
		binaryPreOrder(p->right);
	}
}
void binaryPostOrder(node* p) {
	if (p->left != 0) {
		binaryPostOrder(p->left);
	}
	if (p->right != 0) {
		binaryPostOrder(p->right);
	}
	printf("%d ", p->data);

}
void inOrder(node* p) {
	if (p->left != 0) {
		inOrder(p->left);
	}
	printf("%d ", p->data); 
	if (p->right != 0) {
		inOrder(p->right);
	}
}
void FindPrint(int com, int id, node* p) {
	if (p->id == id) {
		if (com == 1) binaryPreOrder(p);
		if (com == 2) inOrder(p); 
		if (com == 3)  binaryPostOrder(p);
	}
	if (p->left != 0) {
		FindPrint(com, id, p->left);
	}
	if (p->right != 0) {
		FindPrint(com, id, p->right);
	}
}
