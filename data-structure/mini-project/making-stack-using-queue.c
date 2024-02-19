#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#pragma warning(disable:4996)

int size = 0;

typedef struct node {
    int elem;
    struct node* prev, * next;
}node;

node* getnode();
void putnode(node* p);
int isEmpty(node* F);
void push(node* F, int e);
void pop(node* F1, node* R1, node* F2, node* R2);
void add_first(node* F, int e);
int delete_last( node* R);
void top(node* F);
void pushmillion(node* F, node* R); // 함수 원형 선언

int main() {
    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;
    node* F1 = getnode();
    node* R1 = getnode(); // 메인 큐
    node* F2 = getnode();
    node* R2 = getnode(); // 보조 큐
    F1->next = R1;
    R1->prev = F1;
    F2->next = R2;
    R2->prev = F2;
    char c;
    int e; // 헤더 & 트레일러 초기화 및 변수 선언

    while (1) {
        scanf("%c", &c);
        if (c == 'S') {
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);
            if (isEmpty(F1) == 0) printf("Empty"); // 비어있는 경우
            else printf("Nonempty"); // 아닌 경우
            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf(" (%d), cputime = %.10lf\n", size, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
        }
        else if (c == 'o') {
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);
            if (isEmpty(F1) == 0) {
                printf("Empty Stack Exception!!"); // 비어있는 경우
                QueryPerformanceCounter(&end);
                diff.QuadPart = end.QuadPart - start.QuadPart;
                printf(" (%d), cputime = %.10lf\n", size, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
                continue;
            }
            pop(F1, R1, F2, R2); // pop 함수 호출
            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf(" (%d), cputime = %.10lf\n", size, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
        }
        else if (c == 'p') {
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);
            while (getc(stdin)!= '\n') { // 엔터가 입력될 때 까지
                scanf("%d", &e); // 원소 입력
                push(F1, e); // push 함수 호출
            }
            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("OK (%d), cputime = %.10lf\n", size, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
        }
        else if (c == 'P') {
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);
            pushmillion(F1, R1); // pushmillion 함수 호출
            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("OK (%d), cputime = %.10lf\n", size, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
        }
        else if (c == 't') {
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);
            top(F1); // top 함수 호출
            QueryPerformanceCounter(&end);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf(" (%d), cputime = %.10lf\n", size, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart) * 1000);
        }
        else if (c == 'q') break;
    }
}

node* getnode() {
    return (node*)calloc(1, sizeof(node));
}
void putnode(node* p) {
    free(p);
}
void add_first(node* F, int e) { // 큐 앞에 삽입
    node* p = getnode();
    p->elem = e;
    p->next = F->next;
    F->next->prev = p;
    p->prev = F;
    F->next = p;
}
int delete_last(node* R) { // 큐 맨 뒤 삭제
    node* p = R->prev;
    R->prev = p->prev;
    p->prev->next = R;
    putnode(p);
    return e;
}
void push(node* F, int e) { // 스택 맨 위 삽입
    add_first(F, e);
    size += 1;
}
void pop(node* F1, node* R1, node *F2, node* R2) { // 스택 맨 위 삭제
    int e;
    while (1) {
        e = delete_last(R1);
        if (R1->prev == F1) break;
        add_first(F2, e);
    } // 맨 마지막 원소 제외하고 보조큐로 이동
    printf("%d", e); 
    while (R2->prev != F2) {
        e = delete_last(R2);
        add_first(F1, e);
    } // 보조큐에 있는 모든 원소 메인 큐로 이동
    size -= 1;
}
int isEmpty(node* F) { // 비어있는지 아닌지 반환
    if (size == 0) return 0;
    return 1;
}
void top(node* F) { // top 원소 반환
    if (F->next == 0);
    else printf("%d", F->next->elem);
}
void pushmillion(node* F, node* R) { // 1000000만개의 난수 스택에 삽입
    srand(time(NULL));
    int e;
    for (int i = 0; i < 1000000; i++) { // 1000000번동안
        e = rand() % 90 + 10; // 10-99 사이의 난수 정수 생성
        add_first(F, e); // 난수 정수 push
        size += 1;
    }
}
