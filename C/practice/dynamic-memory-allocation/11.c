#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)


int main(void) {
	int* p = (int*)malloc(5 * sizeof(int)), n_cnt = 0, p_cnt = 0;

	for (int *pp=p;;pp++) {
		scanf("%d", pp); // 입력
		if (*pp == -1) break;
		if (n_cnt == 5) {
			p_cnt += 1;
			int* np = (int*)malloc(5 + 3* p_cnt * sizeof(int));
			for (int i = 0; i < 5 + 3 * (p_cnt - 1); i++) *(np + i) = *(p + i);
			free(p);
			p = (int*)malloc(5 + 3 * p_cnt * sizeof(int));
			for (int i = 0; i < 5 + 3 * (p_cnt); i++) *(p + i) = *(np + i);
			free(np);
			pp = p + 5 + 3 * (p_cnt - 1) - 1;
			n_cnt = 0;
		}
		if (p_cnt == 4) break;
	}

	for (int* pp = p; *(pp - 1) != -1; pp++) printf("%d ", *pp);
	if (p != NULL) free(p);
}
