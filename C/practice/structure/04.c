#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

struct std {
	char n[20];
	double e1,e2,e3;
};

int main() {
	struct std c[20];
	int n;
	double avg = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s %lf %lf %lf", &c[i].n, &c[i].e1, &c[i].e2, &c[i].e3);
	}
	for (int i = 0; i < n; i++) {
		avg = (c[i].e1 + c[i].e2 + c[i].e3) / 3;
		printf("%s ", c[i].n);
		printf("%.1lf ", avg);
		if (avg >= 90) printf("A");
		else if (avg >= 80) printf("B");
		else if (avg >= 70)printf("C");
		else printf("F");
	}
}
