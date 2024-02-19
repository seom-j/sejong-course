#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)


int main(void) {
	int n,a[20], b[20], c[20];
	scanf("%d", &n);
	for (int* pa = a; pa < a + n; pa++) scanf("%d", pa);
	for (int* pb = b; pb < b + n; pb++) scanf("%d", pb);
	for (int* pa = a, *pb = b + n - 1, *pc = c; pa < a + n; pa++, pb--, pc++)*pc = *pa + *pb;
	for (int* pc = c; pc < c + n; pc++) printf(" %d", *pc);
}
