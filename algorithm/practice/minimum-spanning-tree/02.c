#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#pragma warning(disable:4996)

typedef struct {
    int weight;   
    int u;          
    int v;        
} Edge;
typedef struct {
    Edge heap[100];
    int heapSize;
} HeapType;

int parent[100];
int num[100];

int findSet(int vertex);
void unionSet(int s1, int s2);
void insertUpHeap(HeapType* h, Edge e);
Edge removeMin(HeapType* h);
void insertEdge(HeapType* h, int u, int v, int weight);
void kruskal(HeapType* h, int n);

int main() {
    int n, m;
    int v1, v2, w;
    HeapType* h = malloc(sizeof(HeapType));
    h->heapSize = 0;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &v1, &v2, &w);
        insertEdge(h, v1, v2, w);
    }
    kruskal(h, n);
}

int findSet(int vertex) {
    int p, s, i = -1;
    for (i = vertex; (p = parent[i]) >= 0; i = p);
    s = i;   // 루트 s 찾기
    for (i = vertex; (p = parent[i]) >= 0; i = p) { 
        parent[i] = s;
    }  // 모두 루트를 가르키도록
    return s;   //루트 반환
}
void unionSet(int s1, int s2) {  
    if (num[s1] < num[s2]) {
        parent[s1] = s2;
        num[s2] += num[s1];
    }
    else {
        parent[s2] = s1;
        num[s1] += num[s2];
    }
}
void insertUpHeap(HeapType* h, Edge e) {
    int i = ++h->heapSize;
    while (e.weight < h->heap[i / 2].weight) {    //거슬러 올라가며 교체..연산
        if (i == 1) break;
        h->heap[i] = h->heap[i / 2];
        i /= 2; //부모노드의 자리로 이동
    }
    h->heap[i] = e; //삽입
}
Edge removeMin(HeapType* h) {
    int parent, child;
    Edge e, temp;
    e = h->heap[1]; //루트노드(최소값) 저장
    temp = h->heap[h->heapSize]; //마지막노드(최대값) 저장
    h->heapSize--;  //루트 자리에 두었다고 가정
    //시작 - 루트와 그 왼쪽 자식
    parent = 1;
    child = 2;
    while (1) {
        if (child > h->heapSize) break;
        if (h->heap[child].weight > h->heap[child + 1].weight) child++;  //우측자식 선택
        if (temp.weight <= h->heap[child].weight) break;

        h->heap[parent] = h->heap[child];   //자식과 교환
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp; //삽입

    return e;
}
void insertEdge(HeapType* h, int u, int v, int weight) {
    Edge e;
    e.u = u;
    e.v = v;
    e.weight = weight;
    insertUpHeap(h, e);
}
void kruskal(HeapType* h, int n) {
    int edgeCount = 0;  //현재까지 선택된 간선 수
    int uset, vset;
    Edge e;
    int sum = 0;
    //집합 초기화
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
        num[i] = 1;
    }
    while (1) {
        if (edgeCount == n - 1) break;
        e = removeMin(h);   //최소 가중치 간선
        uset = findSet(e.u);   //정점이 어느 집합에 속해있는지 찾기
        vset = findSet(e.v);

        if (uset != vset) { //서로 다른 집합에 속해 있으면
            printf(" %d", e.weight);
            sum += e.weight;
            edgeCount++;    //선택 간선 수 ++
            unionSet(uset, vset);  //합침
        }
    }
    printf("\n%d", sum);
}
