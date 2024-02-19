#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int main() {
	char str[101] = { NULL }, * ps = str;
	char w[50][101], b_wo[101] = { NULL };
	gets(str);
	int cnt = strlen(str), i = 0, j = 0, b_idx;

	for (i, j; i < cnt + 1; i++) {
		if (str[i] == ' ' || str[i] == 0) {
			str[i] = 0;
			strcpy(w[j++], ps);
			ps = &str[i + 1];
		}
	}

	strcpy(b_wo, w[0]);
	b_idx = 0;

	for (i = 0; i < j; i++) {
		printf("%s\n", w[i]);
		if (strcmp(w[i], b_wo) < 0) {
			for (int k = 0; b_wo[k] != 0; k++) b_wo[k] = 0;
			strcpy(b_wo, w[i]);
			b_idx = i;
		}
	}
	
	printf("%s", b_wo);
}
