#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

struct st {
	char ma[51], id[8];
};

int main(void) {
	struct st c[100], tmp;
	int n;
	scanf("%d", &n);
	getchar();
	
	for (int i = 0; i < n; i++) {
		gets(&c[i].ma);
		gets(&c[i].id);
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (strcmp(&c[j].ma, &c[j + 1].ma) > 0) {
				tmp = c[j];
				c[j] = c[j + 1];
				c[j + 1] = tmp;
			}
			if (strcmp(&c[j].ma, &c[j + 1].ma) == 0) {
				if (strcmp(&c[j].id, &c[j + 1].id) > 0) {
					tmp = c[j];
					c[j] = c[j + 1];
					c[j + 1] = tmp;
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%s %s\n", c[i].ma, c[i].id);
	}
}
