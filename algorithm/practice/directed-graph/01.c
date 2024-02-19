#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

typedef struct node {
	int elem;
	struct node* next;
}node;
typedef struct vertex {
	char name;
	int indegree;
	struct node* outEdges;
	struct node* inEdges;
}vertex;
typedef struct edge {
	int origin;
	int destination;
}edge;
typedef struct graph {
	vertex* vertices;
	edge* edges;
}graph;
typedef struct queue {
	int front;
	int rear;
	int* queue;
}queue;

int n, m; // 정점 수, 간선 수
int* topOrder; // (topOrder 배열)
graph G; // (G 방향그래프)
queue Q; // (Q 큐)

// 필요 전역 데이터구조 선언

node* getNode();
void buildGraph();
void insertVertex(char, int);
void insertDirectedEdge(char, char, int);
int index(char);
void addFirst(node*, int);
void topologicalSort();
int isEmpty();
void Enqueue(int);
int Dequeue();
void freeAll();

//함수 원형선언


int main() {
	buildGraph();
	topologicalSort();
	if (topOrder[0] == 0) {
		printf("0\n");
	}
	else {
		for (int i = 1; i <= n; i++) {
			printf("%c ", G.vertices[topOrder[i]].name);
		}
	}
	freeAll();
	return 0;
}



node* getNode() {
	return (node*)calloc(1, sizeof(node));
}
void buildGraph() {
	char v, u, w;
	scanf("%d", &n);
	getchar();
	G.vertices = (vertex*)calloc(n, sizeof(vertex));
	for (int i = 0; i < n; i++) {
		scanf("%c", &v);
		getchar();
		insertVertex(v, i);
	}
	scanf("%d", &m);
	getchar();
	G.edges = (edge*)calloc(m, sizeof(edge));
	for (int i = 0; i < m; i++) {
		scanf("%c %c", &u, &w);
		getchar();
		insertDirectedEdge(u, w, i);
	}
	return;
}
void insertVertex(char v, int i) { // 정점에 대입 & 간선들 초기화
	G.vertices[i].name = v;
	G.vertices[i].outEdges = getNode();
	G.vertices[i].outEdges->next = NULL;
	G.vertices[i].inEdges = getNode();
	G.vertices[i].inEdges->next = NULL;
	G.vertices[i].indegree = 0;
	return;
}
void insertDirectedEdge(char u, char w, int i) { // 각각의 방향간선에 해당하는 인덱스 대입
	int uN, wN;
	uN = index(u);
	wN = index(w);
	G.edges[i].origin = uN;
	G.edges[i].destination = wN;
	addFirst(G.vertices[uN].outEdges, i);
	addFirst(G.vertices[wN].inEdges, i);
	G.vertices[wN].indegree++; // 차수 증가
	return;
}
int index(char N) {
	for (int i = 0; i < n; i++) {
		if (G.vertices[i].name == N) {
			return i;
		}
	}
}
void addFirst(node* p, int i) { // 간선 인덱스 대입
	node* q = getNode();
	q->elem = i;
	q->next = p->next;
	p->next = q;
	return;
}
void topologicalSort(){ // 위상 정렬
	int u;
	int* in = (int*)malloc(sizeof(int) * n);  // 정점 i의 진입차수 (in 배열)
	topOrder = (int*)malloc(sizeof(int) * (n + 1));  // 1 ~ n : 정점의 위상순서, 0 : 방향사이클 여부
	Q.queue = (int*)malloc(sizeof(int) * n);
	Q.front = -1; Q.rear = -1;

	for (int i = 0; i < n; i++){
		in[i] = G.vertices[i].indegree;  // 진입차수 대입
		if (in[i] == 0)  // 진입차수가 0인 정점의 인덱스 큐에 삽입
			Enqueue(i);
	}
	int t = 1, e, w;
	node* cur;
	while (!isEmpty()){
		u = Dequeue();
		topOrder[t] = u;
		t++;
		cur = G.vertices[u].outEdges->next;
		while (cur != NULL){
			e = cur->elem;
			w = G.edges[e].destination;
			in[w]--;
			if (in[w] == 0)
				Enqueue(w);  // 진입차수가 0인 정점의 인덱스 큐에 삽입
			cur = cur->next;
		}
	}
	if (t <= n) {
		topOrder[0] = 0;  // 방향싸이클 존재
	}
	else {
		topOrder[0] = 1;  // G = DAG
	}
	free(in);
	return;
}

int isEmpty(){
	if (Q.front == Q.rear) {
		return 1;
	}
	else {
		return 0;
	}
}
void Enqueue(int i){
	Q.rear = (Q.rear + 1) % n;
	Q.queue[Q.rear] = i;
	return;
}
int Dequeue(){
	Q.front = (Q.front + 1) % n;
	return Q.queue[Q.front];
}

void freeAll(){
	node* curOutEdge, * prevOutEdge, * curInEdge, * prevInEdge;
	for (int i = 0; i < n; i++){
		curOutEdge = G.vertices[i].outEdges->next;
		prevOutEdge = G.vertices[i].outEdges;
		while (curOutEdge != NULL){
			free(prevOutEdge);
			prevOutEdge = curOutEdge;
			curOutEdge = curOutEdge->next;
		}
		free(prevOutEdge); // out

		curInEdge = G.vertices[i].inEdges->next;
		prevInEdge = G.vertices[i].inEdges;
		while (curInEdge != NULL){
			free(prevInEdge);
			prevInEdge = curInEdge;
			curInEdge = curInEdge->next;
		}
		free(prevInEdge); //in
	}
	free(G.vertices);
	free(G.edges);
	free(topOrder);
	free(Q.queue);
	return;
}
