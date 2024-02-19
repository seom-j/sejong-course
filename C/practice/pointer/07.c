#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

void input(int*, int*, int*);
void output(int*, int*, int*);

int main() {
	int a, b, c;
	input(&a, &b, &c);
	output(&a, &b, &c);
}

void input(int* a, int* b, int* c) {
	scanf("%d%d%d", a, b, c);
}
void output(int* a, int* b, int* c) {
	printf("%d %d %d", *a, *b, *c);
}
