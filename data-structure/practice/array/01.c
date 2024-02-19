#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int main(void) {
	int xn, cn, x[100] = { NULL }, s, e, tmp;
	scanf("%d", &xn);
	for (int i = 0; i < xn; i++) scanf("%d", &x[i]);
	scanf("%d", &cn);
	for (int i = 0; i < cn; i++) {
		scanf("%d %d", &s, &e);
		for (int j = s, k = e; j <= s + (e - s) / 2; j++, k--) {
			tmp = x[j];
			x[j] = x[k];
			x[k] = tmp;
		}
	}
	for (int i = 0; i < xn; i++) printf(" %d", x[i]);
}
