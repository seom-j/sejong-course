#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)


int main(void) {
    int n;
    float b_num = 0;
    scanf("%d", &n);
    float* p = (float*)malloc(n * sizeof(float));
    if (p == NULL) return -1;

    for (float* pp = p; pp < p + n; pp++) {
        scanf("%f", pp);
        if (pp == p) b_num = *pp;
        if (b_num < *pp) b_num = *pp;
    }
    printf("%.2f", b_num);

    if (p != NULL) free(p);
}
