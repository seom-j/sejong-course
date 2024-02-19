#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int main() {
    int x[100][100] = {NULL};
    int n, m, id = 0, jd = 0, addi = 1, addj = 1;

    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n * m; i++) {
        x[id][jd] = i;
        if (jd < m && addi == 1 && addj == 1) {
            if (jd + 1 < m && x[id][jd + 1] == 0)  jd++; 
            else {
                id++;
                addi = -1;
            }
        }
        else if (id < n && addi == -1 && addj == 1) {
            if (id + 1 < n && x[id + 1][jd] == 0)  id++; 
            else {
                jd--;
                addj = -1;
            }
        }
        else if (jd >= 0 && addi == -1 && addj == -1) {
            if (jd > 0 && x[id][jd - 1] == 0) jd--; 
            else {
                id--;
                addi = 1;
            }
        }
        else if (id >= 0 && addj == -1 && addi == 1) {
            if (id > 0 && x[id - 1][jd] == 0) id--;
            else {
                jd++;
                addj = 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) printf("%d ", x[i][j]);
        printf("\n");
    }
}
