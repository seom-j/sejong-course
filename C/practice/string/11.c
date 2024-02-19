#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main(void) {
	int f = 0;
	char str1[81] = { NULL }, str2[11] = { NULL };
	scanf("%s %s", str1, str2);
	for (char* p = str1; p < str1 + strlen(str1); p++) {
		if (strncmp(p, str2, strlen(str2)) == 0) f = 1;
	}

	printf("%d %d", strlen(str1), f);
	return 0;
}
