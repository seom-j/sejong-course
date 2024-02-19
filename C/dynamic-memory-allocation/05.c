#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)


int main(void) {
    int n;
    scanf("%d", &n);

    int* p = NULL, tmp;
    p = (int*)malloc(n*sizeof(int));

    if (p == NULL) return -1;
    for (int* pp = p; pp < p + n; pp++)  scanf("%d", pp);


    for (int* pp = p; pp < p + n-1; pp++) {
        if (*pp > *(pp + 1)) {
            tmp = *pp;
            *pp = *(pp + 1);
            *(pp + 1) = tmp;
        }
    }

    for (int* pp = p; pp < p + n; pp++) printf("%d\n", *pp);
    if (p != NULL) free(p);
}
