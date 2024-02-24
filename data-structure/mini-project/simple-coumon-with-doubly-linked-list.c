#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

typedef struct node {
	struct node* H, *L;
}node;

typedef struct Elements {
	node* L;
	char e;
}Elements;

typedef struct Groups {
	node* H;
	char g;
}Groups;

node* getNode();
void initShare(Groups* g, Elements* e);
void addShare(Groups* g, Elements* e, char gr, char el);
void removeShare(Groups* g, Elements* e, char gr, char el);
void traverseShareElements(Groups* g, Elements* e, char gr);
void traverseShareGroups(Groups* g, Elements* e, char el);

int main() {
	char str[6] = { NULL }; // 문자열로 입력받기 (필요한 요소만 사용하기 위함)
	Groups G[5];
	Elements E[4];
	initShare(G, E); // 구조체배열 초기화

	while (1) {
		gets(str);
		if (str[0] == 'a') {
			addShare(G, E, str[4], str[2]);
			printf("OK\n");
		}
		if (str[0] == 'r') {
			removeShare(G, E, str[4], str[2]);
			printf("OK\n");
		}
		if (str[0] == 'e') {
			traverseShareElements(G, E, str[2]);
		}
		if (str[0] == 'g') {
			traverseShareGroups(G, E, str[2]);
		}
		if (str[0] == 'q') break;
	} // 각 첫글자에 맞는 명령어 반복수행
}

node* getNode() {
	return (node*)calloc(1, sizeof(node));
} // 노드 동적할당

void initShare(Groups* g, Elements* e) {
	for (int i = 0; i < 4; i++) {
		e[i].L = getNode();
		e[i].L->L = e[i].L;
		e[i].e = '1' + i;
	}
	for (int i = 0; i < 5; i++) {
		g[i].H = getNode();
		g[i].H->H = g[i].H;
		g[i].g = 'A' + i;
	} // 각 구조체배열 헤더 연결 및 문자 입력
} // 노드 초기화

void addShare(Groups* g, Elements* e, char gr, char el) {
	node* p = getNode(); // 새 노드 생성
	int i = 0, j = 0;
	while (e[i].e != el) i++;
	while (g[j].g != gr) j++; // 입력받은 gr과 el의 위치 찾기
	node* hg = g[j].H;
	p->H = hg->H;
	hg->H = p;
	node* he = e[i].L;
	p->L = he->L;
	he->L = p; // 그 위치에 원형 연결
} // 노드 추가

void removeShare(Groups* g, Elements* e, char gr, char el) {
	int i = 0, j = 0;
	while (e[i].e != el) i++;
	while (g[j].g != gr) j++; // 입력받은 gr과 el의 위치 찾기
	node* L = e[i].L;
	node* p = L->L;
	node* H, * q;
	node* prev_p = L, * prev_q; // 원형 노드 제거를 위한 직전노드 저장
	while (L != p) {
		H = g[j].H;
		q = H->H;
		prev_q = H; // 반복 위해 매번 초기화
		while (H != q) {
			if (p == q) {
				prev_p->L = p->L;
				prev_q->H = p->H;
				p->L = 0;
				p->H = 0;
				free(p); // 원형 노드 제거
				return;
			}
			prev_q = q;
			q = q->H; // 다음 노드
		}
		prev_p = p;
		p = p->L; // 다음 노드
	}
} // 알맞은 노드의 위치를 찾아 입력된 노드 삭제

void traverseShareElements(Groups* g,Elements* e, char gr) {
	int j = 0, cnt = 0;
	while (g[j].g != gr) j++;  // 입력받은 gr의 위치 찾기
	node* H = g[j].H;
	node* p = H->H;
	node* L, *q;
	while (H != p) {
		for (int i = 0; i < 4; i++) {
			L = e[i].L;
			q = L->L;
			while (L != q) {
				if (p == q) {
					printf("%c ", e[i].e);
					cnt += 1;
				}
				q = q->L;
			}
		}
		p = p->H;
	} // 입력받은 가입자와 만나는(가입자가 구매한) 쿠폰의 노드를 찾아 쿠폰 출력
	if (cnt == 0) printf("0");
	printf("\n");
} // 순회 및 알맞은 값 출력

void traverseShareGroups(Groups* g, Elements* e, char el) {
	int i = 0, cnt = 0;
	while (e[i].e != el) i++;
	node* L = e[i].L;
	node* p = L->L;
	node* H, * q;
	while (L != p) {
		for (int j = 0; j < 5; j++) {
			H = g[j].H;
			q = H->H;
			while (H != q) {
				if (p == q) {
					printf("%c ", g[j].g);
					cnt += 1;
				}
				q = q->H;
			}
		}
		p = p->L;
	} // 입력받은 쿠폰과 만나는(쿠폰을 구매한) 가입자의 노드를 찾아 가입자 출력
	if (cnt == 0) printf("0");
	printf("\n");
} // 순회 및 알맞은 값 출력
