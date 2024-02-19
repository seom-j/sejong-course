#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)


int main(void) {
	int n;
	scanf("%d", &n);
	getchar();

	char** p, tmp[101] = { NULL }, *temp;
	p = (char*)malloc(sizeof(char*) * n);
	if (p == NULL) return-1;
	for (int i = 0; i < n; i++) {
		gets(tmp);
		p[i] = (char*)malloc(strlen(tmp) + 1);
		if (p[i] == NULL) return -1;
		strcpy(p[i], tmp);
	}

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (strcmp(p[j], p[j + 1]) > 0) {
				temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < n; i++) puts(p[i]);

	for (int i = 0; i < n; i++) {
		if (p[i] != NULL) {
			free(p[i]);
			p[i] = 0;
		}
	}
	if (p != NULL) {
		free(p); 
		p = 0;
	}
}
