#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <Windows.h>
#pragma warning(disable:4996)


int MAX = 30;
int* A, * H;
int* m;
// 필요 전역변수 선언

int airtelDC(int n, int s, int d);
int airtelDP(int n, int s, int d);
// 함수 원형 선언

int main() {
	A = (int*)calloc(MAX, sizeof(int)); // 항공료
	H = (int*)calloc(MAX, sizeof(int)); // 숙박비
	m = (int*)calloc(MAX, sizeof(int)); // 동적 알고리즘을 위한 추가 공간
	// 모두 calloc을 통해 0으로 초기화 된 상태

	int sample[4][2] = {{0,4},{2,5}, {2,4},{1,28}}; // 샘플 출발지, 도착지
	int minc=0, mind=0; // 각 방법 별 최소요금

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff; // 시간측정을 위한 변수

	A[1] = 1;
	for (int i = 2; i < MAX; i++) {
		A[i] = A[i - 1] + A[i - 1] % 5 + 3;
	}
	H[1] = 5;
	for (int i = 2; i < MAX; i++) {
		H[i] = (H[i - 1] + i)%9 + 1;
	} // 거리별, 인덱스별 알맞은 금액으로 초기화

	printf("n    s    d    mincost    version    cputime    \n"); // 카테고리

	// 각 샘플에 맞는 요소들 출력
	int n = 6, i = 0;
	for (i = 0; i < 3; i++) { 
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		minc = airtelDC(n, sample[i][0], sample[i][1]);
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;

		printf("%-4d %-4d %-4d %-10d DC         %-.08lf\n", n, sample[i][0], sample[i][1], minc, (1000 * (double)diff.QuadPart / (double)ticksPerSec.QuadPart));
		
		
		QueryPerformanceFrequency(&ticksPerSec);
		QueryPerformanceCounter(&start);
		mind = airtelDP(n, sample[i][0], sample[i][1]);
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		
		printf("%-4d %-4d %-4d %-10d DP         %-.08lf\n", n, sample[i][0], sample[i][1], mind, (1000 * (double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	}
	n = MAX;
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	minc = airtelDC(n, sample[i][0], sample[i][1]);
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%-4d %-4d %-4d %-10d DC         %-.08lf\n", n, sample[i][0], sample[i][1], minc, (1000 * (double)diff.QuadPart / (double)ticksPerSec.QuadPart));
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	mind = airtelDP(n, sample[i][0], sample[i][1]);
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%-4d %-4d %-4d %-10d DP         %-.08lf\n", n, sample[i][0], sample[i][1], mind, (1000 * (double)diff.QuadPart / (double)ticksPerSec.QuadPart));
}

int airtelDC(int n, int s, int d) {
	if (d == s) return 0;
	int mincost = 50000, cost = 0;
	for (int i = s; i < d; i++) {
		if (i != s) {
			cost = airtelDC(n, s, i) + H[i] + A[d - i];
		} // 경유지까지의 최소비용(재귀) + 경유지 숙박비 + 항공비
		else{
			cost = A[d - s];
		} // 한번에 갈 경우 (경우지를 거치지 않는 경우) 항공비만 소요
		mincost = min(mincost, cost);
	}
	return mincost; // 이에 따른 최솟값 반환
}

int airtelDP(int n, int s, int d) {
	int cost = 0;
	m[s] = 0;
	for (int D = s + 1; D <= d; D++) {
		m[D] = 50000;
		for (int j = s; j < D; j++) {
			if (j != s) {
				cost = m[j] + H[j] + A[D - j];
			}  // 경유지까지의 최소비용 + 경유지 숙박비 + 항공비
			else {
				cost = A[D - s];
			} // 한번에 갈 경우 (경우지를 거치지 않는 경우) 항공비만 소요
			m[D] = min(m[D], cost);
		}
	}
	return m[d];// 이에 따른 최솟값 반환
}
