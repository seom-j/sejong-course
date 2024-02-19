#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main(void) {
	int n, cnt;
	scanf("%d", &n);
	getchar();
	
	char** p, tmp[101], min[101], max[101];
	p = (char**)malloc(sizeof(char*) * n);
	if (p == NULL) return -1;

	for (int i = 0; i < n; i++) {
		gets(tmp);
		p[i] = (char*)malloc(strlen(tmp) + 1);
		if (p[i] == NULL) return -1;
		strcpy(p[i], tmp);
	}

	strcpy(min, p[0]);
	strcpy(max, p[0]);
	for ( int i = 1; i < n; i++) {
		if (strlen(min) > strlen(p[i]))
			strcpy(min, p[i]); 
		else if (strlen(max) < strlen(p[i]))
			strcpy(max, p[i]);
	}
	int M = strlen(min);
	char* min_w = min;
	for (char *q_s = min, *q_e = min; q_e <= min + M; q_e++) {
		if (*q_e == ' ' || *q_e == '\0') {
			*q_e = '\0';
			if (strlen(min_w) > strlen(q_s)) {
				min_w = q_s;
			}
			q_s = q_e + 1;
		}
	}
	M = strlen(max);
	char* max_w = max;
	for (char* q_s = max, *q_e = max; q_e <= max + M; q_e++) {
		if (*q_e == ' ' || *q_e == '\0') {
			*q_e = '\0';
			if (strlen(max_w) < strlen(q_s)) {
				max_w = q_s;
			}
			q_s = q_e + 1;
		}
	}

	printf("%s\n%s", min_w, max_w);
}
