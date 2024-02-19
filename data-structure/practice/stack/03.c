#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

int t = -1;
char S[101] = { NULL };

int rank(char c) {
    if (c == '|') return 1;
    if (c == '&') return 2;
    if (c == '<' || c == '>') return 3;
    if (c == '-' || c == '+') return 4;
    if (c == '/' || c == '*') return 5;
    if (c == '!') return 6;
    else return 0;
} // 우선순위 판별 (클수록 높음)

void push(char* S, char c) {
    if (t >= 99 || t < -1) return;
    else {
        t += 1;
        S[t] = c;
    }
}
char pop(char* S) {
    if (t <= -1 || t > 99) return;
    else {
        t -= 1;
        return S[t + 1];
    }
}
char* peek(char* S) {
    if (t <= -1 || t > 99) return;
    else {
        char* p = &S[t];
        return p;
    }
}

int main() {
    int n = 0, s = 0;
    char x[101] = { NULL }, c = 0, pm = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", x);
        for (int j = 0; j < strlen(x); j++) {
            if (x[j] == '-' || x[j] == '+') {
                if (j == 0) {
                    s = 1;
                    pm = x[j];
                    continue;
                }
                else {
                    if (x[j - 1] == '*' || x[j - 1] == '!' || x[j - 1] == '+' ||
                        x[j - 1] == '-' || x[j - 1] == '/' || x[j - 1] == '>' ||
                        x[j - 1] == '<' || x[j - 1] == '|' || x[j - 1] == '&') {
                        s = 1;
                        pm = x[j];
                        continue;
                    }
                }
            }
            if (x[j] == '(') push(S, x[j]); // 열린 괄호 그냥 대입
            else if (x[j] == ')') {
                c = pop(S);
                while (c != '(') {
                    printf("%c", c);
                    c = pop(S);
                }
            } // 닫힌 괄호일 경우 열린 괄호 나올때까지 출력 (괄호 끝날 때까지 출력 안된 문자 출력)
            else if (x[j] == '*' || x[j] == '!' || x[j] == '+' ||
                x[j] == '-' || x[j] == '/' || x[j] == '>' ||
                x[j] == '<' || x[j] == '|' || x[j] == '&') {
                while ((t != -1) && (rank(*peek(S)) >= rank(x[j]))) {
                    printf("%c", pop(S));
                } // 스택이 비어있지 않고 우선순위가 스택 속의 것이 높다면 출력
                if (x[j] == '|' || x[j] == '&') {
                    push(S, x[j++]);
                } // |과 &는 2번 스택에 저장 (다음 |, &가 위 출력에 들어가지 않기 위함)
                push(S, x[j]); // 스택에 저장
            }
            else if (x[j] >= 'A' && x[j] <= 'Z') {
                printf("%c", x[j]);
                if (s == 1) printf("%c", pm);
                s = 0;
            } // 피연산자 무조건 출력
        }

        while (t != -1) {
            printf("%c", pop(S));
        } // 나머지 출력

        printf("\n");
    }
}
