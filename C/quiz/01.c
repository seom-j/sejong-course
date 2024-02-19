#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int compare(double*, double*);

int main() {
	int n, rank[100] = { 0, }, * pr = rank;
	double x[100], * px = x, k, e, m;

	scanf("%d", &n);
	for (px = x; px < x + n; px++) {
		scanf("%lf %lf %lf", &k, &e, &m);
		*px = (k + e + m) / 3.0;
	}
	for (px = x,pr=rank; px < x + n; px++,pr++) {
		for (double* pxx = x; pxx < x + n; pxx++) {
			if (compare(px,pxx)==0) *pr += 1;
		}
		*pr += 1;
	}
	for (px = x, pr = rank; px < x + n; px++, pr++) {
		printf("%d %.2lf\n", *pr, *px);
	}
}

int compare(double* a, double* b) {
	if (*a >= *b) return 1;
	else return 0;
}
