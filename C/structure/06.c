#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct student {
	int g, w, h;
};
int main(void) {
	struct student c[10];
	int n, d1=0,d2=0,d3=0;
	scanf("%d", &n);

	for (struct student* p = c; p < c + n; p++) scanf("%d %d %d", &p->g, &p->w, &p->h);

	for (struct student* p = c; p < c + n; p++) {
		if (p->g == 1) {
			if (p->w < 60) {
				if (p->h < 165) d1 += 1;
				else if ( p->h < 175)d2 += 1;
				else d3 += 1;
			}
			else if (p->w < 70) {
				if (p->h < 165)d3 += 1;
				else if (p->h < 175) d1 += 1;
				else d2 += 1;
			}
			else {
				if (p->h < 165) d2 += 1;
				else if (p->h < 175)d3 += 1;
				else d1 += 1;
			}
		}
		else if (p->g == 2) {
			if (p->w < 50) {
				if (p->h < 165) d1 += 1;
				else if (p->h < 175) d2 += 1;
				else d3 += 1;
			}
			else if (p->w < 60) {
				if (p->h < 165) d3 += 1;
				else if (p->h < 175) d1 += 1;
				else d2 += 1;
			}
			else {
				if (p->h < 165) d2 += 1;
				else if (p->h < 175) d3 += 1;
				else d1 += 1;
			}
		}
	}

	printf("%d %d %d", d1, d2, d3);
	return 0;
}
