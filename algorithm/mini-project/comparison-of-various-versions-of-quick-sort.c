#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>	
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

typedef struct Index {
	int a, b;
}index; // a, b쌍을 위한 구조체

int n = 100000;
int Limits[4] = { 1, 100, 500, 1000 };
char* modeList[4] = { "deterministic1", "deterministic3", "randomized1","randomized3" };
char* mode;
int limit; // 필요 전역변수 선언

void swap(int*, int*);
int* copyof(int* tA, int* A);
int* createArray();
index inPlacePartition(int* arr, int left, int right, int k);
void quickSort(int* A, int n);
void rQuickSort(int* arr, int left, int right);
void insertionSort(int* A, int n);
int findMedian(int* A, int a, int b, int c);
int findPivot(int* A, int l, int r);
// 함수 원형 선언

void main() {
	int* A = createArray();
	int* tA = (int*)calloc(n, sizeof(int));
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	printf("%-15s", "Limit");
	printf(" %-15s", "결정적1");
	printf(" %-15s", "결정적3");
	printf(" %-15s", "무작위1");
	printf(" %-15s", "무작위3");
	printf("\n"); // 출력 예시와 같게 출력

	for (int i = 0; i < 4; i++) {
		limit = Limits[i];
		printf("%-15d", limit);
		for (int j = 0; j < 4; j++) {
			mode = modeList[j];
			copyof(tA, A);
			QueryPerformanceFrequency(&ticksPerSec);
			QueryPerformanceCounter(&start);
			quickSort(tA, n);
			QueryPerformanceCounter(&end); 
			diff.QuadPart = end.QuadPart - start.QuadPart;
			printf(" %-13.09fms", (1000 * (double)diff.QuadPart / (double)ticksPerSec.QuadPart));
		}
		printf("\n");
	}
	free(tA);
	free(A); // 동적 할당 해제
	return 0;
} // 과제 요구사항과 동일



int* copyof(int* tA, int* A) {
	for (int i = 0; i < n; i++) {
		tA[i] = A[i];
	}
	return tA;
} // 임의의 장소 tA에 A를 복제

int* createArray() {
	int* A = (int*)calloc(n, sizeof(int));
	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++) {
		A[i] = (rand() % n) + 1;
	}
	return A;
} // A를 n개의 난수로 초기화

void quickSort(int* A, int n) {
	rQuickSort(A, 0, n - 1);
	if (limit > 1) {
		insertionSort(A, n);
	}
}// 조건에 맞는 퀵정렬 후 삽입정렬

void rQuickSort(int* A, int left, int right) {
	if (right - left >= limit) {
		int k = findPivot(A, left, right);
		index I = inPlacePartition(A, left, right, k);
		rQuickSort(A, left, (I.a - 1));
		rQuickSort(A, (I.b + 1), right);
	}
} // 퀵정렬 (분할 크기가 limit보다 작아질 때 까지)

index inPlacePartition(int* A, int left, int right, int k) {
	if (right <= left) {
		return;
	}
	swap(A + k, A + left);
	int idxPivotLeft = left, idxMove = left + 1, idxChangeRight = right;
	while (idxMove <= idxChangeRight) { // idxMove를 움직여가며
		if (A[idxMove] == A[idxPivotLeft]) { // 피봇과 같을 경우                                                                                            
			idxMove++; // 이동
		}
		else if (A[idxMove] < A[idxPivotLeft]) { // 피봇보다 작을 경우
			swap(A + idxMove, A + idxPivotLeft); // swap
			idxPivotLeft++; // 이동
			idxMove++; // 이동
		}
		else { // 피봇보다 클 경우
			swap(A + idxMove, A + idxChangeRight); // swap
			idxChangeRight--; // 이동
		}
	} // idxMove을 움직이며 피봇과 비교하였을때 작을 경우 교환, 클 경우 idxChangeRight와 교환
	index I;
	I.a = idxPivotLeft; // 피봇과 동일한 수의 배열의 가장 왼쪽 경계
	I.b = idxChangeRight; // 피봇과 동일한 수의 배열의 가장 오른쪽 경계
	return I;
} // Index 이동하며 정렬 (중복 키 허용)

void insertionSort(int* A, int n) {
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = A[i];
		for (j = i - 1; j >= 0 && A[j] > key; j--) {
			A[j + 1] = A[j];
		} // 밀기
		A[j + 1] = key; // 대입
	}
} // 삽입정렬 알고리즘

int findPivot(int* A, int l, int r) {
	if (strcmp(mode, "deterministic1") == 0) { // 결정적 1 일때
		return r;
	} // 가장 오른쪽 수
	if (strcmp(mode, "randomized1") == 0) { // 무작위 1 일때
		srand((unsigned)time(NULL));
		return (((long)rand() << 15) % (r - l + 1) + l);
	} // r부터 l 사이의 난수 
	if (strcmp(mode, "deterministic3") == 0) { // 결정적 3 일때
		return findMedian(A, l, (l + r) / 2, r);
	} // l, (l+r)/2, r 중 중앙값
	if (strcmp(mode, "randomized3") == 0) {
		srand((unsigned)time(NULL));
		return findMedian(A, (((long)rand() << 15) % (r - l + 1) + l), (((long)rand() << 15) % (r - l + 1) + l), (((long)rand() << 15) % (r - l + 1) + l));
	} // r부터 l 사이의 세 난수 중 중앙값
} // 과제 요구사항에 맞는 피봇 반환 함수

int findMedian(int* A, int idxa, int idxb, int idxc) {
	if (A[idxa] >= A[idxb]) {
		if (A[idxb] >= A[idxc]) {
			return idxb;
		}
		else if (A[idxa] <= A[idxc]) {
			return idxa;
		}
		else {
			return idxb;
		}
	}
	else if (A[idxc] < A[idxa]) {
		return idxa;
	}
	else if (A[idxb] > A[idxc]) {
		return idxc;
	}
	else {
		return idxb;
	}
} // 중앙값 반환 함수

void swap(int* a, int* b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
} // a, b 교환 함수
