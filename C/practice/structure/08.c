#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

struct complex {
	double real, imag;
};

struct complex add(struct complex, struct complex);

int main() {
	struct complex c1, c2, c3;

	scanf("%lf%lf", &c1.real, &c1.imag); 
	scanf("%lf%lf", &c2.real, &c2.imag);

	c3 = add(c1, c2);

	printf("%.1lf + %.1lfi", c3.real, c3.imag);
}

struct complex add(struct complex a, struct complex b) {
	struct complex c;
	c.real = a.real + b.real;
	c.imag = a.imag + b.imag;

	return c;
}
