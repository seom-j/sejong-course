#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

void gcdlcm(int, int, int*, int*);

int main(void) {
	int n, m, g = 0, l = 0;
	int *pg = &g, *pl = &l;
	scanf("%d %d", &n, &m);
	gcdlcm(n, m, pg, pl);
	printf("%d %d", g, l);
}

void gcdlcm(int n, int m, int* pg, int* pl) {
	int ma=n, mi=m;
	if (ma < mi) {
		ma = m;
		mi = n;
	}
	for (int i = 1; i <= mi; i++) {
		if (ma % i == 0 && mi % i == 0) *pg = i;
	}
	for (int i = ma * mi; i >= mi; i--) {
		if (i % ma == 0 && i % mi == 0) *pl = i;
	}
}
