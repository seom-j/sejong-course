#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

typedef struct node {
	struct node* next;
	int elem;
}node; // 노드

typedef struct edge {
	int edges[2];
	int elem;
}edge; // 엣지

node* getNode(int);
int reverse(int, node*, edge*);
void printNodeAndWeight(int, node*, edge*);
void updateEdge(int, int, int, node*, edge**, int*);
void updateList(int, int, int, int, node*);
void clearAll(node*);
// 함수 원형선언

void main() {
	int nodeNum, a, b, w, edgeLen = 8;
	char com;
	node* cur = NULL;
	node* nodes = (node*)malloc(sizeof(node) * 6);
	edge* edges = (edge*)malloc(sizeof(edge) * 8);

	for (int i = 0; i < 6; i++) {
		(nodes + i)->elem = i + 1;
		(nodes + i)->next = (node*)malloc(sizeof(node));
		(nodes + i)->next->next = NULL;
	}
	cur = nodes[0].next;
	cur->next = getNode(0); cur = cur->next;
	cur->next = getNode(1); cur = cur->next;
	cur->next = getNode(2); cur = cur->next;
	cur->next = getNode(3);
	cur = nodes[1].next;
	cur->next = getNode(0); cur = cur->next;
	cur->next = getNode(4);
	cur = nodes[2].next;
	cur->next = getNode(1); cur = cur->next;
	cur->next = getNode(4); cur = cur->next;
	cur->next = getNode(5);
	cur = nodes[3].next;
	cur->next = getNode(2);
	cur = nodes[4].next;
	cur->next = getNode(5); cur = cur->next;
	cur->next = getNode(6); cur = cur->next;
	cur->next = getNode(7);
	cur = nodes[5].next;
	cur->next = getNode(3); cur = cur->next;
	cur->next = getNode(7);
	edges[0].edges[0] = 0;
	edges[0].edges[1] = 1;
	edges[0].elem = 1;
	edges[1].edges[0] = 0;
	edges[1].edges[1] = 2;
	edges[1].elem = 1;
	edges[2].edges[0] = 0;
	edges[2].edges[1] = 3;
	edges[2].elem = 1;
	edges[3].edges[0] = 0;
	edges[3].edges[1] = 5;
	edges[3].elem = 2;
	edges[4].edges[0] = 1;
	edges[4].edges[1] = 2;
	edges[4].elem = 1;
	edges[5].edges[0] = 2;
	edges[5].edges[1] = 4;
	edges[5].elem = 4;
	edges[6].edges[0] = 4;
	edges[6].edges[1] = 4;
	edges[6].elem = 4;
	edges[7].edges[0] = 4;
	edges[7].edges[1] = 5;
	edges[7].elem = 3;  // 그래프 초기화

	while (1) {
		scanf("%c", &com);
		if (com == 'a') {
			scanf("%d", &nodeNum); getchar();
			printNodeAndWeight(nodeNum - 1, nodes, edges);
		}
		if (com == 'm') {
			scanf("%d %d %d", &a, &b, &w); getchar();
			if (a <= b) {
				updateEdge(a - 1, b - 1, w, nodes, &edges, &edgeLen);
			}
			else {
				updateEdge(b - 1, a - 1, w, nodes, &edges, &edgeLen);
			}
		}
		if (com == 'q') {
			break;
		}
	} // 명령어에 맞는 명령 수행

	for (int i = 0; i < 6; i++) {
		clearAll((nodes + i)->next);
	}
	free(nodes);
	free(edges); // 메모리 해제
	return;
}

node* getNode(int elem) {
	node* newnode = (node*)malloc(sizeof(node));
	newnode->next = NULL;
	newnode->elem = elem;
	return newnode;
} 

int reverse(int k, node* v, edge* e) {
	int i = v->elem, u, w;
	u = (e + i)->edges[0];
	w = (e + i)->edges[1];
	if (k == u) {
		return w;
	}
	else {
		return u;
	}
} // 반대

void printNodeAndWeight(int k, node* nodes, edge* edges) { // 노드와 길이 출력
	int result;
	node* cur = (nodes + k)->next;
	if (k < 0 || k > 5) {
		printf("-1\n");
		return;
	}
	while (cur->next != NULL) {
		result = reverse(k, cur->next, edges);
		printf(" %d %d", (nodes + result)->elem, (edges + cur->next->elem)->elem);
		cur = cur->next;
	}
	printf("\n");
	return;
}

