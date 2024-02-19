#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int* Dictionary; // 사전
int front; // 작으면서 가장 큰 수의 위치

int findIdx(int key, int left, int right);

int main() {
	int n, key, idx;
	scanf("%d %d", &n, &key);

	Dictionary = (int*)calloc(n, sizeof(int));

	for (int i = 0; i < n; i++) {
		scanf("%d", &Dictionary[i]);
	}

	idx = findIdx(key, 0, n - 1);

	if (idx == -1) {
		if (front != NULL) {
			printf(" %d", front);
		}
		else {
			printf(" %d", idx);
		}
	}
	else {
		printf(" %d", idx);
	} // 경우에 따른 출력

	return 0;
}


int findIdx(int key, int left, int right) {
	int mid;
	if (left > right) return -1; // k가 존재하지 않는 경우

	mid = (left + right) / 2;
	if (key == Dictionary[mid]) {
		return mid;
	}

	else if (key < Dictionary[mid]) {
		return findIdx(key, left, mid - 1);
	} // 좌

	else {
		front = mid;
		return findIdx(key, mid + 1, right);
	} // 우
}
