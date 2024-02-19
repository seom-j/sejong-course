#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)


int main(void) {
	int n,d;
	scanf("%d", &n);

	char** p, tmp[9];
	p = (char**)malloc(sizeof(char*) * n);
	if (p == NULL) return -1;
	for (int i = 0; i < n; i++) {
		scanf("%s", tmp);
		p[i] = (char*)malloc(strlen(tmp)+1);
		if (p[i] == NULL) return -1;
		strcpy(p[i], tmp);
	}

	scanf("%d", &d);

	p = (char**)realloc(p, sizeof(char*) * (n - d));

	for (int i = 0; i < n - d; i++) printf("%s", p[i]);

	for (int i = 0; i < n - d; i++) {
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
