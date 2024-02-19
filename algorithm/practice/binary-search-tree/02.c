#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

typedef struct node {
	int key;
	int height;
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
node* inOrderSuccRight(node* w);
node* inOrderSuccLeft(node* w);
node* reduceExternal(node* z);
void preorder(node* w);
void printTree(); // 함수 원형 선언

int Max(int a, int b);
int Abs(int a);
int UpdateHeight(node* w);
int isBalanced(node* w);
node* restructure(node* w);
void searchAndFixAfterInsertion(node* w);
node* searchAndFixAfterRemoval(node* w); // 


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
			searchAndFixAfterInsertion(tmp);
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

node* inOrderSuccRight(node* w) {
	node* z = w->rChild;
	if (isExternal(z)) {
		return NULL;
	}
	while (isInternal(z->lChild)) {
		z = z->lChild;
	}
	return z;
}
node* inOrderSuccLeft(node* w) {
	node* z = w->lChild;
	if (isExternal(z)) {
		return NULL;
	}
	while (isInternal(z->rChild)) {
		z = z->rChild;
	}
	return z;
}


node* reduceExternal(node* z) {
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
	return zs;
} // 자식, 부모노드 모두 제거 후 자식의 현제와 새 부모노드 연결

void removeElement(int k) {
	if (tree == NULL) {
		printf("X\n");
		return;
	}
	node* w = treeSearch(tree, k);
	node* zs;
	if (isExternal(w)) {
		printf("X\n");
	}
	else {
		printf("%d\n", k);
		node* z = w->lChild;
		if (!isExternal(z)) {
			z = w->rChild;
		}
		if (!isInternal(z)) {
			zs = reduceExternal(z);
		}
		else {
			node* p = inOrderSuccRight(w);
			if (p != NULL) {
				w->key = p->key;
				z = p->lChild;
				zs = reduceExternal(z);
			}
			else {
				p = inOrderSuccLeft(w);
				w->key = p->key;
				z = p->rChild;
				zs = reduceExternal(z);
			}
		}
		searchAndFixAfterRemoval(zs->parent);
	}
}

void preorder(node* w) {
	if (w != NULL) {
		if (isInternal(w)) {
			printf(" %d", w->key);
			preorder(w->lChild);
			preorder(w->rChild);
		}
	}
}

void printTree() {
	preorder(tree);
	printf("\n");
}

int Max(int a, int b) {
	return a > b ? a : b;
}
int Abs(int a) {
	return a > 0 ? a : (-1) * a;
}

int isBalanced(node* w) {
	if (w == NULL) {
		return 1;
	}
	node* l = w->lChild;
	node* r = w->rChild;
	if (Abs(l->height - r->height) < 2) {
		return 1;
	}
	return 0;
}

node* restructure(node* x) {
	node* y = x->parent, * z = y->parent;
	node* a, * b, * c;
	node* tmp1, * tmp2, * tmp3, * tmp4;
	if (z->key > y->key && y->key > x->key) {
		b = y, a = x, c = z;
		tmp1 = x->lChild, tmp2 = x->rChild, tmp3 = y->rChild, tmp4 = z->rChild;
	} // z>y>x : LL
	else if (z->key > x->key && x->key > y->key) {
		b = x, a = y, c = z;
		tmp1 = y->lChild, tmp2 = x->lChild, tmp3 = x->rChild, tmp4 = z->rChild;
	} // z>x>y : LR
	else if (x->key > y->key && y->key > z->key) {
		b = y, a = z, c = x;
		tmp1 = z->lChild, tmp2 = y->lChild, tmp3 = x->lChild, tmp4 = x->rChild;
	} // x>y>z : RR
	else {
		b = x, a = z, c = y;
		tmp1 = z->lChild, tmp2 = x->lChild, tmp3 = x->rChild, tmp4 = y->rChild;
	} // y>x>z : RL

	if (z == tree) {
		tree = b;
		b->parent = NULL;
	}
	else if (z->parent->lChild == z) {
		z->parent->lChild = b;
		b->parent = z->parent;
	}
	else {
		z->parent->rChild = b;
		b->parent = z->parent;
	}

	a->lChild = tmp1;
	tmp1->parent = a;
	a->rChild = tmp2;
	tmp2->parent = a;
	a->height = Max(tmp1->height, tmp2->height) + 1;

	c->lChild = tmp3;
	tmp3->parent = c;
	c->rChild = tmp4;
	tmp4->parent = c;
	c->height = Max(tmp3->height, tmp4->height) + 1;

	b->lChild = a;
	a->parent = b;
	b->rChild = c;
	c->parent = b;
	b->height = Max(a->height, c->height) + 1;

	return b;
}


void searchAndFixAfterInsertion(node* w) {
	node* x, * y, * z = w;
	while (UpdateHeight(z)) {
		if (z == NULL) {
			return;
		}
		z = z->parent;
	}

	if (z->lChild->height > z->rChild->height) {
		y = z->lChild;
	}
	else {
		y = z->rChild;
	}
	if (y->lChild->height > y->rChild->height) {
		x = y->lChild;
	}
	else if (y->lChild->height < y->rChild->height) {
		x = y->rChild;
	}
	else {
		if (y == z->lChild) {
			x = y->lChild;
		}
		else {
			x = y->rChild;
		}
	}
	restructure(x);
}

node* searchAndFixAfterRemoval(node* w) {
	node* x, * y, * z = w;
	while (UpdateHeight(z)) {
		if (z == NULL) {
			return;
		}
		z = z->parent;
	}
	if (z->lChild->height > z->rChild->height) {
		y = z->lChild;
	}
	else {
		y = z->rChild;
	}
	if (y->lChild->height > y->rChild->height) {
		x = y->lChild;
	}
	else if (y->lChild->height < y->rChild->height) {
		x = y->rChild;
	}
	else {
		if (y == z->lChild) {
			x = y->lChild;
		}
		else {
			x = y->rChild;
		}
	}
	node* p = restructure(x);
	searchAndFixAfterRemoval(p->parent);
}

int UpdateHeight(node* w) {
	if (w == NULL) {
		return 1;
	}
	node* l = w->lChild;
	node* r = w->rChild;
	w->height = Max(l->height, r->height) + 1;
	if (Abs(l->height - r->height) < 2) {
		return 1;
	}
	return 0;
}
