#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int main() {
	int n, corrent, *move, *list;
	scanf("%d", &n);
	list = (int*)malloc(n * sizeof(int));
	for (int* p = list; p < list + n; p++) scanf("%d", p);
	for (int* p = list + 1; p < list + n; p++) {
		corrent = *p; // 당시 값 저장
		move = p - 1; // 직전 위치부터
		while ((move >= list) && (*move > corrent)) {
			*(move + 1) = *move;
			move -= 1;
		}//저장해놓은 값보다 작은 값이 나올때까지 밀기
		*(move + 1) = corrent;
	}
	for (int* p = list; p < list + n; p++) printf(" %d", *p);
	printf("\n");
}
