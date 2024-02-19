#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

typedef struct node {
    int elem;
    struct node* prev,* next;
}node;

node* getnode();
void putnode(node* p);
node* add_front(node* F, int e);
node* add_rear(node* R, int e);
node* delete_front(node* F);
node* delete_rear(node* R);
void print(node* F);

int main() {
    node* F = 0, *R = 0;
    int n, e;
    char x[3];
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++) {
        scanf("%s", x);
        if (strncmp(x, "AF", 2) == 0) {
            scanf("%d", &e);
            getchar();
            F = add_front(F, e);
            if (R == 0) R = F;
        }
        if (strncmp(x, "AR", 2) == 0) {
            scanf("%d", &e);
            getchar();
            R = add_rear(R, e);
            if (F == 0) F = R;
        }
        if (strncmp(x, "DF", 2) == 0) {
            if (F == 0) {
                printf("underflow\n");
                break;
            }
            F = delete_front(F);
            if (F == 0) R = 0;;

        }
        if (strncmp(x, "DR", 2) == 0) {
            if (R == 0) {
                printf("underflow\n");
                break;
            }
            R = delete_rear(R);
            if (R == 0) F = 0;
        }
        if (strncmp(x, "P", 1) == 0) {
            print(F);
        }
    }
}

node* getnode() {
    return (node*)calloc(1, sizeof(node));
}
void putnode(node* p) {
    free(p);
}
node* add_front(node* F, int e) {
    node* p = getnode();
    if (F == 0) p->next = 0;
    else {
        p->next = F;
        F->prev = p;
    }
    p->prev = 0;
    p->elem = e;
    F = p;
    return F;
}
node* add_rear(node* R, int e) {
    node* p = getnode();
    if (R == 0) p->prev = 0;
    else {
        p->prev = R;
        R->next = p;
    }
    p->next = 0;
    p->elem = e;
    R = p;
    return R;
}
node* delete_front(node* F) {
    node* p = F;
    if (F->next == 0) {
        putnode(p);
        F = 0;
        return F;
    }
    F = F->next;
    F->prev = 0;
    putnode(p);
    return F;
}
node* delete_rear(node* R) {
    node* p = R;
    if (R->prev == 0) {
        putnode(p);
        R = 0;
        return R;
    }
    R = R->prev;
    R->next = 0;
    putnode(p);
    return R;
}
void print(node* F) {
    node* p = F;
    while (!(p->next == 0)) {
        printf(" %d", p->elem);
        p = p->next;
    }
    printf(" %d\n", p->elem);
}
