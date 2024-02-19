#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int cut(int);

int main(void) {
	int n;
	scanf("%d", &n);
	cut(n);
	return 0;
}

int cut(int n) {
	int x;
	if (n == 0) return 0;
	x = n % 10;
	n /= 10;
	cut(n);
	printf("%d\n", x);
}
