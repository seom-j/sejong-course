#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int t = -1;
char S[101];

void push(char* S, char e) {
    if (t >= 99) {
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
char* peek(char* S) {
    if (t <= -1) {
        printf("Stack Empty\n");
    }
    else {
        char* p = &S[t];
        return p;
    }
}

int main() {
    int n, num = 0;
    char x[101] = { NULL };
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", x);
        for (int j = 0; j < strlen(x); j++) {
            if ((x[j] - '0') >= 0 && (x[j] - '0') <= 9) {
                push(S, x[j]);
            }
            else {
                num = pop(S) - '0';
                if (x[j] == '*') {
                    *peek(S) = ((*peek(S) - '0') * num) + '0';
                }
                else if (x[j] == '/') {
                    *peek(S) = ((*peek(S) - '0') / num) + '0';
                }
                else if (x[j] == '+') {
                    *peek(S) = ((*peek(S) - '0') + num) + '0';
                }
                else if (x[j] == '-') {
                    *peek(S) = ((*peek(S) - '0') - num) + '0';
                }
            }
        }
        printf("%d\n", *peek(S) - '0');
    }
}
