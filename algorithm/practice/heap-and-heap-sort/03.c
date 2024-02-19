#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int H[100], n, size;
void swap(int* a, int* b);
void inPlaceHeapSort();
void printArray();
void upHeap(int);
void insertitem(int);
void downHeap(int);
void rBuildHeap(int i);
void buildHeap(); //함수 원형

int main() {
	int tmp_n;
	scanf("%d", &tmp_n);
	size = tmp_n;
	for (int i = 1; i <= tmp_n; i++) {
		scanf("%d", &H[i]);
		insertitem(H[i]);
	}
	inPlaceHeapSort();
	printArray();
}


void swap(int* a, int* b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
} // 두 정수 swap

void inPlaceHeapSort() {
	rBuildHeap(1);
	for (int i = n; i >= 2; i--) {
		swap(H + 1, H + i);
		n--;
		downHeap(1);
	}
	return;
} // 제자리 힙정렬

void printArray() {
	for (int i = 1; i <= size; i++) {
		printf("%d ", H[i]);
	}
	printf("\n");
	return;
}

void upHeap(int i) { // 상향 경로를 따라가며 key 교환
	if (i == 1) {
		return;
	} // 루트노드인 경우
	if (H[i] <= H[i / 2]) {
		return;
	} // 이미 부모 노드보다 작은 경우
	swap(H + i, H + i / 2); // 나머지 위반 경우 수행 (상향 이동)
	upHeap(i / 2); // 상향 경로(부모인덱스 대입)를 따라감
}

void insertitem(int key) {
	H[++n] = key; // n값 갱신 후 key값 대입
	upHeap(n); // 상향 경로를 따라 힙 정렬
}

void downHeap(int i) { // 루트로부터 하향 경로를 따라가며 key  교환
	int bigger;
	if ((n < (i * 2)) && (n < (i * 2 + 1))) {
		return;
	} // 외부 노드일 경우
	bigger = i * 2; // 왼쪽 자식 대입
	if (n >= (i * 2 + 1)) { // 오른쪽 자식보다 n이 클 경우 (위반)
		if (H[i * 2 + 1] > H[bigger]) { // 오른쪽 자식이 왼쪽 자식보다 클 경우 
			bigger = i * 2 + 1; // 오른쪽 자식 대입
		}
	}
	if (H[i] >= H[bigger]) { // 부모노드(자신)과 좌/우 중 
		return;
	} // 부모노드(자신)가 좌/우 중 큰 자식보다 클 경우
	swap(H + i, H + bigger); //나머지 위반 경우 수행 (하향 이동)
	downHeap(bigger); // 하향 경로(자식 노드 대입)를 따라감
}

void rBuildHeap(int i) {
	if (i > n) {
		return;
	} // n보다 크다면 예외
	rBuildHeap(2 * i); // 좌
	rBuildHeap(2 * i + 1); // 우
	downHeap(i); // 하향식 정렬
	return;
} // 재귀버전 힙

void buildHeap() {
	for (int i = n / 2; i >= 1; i--) {
		downHeap(i);
	}
	// n/2 보다 큰 경우 단독 내부노드로서 힙의 조건을 이미 만족하므로
	// 그 전 트리를 힙화
} // 비재귀버전 힙 (배열일 경우에만 활용)
