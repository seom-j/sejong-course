#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct student {
	char ma[51], na[21], bi[11];
};

struct student input(void);
void swap(struct student*, struct student*);
void output(struct student);

int main(void) {
	struct student st[100];
	int n;
	scanf("%d", &n);
	getchar();

	for (struct student* p = st; p < st + n; p++) *p = input();

	for (struct student* q = st; q < st + n-1; q++) {
		for (struct student* p = st; p < st + n-1; p++) {
			if (strcmp(p->ma, (p + 1)->ma) > 0) swap(p, p + 1);
		}
	}

	for (struct student* p = st; p < st + n; p++) output(*p);
}

struct student input(void) {
	struct student st;
	gets(&st.ma);
	scanf("%s %s", &st.na, &st.bi);
	getchar();

	return st;
}

void swap(struct student *a, struct student* b) {
	struct student tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void output(struct student a) {
	printf("%s %s %s\n", a.ma, a.na, a.bi);
}
