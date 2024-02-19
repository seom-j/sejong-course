#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int findk(int a, int b, int n, char *str);

int main() {
	int a, b, n;
	char str[1000] = { NULL };
	int k = 0;

	scanf("%d %d %d", &a, &b, &n);
	scanf("%s", str);

	k = findk(a, b, n, str);
	printf("%d", k);

	return 0;
}


int findk(int a, int b, int n, char *str) {
	int mid;
	int k = 0, idx = 0;

	while (1) {
		mid = (a + b) / 2;

		if (a == b) {
			k = mid;
			break;
		}

		if (str[idx] == 'Y') {
			a = mid + 1;
		}
		else if (str[idx] == 'N') {
			b = mid;
		}

		idx++;
	}

	return k;
}
