#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)


int main(void) {
    int n, m;
    scanf("%d %d", &n,&m);

    char ** p;
    p = (char**)malloc(m * sizeof(char*)); // 세로

    for (int i = 0; i < m; i++) {
        p[i] = (char*)malloc(n * sizeof(char));
    } // 가로

    char ch = 'a';
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            p[i][j] = ch;
            ch += 1;
            if (ch == 'z' + 1) ch = 'A';
            if (ch == 'Z' + 1) ch = 'a';
        }
    } // 알파벳 할당

    if (p == NULL) return -1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)  printf("%c ", p[i][j]);
        printf("\n");
    }

    if (p != NULL) free(p);
}
