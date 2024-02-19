#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int H[100] = { 0 }, n = 0;
void swap(int* a, int* b);
void insertitem(int key);
void downHeap(int i);
int removeMax();
void printHeap();

int main() {
	char command = 0;
	int key = 0;
	int i = 1, j = 2;
	while (command != 'q') {
		scanf("%c", &command);
		if (command == 'i') {
			scanf("%d", &key);
			insertitem(key);
			printf("0\n");
		}
		else if (command == 'd') {
			printf("%d\n", removeMax());
		}
		else if (command == 'p') {
			printHeap();
		}
		getchar();
	} // 각 명령어에 맞는 함수 수행
}
void swap(int* a, int* b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
} // 두 정수 swap
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
int removeMax() {
	int key;
	key = H[1]; // 루트 key값 저장
	H[1] = H[n--]; // 마지막 노드 대입 후 n값 갱신
	downHeap(1); // 루트노드부터 하향식 정렬
	return key; // 삭제된 저장값 반환
}
void printHeap() {
	for (int i = 1; i < n + 1; i++) {
		printf(" %d", H[i]);
	} // 인덱스 1부터 n까지 순차적으로 출력
	printf("\n");
}
