#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

typedef struct node {
	int key;
	struct node* next;
}node;

struct node* hashTable;
int M;

int h(int);
node* getNode();
void insertItem(int);
int searchItem(int);
int deleteItem(int);
void printTable();
void freeTable();

int main(){
	int key;
	char com;
	scanf("%d", &M);
	getchar();
	hashTable = (node*)calloc(M, sizeof(node));

	while (1) {
		scanf("%c", &com);
		if (com == 'i') {
			scanf("%d", &key);
			insertItem(key);
		}
		if (com == 's') {
			scanf("%d", &key);
			printf("%d\n", searchItem(key));
		}
		if (com == 'd') {
			scanf("%d", &key);
			printf("%d\n", deleteItem(key));
		}
		if (com == 'p') {
			printTable();
		}
		if (com == 'e') {
			break;
		}
		getchar();
	}
	freeTable();
}

int h(int x) {
	return x % M;
}
node* getNode() {
	return (node*)calloc(1, sizeof(node));
}
void insertItem(int x) {
	int v = h(x);
	node* p = hashTable + v;
	node* newNode = getNode();
	newNode->key = x;
	newNode->next = NULL;
	if (p->next == NULL) {
		p->next = newNode;
	}
	else {
		newNode->next = p->next;
		p->next = newNode;
	}
}
int searchItem(int x) {
	int cnt = 0, v = h(x);
	node* p = hashTable + v;
	if (p->next == NULL) {
		return 0;
	}
	while (1) {
		p = p->next;
		cnt++;
		if (p->key == x) {
			return cnt;
		}
		if (p->next == NULL) {
			return 0;
		}

	}
}
int deleteItem(int x) {
	int cnt = 0, v = h(x);
	node* pTmp = hashTable + v, * p = hashTable + v;
	if (p->next == NULL) {
		return 0;
	}
	while (1) {
		p = p->next;
		cnt++;
		if (p->key == x) {
			while (pTmp->next != p) {
				pTmp = pTmp->next;
			}
			pTmp->next = p->next;
			free(p);
			return cnt;
		}
		if (p->next == NULL) {
			return 0;
		}
	}
}
void printTable() {
	node* p;
	for (int i = 0; i < M; i++) {
		p = hashTable + i;
		if (p->next != NULL) {
			p = p->next;
			printf(" %d", p->key);
			while (p->next != NULL) {
				p = p->next;
				printf(" %d", p->key);
			}
		}
	}
	printf("\n");
}
void freeTable() {
	node* p, * q;
	for (int i = 0; i < M; i++) {
		if ((hashTable + i)->next != NULL) {
			p = (hashTable + i)->next;
			q = p;
			while (q->next != NULL) {
				p = p->next;
				free(q);
				q = p;
			}
		}
	}
	free(hashTable);
}
