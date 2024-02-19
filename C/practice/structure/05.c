#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct student {
    char name[9];
    double av;
};

int main(void) {
    int n, k, e, m;
    scanf("%d", &n);
    getchar();

    struct student c[50];

    for (struct student* pc = c; pc < c + n; pc++) {
        scanf("%s %d %d %d", &pc->name, &k, &e, &m);
        getchar();
        pc->av = (k + e + m) / 3.0;
    }

    for (struct student* pc = c; pc < c + n; pc++) {
        printf("%s %.1lf ", pc->name, pc->av);
        if (pc->av >= 90) printf("A");
        else if (pc->av >= 80) printf("B");
        else if (pc->av >= 70) printf("C");
        else printf("D");
        printf("\n");
    }
}
