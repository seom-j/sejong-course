#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

typedef struct node {
	char elem;
	struct node* prev, * next;
}node;

node* getNode();
void add(node* list, int r, char e);
void delete(node* list, int r);
char get(node* list, int r);
void print(node* list);

int main() {
	node* H = getNode();
	node* T = getNode();
	node* p = H;
	H->next = T;
	T->prev = H;
	int n;
	char in[100] = { '\0', };

	scanf("%d", &n);
	getchar();
	for (int i = 0; i < n; i++) {
		gets(in);
		if (atoi(in + 2) < 1) {
			printf("invalid position");
			continue;
		}
		if (in[0] == 'A') add(H, atoi(in + 2), in[strlen(in) - 1]);
		if (in[0] == 'D') delete(H, atoi(in + 2));
		if (in[0] == 'G') {
			if (get(H, atoi(in + 2)) == 0) continue;
			printf("%c\n", get(H, atoi(in + 2)));
		}
		if (in[0] == 'P') print(H);
	}
}

node* getNode() {
	return (node*)calloc(1, sizeof(node));
}

void add(node* list, int r, char e) {
	int ch = 0;
	node* p = list;
	for (int i = 1; i <= r; i++) {
		if (ch == 1) {
			printf("invalid position\n");
			return;
		}
		p = p->next;
		if (p->next == NULL) ch = 1;
	}
	node* q = getNode();
	q->elem = e;
	q->prev = p->prev;
	q->next = p;
	(p->prev)->next = q;
	p->prev = q;
}

void delete(node* list, int r) {
	int ch = 0;
	node* p = list;
	for (int i = 1; i <= r; i++) {
		if (ch == 1) {
			printf("invalid position\n");
			return;
		}
		p = p->next;
		if (p->next == NULL) ch = 1;
	}
	if (p->next == NULL) {
		printf("invalid position\n");
		return 0;
	}
	(p->prev)->next = p->next;
	(p->next)->prev = p->prev;
	free(p);
}

char get(node* list, int r) {
	int ch = 0;
	node* p = list;
	for (int i = 1; i <= r; i++) {
		if (ch == 1) {
			printf("invalid position\n");
			return 0;
		}
		p = p->next;
		if (p->next == NULL) ch = 1;
	}
	if (p->next == NULL) {
		printf("invalid position\n");
		return 0;
	}
	return p->elem;
}

void print(node* list) {
	node* p = list;
	while (p->next->next != NULL) {
		p = p->next;
		printf("%c", p->elem);
	}
	printf("\n");
}
