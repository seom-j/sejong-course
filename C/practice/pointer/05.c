#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main(void) {
	int x[5], r[5];

	for (int* px = x; px < x + 5; px++) scanf("%d", px);

	for (int* px = x, *pr = r; px < x + 5; px++, pr++) {
		*pr = 1;
		for (int* qx = x; qx < x + 5; qx++) {
			if (*px < *qx) *pr += 1;
		}
	}
	
	for (int* px = x, *pr = r; px < x + 5; px++, pr++) printf("%d=r%d ", *px, *pr);
}
