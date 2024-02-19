#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int main() {
	char d[9] = { NULL };
	int n = 0, i = 0;
	scanf("%d", &n);
	while (n > 0) {
		d[i++] = n % 10 + '0';
		n /= 10;
	}
	printf("%s", d);
}
