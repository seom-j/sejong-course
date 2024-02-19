#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int main(void) {
	int xn, x[100] = { NULL };
	int cn, c, f_c, b_x, tmp;
	scanf("%d", &xn);
	for (int i = 0; i < xn; i++) scanf("%d", &x[i]);
	scanf("%d", &cn);
	for (int i = 0; i < cn; i++) {
		scanf("%d", &c);
		if (i == 0) {
			f_c = c;
			b_x = x[c];
		}
		if (i == cn - 1) {
			x[c] = b_x;
		}
		else {
			tmp = x[c];
			x[c] = b_x;
			b_x = tmp;
		}
	}
	for (int i = 0; i < xn; i++) printf(" %d", x[i]);
}
