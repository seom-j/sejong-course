#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main(void) {
	int n, cnt, b_cnt=101;
	char str[101], b_str[101];
	scanf("%d", &n);
	getchar();

	for (int i = 0; i < n; i++) {
		gets(str);
		cnt = strlen(str);
		if (b_cnt > cnt) {
			b_cnt = cnt;
			for (char* p = b_str; p < b_str + strlen(b_str); p++) *p = 0;
			strcpy(b_str, str);
		}
	}

	printf("%s", b_str);
	return 0;
}
