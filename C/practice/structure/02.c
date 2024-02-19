#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

struct time {
	int h, m, s;
};

int main() {
	struct time t[3];

	for (int i = 0; i < 2; i++) {
		scanf("%d %d %d", &t[i].h, &t[i].m, &t[i].s);
	}

	t[2].h = t[1].h - t[0].h;
	t[2].m = t[1].m - t[0].m;
	t[2].s = t[1].s - t[0].s;

	if (t[2].s < 0) {
		t[2].s += 60;
		t[2].m -= 1;
	}
	if (t[2].m < 0) {
		t[2].m += 60;
		t[2].h -= 1;
	}

	printf("%d %d %d", t[2].h, t[2].m, t[2].s);
}
