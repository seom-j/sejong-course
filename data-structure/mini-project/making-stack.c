#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#pragma warning(disable:4996)

int size = 0;

typedef struct node{
    int elem;
    struct node* next;
}node;

node* getnode();
void putnode(node* p);
node* push(node* TH, node* MH, int e);
node* pushMillion(node* TH, node* MH);
int pop(node* TH, node* MH);
void popMillion(node* TH, node* MH);
int* findMin(node* MH); // 함수 원형 선언

int main() {
    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;
    node* TH = getnode();
    node* MH = getnode();
    int e;
    char c;
    scanf("%c", &c);
    while (c != 'q') {
        if (c == 'p') {
            scanf("%d", &e);
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);
            push(TH, MH, e);
            QueryPerformanceCounter(&end);
            printf("push %d", TH->next->elem);
            printf(" (%d) ", size);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("cputime: %.10lf\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart))*1000;
        }
        else if (c == 'P') {
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);
            pushMillion(TH, MH);
            QueryPerformanceCounter(&end);
            printf("pushMillion");
            printf(" (%d) ", size);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("cputime: %.10lf\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart))*1000;
        }
        else if (c == 'o') {
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);
            e = pop(TH, MH);
            QueryPerformanceCounter(&end);
            printf("pop %d", e);
            printf(" (%d) ", size);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("cputime: %.10lf\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart))*1000;
        }
        else if (c == 'O') {
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);
            popMillion(TH, MH);
            QueryPerformanceCounter(&end);
            printf("popMillion");
            printf(" (%d) ", size);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("cputime: %.10lf\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart))*1000;
        }
        else if (c == 'f') {
            QueryPerformanceFrequency(&ticksPerSec);
            QueryPerformanceCounter(&start);
            e = findMin(MH);
            QueryPerformanceCounter(&end);
            printf("min %d",e);
            printf(" (%d) ", size);
            diff.QuadPart = end.QuadPart - start.QuadPart;
            printf("cputime: %.10lf\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart))*1000;
        }
        else if (c == 'q') break;
        scanf("%c", &c);
    } // 각 경우에 따른 출력 (출력 예시에 따름)
     
    while (TH->next != 0) pop(TH, MH);
    getnode(TH);
    getnode(MH); // 스택 비우기

    return 0;
}


node* getnode() {
    return (node*)calloc(1, sizeof(node));
} // 노드 생성

void putnode(node* p) {
    free(p);
} // 노드 해제

node* push(node* TH, node* MH, int e) {
    node* p = getnode();
    p->elem = e;
    p->next = TH->next;
    TH->next = p; // push

    if (MH == 0) return; // 최솟값 스택의 push의 경우를 판단하기 위함
    if (MH->next == 0) { // 최솟값 스택이 비어있을 경우 -> 첫 수일 경우
        node* q = getnode();
        q->elem = e;
        q->next = MH->next;
        MH->next = q; // 최솟값 스택에 추가
    }
    if (MH->next->elem >= e) { // 최솟값 스택의 top의 원소보다 추가하려는 e가 작을 경우
        push(MH, 0, e); // 최솟값 스택의 top에 push
    } // (최솟값 스택의 top에 무조건 최솟값이 오도록)

    size += 1; // 최솟값 스택에 대한 push가 아닌 메인 스택에 대한 push에 대해서만 size up
    return;
}

node* pushMillion(node* TH, node* MH) {
    srand(time(NULL));
    int e;
    for (int i = 0; i < 1000000; i++) { // 1000000번동안
        e = rand() % 9000 + 1000; // 1000-9999 사이의 난수 정수 생성
        push(TH, MH, e); // 난수 정수 push
    }
}

int pop(node* TH, node* MH) {
    if (isEmpty(TH)) return; // 비어있다면 종료 (pop 불가)
    int e = TH->next->elem; // 반환을 위해 값 저장
    node* p = TH->next;
    TH->next = p->next;
    putnode(p); // pop

    if (MH == 0) return e; // 최솟값 스택의 pop의 경우를 판단하기 위함
    if (e == MH->next->elem) { // 최솟값 스택의 수가 메인 스택에서 사라진다면
        pop(MH, 0); // pop
    } // 중복시에도 최솟값 스택에 들어가므로 고려 X

    size -= 1; // 최솟값 스택에 대한 pop이 아닌 메인 스택에 대한 pop에 대해서만 size down
    return e;
}

void popMillion(node* TH, node* MH) {
    if (size < 1000000) return; // 사이즈가 1000000보다 작다면 종료 (pop불가)
    for (int i = 0; i < 1000000; i++) { // 1000000번동안
        pop(TH, MH); // pop
    }
}

int* findMin(node* MH) {
    return MH->next->elem; // 최솟값 스택의 top 원소 출력
}
