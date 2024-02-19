#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct student {
    char name[10];
    int q1, q2, q3;
    double avq;
};

void read_data(struct student*);
void cal_avg(struct student*);
void sort(struct student*);
void print_score(struct student*);

int main(void) {
    struct student c[10];
    read_data(c);
    cal_avg(c);
    sort(c);
    print_score(c);
}

void read_data(struct student* c) {
    for (struct student* pc = c; pc < c + 10; pc++) {
        scanf("%s %d %d %d", &pc->name, &pc->q1, &pc->q2, &pc->q3);
        getchar();
    }
}
void cal_avg(struct student* c) {
    for (struct student* pc = c; pc < c + 10; pc++) {
        pc->avq = (pc->q1 + pc->q2 + pc->q3) / 3.0;
    }
}
void sort(struct student* c) {
    struct student tmp;
    for (struct student* qc = c; qc < c + 9; qc++) {
        for (struct student* pc = c; pc < c + 9; pc++) {
            if (pc->avq < (pc + 1)->avq) {
                tmp = *pc;
                *pc = *(pc + 1);
                *(pc + 1) = tmp;
            }
        }
    }
}
void print_score(struct student* c) {
    printf("%s %.2lf\n", c->name, c->avq);
    printf("%s %.2lf\n", (c + 9)->name, (c + 9)->avq);
    printf("%s %.2lf\n", (c + 7)->name, (c + 7)->avq);
    printf("%s %.2lf\n", (c + 8)->name, (c + 8)->avq);
    printf("%s %.2lf", (c + 9)->name, (c + 9)->avq);

}
