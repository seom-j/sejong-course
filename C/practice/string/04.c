#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int main() {
	char a[101] = { NULL }, b[101] = { NULL };
	int cnta = 0, cntb = 0, pass = 1;
	scanf("%s", a);
	scanf("%s", b);
	for (cnta; a[cnta] != 0; cnta++);
	for (cntb; b[cntb] != 0; cntb++);

	for (int i = 0; a[i] != 0; i++) {
		if (a[i] != b[i]) pass = 0;
	}

	if (cnta != cntb) pass = 0;

	printf("%d %d", cnta, pass);
}
