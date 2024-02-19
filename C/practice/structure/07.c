#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct num {
	int n, r;
};
int main(void) {
	struct num x[10];

	for (int i = 0; i < 10; i++) scanf("%d", &x[i].n);

	for (int i = 0; i < 10; i++) {
		x[i].r = 1;
		for (int j = 0; j < 10; j++) {
			if (x[i].n < x[j].n) x[i].r += 1;
		}
	}

	for (int i = 0; i < 10; i++) if (x[i].r == 3) printf("%d ", x[i].n);
	for (int i = 0; i < 10; i++) if (x[i].r == 7) printf("%d", x[i].n);

	return 0;
}
