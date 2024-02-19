#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main(void) {
	char* num[] = { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	char* digit[] = { "", "TEN", "HUN", "THO" };
	int nu=0, len = 0, n = 0;
	scanf("%d", &nu);

	while (nu > 0) {
		n *= 10;
		n += nu % 10;
		nu /= 10;
		len += 1;
	}

	while (n > 0) {
		if (n % 10 != 0) {
			printf("%s ", num[n % 10]);
			printf("%s ", digit[len - 1]);
		}
		n /= 10;
		len -= 1;
	}

	return 0;
}
