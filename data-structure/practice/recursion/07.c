#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int strr(char str[], char);
int cnt = 0;

int main(void) {
	char str[100] = { NULL }, x;
	gets(str);
	scanf("%c", &x);

	printf("%d", strr(str, x));

	return 0;
}

int strr(char str[], char x) {
	if (*str == 0) return cnt;
	if (*str == x) cnt += 1;
	str += 1;
	strr(str, x);
}
