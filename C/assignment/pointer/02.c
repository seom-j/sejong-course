#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int passengerN(int n);
void rebooking(int* ar);
int changeseat(int* ar);

int main(void) {
    int n, ar[100] = { 0 };
    scanf("%d", &n);
    for (int* p = ar; p < ar + n; p++) scanf("%d", p);

    printf("%d\n", passengerN(n));

    if (passengerN(n) == 0) {
        rebooking(ar);
        for (int* p = ar; p < ar + n; p++) printf("%d ", *p);
    }
}

int passengerN(int n) {
    if (n >= 5) return 0;
    return -1;
}
void rebooking(int* ar) {
    for (int* p = ar;; p++) {
        if (*p == 0) break;
        for (int* q = p+1;; q++) {
            if (*q == 0) break;
            if (*p == *q) *q = changeseat(ar);
        }
    }
}
int changeseat(int* ar) {
    int f = 0;
    for (int i = 1; i <= 21; i++) {
        for (int* p = ar;; p++) {
            if (*p == 0) break;
            if (i == *p) f = 1;
        }
        if (f == 0) return i;
        f = 0;
    }
}
