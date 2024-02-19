#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning (disable:4996)

// 다익스트라 확장을 통한 최단경로 및 최단경로의 수

typedef struct adjacencyList {
	int vertex;
	int weight;
	struct adjacency* link;
}adjacencyList; // 인접리스트 구조체

adjacencyList* G[6]; // 인접리스트 (그래프)

void initG();
void insertEdge(int, int, int);
void DijkstraExpansion(int, int);

void main() {
	initG(); // 그래프 초기화

	DijkstraExpansion(2, 0); // C, A의 최단거리와 최단경로수
	DijkstraExpansion(2, 5); // C, F의 최단거리와 최단경로수
	DijkstraExpansion(5, 2); // F, C의 최단거리와 최단경로수
	DijkstraExpansion(1, 3); // B, D의 최단거리와 최단경로수
}

void initG() { // 그래프 초기화
	insertEdge(0, 1, 8);	// A-B
	insertEdge(0, 2, 1);	// A-C
	insertEdge(0, 3, 4);	// A-D
	insertEdge(1, 2, 7);	// B-C
	insertEdge(1, 4, 4);	// B-E
	insertEdge(2, 3, 5);	// C-D
	insertEdge(2, 4, 3);	// C-E
	insertEdge(2, 5, 9);	// C-F
	insertEdge(3, 5, 4);	// D-F
} // 과제 5에 주어진 샘플 그래프 G와 동일

void insertEdge(int start, int end, int weight) {
	adjacencyList* node;

	node = (adjacencyList*)calloc(1, sizeof(adjacencyList));
	node->vertex = end;
	node->weight = weight;
	node->link = G[start];
	G[start] = node;

	node = (adjacencyList*)calloc(1, sizeof(adjacencyList));
	node->vertex = start;
	node->weight = weight;
	node->link = G[end];
	G[end] = node;
} // 양방향 간선 연결

void DijkstraExpansion(int start, int target) {
	int distance[6]; // 가방과의 거리
	int pathCnt[6] = { 0, }; // 각 경로 수
	int bag[6] = { 0, }; // 가방 안에 있는지 여부 (없다면 0, 있다면 1)
	adjacencyList* recentVertexList; // 가장 최근에 들어온 정점 (u)를 저장
	int Idx = 0; // 반복 횟수
	int min; // 최단거리
	int recentVertex; // 최근 들어온 정점의 vertexValue

	for (int i = 0; i < 6; i ++) {
		distance[i] = 9999;
	}
	distance[start] = 0; // distance 배열 초기화

	while (Idx < 6) {
		min = 9999;

		for (int i = 0; i < 6; i++) {
			if (distance[i] < min && !bag[i]) { // 최소 거리로부터 시작하기 위함
				min = distance[i];
				recentVertex = i;
			}
		}

		bag[recentVertex] = 1; // in
		recentVertexList = G[recentVertex]; // 최근 정점 저장

		while (recentVertexList != NULL) {
			if (!bag[recentVertexList->vertex]) { // out 정점일 경우
				if (min + recentVertexList->weight == distance[recentVertexList->vertex]) {
					pathCnt[recentVertexList->vertex] += pathCnt[recentVertex];
				} // 수행한 거리가 기존 최단 거리와 같을 경우 -> 최단거리 수 합하기

				if (min + recentVertexList->weight < distance[recentVertexList->vertex]) {
					distance[recentVertexList->vertex] = min + recentVertexList->weight;
					if (recentVertex == start) {
						pathCnt[recentVertexList->vertex] = 1;
					}
					else {
						pathCnt[recentVertexList->vertex] = pathCnt[recentVertex];
					}
				} // 수행한 거리가 기존 최단거리보다 작을 경우 -> 간선 relexing 진행
			}
			recentVertexList = recentVertexList->link;
		}

		Idx++;
		if (recentVertex == target)break; // 최근 정점이 도착 정점이라면 break
	}

	printf("%c, %c : 최단거리 = %d, 최단경로 수 = %d\n", start + 'A', target + 'A', distance[target], pathCnt[target]);
	// 과제 5의 수행결과와 동일한 인쇄
}
