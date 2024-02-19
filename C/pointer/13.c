#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)


int main(void) {
	int n, s, e, x[100], cnt=0;
	scanf("%d %d %d", &n, &s, &e);
	for (int* px = x; px < x + n; px++)scanf("%d", px);
	for (int* px = x + s; px <= x + e; px++) cnt += *px;
	printf("%d", cnt);
}
