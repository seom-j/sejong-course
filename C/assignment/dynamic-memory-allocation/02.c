#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main(void) {
	char tmp[101], * p1, * p2;
	gets(tmp);
	p1 = (char*)malloc(strlen(tmp) + 1);
	if (p1 == NULL)return-1;
	strcpy(p1, tmp);
	gets(tmp);
	p2 = (char*)malloc(strlen(tmp) + 1);
	if (p2 == NULL)return-1;
	strcpy(p2, tmp); // 입력

	char** w1, ** w2;
	char* po1 = p1, * po2 = p2;
	int len1 = strlen(p1), len2 = strlen(p2), id1 = 0, id2 = 0;
	int wn1 = 0, wn2 = 0;
	for (char* pp = p1; pp < p1 + len1 + 1; pp++) {
		if (*pp == ' ' || *pp == 0) {
			wn1 += 1;
		}
	}
	w1 = (char**)malloc(wn1 * sizeof(char*));
	for (char* pp = p2; pp < p2 + len2 + 1; pp++) {
		if (*pp == ' ' || *pp == 0) wn2 += 1;
	}
	w2 = (char**)malloc(wn2 * sizeof(char*));
	// 단어 갯수 동적할당

	for (char* pp = p1; pp < p1 + len1 + 1; pp++) {
		if (*pp == ' ' || *pp == 0) {
			*pp = 0;
			w1[id1] = (char*)malloc(strlen(po1) + 1);
			strcpy(w1[id1++], po1);
			po1 = pp + 1;
		}
	}
	for (char* pp = p2; pp < p2 + len2 + 1; pp++) {
		if (*pp == ' ' || *pp == 0) {
			*pp = 0;
			w2[id2] = (char*)malloc(strlen(po2) + 1);
			strcpy(w2[id2++], po2);
			po2 = pp + 1;
		}
	} // 단어 자르기

	char* wtmp;
	for (int i = 0; i < wn2 - 1; i++) {
		for (int j = 0; j < wn2 - 1; j++) {
			if (strlen(w2[j]) < strlen(w2[j + 1]) ||
				(strlen(w2[j]) == strlen(w2[j + 1]) && strcmp(w2[j], w2[j + 1]) > 0)) {
				wtmp = w2[j];
				w2[j] = w2[j + 1];
				w2[j + 1] = wtmp;
			}
		}
	} // 배열 2 정렬

	int f = 0;

	for (int i = 0; i < wn2; i++) {
		f = 0;
		for (int j = 0; j < wn1; j++) {
			if (strncmp(w1[j], w2[i], strlen(w1[j])) == 0) {
				for (int k = 0; k < wn1; k++) {
					if (strcmp(w1[j], w1[k]) == 0) continue;
					if (strcmp(w1[k], w2[i] + strlen(w1[j])) == 0) {
						printf("%s\n", w2[i]);
						f = 1;
					}
				}
			}
			if (f == 1) break;
		}
	} // 출력

	for (int i = 0; i < wn1; i++) {
		if (w1[i] != NULL) {
			free(w1[i]);
			w1[i] = NULL;
		}
	}
	if (w1 != NULL) {
		free(w1);
		w1 = NULL;
	}
	for (int i = 0; i < wn2; i++) {
		if (w2[i] != NULL) {
			free(w2[i]);
			w2[i] = NULL;
		}
	}
	if (w2 != NULL) {
		free(w2);
		w2 = NULL;
	} // 해제

	return 0;
}
