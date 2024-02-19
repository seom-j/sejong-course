#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct student {
    int h, l, g;
    char pf;
};

void passorfail(struct student*);

int main(void) {
    struct student c;
    scanf("%d %d %d", &c.h, &c.l, &c.g);
    passorfail(&c);
    printf("%d %c", c.h - c.l, c.pf);
}

void passorfail(struct student* c) {
    if ((c->h - c->l) > (c->g)) c->pf = 'F';
    else c->pf = 'P';
}
