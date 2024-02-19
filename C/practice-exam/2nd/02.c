#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct complex {
	double r, i, a;
};

struct complex add(struct complex, struct complex);
struct complex sub(struct complex, struct complex);
void abs_val(struct complex* p1, struct complex* p2, struct complex* p3);

int main(void) {
	struct complex p1, p2, p3, tmp;

	scanf("%lf %lf", &p1.r, &p1.i);
	scanf("%lf %lf", &p2.r, &p2.i);
	scanf("%lf %lf", &p3.r, &p3.i);

	abs_val(&p1, &p2, &p3);

	printf("%.1lf%+.1lfi\n", add(p1, p2).r, add(p1, p2).i);
	printf("%.1lf%+.1lfi", sub(p1, p2).r, sub(p1, p2).i);

}
struct complex add(struct complex x, struct complex y) {
	struct complex z;
	z.r = x.r + y.r;
	z.i = x.i + y.i;
	return z;
}
struct complex sub(struct complex x, struct complex y) {
	struct complex z;
	z.r = x.r - y.r;
	z.i = x.i - y.i;
	return z;
}
void abs_val(struct complex* p1, struct complex* p2, struct complex* p3) {
	struct complex tmp;
	p1->a = p1->r * p1->r + p1->i * p1->i;
	p2->a = p2->r * p2->r + p2->i * p2->i;
	p3->a = p3->r * p3->r + p3->i * p3->i;

	if (p1->a < p2->a) {
		tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
	}
	if (p1->a < p3->a) {
		tmp = *p1;
		*p1 = *p3;
		*p3 = tmp;
	} //p1에 젤 큰거

	if (p2->a > p3->a) {
		tmp = *p2;
		*p2 = *p3;
		*p3 = tmp;
	}
	if (p2->a > p1->a) {
		tmp = *p2;
		*p2 = *p1;
		*p1 = tmp;
	}// p2에 젤 큰거
}
