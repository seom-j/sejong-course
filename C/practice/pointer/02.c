#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)


int main(void) {
	char ch[20] = { NULL };
	int idx = 0;

	for (char* pch = ch;; pch++, idx++) {
		scanf("%c", pch);
		if (*pch == '#') break;
	}

	for (char* pch = ch + idx - 1; pch >= ch; pch--) printf("%c", *pch);

	return 0;
}
