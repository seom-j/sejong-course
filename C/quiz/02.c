#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

void input(double*, int);
void sort(double*, int);
void output(double*, int);

int main() {
	int n;
	double x[100];
	scanf("%d", &n);
	input(x, n);
	sort(x, n);
	output(x, n);
	
}

void input(double* x, int n) {
	double* px = x, k, e, m;
	for (px = x; px < x + n; px++) {
		scanf("%lf %lf %lf", &k, &e, &m);
		*px = (k + e + m) / 3.0;
	}
}
void sort(double* x, int n) {
	double* pp = x, * px = x, tmp;
	for (pp = x; pp < x + n - 1; pp++) {
		for (px = x; px < x + n - 1; px++) {
			if (*px < *(px + 1)) {
				tmp = *px;
				*px = *(px + 1);
				*(px + 1) = tmp;
			}
		}
	}
}
void output(double* x, int n) {
	double* px = x, * pp = x;
	int ra[100] = { 0, }, *pr = ra;
	for (px = x, pr = ra; px < x + n; px++, pr++) {
		for (pp = x; pp < x + n; pp++) {
			if (*px < *pp) *pr += 1;
		}
		*pr += 1;
	}
	for (px = x, pr = ra; px < x + n; px++, pr++) {
		printf("%d %.2lf\n", *pr, *px);
	}
}
