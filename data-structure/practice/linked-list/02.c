#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

typedef struct node {
	int coef, exp;
	struct node* next;
}node;

node* getNode();
void appendTerm(node*, int, int);
node* addpoly(node*, node*);
void print(node*);

int main() {
	node* H1 = getNode();
	node* H2 = getNode();
	int n, c, e;
	scanf("%d", &n);
	for (int j = 0; j < n; j++) {
		scanf("%d %d", &c, &e);
		appendTerm(H1, c, e);
	}
	scanf("%d", &n);
	for (int j = 0; j < n; j++) {
		scanf("%d %d", &c, &e);
		appendTerm(H2, c, e);
	}
	print(addpoly(H1, H2));
}

node* getNode() {
	return (node*)calloc(1, sizeof(node));
}

void appendTerm(node* k, int c, int e) {
	while (k->next != NULL) {
		k = k->next;
	}
	node* t = getNode();
	t->coef = c;
	t->exp = e;
	t->next = NULL;
	k->next = t;
}

node* addpoly(node* x, node* y) {
	node* result = getNode(), * i = x->next, * j = y->next, * k = result;
	int sum;
	result->next = NULL;
	while (i != NULL && j != NULL) {
		if (i->exp > j->exp) {
			appendTerm(k, i->coef, i->exp);
			i = i->next;
		}
		else if(i->exp < j->exp) {
			appendTerm(k, j->coef, j->exp);
			j = j->next;
		}
		else {
			sum = i->coef + j->coef;
			if (sum != 0) appendTerm(k, sum, i->exp);
			i = i->next;
			j = j->next;
		}
	}
	while (i != NULL) {
		appendTerm(k, i->coef, i->exp);
		i = i->next;
	}
	while (j != NULL) {
		appendTerm(k, j->coef, j->exp);
		j = j->next;
	}
	return result;
}

void print (node* k) {
	node* p = k;
	while (p->next != NULL) {
		p = p->next;
		printf(" %d %d", p->coef, p->exp);
	}
}
