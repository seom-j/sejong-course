#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int r, f = 1;
int isEmpty(int* Q, int q, int f, int r);
int isFull(int* Q, int q, int f, int r);
int enqueue(int* Q, int q, int f, int r, int e);
int dequeue(int* Q, int q, int f, int r);

int main() {
	int q, n, e, flag;
	scanf("%d %d", &q, &n);
	char c;
	r = q;
	int* Q = (int*)calloc(q, sizeof(int));
	for (int i = 0; i < n; i++) {
		getchar();
		scanf("%c", &c);
		if (c == 'I') {
			scanf("%d", &e);
			r = enqueue(Q, q, f, r, e);
			if (r > q) {
				printf("overflow");
				for (int j = 0; j < q; j++) printf(" %d", Q[j]);
				printf("\n");
				break;
			}
		}
		if (c == 'D') {
			f = dequeue(Q, q, f, r);
			if (f > q) {
				printf("underflow\n");
				break;
			}
		}
		if (c == 'P') {
			for (int j = 0; j < q; j++) printf(" %d", Q[j]);
			printf("\n");
		}
	}
}
int isEmpty(int* Q, int q, int f, int r) {
	return (r + 1) % q == f;
}
int isFull(int* Q, int q, int f, int r) {
	return (r + 2) % q == f;
}
int enqueue(int* Q, int q, int f, int r, int e) {
	if (isFull(Q, q, f, r)) return q + 1; // 가득 찬 경우
	r = (r + 1) % q;
	Q[r] = e;
	return r;
}
int dequeue(int* Q, int q, int f, int r) {
	if (isEmpty(Q, q, f, r)) return q + 1; // 비어있는 경우
	Q[f] = 0;
	f = (f + 1) % q;
	return f;
}
