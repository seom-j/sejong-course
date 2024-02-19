#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main(void) {
	char str1[101] = { NULL }, str2[101] = { NULL };
	int cnt = 0;

	gets(str1);
	scanf("%s", str2);

	for (char* p = str1; p < str1 + strlen(str1); p++) {
		if (strncmp(p, str2, strlen(str2)) == 0) {
			cnt += 1;
			p += strlen(str2) - 1;
		}
	}

	printf("%d", cnt);
	return 0;
}
