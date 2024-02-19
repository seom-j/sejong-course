#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int* hashTable, M;

int h(int);
int getNextBucket(int, int);
void insertItem(int);
void searchItem(int);

int main() {
	int n, key;
	char com;
	scanf("%d", &M);
	hashTable = (int*)calloc(M, sizeof(int));
	scanf("%d", &n);
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
		if (com == 'e') {
			break;
		}
	}
}

int h(int x) {
	return x % M;
}
int getNextBucket(int v, int i) {
	return (v + i) % M;
}
void insertItem(int x) {
	int v = h(x), i = 0, b;
	while (i < M) {
		b = getNextBucket(v, i);
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
	int v = h(x), i = 0, b;
	while (i < M) {
		b = getNextBucket(v, i);
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
