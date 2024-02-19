#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int main(void) {
	char str[100] = { NULL }, * ps = str;
	char wo[10][101] = { NULL }, tmp[101] = { NULL };
	gets(str);
	int cnt = strlen(str), j = 0;

	for (int i = 0; i < cnt + 1; i++) {
		if (str[i] == ' ' || str[i] == 0) {
			str[i] = 0;
			strcpy(wo[j], ps);
			puts(wo[j++]);
			ps = &str[i + 1];
		}
	}

	for (int i = 0; i < j-1; i++) {
		for (int k = 0; k < j-1; k++) {
			if (strcmp(wo[k], wo[k + 1]) > 0) {
				for (int q = 0; wo[k][q] != 0; q++) tmp[q] = wo[k][q];
				for (int q = 0; wo[k][q] != 0; q++) wo[k][q] = 0;

				for (int q = 0; wo[k + 1][q] != 0; q++) wo[k][q] = wo[k + 1][q];
				for (int q = 0; wo[k + 1][q] != 0; q++) wo[k + 1][q] = 0;

				for (int q = 0; tmp[q] != 0; q++) wo[k + 1][q] = tmp[q];
				for (int q = 0; tmp[q] != 0; q++) tmp[q] = 0;
			}
		}
	}

	puts(wo[0]);
}
