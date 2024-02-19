#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main(void) {
    char ar[100] = { NULL };
    int n = 0, b_n = 0, num = 0;

    for (char* p = ar;; p++) {
        scanf("%c", p);
        num += 1;
        if (*p == '#') break;
    }

    for (char* p = ar; p < ar + num +1; p++) {

        if (*p >= 'a' && *p <= 'z') {
            printf("%c", *p);
            n += 1;
        }

        else if (!(*p >= 'a' && *p <= 'z') && (*(p - 1) >= 'a' && *(p - 1) <= 'z')) {
            if (b_n < n) b_n = n;
            printf("\n");
            n = 0;
        }
    }

    printf("%d", b_n);
}
