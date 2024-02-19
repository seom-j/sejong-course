#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int maxi(int x[], int n, int ma);
cnt = 0;

int main(void) {
	int n, x[20] = { NULL };
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &x[i]);
	printf("%d", maxi(x, n, *x));
	return 0;
}

int maxi(int x[], int n, int ma) {
	if (cnt > n) return ma;
	if (x[cnt] > ma) ma = x[cnt];
	cnt += 1;
	maxi(x, n, ma);
}
