#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int s_check(char* p, char* q);

int main(void) {
	char str[10][201] = { NULL };
	int n, k1, k2;
	scanf("%d", &n);
	scanf("%d %d", &k1, &k2);
	getchar();
	for (int i = 0; i < n; i++) {
		gets(str[i]);
		if (s_check(str[i] + k1, str[i] + k2) > 0) printf("%d", s_check(str[i] + k1, str[i] + k2));
	}
}

int s_check(char* p, char* q) {
	int cnt = 0;
	for (char* pp = p; pp <= q; pp++) {
		if (*pp >= 'a' && *pp <= 'z') cnt++;
	}
	return cnt;
}
