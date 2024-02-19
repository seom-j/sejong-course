#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int countOnesButSlow(int* A[], int n);
int countOnes(int* A[], int n);

int main(void) {
	int n;
	scanf("%d", &n);
	int** A = (int**)malloc(n * sizeof(int*));
	if (A == NULL) return -1;
	for (int i = 0; i < n; i++) {
		A[i] = (int*)malloc(n * sizeof(int));
		if (A[i] == NULL) return -1;
	} 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) scanf("%d", &A[i][j]);
	} // 동적할당 & 입력받기

	printf("%d\n", countOnesButSlow(A, n));
	printf("%d", countOnes(A, n)); // 출력

	for (int i = 0; i < n; i++) {
		if (A[i] != NULL) free(A[i]);
	}
	if (A != NULL) free(A); // 동적할당 해제
}

int countOnesButSlow(int* A[], int n) {
	int cnt = 0, j = 0;
	for (int i = 0; i < n; i++) {
		j = 0;
		while ((j < n) && (A[i][j] == 1)) {
			cnt += 1;
			j += 1;
		}
	}
	return cnt;
}

int countOnes(int* A[], int n) {
	int cnt = 0, jd = n - 1; // 1의 개수 cnt, x축 인덱스 jd 설정
	for (int i = 0; i < n; i++) { // n-1 줄 동안
		while (A[i][jd] == 0) jd--; // 0이면 왼쪽으로 (아래 행보다 위 행잉 작지 않음)
		if (A[i][jd] == 1 && jd >= 0) { // 해당 칸이 1이면서 jd >= 0이면 jd+1줄 cnt 더하기 (모든 칸이 0인 경우 대비)
			cnt += jd + 1;
		} // 더하기 완료면 줄바꿈
	}
	return cnt;
}
