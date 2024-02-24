#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#pragma warning(disable:4996)

struct print {
	int Total, f_one, s_one;
	double f_cputime, s_cputime;
};
typedef struct print pr;

int countOnesButSlow(int* A[], int n);
int countOnes(int* A[], int n);

int main(void) {
	int n;
	int** A, pidx = 0;
	int kTotal, k_b, k_a;
	pr print[3];
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	srand(time(NULL)); // 매번 다르도록

	for (int i = 1; i < 4; i++) {
		n = i * 1000;
		kTotal = 0; k_b = n; k_a = 0;
		A = (int**)malloc(n * sizeof(int*));
		if (A == NULL) return -1;
		for (int i = 0; i < n; i++) {
			A[i] = (int*)malloc(n * sizeof(int));
			if (A[i] == NULL) return -1;
		} // 동적할당
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) A[i][j] = 0;
		} // 우선 0으로 초기화
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= k_b * 0.9; j++) {
				A[i][j] = 1;
				k_a += 1; // 1 설정 후 개수 추가
			} // 이전 줄 혹은 첫째줄일경우 n의 갯수의 0.9배 만큼은 1로 초기화
			for (int j = k_b * 0.9 + 1; j < k_b; j++) {
				A[i][j] = rand() % 2; // 이후의 비트는 우선 0 또는 1을 받음
				if (A[i][j] == 0) break; // 0이 나올 경우 뒤에 1이 없도록 중지 (뒷 숫자들은 0으로 초기화되어있음)
				k_a += 1; // 1 설정 후 개수 추가
			}
			kTotal += k_a; // 그 줄의 1의 개수를 총 합에 더하기
			k_b = k_a; // (전) 줄의 1의 개수 저장
			k_a = 0; // 다음 줄을 위해 줄별 1의 개수 초기화
		}
		print[pidx].Total = kTotal;
		print[pidx].f_one = countOnes(A, n);
		print[pidx].s_one = countOnesButSlow(A, n);
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		countOnes(A, n);
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		print[pidx].f_cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		countOnesButSlow(A, n);
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		print[pidx].s_cputime = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000;
		pidx++; // 각 변수에 필요한 값 저장 & 인덱스 증가
		for (int i = 0; i < n; i++) {
			if (A[i] != NULL) free(A[i]);
		}
		if (A != NULL) free(A); // 동적 할당 해제
	}

	printf("%d, %d, %.9f ms\n", print[2].Total, print[2].f_one, print[2].f_cputime);
	printf("%d, %d, %.9f ms\n", print[0].Total, print[0].f_one, print[0].f_cputime);
	printf("%d, %d, %.9f ms\n", print[1].Total, print[1].f_one, print[1].f_cputime);

	printf("%d, %d, %.9f ms\n", print[2].Total, print[2].s_one, print[2].s_cputime);
	printf("%d, %d, %.9f ms\n", print[0].Total, print[0].s_one, print[0].s_cputime);
	printf("%d, %d, %.9f ms\n", print[1].Total, print[1].s_one, print[1].s_cputime);
	// 문제 순서에 따라 출력
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
} // 각 행에서 왼쪽에서 오른쪽으로 이동하면서 1의 개수를 세는 간단한 방식

int countOnes(int* A[], int n) {
	int cnt = 0, jd = n - 1; // 1의 개수 cnt, x축 인덱스 jd 설정
	for (int i = 0; i < n; i++) { // n-1 줄 동안
		while (A[i][jd] == 0) jd--; // 0이면 왼쪽으로 (아래 행보다 위 행잉 작지 않음)
		if (A[i][jd] == 1 && jd >= 0) { // 해당 칸이 1이면서 jd >= 0이면 jd+1줄 cnt 더하기 (모든 칸이 0인 경우 대비)
			cnt += jd + 1;
		} // 더하기 완료면 줄바꿈
	}
	return cnt;
} //각 행을 역순으로 순회하면서 1의 개수를 세는 방식
