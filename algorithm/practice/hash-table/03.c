#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int* hashTable;
int M, n, q;

int h1(int);
int h2(int);
int getNextBucket(int, int, int);
void insertItem(int);
void searchItem(int);
void printTable();

int main() {
	int key;
	char com;
	scanf("%d %d %d", &M, &n, &q);
	hashTable = (int*)calloc(M, sizeof(int));
	getchar();
	while (1) {
		scanf("%c", &com);
		if (com == 'i') {
			scanf("%d", &key);
			insertItem(key);
		}
		if (com == 's') {
			scanf("%d", &key);
			searchItem(key);
		}
		if (com == 'p') {
			printTable();
		}
		if (com == 'e') {
			printTable();
			break;
		}
		getchar();
	}
	free(hashTable);
}

int h1(int x) {
	return x % M;
}
int h2(int x) {
	return q - (x % q);
}
int getNextBucket(int v, int i, int x) {
	return (v + i * h2(x) % M) % M;
}
void insertItem(int x) {
	int v = h1(x), i = 0, b;
	while (i < M) {
		b = getNextBucket(v, i, x);
		if (hashTable[b] == 0) {
			hashTable[b] = x;
			for (int j = 0; j < i; j++) {
				printf("C");
			}
			printf("%d\n", b);
			return;
		}
		else {
			i++;
		}
	}
}
void searchItem(int x) {
	int v = h1(x), i = 0, b;
	while (i < M) {
		b = getNextBucket(v, i, x);
		if (hashTable[b] == 0) {
			printf("-1\n");
			return;
		}
		else if (hashTable[b] == x) {
			printf("%d %d\n", b, hashTable[b]);
			return;
		}
		else {
			i++;
		}
	}
	printf("-1\n");
}
void printTable() {
	for (int i = 0; i < M; i++) {
		printf(" %d", hashTable[i]);
	}
	printf("\n");
}
