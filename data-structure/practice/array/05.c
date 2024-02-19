#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int main() {
    int x[100][100] = { NULL };
    int n, m, id = 0, jd = 0, num = 1;
    scanf("%d %d", &n, &m);

    for (int sum = 0; sum <= n * m; sum++) {
        if (sum < m) {
            id = 0;
            jd = sum;
        }
        else {
            jd = m - 1;
            id = sum - (m - 1);
        }

        while (sum == id + jd && jd >= 0 && id < n) {
            x[id][jd] = num++;
            id++;
            jd--;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) printf(" %d", x[i][j]);
        printf("\n");
    }
}
