#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

struct bike_info {
	int id, tel;
	char pro, che;
	int s_pro, time, pay;
};

void input(struct bike_info* p);
void compute(struct bike_info* p);
void display(struct bike_info* p, int N);
void bike_info_sort(struct bike_info* p, int N);

int main(void) {
	struct bike_info p[100];
	int n, sp = 0, dp = 0;
	scanf("%d", &n);
	for (struct bike_info* pp = p; pp < p + n; pp++) {
		input(pp);
		compute(pp);
		if (pp->pro == 'S') sp += pp->pay;
		else if (pp->pro == 'D') dp += pp->pay;
	}
	bike_info_sort(p, n);
	display(p, n);
	printf("%d %d %d", dp, sp, dp + sp);
}

void input(struct bike_info* p) {
	scanf("%d %d %c", &p->id, &p->tel, &p->pro);
	getchar();
	if (p->pro == 'S') scanf("%c %d %d", &p->che, &p->s_pro, &p->time);
	else if (p->pro == 'D') scanf("%d", &p->time);
}

void compute(struct bike_info* p) {
	p->pay = 0;
	if (p->pro == 'S') {
		if (p->che == 'N') {
			if (p->s_pro == 7) p->pay += 3000;
			else if (p->s_pro == 30) p->pay += 5000;
			else if (p->s_pro == 180)p->pay += 15000;
			p->time -= 60;
			if (p->time < 0) p->time = 0;
		}
		else if (p->che == 'Y') {
			p->time -= 60;
			if (p->time < 0) p->time = 0;
		}
	}
	else if (p->pro == 'D') {
		p->pay += 1000;
		if (p->time >= 60) p->time -= 60;
		else p->time = 0;
	}
	p->pay += ((int)(p->time / 5) * 200);
}
void display(struct bike_info* p, int N) {
	for (struct bike_info* pp = p; pp < p + N; pp++) printf("%d %d %c %d\n", pp->id, pp->tel, pp->pro, pp->pay);
}

void bike_info_sort(struct bike_info* p, int N) {
	struct bike_info tmp;
	for (struct bike_info* pp = p; pp < p + N - 1; pp++) {
		for (struct bike_info* q = p; q < p + N - 1; q++) {
			if (q->pro>(q + 1)->pro||
				(q->pro == (q + 1)->pro && q->id > (q + 1)->id)) {
				tmp = *q;
				*q = *(q + 1);
				*(q + 1) = tmp;
			}
		}
	}
}
