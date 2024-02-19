#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#pragma warning(disable:4996)

typedef struct Vertex {
	int index;
	float weight;
	int flag;
}Vertex;

int main() {
	int n, m;
	int u, v;
	float w, sum = 0;

	scanf("%d %d", &n, &m);
	Vertex* vertices = malloc(n * sizeof(Vertex));
	float** adjacencyMatrix = malloc(n * sizeof(float*));
	int* result = malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) {
		adjacencyMatrix[i] = malloc(n * sizeof(float));
		vertices[i].index = i;
		vertices[i].weight = INFINITY;
		vertices[i].flag = 0;
		for (int j = 0; j < n; j++) {
			adjacencyMatrix[i][j] = 0;	// 간선이 존재하지 않을 경우 0
		}
	}

	for (int i = 0; i < m; i++) {
		scanf("%d %d %f", &u, &v, &w);
		adjacencyMatrix[u - 1][v - 1] = w;
		adjacencyMatrix[v - 1][u - 1] = w;
	}

	int idx = 0, minIdx = 0, resultIdx = 0;
	result[resultIdx++] = vertices[minIdx].index + 1;
	vertices[minIdx].flag = 1;

	for (int i = 1; i < n; i++) {	//n-1회 반복
		for (int j = 1; j < n; j++) {	//인접행렬 검사
			if (adjacencyMatrix[minIdx][j] != 0 && vertices[j].flag == 0) {
				vertices[j].weight = vertices[j].weight < adjacencyMatrix[minIdx][j] ? vertices[j].weight : adjacencyMatrix[minIdx][j];
			}
		}
		minIdx = 0;
		for (int k = 1; k < n; k++) {
			if (vertices[k].flag == 0 && vertices[k].weight < vertices[minIdx].weight) minIdx = k;
		}
		result[resultIdx++] = vertices[minIdx].index + 1;
		vertices[minIdx].flag = 1;
		sum += vertices[minIdx].weight;
	}

	for (int i = 0; i < n; i++) printf(" %d", result[i]);
	printf("\n%.0f", sum);


	// 동적할당 해제
	for (int i = 0; i < n; i++) free(adjacencyMatrix[i]);
	free(adjacencyMatrix);
	free(vertices);
	free(result);
}
