#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

typedef struct node {
	struct node * next;
	int element;
}node;

node* getNode();
void addLast(node* S, int n);
node* Union(node* A, node* B);
node* Intersect(node* A, node* B);
void print(node* S);

int main() {
	int n, m, e;
	node* AH = getNode();
	node* BH = getNode();

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &e);
		addLast(AH, e);
	}
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &e);
		addLast(BH, e);
	}
	print(Union(AH, BH));
	print(Intersect(AH, BH));
}
node* getNode() { return (node*)calloc(1, sizeof(node)); }

void addLast(node* S, int n) {
	node* p = getNode();
	while (S->next != 0) S = S->next;
	p->element = n;
	S->next = p;
}

node* Union(node* A, node* B) {
	if (A == 0 && B == 0) return 0;
	node* C = getNode();
	if (A == 0) {
		C->element = B->element;
		C->next = Union(A, B->next);
	}
	else if (B == 0) {
		C->element = A->element;
		C->next = Union(A->next, B);
	}
	else {
		if (A->element < B->element) {
			C->element = A->element;
			C->next = Union(A->next, B);
		}
		else if (A->element > B->element) {
			C->element = B->element;
			C->next = Union(A, B->next);
		}
		else {
			C->element = A->element;
			C->next = Union(A->next, B->next);
		}
	}
	return C;
}
node* Intersect(node* A, node* B) {
	if (A == 0 || B == 0) return 0;
	if (A->element < B->element) {
		return Intersect(A->next, B);
	}
	else if (A->element > B->element) {
		return Intersect(A, B->next);
	}
	else {
		node* C = getNode();
		C->element = A->element;
		C->next = Intersect(A->next, B->next);
		return C;
	}
}

void print(node* S) {
	if (S->next==0) printf(" %d", S->element);
	else {
		S=S->next;
		while (1) {
			printf(" %d", S->element);
			if (S->next == 0) break;
			S = S->next;
		}
	}
	printf("\n");
}
