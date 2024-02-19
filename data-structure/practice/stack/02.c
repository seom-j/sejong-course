#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int t , n = 1000;
char* S;

void push(char* S, char e) {
    if (t == n - 1) {
    }
    else {
        t += 1;
        S[t] = e;
    }
}
char pop(char* S) {
    if (t != -1) {
        t -= 1;
        return S[t + 1];
    }
    else {
    }
}
char peek(char* S) {
    if (t != -1) {
        return S[t];
    }
    else {
        return 0;
    }
}
void print(char* S) {
    for (int i = t; i >= 0; i--) {
        printf("%c", S[i]);
    }
    printf("\n");
}
int main() {
    t = -1;
    int cnt = 0;
    char x[1001] = { NULL }, S[1001] = { NULL };
    gets(x);
    for (int i = 0; i < strlen(x); i++)
        if (x[i] == '(' || x[i] == ')' || x[i] == '{' || x[i] == '}' || x[i] == '[' || x[i] == ']')
            cnt += 1;

    for (int i = 0; i < strlen(x); i++) {
        if (x[i] == '(' || x[i] == '{' || x[i] == '[') {
            push(S, x[i]);
        }
        else if (x[i] == ')' || x[i] == '}' || x[i] == ']') {
            if (peek(S) == '(' && x[i]==')') pop(S);
            else if (peek(S) == '{' && x[i] == '}') pop(S);
            else if (peek(S) == '[' && x[i] == ']') pop(S);
            else {
                printf("Wrong_%d", cnt);
                return;
            }
        }
    }
    if (t == -1) printf("OK_%d", cnt);
    else printf("Wrong_%d", cnt);

}
