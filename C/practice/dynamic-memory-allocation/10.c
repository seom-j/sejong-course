#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main(void) {
	int n, num = 0;
	scanf("%d", &n);
	int* p, *q;
	p = (int*)malloc(n * sizeof(int));
	if (p == NULL) return -1;
	q = (int*)malloc((n - 1) * sizeof(int));
	if (q == NULL) return -1;


	for (int* pp = p; pp < p + n; pp++, num++) {
		*pp = num;
	}
	num = 0;
	
	for (int* qq = q; qq < q + n - 1; qq++, num++) {
		if (num == n / 2) num += 1;
		*qq = num;
		printf(" %d", *qq);
	}
	if (p != NULL) {
		free(p);
		p = 0;
	}
	if (q != NULL) {
		free(q);
		q = 0;
	}
}
