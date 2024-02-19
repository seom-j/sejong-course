#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

typedef struct node {
	int elem;
	struct node* next;
}node;

node* getNode();
void addNode(node*, int);
void partition(node*, node**, node**, int);
node* merge(node*, node*);
void mergeSort(node**, int);
void printNode(node*);
void putNode(node*);

int main() {
	int N, elem;
	node* List = getNode();

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &elem);
		if (i == 0) {
			List->elem = elem;
			List->next = NULL;
		}
		else {
			addNode(List, elem);
		}
	}
	mergeSort(&List, N);
	printNode(List);
	putNode(List);

}
node* getNode() {
	return (node*)calloc(1, sizeof(node)); 
}
void addNode(node* List, int elem) {
	node* q = getNode();
	node* p = List;
	q->elem = elem;
	q->next;
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = q;
}
void partition(node* List, node** pL, node** pR, int size) {
	node* p = List;
	*pL = p; // p의 왼쪽 분할 위치
	for (int i = 0; i < (size / 2) - 1; i++) {
		p = p->next;
	}
	*pR = p->next; // p의 오른쪽 분할 위치
	p->next = NULL;
}
node* merge(node* pL, node* pR) {
	node* p = NULL; // O(1)의 공간 추가 사용
	if (pL == NULL) return pR;
	else if (pR == NULL) return pL; // 하나가 비었을 경우 나머지 연결

	if (pL->elem < pR->elem) { // pL의 elem이 더 작다면
		p = pL; // pL을 저장
		p->next = merge(pL->next, pR);  // pL의 다음 것과 pR을 합병 후 next에 연결
	}
	else { // pR의 elem이 더 작다면
		p = pR; // pR을 저장
		p->next = merge(pL, pR->next); // pR의 다음 것과 pR 합병 후 next에 연결
	}
	return p; // 합병된 리스트 반환
}
void mergeSort(node** List, int size) {
	node* p = *List;
	node* pL, * pR;
	if (size <= 1) return;
	partition(p, &pL, &pR, size);
	if (size % 2 == 0) {
		mergeSort(&pL, size / 2);
		mergeSort(&pR, size / 2);
	}
	else {
		mergeSort(&pL, size / 2);
		mergeSort(&pR, size / 2 + 1);
	}
	*List = merge(pL, pR);
}
void printNode(node* List) {
	node* p = List;
	while (p != NULL) {
		printf(" %d", p->elem);
		p = p->next;
	}
}
void putNode(node* List) {
	node* p = List;
	while (p != NULL) {
		free(p);
		List = List->next;
		p = List;
	}
}
