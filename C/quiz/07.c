#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct student {
	char name[21];
	int kor, eng, math;
	double avg;
};

struct average {
	double kor, eng, math;
};

struct average calculate_avg(struct student* st, int N);

int main(void) {
	int n;
	scanf("%d", &n);

	struct student* p, tmp;
	p = (struct student*)malloc(sizeof(struct student) * n);
	if (p == NULL) return -1;
	for (struct student* pp = p; pp < p + n; pp++) {
		scanf("%s %d %d %d", pp->name, &pp->kor, &pp->eng, &pp->math);
		pp->avg = (pp->kor + pp->eng + pp->math) / 3.0;
	}

	struct average av = calculate_avg(p, n);

	for (struct student* qq = p; qq < p + n-1; qq++) {
		for (struct student* pp = p; pp < p + n-1; pp++) {
			if (pp->avg < (pp + 1)->avg) {
				tmp = *pp;
				*pp = *(pp + 1);
				*(pp + 1) = tmp;
			}
		}
	}

	printf("%.1lf %.1lf %.1lf\n", av.kor, av.eng, av.math);
	for (struct student* pp = p; pp < p + n; pp++) {
		if (pp->kor < av.kor || pp->eng < av.eng || pp->math < av.math) {
			printf("%s %d %d %d %.1lf\n", pp->name, pp->kor, pp->eng, pp->math, pp->avg);
		}
	}
}

struct average calculate_avg(struct student* st, int N) {
	struct average av;
	av.eng = 0;
	av.kor = 0;
	av.math = 0;

	for (struct student* pp = st; pp < st + N; pp++) {
		av.kor += pp->kor;
		av.eng += pp->eng;
		av.math += pp->math;
	}

	av.kor /= N;
	av.eng /= N;
	av.math /= N;

	return av;
}
