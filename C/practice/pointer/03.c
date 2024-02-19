#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)


int main(void) {
	int arr[50] = { NULL };
	int n, num = 0;

	scanf("%d", &n);

	for (int* p = arr; p < arr + n; p++) {
		scanf("%d", p);
	}

	for (int* p = arr; p < arr + n; p++, num++) {
		if (*p == 0) {
			printf("%d", num);
			break;
		}
	}

	return 0;
}
