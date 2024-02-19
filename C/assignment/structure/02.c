#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

struct _bank {
	int id; // 아이디, T1, T2, T3 대신, 1, 2, 3, ... 으로 한다. 
	int arrival_time; // 도착시간
	int service_time; // 서비스시간
	int waiting_time; // 대기시간
};

void waitingtime(struct _bank guest[], int N);
double avgtime(struct _bank guest[], int N);

int main(void) {
	struct _bank p[100]; // 구조체 선언
	int n; // 갯수 변수 선언
	scanf("%d", &n); // 갯수 변수 입력
	for (struct _bank* pp = p; pp < p + n; pp++) scanf("%d %d %d", &pp->id,&pp->arrival_time, &pp->service_time); // 구조체 입력

	waitingtime(p, n); // 계산 함수 호출
	printf("%.2lf", avgtime(p, n)); // 프린트 평균 함수 호출값
}

void waitingtime(struct _bank guest[], int N) {
	for (struct _bank* p = guest; p < guest + N; p++) {
		p->waiting_time = 0; // 0으로 초기화
		for (struct _bank* q = guest; q < p; q++) {
			p->waiting_time += q->service_time; // 앞전의 서비스타임 모두 더하기
		}
		p->waiting_time -= p->arrival_time; // 자신의 도착시간 빼기
	} // 계산 완료
}

double avgtime(struct _bank guest[], int N) {
	double avg, sum = 0; // 변수 선언
	for (struct _bank* p = guest; p < guest + N; p++) sum += p->waiting_time; // 대기시간 총 합 계산
	avg = sum / N; // 총 합/인원수 계산 (평균 계산)
	return avg; // 평균값 반환
}
