#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

struct hotel_info {
	char name[31];
	int gr;
	double star, dist;
	char bru;
}; // 구조체 선언

int in_hotel_info(struct hotel_info* p);
void out_hotel_info(struct hotel_info* p, int N, int G, double D); // 함수 원형 선언

int main(void) {
	struct hotel_info h[100], tmp;
	int n = in_hotel_info(h), g; // 갯수 선언과 동시에 입력
	double d; // 선언
	scanf("%d %lf", &g, &d); // g d 입력

	for (struct hotel_info* p = h; p < h + n-1; p++) {
		for (struct hotel_info* q = h; q < h + n - 1; q++) {
			if (q->star < (q + 1)->star || (q->star == (q + 1)->star && strcmp(&q->name, &(q + 1)->name) > 0)) {
				tmp = *q;
				*q = *(q + 1);
				*(q + 1) = tmp;
			}
		}
	} // 평판도 -> 이름 순으로 정렬

	out_hotel_info(h, n, g, d); // 함수 호출
}

int in_hotel_info(struct hotel_info* p) {
	int cnt = 0;
	for (struct hotel_info* pp = p;; pp++) {
		scanf("%s", &pp->name); // 이름부터 입력받기 (띄어쓰기하면 종료됨)
		if (*pp->name == '0') return cnt; // 0이면 stop
		scanf("%d %lf %lf %c", &pp->gr, &pp->star, &pp->dist, &pp->bru); // 0아니면 나머지 입력받기
		cnt += 1; // 갯수 더하기
	}
}

void out_hotel_info(struct hotel_info* p, int N, int G, double D) {
	for (struct hotel_info* pp = p; pp < p + N; pp++) {
		if (pp->gr >= G && pp->dist <= D) printf("%s %d %.1lf %.1lf %c\n", pp->name, pp->gr, pp->star, pp->dist, pp->bru); 
	} // 제시된 조건 내에 있으면 프린트
}
