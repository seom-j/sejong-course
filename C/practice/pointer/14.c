#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int add_to_k(int*, int*);

int main(void) {
	int n,d[100],s=0;
	scanf("%d", &n);
	for (int* pd = d; pd < d + n; pd++) scanf("%d", pd);

	for (int* pd = d; pd < d + n; pd++) s += add_to_k(d, pd);
	printf("%d", s);
}

int add_to_k(int* s, int* e) {
	int sum = 0;
	for (int* px = s; px <= e; px++) sum += *px;
	return sum;
}
