#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int* mid(int*);

int main(void) {
	int x[3] = { 0 };
	for (int* px = x; px < x + 3; px++) scanf("%d", px);
	printf("%d", *mid(x));
}

int* mid(int* x) {
	int tmp;
	for (int* qx = x; qx < x + 2; qx++) {
		for (int* px = x; px < x + 2; px++) {
			if (*px > *(px + 1)) {
				tmp = *px;
				*px = *(px + 1);
				*(px + 1) = tmp;
			}
		}
	}
	return x + 1;
}
