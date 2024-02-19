#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

struct date {
    int y, m, d;
};

struct date* select_min(struct date*, struct date*);

int main() {
    struct date to_ye[2], * pt = to_ye;

    for (pt; pt < to_ye + 2; pt++) {
        scanf("%d/%d/%d", &pt->y, &pt->m, &pt->d);
    }

    struct date ear = *(select_min(to_ye, to_ye + 1));

    printf("%d/%d/%d", ear.y, ear.m, ear.d);
}

struct date* select_min(struct date* a, struct date* b) {
    if (a->y > b->y) return b;
    else if (a->y < b->y) return a;
    else {
        if (a->m > b->m) return b;
        else if (a->m < b->m) return a;
        else {
            if (a->d > b->d) return b;
            else if (a->d < b->d) return a;
        }
    }
}
