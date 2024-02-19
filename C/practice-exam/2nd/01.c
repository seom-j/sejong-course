#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

void input(int* p, int N);
void output(int* p, int K);

int main(void) {
	int m, n, k, midx = 0, nidx = 0, c = 0;
	scanf("%d %d", &m, &n);
	int x[100] = { 0 }, y[100] = { 0 };

	input(x, m);
	input(y, n);

	scanf("%d", &k);

	for (int* px = x; px < x + (m + n) / k; px++) {
		if (c == 0) {
			if (midx + k > m) {
				output(y + nidx, k);
				nidx += k;
			}
			else {
				output(x + midx, k);
				midx += k;
				c = 1;
			}
		}
		else if (c == 1) {
			if (nidx + k > n) {
				output(x + midx, k);
				midx += k;
			}
			else {
				output(y + nidx, k);
				nidx += k;
				c = 0;
			}
		}
	}
}

void input(int* p, int N) {
	for (int* px = p; px < p + N; px++) scanf("%d", px);
}
void output(int* p, int K) {
	for (int* px = p; px < p + K; px++) printf(" %d", *px);
}
