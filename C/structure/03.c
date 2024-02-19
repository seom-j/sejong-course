#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

struct std {
	char n[10];
	double g;
};

int main() {
	struct std c[5];
	double sum = 0, avg = 0;
	for (int i = 0; i < 5; i++) {
		scanf("%s %lf", &c[i].n, &c[i].g);
		sum += c[i].g;
	}
	avg = sum / 5.0;
	for (int i = 0; i < 5; i++) {
		if (c[i].g < avg) printf("%s\n", c[i].n);
	}
}
