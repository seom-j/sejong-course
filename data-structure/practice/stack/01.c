#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int t = -1;
char* S;

void push(char* S, char e, int n) {
    if (t >= n-1) {
        printf("Stack FULL\n");
    }
    else {
        t += 1;
        S[t] = e;
    }
}
char pop(char* S) {
    if (t <= -1) {
        printf("Stack Empty\n");
    }
    else {
        t -= 1;
        return S[t + 1];
    }
}
void peek(char* S) {
    if (t <= -1) {
        printf("Stack Empty\n");
    }
    else {
        printf("%c\n", S[t]);
    }
}
void duplicate(char* S, int n) {
    if (t >= n-1) {
        printf("StackFULL\n");
    }
    char e = pop(S);
    push(S, e, n);
    push(S, e, n);
}
void downRotate(char* S, int n) {
    if (n > t + 1) return;
    char tmp = S[t - n + 1];
    for (int j = t - n + 1; j <= t; j++) {
        S[j] = S[j + 1];
    }
    S[t] = tmp;
}
void upRotate(char* S, int n) {
    if (n > t + 1) return;
    char tmp = S[t];
    for (int j = t; j > t - n; j--) {
        S[j] = S[j - 1];
    }
    S[t - n + 1] = tmp;
}

void print(char* S) {
    for (int i = t; i >= 0; i--) {
        printf("%c", S[i]);
    }
    printf("\n");
}

int main() {
    char x[8] = { NULL };
    int n, m;
    scanf("%d %d", &n, &m);
    getchar();
    S = (char*)calloc(n, sizeof(char));
    for (int i = 0; i < m; i++) {
        gets(x);
        if (strncmp(x, "POP", 3) == 0) {
            pop(S);
        }
        if (strncmp(x, "PUSH", 4) == 0) {
            push(S, x[5], n);
        }
        if (strncmp(x, "PEEK", 4) == 0) {
            peek(S);
        }
        if (strncmp(x, "DUP", 3) == 0) {
            duplicate(S, n);
        }
        if (strncmp(x, "UpR", 3) == 0) {
            upRotate(S, atoi(x + 4));
        }
        if (strncmp(x, "DownR", 5) == 0) {
            downRotate(S, atoi(x + 6));
        }
        if (strncmp(x, "PRINT", 5) == 0) {
            print(S);
        }
    }
}
