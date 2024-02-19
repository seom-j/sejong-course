#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

void swap(int*, int*);
int findPivot(int*, int, int);
int inPlacePartition(int*, int, int, int);
void inPlaceQuickSort(int*, int, int);
void printArray(int*, int);

int main() {
	int N;
	scanf("%d", &N);

	int* Array = (int*)calloc(N, sizeof(int)); // 동적할당

	for (int i = 0; i < N; i++) {
		scanf("%d", &Array[i]);
	}

	inPlaceQuickSort(Array, 0, N - 1); // 퀵정렬
	printArray(Array, N); // 프린트

	free(Array); // 동적할당 해제

	return 0;
}

void swap(int* a, int* b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}
int findPivot(int* Array, int l, int r) {
	if (r - 1 <= 1) return l;

	srand((unsigned)time(NULL));
	int pivot = (rand() % (r - l)+1) + l; // 기준값 위치 무작위 선택

	return pivot; // 기준값 반환
}
int inPlacePartition(int* Array, int l, int r, int pivot) {
	int p, left = l + 1, right = r;

	p = Array[pivot]; // 기준값 저장

	swap(Array + l, Array + pivot);

	while (left <= right) {
		if (Array[left] < p) {
			left++;
			continue;
		}
		if (Array[right] >= p) {
			right--;
			continue;
		}
		if (left >= right) {
			break;
		}
		swap(Array + left, Array + right);
	}
	swap(Array + left - 1, Array + l);

	return right;
}
void inPlaceQuickSort(int* Array, int l, int r) {
	int pivot, a, b, tmpb;
	if (l >= r) return;

	pivot = findPivot(Array, l, r);
	b = inPlacePartition(Array, l, r, pivot);
	tmpb = b;

	while (1) {
		if (Array[tmpb] != Array[b]) {
			a = tmpb + 1;
			break;
		}
		tmpb--;
	} // a 인덱스 저장

	inPlaceQuickSort(Array, l, a - 1);
	inPlaceQuickSort(Array, b + 1, r);

	return;
}
void printArray(int* Array, int N) {
	for (int i = 0; i < N; i++) {
		printf(" %d", Array[i]);
	}
	printf("\n");

	return;
}
