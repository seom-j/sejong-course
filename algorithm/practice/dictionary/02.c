#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int* Dictionary = 0; // 사전
int front = -1; // 작으면서 가장 큰 수의 위치 (범위 밖의 수로 초기화)

int findIdx(int key, int n);

int main() {
	int n, key, idx;
	scanf("%d %d", &n, &key);

	Dictionary = (int*)calloc(n, sizeof(int));

	for (int i = 0; i < n; i++) {
		scanf("%d", &Dictionary[i]);
	}

	idx = findIdx(key, n); // 함수 호출

	if (idx == -1) {
		if (front == -1) {
			printf(" %d", n);
		}
		else {
			printf(" %d", front);
		}
	}
	else {
		printf(" %d", idx);
	} // 경우에 따른 출력

	return 0;
}


int findIdx(int key, int n) {
	int left = 0;
	int right = n - 1;
	int mid;

	while (left <= right) {
		mid = (left + right) / 2;
		if (key == Dictionary[mid]) {
			return mid;
		}
		else if (key < Dictionary[mid]) {
			front = mid;
			right = mid - 1; // 왼쪽 경우를 보기 위해 오른쪽 줄이기
		}
		else {
			left = mid + 1; // 오른쪽 경우를 보기 위해 왼쪽 늘이기
		}
	}

	return -1;
}
