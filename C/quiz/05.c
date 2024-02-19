#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

struct std_i {
	char ma[51], na_bi[35];
};

int main() {
	struct std_i c[100];
	struct std_i tmp;
	int n;
	scanf("%d", &n);
	getchar();
	for (int i = 0; i < n; i++) {
		gets(&c[i].ma);
		gets(&c[i].na_bi);
	}

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (strcmp(c[j].ma, c[j + 1].ma) > 0) {
				tmp = c[j];
				c[j] = c[j + 1];
				c[j + 1] = tmp;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		printf("%s %s\n", c[i].ma, c[i].na_bi);
	}
}
