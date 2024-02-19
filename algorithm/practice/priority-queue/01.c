#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int main() {
	int n, *list, maxLoc, tmp; 
	// 동적할당 개수 n, list, 최댓값 저장 변수 maxLoc, switch용 tmp 선언
	scanf("%d", &n);
	list = (int*)malloc(n * sizeof(int));
	for (int* p = list; p < list + n; p++) {
		scanf("%d", p);
	} // 배열 값 입력
	for (int pass = n - 1; pass >= 0; pass--) {
		maxLoc = pass;
		for (int j = 0; j < pass; j++) {
			if (list[j] > list[maxLoc]) {
				maxLoc = j;
			} // 최댓값 위치 저장
		}
		tmp = list[pass];
		list[pass] = list[maxLoc];
		list[maxLoc] = tmp; // 최댓값과 현재위치 변경
		// 선택정렬 수행
	}
	for (int* p = list; p < list + n; p++) {
		printf(" %d", *p);
	}
	printf("\n");
	// 배열 값 출력
}
