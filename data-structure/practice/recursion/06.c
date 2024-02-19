#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int gcd(int n1, int n2);

int main(void) {
	int n1 = 0, n2 = 0;
	scanf("%d %d", &n1, &n2);
	printf("%d", gcd(n1, n2));
	return 0;
}

int gcd(int n1, int n2) {
	int tmp;
	tmp = n2;
	n2 = n1 % n2;
	n1 = tmp;

	if (n2 == 0) return n1;
	gcd(n1, n2);
}
