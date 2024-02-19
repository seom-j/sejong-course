#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct student {
    char name[10];
    int fe;
};

int main(void) {
    struct student c[5], lows;
    int s=0, b_low=100;

    for (struct student* pc = c; pc < c + 5; pc++) {
        scanf("%s %d", &pc->name, &pc->fe);
        getchar();
        s = pc->fe;
        if (b_low > s) {
            lows = *pc;
            b_low = s;
        }
    }

    printf("%s %d", lows.name, lows.fe);
}
