#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int main() {
	char str[100] = { NULL }, tmp = 0;
	int j = 0;
	scanf("%s", str);
	for (int i = 0; str[i] != 0; i++) {
		printf("%s\n", str);
		tmp = str[0];
		for (j = 0; str[j+1] != 0; j++) {
			str[j] = str[j + 1];
		}
		str[j] = tmp;
	}
