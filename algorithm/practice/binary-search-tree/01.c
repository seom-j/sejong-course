#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

typedef struct node {
	int key;
	struct node* parent;
	struct node* lChild;
	struct node* rChild;
}node;

node* tree;

node* getNode(node* P);
int findElement(int k);
void insertItem(int k);
node* treeSearch(node* w, int k);
void treeSearchPrint(int k);
void removeElement(int k);
int  isExternal(node* w);
int isInternal(node* w);
node* inOrderSucc(node* w);
void reduceExternal(node* z);
void preorder(node* w);
void printTree(); // 함수 원형 선언

void main() {
	tree = getNode(NULL);

	int key;
	char com;
	while (1) {
		scanf("%c", &com);
		getchar();
		if (com == 'i') {
			scanf("%d", &key);
			getchar();
			insertItem(key);
		}
		else if (com == 'd') {
			scanf("%d", &key);
			getchar();
			removeElement(key);
		}
		else if (com == 's') {
			scanf("%d", &key);
			getchar();
			treeSearchPrint(key);
		}
		else if (com == 'p') {
			printTree();
		}
		else if (com == 'q') {
			break;
		}
	}
}

node* getNode(node* P) {
	node* newnode = (node*)calloc(1, sizeof(node));
	newnode->parent = P;
	// calloc으로 초기화 후 parent 연결
	return newnode;
} // 노드 생성

int isInternal(node* w) {
	if (w->lChild != NULL || w->rChild != NULL) {
		return 1;
	}
	return 0;
} // 내부노드 여부 판단

int  isExternal(node* w) {
	if (w->lChild == NULL && w->rChild == NULL) {
		return 1;
	}
	return 0;
} // 외부노드 여부 판단

int findElement(int k) {
	return k;
} 

node* treeSearch(node* w, int k) {
	if (isExternal(w)) {
		return w;
	} // 외부노드일 경우 키값을 붙일 노드 위치 반환
	if (w->key == k) {
		return w;
	} // 해당 키가 이미 있을 경우 그 노드 위치 반환 (삽입 X)
	else if (w->key > k) {
		return treeSearch(w->lChild, k);
	}
	else {
		return treeSearch(w->rChild, k);
	}
}

void insertItem(int k) {
	if (tree == NULL) {
		tree = getNode(NULL);
		tree->key = k;
		tree->lChild = getNode(tree);
		tree->rChild = getNode(tree);
	} // 루트노드인 경우
	else {
		node* tmp = treeSearch(tree, k);
		if (isInternal(tmp)) {
			return;
		}
		else {
			tmp->key = k;
			tmp->lChild = getNode(tmp);
			tmp->rChild = getNode(tmp);
		}
	}
}

void treeSearchPrint(int k) {
	node* tmp = treeSearch(tree, k);
	if (isExternal(tmp)) {
		printf("X\n");
	}
	else {
		printf("%d\n", tmp->key);
	}
} // 존재 여부를 판단하여 X 출력 혹은 key 출력

node* inOrderSucc(node* w) {
	node* z = w;
	while (isInternal(z->lChild)) {
		z = z->lChild;
	}
	return z;
}

void reduceExternal(node* z) {
	node* w = z->parent;
	node* zs = w->lChild == z ? w->rChild : w->lChild;
	if (w == tree) {
		tree = zs;
		zs->parent = NULL;
	}
	else {
		node* g = w->parent;
		zs->parent = g;
		if (g->lChild == w) {
			g->lChild = zs;
		}
		else {
			g->rChild = zs;
		}
	}
} // 자식, 부모노드 모두 제거 후 자식의 현제와 새 부모노드 연결

void removeElement(int k) {
	node* tmp = treeSearch(tree, k);
	if (isExternal(tmp)) {
		printf("X\n");
		return;
	}
	else {
		printf("%d\n", tmp->key);
		node* z = tmp->lChild;
		if (isInternal(z)) {
			z = tmp->rChild;
		}
		if (!isExternal(z)) {
			node* y = inOrderSucc(z);
			node* r = y->rChild;
			tmp->key = y->key;
			reduceExternal(y->lChild);
		}
		else {
			reduceExternal(z);
		}
	}
}

void preorder(node* w) {
	if (isInternal(w)) {
		printf(" %d", w->key);
		preorder(w->lChild);
		preorder(w->rChild);
	}
}

void printTree() {
	preorder(tree);
	printf("\n");
}
