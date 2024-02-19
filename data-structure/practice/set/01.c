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
int subset(node* A, node* B);
int member(e);

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

	printf("%d", subset(AH, BH));
}

node* getNode() { return (node*)calloc(1, sizeof(node)); }

void addLast(node* S, int n) {
	node* p = getNode();
	while (S->next != 0) S = S->next;
	p->element = n;
	S->next = p;
}

int subset(node* A, node* B) {
	if (A == 0) return 0;
	node* p = A;
	while (1) {
		if (member(B, p->element)) {
			if (p->next == 0) return 0;
			else p = p->next;
		}
		else return p->element;
	}
}
int member(node*A, int e) {
	if (A == 0) return 0;
	node* p = A;
	int a;
	while (1) {
		a = p->element;
		if (a < e) {
			if (p->next == 0) return 0;
			else p = p->next;
		}
		else if (a > e) return 0;
		else return 1;
	}
}
