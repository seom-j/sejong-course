#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#pragma warning(disable:4996)

void swap(int*, int*);
int* buildList(int, int, int);
void insertHeap(int* tmpL, int elem, int n);
int deleteHeap(int* tmpL, int n);
int findKthSmallest(int*, int, int);
void writeList(int*, int); // 함수 원형 선언

int main() {
	int output[4] = { 0 }, e, * L;
	LARGE_INTEGER ticksPerSec1, ticksPerSec2;
	LARGE_INTEGER start1, end1, diff1, start2, end2, diff2; // 변수 선언

	L = buildList(10, 1, 100); // 1과 100 사이의 정수 10개로 구성된 리스트 생성 후 저장
	writeList(L, 10); // L의 정수들 한 라인에 출력 # 출력조건 1

	for (int k = 1; k <= 3; k++) {
		output[k] = findKthSmallest(L, 10, k);
	} // k = 1, 2, 3 일때의 함수 결과값 저장
	printf("%d %d %d\n", output[1], output[2], output[3]); // 결과값 한 라인에 출력 # 출력조건 2

	L = buildList(100000, 1, 1000000); // 1~100만 사이의 정수 10만개로 구성된 리스트 생성 후 저장
	int karray[4] = { 1, 100, 99900, 99999 }; // karray 생성
	for (int i = 0; i < 4; i++) {
		QueryPerformanceFrequency(&ticksPerSec1);
		QueryPerformanceCounter(&start1);
		e = findKthSmallest(L, 100000, karray[i]); // karray로 합수 호출
		QueryPerformanceCounter(&end1);
		diff1.QuadPart = end1.QuadPart - start1.QuadPart;
		printf("%.9f ms", ((double)diff1.QuadPart / (double)ticksPerSec1.QuadPart) * 1000);
		printf(" %d\n", e); // 4개의 라인으로 시간과 k번째 작은 수 출력 # 출력조건 3, 4, 5, 6
	}

	return 0;
}

void swap(int* a, int* b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
} // 두 정수 swap

int* buildList(int n, int min, int max) {
	int* L = (int*)calloc(n + 1, sizeof(int));
	srand((unsigned)time(NULL));
	for (int i = 1; i <= n; i++) {
		L[i] = (rand() % (max - min + 1)) + min; // min ~ max 사이의 난수 대입
	}
	return L; // 무순리스트 반환
} // 랜덤의 min - max 사이의 수들이 들어있는 무순 리스트 생성 & 반환

void insertHeap(int* tmpL, int elem, int n) {
	int i = 0;
	i = ++n;
	while ((i != 1) && elem < tmpL[i / 2]) {
		tmpL[i] = tmpL[i / 2];
		i = i / 2;
	}
	tmpL[i] = elem;
} // 우선순위 큐 삽입

int deleteHeap(int* tmpL, int n) {
	int first, tmp, parent, child;
	first = tmpL[1];
	tmp = tmpL[n--];
	parent = 1;
	child = 2;
	while (child <= n) {
		if ((child < n) && (tmpL[child] > tmpL[child + 1])) {
			child++;
		}
		if (tmp <= tmpL[child]) {
			break;
		}
		tmpL[parent] = tmpL[child];
		parent = child;
		child *= 2;
	}
	tmpL[parent] = tmp;
	return first;
} // 우선순위 큐 삭제

int findKthSmallest(int* L, int N, int k) {
	int cnt = 0;
	int* tmpL = (int*)calloc(N + 1, sizeof(int)); // 임의의 우선순위 큐 생성
	for (int i = 1; i <= N; i++) {
		insertHeap(tmpL, L[i], cnt); // n
		cnt++;
	} // 삽입하는 과정에서 정렬
	for (int i = 1; i < k; i++) {
		deleteHeap(tmpL, cnt); // O(klogn)
		cnt--;
	} // k-1 만큽 삭제
	int p = tmpL[1]; // 루트노드 저장
	free(tmpL); // 임의의 우선순위 큐 해제
	return p; // 저장된 루트노드 반환
} // 임의의 우선순위 큐에 넣고 k-1만큼 삭제한 후, 루트노드를 반환하는 식의 k번째 원소 반환

void writeList(int* L, int n) {
	for (int i = 1; i <= n; i++) {
		printf(" %d", L[i]);
	}
	printf("\n");
} // List 출력
