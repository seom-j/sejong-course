#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main(void) {
	char str1[101] = { NULL }, str2[101] = { NULL };
	scanf("%s %s", str1, str2);
	if (strcmp(str1, str2) > 0) {
		strcat(str1, str2);
		printf("%s", str1);
	}
	else {
		strcat(str2, str1);
		printf("%s", str2);
	}

	return 0;
}
