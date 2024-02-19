#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int input(char*);
int check_flag(char*, char*);
void output(char*, char*);

int main() {
	char x[101] = { NULL }, y[101] = { NULL };
	char* px = x, * py = y;

	int n = input(x);

	for (px = x, py = y; px < x + n; px++) {
		if (check_flag(x, px) == 0) {
			*py = *px;
			py++;
		}
	}

	output(y, py);
}

int input(char* x) {
	int n;
	scanf("%d", &n);
	getchar();
	gets(x);
	return n;
}

int check_flag(char* x, char* b) {
	for (char* pp = x; pp < b; pp++) {
		if (*b == *pp) return 1;
	}
	return 0;
}

void output(char* y, char* py) {
	for (char* ppy = y; ppy < py; ppy++) printf("%c", *ppy);
}
