#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int fac(int );
int x = 0;

int main(void) {
	int n;
	scanf("%d", &n);
	printf("%d",fac(n));

	return 0;
}

int fac(int n) {
	x += n;
	n -= 1;
	if (n == 0) return x;
	fac(n);
}
