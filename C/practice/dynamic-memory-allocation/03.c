#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)


int main(void) {
    int n;
    scanf("%d", &n);
    getchar();

    char tmp[100] = { NULL }, * p = NULL;
    gets(tmp);
    p = (char*)malloc(strlen(tmp) + 1);

    if (p == NULL) return -1;
    strcpy(p, tmp);

    char a, b;
    int an = 0, bn = 0;
    scanf("%c %c", &a, &b);

    for (char* pp = p; pp < p + strlen(p); pp++) {
        if (*pp == a) an += 1;
        if (*pp == b) bn += 1;
    }

    printf("%d %d", an, bn);
    
    if (p != NULL) free(p);
}
