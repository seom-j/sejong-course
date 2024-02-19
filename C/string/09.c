#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int check(char*);
int main(void) {
	char x[31] = { NULL };
	scanf("%s", x);
	printf("%d %d", strlen(x), check(x));

	return 0;
}

int check(char* x) {
	for (char* p = x , *q = x + strlen(x) - 1; p < x + strlen(x) / 2; p++,q--) {
		if (*p != *q) return 0;
	}
	return 1;
}
