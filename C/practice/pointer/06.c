#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main(void) {
	char x[10], *b_p = x;
	int cnt = 0, b_cnt = 0;
	for (char* px = x; px < x + 10; px++) scanf("%c", px);

	for (char* px = x; px < x + 10; px++) {
		for (char* qx = x; qx < x + 10; qx++) {
			if (*px == *qx)  cnt += 1;
		}
		if (cnt > b_cnt) {
			b_cnt = cnt;
			b_p = px;
		}
		cnt = 0;
	}

	printf("%c %d", *b_p, b_cnt);
}
