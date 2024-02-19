#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int check(char* a, char* b);

int main(void) {
	char a[21] = { NULL }, b[21] = { NULL };
	gets(a);
	gets(b);
	if (check(a, b) == 1) printf("1");
	else if (check(b, a) == 1) printf("2");
	else printf("0");
}

int check(char* a, char* b) {
	char c[500] = { NULL };
	int idx = 0, m = 0, f = 0;

	for (int n = 1; n <= 10; n++) {
		for (int i = 0; c[i] != 0; i++) c[i] = 0;
		idx = 0;

		for (int i = 0; a[i] != 0; i++) {

			if (a[i] >= 'a' && a[i] <= 'z') c[idx++] = a[i] - n;
			else if (a[i] >= 'A' && a[i] <= 'Z') c[idx++] = a[i] + n;
			else if (a[i] >= '0' && a[i] <= '9') {
				m = m * 10 + a[i] - '0';
				if (a[i + 1] == 0 || (a[i + 1] <= '0' || a[i + 1] >= '9')) {
					for (int k = 0; k < n; k++) c[idx++] = 'A' + m - 1;
					m = 0;
				}
			}

			else c[idx++] = ' ';
		}

		for (int i = 0; c[i] != 0; i++) if (c[i] != b[i]) f = 1;
		if (f == 0) return 1;
		f = 0;
	}
	return 0;
}
