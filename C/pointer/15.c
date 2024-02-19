#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

void ABC(int*, int);

int main(void) {
	int x[10];
	for (int* px = x; px < x + 10; px++) scanf("%d", px);
	for (int* px = x, i = 10; px < x + 10; px++, i--) ABC(px, i);
	for (int* px = x; px < x + 10; px++) printf(" %d", *px);
}

void ABC(int* x, int k) {
	int f = 0, tmp;
	for (int* px = x; px < x + k; px++) {
		f = 0;
		for (int* qx = x; qx < x + k; qx++) {
			if (*px < *qx) f = 1;
		}
		if (f == 0) {
			tmp = *px;
			*px = *x;
			*x = tmp;
		}
	}
}
