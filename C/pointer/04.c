#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int main() {
	int x[3] = { NULL }, * px = x, * ppx = x, tmp = 0;

	for (px = x; px < x + 3; px++) {
		scanf("%d", px);
	}

	for (px = x; px < x + 2; px++) {
		for (ppx = x; ppx < x + 2; ppx++) {
			if (*ppx < *(ppx + 1)) {
				tmp = *ppx;
				*ppx = *(ppx + 1);
				*(ppx + 1) = tmp;
			}
		}
	}

	px = x;

	printf("%d", *(px + 1));
}