void updateEdge(int a, int b, int w, node* nodes, edge** copyNode, int* edge_len) { // 업데이트 Edge
	int index = 0;
	edge* copy = NULL, * del = NULL;
	if (a < 0 || a > 5 || b < 0 || b > 5) {
		printf("-1\n");
		return;
	}
	if (w != 0) {
		for (int i = 0; i < *edge_len; i++) {
			if ((*copyNode + i)->edges[0] == a && (*copyNode + i)->edges[1] == b) {
				(*copyNode + i)->elem = w;
				return;
			}
		}
		for (int i = 0; i < *edge_len; i++) {
			if ((*copyNode + i)->edges[0] > a)
				break;
			else if ((*copyNode + i)->edges[0] < a)
				index++;
			else {
				if ((*copyNode + i)->edges[1] > b)
					break;
				else
					index++;
			}
		}
		(*edge_len)++;
		copy = (edge*)malloc(sizeof(edge) * (*edge_len));
		for (int i = 0; i < index; i++) {
			(copy + i)->elem = (*copyNode + i)->elem;
			(copy + i)->edges[0] = (*copyNode + i)->edges[0];
			(copy + i)->edges[1] = (*copyNode + i)->edges[1];
		}
		(copy + index)->elem = w;
		(copy + index)->edges[0] = a;
		(copy + index)->edges[1] = b;
		for (int i = index + 1; i < *edge_len; i++) {
			(copy + i)->elem = (*copyNode + i - 1)->elem;
			(copy + i)->edges[0] = (*copyNode + i - 1)->edges[0];
			(copy + i)->edges[1] = (*copyNode + i - 1)->edges[1];
		}
		del = *copyNode;
		*copyNode = copy;
		free(del);
		updateList(index, a, b, w, nodes);
	}
	else {
		int flag = 0;
		for (int i = 0; i < *edge_len; i++) {
			if ((*copyNode + i)->edges[0] == a && (*copyNode + i)->edges[1] == b) {
				index = i;
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			return;
		}
		(*edge_len)--;
		copy = (edge*)malloc(sizeof(edge) * (*edge_len));
		for (int i = 0; i < index; i++) {
			(copy + i)->elem = (*copyNode + i)->elem;
			(copy + i)->edges[0] = (*copyNode + i)->edges[0];
			(copy + i)->edges[1] = (*copyNode + i)->edges[1];
		}
		for (int i = index; i < *edge_len; i++) {
			(copy + i)->elem = (*copyNode + i + 1)->elem;
			(copy + i)->edges[0] = (*copyNode + i + 1)->edges[0];
			(copy + i)->edges[1] = (*copyNode + i + 1)->edges[1];
		}
		del = *copyNode;
		*copyNode = copy;
		free(del);
		updateList(index, a, b, w, nodes);
	}
	return;
}

void updateList(int idx, int a, int b, int w, node* nodes) { // 업데이트 Nodes
	node* cur = NULL, * del = NULL;
	if (w != 0) {
		for (int i = 0; i < 6; i++) {
			cur = (nodes + i)->next;
			while (cur->next != NULL) {
				if (cur->next->elem >= idx)
					cur->next->elem++;
				cur = cur->next;
			}
		}
		cur = (nodes + a)->next;
		while (cur->next != NULL && cur->next->elem < idx)
			cur = cur->next;
		if (cur->next != NULL && cur->next->elem > idx) {
			node* newnode = getNode(idx);
			newnode->next = cur->next;
			cur->next = newnode;
		}
		else {
			cur->next = getNode(idx);
		}
		if (a != b) {
			cur = (nodes + b)->next;
			while (cur->next != NULL && cur->next->elem < idx)
				cur = cur->next;
			if (cur->next != NULL && cur->next->elem > idx) {
				node* newnode = getNode(idx);
				newnode->next = cur->next;
				cur->next = newnode;
			}
			else {
				cur->next = getNode(idx);
			}
		}
	}
	else {
		int flag = 0;
		for (int i = 0; i < 6; i++) {
			cur = (nodes + i)->next;
			while (cur->next != NULL) {
				if (cur->next->elem > idx)
					cur->next->elem--;
				cur = cur->next;
			}
		}
		cur = (nodes + a)->next;
		while (idx != cur->next->elem) {
			cur = cur->next;
			if (cur->next->next == NULL) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			del = cur->next;
			cur->next = NULL;
			free(del);
			flag = 0;
		}
		else {
			del = cur->next;
			cur->next = del->next;
			del->next = NULL;
			free(del);
		}
		if (a != b) {
			cur = (nodes + b)->next;
			while (idx != cur->next->elem) {
				cur = cur->next;
				if (cur->next->next == NULL) {
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				del = cur->next;
				cur->next = NULL;
				free(del);
				flag = 0;
			}
			else {
				del = cur->next;
				cur->next = del->next;
				del->next = NULL;
				free(del);
			}
		}
	}
	return;
}

void clearAll(node* p) { // 메모리 해제용 함수
	node* tmp = p->next;
	while (tmp != NULL) {
		free(p);
		p = tmp;
		tmp = tmp->next;
	}
	free(p);
	return;
}
