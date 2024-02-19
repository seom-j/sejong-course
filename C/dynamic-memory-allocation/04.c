#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct student {
	char name[10];
	double k, e, m, av;
};

typedef struct student(ABC);

int main(void) {
	int n;
	scanf("%d", &n);
	getchar();
	
	ABC* p;
	p = (ABC*)malloc(n * sizeof(ABC));
	if (p == NULL) return -1;

	for (ABC* pp = p; pp < p + n; pp++) {
		scanf("%s %lf %lf %lf", &pp->name, &pp->k, &pp->e, &pp->m);
		getchar();
		pp->av = (pp->k + pp->e + pp->m) / 3.0;
	}

	for (ABC* pp = p; pp < p + n; pp++) {
		printf("%s %.1lf ", pp->name, pp->av);
		if (pp->k >= 90 || pp->e >= 90 || pp->m >= 90) printf("GREAT ");
		if (pp->k < 70 || pp->e < 70 || pp->m < 70) printf("BAD");
		printf("\n");
	}
}
