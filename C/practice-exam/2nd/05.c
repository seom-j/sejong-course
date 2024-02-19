#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int check_row(int** p, int M, int N);
int check_col(int** p, int M, int N);

int main(void) {
	int m, n, x, y, z;
	scanf("%d %d", &m, &n);
	int** p;
	p = (int**)malloc(sizeof(int*) * m);
	if (p == NULL) return -1;
	for (int i = 0; i < m; i++) {
		p[i] = (int*)malloc(sizeof(int) * n);
		if (p[i] == NULL) return -1;
		for (int j = 0; j < n; j++) p[i][j] = 0;
	}
	for (;;) {
		scanf("%d %d %d", &x, &y, &z);
		if (x == 0 && y == 0 && z == 0) break;
		p[x][y] = z;
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) printf(" %d", p[i][j]);
		printf("\n");
	}

	if (check_col(p, m, n) > check_row(p, m, n)) printf("%d", check_col(p, m, n));
	else printf("%d", check_row(p, m, n));

	for (int i = 0; i < m; i++) {
		if (p[i] != NULL) {
			free(p[i]);
			p[i] = 0;
		}
	}
	if (p != NULL) {
		free(p);
		p = 0;
	}
}

int check_row(int** p, int M, int N) {
	int cnt = 0, b_cnt = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (p[i][j] == 0) cnt += 1;
			else {
				if (b_cnt < cnt) b_cnt = cnt;
				cnt = 0;
			}
		}
		if (b_cnt < cnt) b_cnt = cnt;
		cnt = 0;
	}
	return b_cnt;
}
int check_col(int** p, int M, int N) {
	int cnt = 0, b_cnt = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (p[j][i] == 0) cnt += 1;
			else {
				if (b_cnt < cnt) b_cnt = cnt;
				cnt = 0;
			}
		}
		if (b_cnt < cnt) b_cnt = cnt;
		cnt = 0;
	}
	return b_cnt;
}
