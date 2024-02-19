#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

void strcopy(char*, char*);

int main(void) {
	char a[6], b[6] = { NULL };
	for (char* pa = a; pa < a + 6; pa++) scanf("%c", pa);
	strcopy(a, b);
	for (char* pb = b; pb < b + 6; pb++) printf("%c", *pb);
}

void strcopy(char* a, char* b) {
	for (char* pb = b, *pa = a; pb < b + 6; pb++, pa++) *pb = *pa;
}
