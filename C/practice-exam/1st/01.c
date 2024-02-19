#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

void input(int* p, int M);
int* sel_max(int* p, int M);
void output(int* p, int N);

int main(void) {
	int in[100], out[100], * max, i, N, M;
	scanf("%d %d", &N, &M);
	for (i = 0; i < N; i++) {
		input(in, M);
		max = sel_max(in, M);
		out[i] = *max;
	}
	output(out, N);
	return 0;
}

void input(int* p, int M) {
	for (int* px = p; px < p + M; px++) {
		scanf("%d", px);
	}
}
int* sel_max(int* p, int M) {
	int* px = p, *pp=p;
	int cnt = 0, bcnt = 0, * bcntp = p;
	for (px=p; px < p + M; px++) {
		for (pp = p; pp < p + M; pp++) {
			if (*px == *pp) {
				cnt += 1;
			}
		}
		if (cnt > bcnt) {
			bcnt = cnt;
			bcntp = px;
		}
		cnt = 0;
	}
	return bcntp;
}
void output(int* p, int N) {
	for (int* px = p; px < p + N; px++) printf(" %d", *px);
}
