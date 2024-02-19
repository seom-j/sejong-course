#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)


int main(void) {
    int n, sum = 0;
    scanf("%d", &n);
    int* p = (int*)malloc(n * sizeof(int));
    if (p == NULL) return -1;

    for (int* pp = p; pp < p + n; pp++) {
        scanf("%d", pp);
        sum += *pp;
    }
    printf("%d", sum);

    if (p != NULL) free(p);
}
