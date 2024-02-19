#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int main(void) {
	int n, x[100][100] = { NULL };
	int id = 0, jd = 0, add = 1;

	scanf("%d", &n);
	for (int i = 1; i <= n * n; i++) {
		x[id][jd] = i;
		if ((jd == 0 && add == 0) || (jd == n-1 && add == 1)) {
			if (add == 0) add = 1;
			else add = 0;
			id++;
			continue;
		}
		if (add == 1) jd++;
		else jd--;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) printf(" %d", x[i][j]);
		printf("\n");
	}
}
