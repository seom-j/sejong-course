#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int* MAX(int* ar);
int* MIN(int* ar);

int main(void) {
    int n, f = 0, ar[100] = { 0 }, *p1, *p2;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int* p = ar;; p++) {
            scanf("%d", p);
            if (*p == 0) break;
        }

        p1 = MAX(ar);
        p2 = MIN(ar);

        if (p1 <= p2) {
            for (int* p = p1 + 1; p < p2; p++) {
                printf("%d ", *p);
                f += 1;
            }
        }
        else {
            for (int* p = p2 + 1; p < p1; p++) {
                printf("%d ", *p);
                f += 1;
            }
        }
        if (f == 0) printf("none");
        f = 0;
        printf("\n");
    }
}

int* MAX(int* ar) {
    int b_n = *ar, *b_p = ar;
    for (int* p = ar; *p != 0; p++) {
        if (b_n < *p) {
            b_n = *p;
            b_p = p;
        }
    }
    return b_p;
}
int* MIN(int* ar) {
    int b_n = *ar, *b_p = ar;
    for (int* p = ar; *p != 0; p++) {
        if (b_n > *p) {
            b_n = *p;
            b_p = p;
        }
    }
    return b_p;
}
