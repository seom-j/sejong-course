#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)


int main(void) {
    int n, cnt=0;
    scanf("%d", &n);
    getchar();
    char tmp[100] = { NULL }, * p = NULL;
    gets(tmp);
    p = (char*)malloc(strlen(tmp) + 1);
    strcpy(p, tmp);
    if (p == NULL)return -1;

    for (char* pp = p; pp < p + strlen(p); pp++) {
        if (strncmp(pp, "cat", 3) == 0) cnt += 1;
    }
    printf("%d", cnt);

    if (p != NULL) free(p);
}
