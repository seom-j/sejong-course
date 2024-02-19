#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)


int main(void) {
    int n = 0, b_idx = 0, cnt = 0, b_cnt = 0, f = 0;
    char x[101] = { NULL }, ** y, tmp[101] ={NULL};
    scanf("%d %s", &n, x);
    getchar();

    y = (char**)malloc(n * sizeof(char*));
    if (y == NULL)return -1;
    for (int i = 0; i < n; i++) {
        gets(tmp);
        y[i] = (char*)malloc(strlen(tmp) + 1);
        if (y[i] == NULL) return-1;
        strcpy(y[i], tmp); // 동적할당, 입력

        cnt = 0;
        for (char* py = y[i]; py < y[i] + strlen(y[i]); py++) {
            if (strncmp(py, x, strlen(x)) == 0) {
                cnt += 1;
                py += strlen(x) - 1;
                cnt += 1;
            }
        } // 같은 것 갯수

        if (cnt > b_cnt) {
            b_cnt = cnt;
            b_idx = i;
        }
    }
    if (b_cnt > 0) puts(y[b_idx]);
    else printf("NONE");

    for (int i = 0; i < n; i++) {
        if (y[i] != NULL) {
            free(y[i]);
            y[i] = NULL;
        }
    }
    if (y != NULL) {
        free(y);
        y = NULL;
    }
}
