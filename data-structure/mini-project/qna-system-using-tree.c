#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)


typedef struct node {
	char data[100];
	struct node* left, * right, *par;
}node;

node* getnode();
void putnode(node*); // 노드 생성 및 삭제용 함수
void free_tree(node* v); // 트리 해제용 함수

node* buildDecisionTree();
node* makeExternalNode(node*);
node* makeInternalNode(node*); // 상담 설계용 함수

void runDecisionTree(node*);
void processNode(node*); // 상담 실행용 함수

node* root;
int depth(node*); // 트리의 깊이 구하기용 함수


void main() {
	node* v = buildDecisionTree();
	root = v;
	printf("Tree complete. Now Running!!\n");
	for (int i = 1; i <= 3; i++) {
		runDecisionTree(v);
	}

	free_tree(v);
	return;
}

node* getnode() {
	return (node*)calloc(1, sizeof(node));
}

void putnode(node* p) {
	free(p);
}

node* buildDecisionTree() {
	printf("***Let's build a dichotomous QA system\n");
	return makeInternalNode(0);
}

node* makeExternalNode(node* par) {
	node* v = getnode();
	printf("Enter decision:");
	char D[100] = { NULL };
	strcpy(v->data, gets(D));
	v->par = par;
	v->left = 0;
	v->right = 0;
	return v;
}

node* makeInternalNode(node* par) {
	node* v = getnode();
	printf("Enter question:");
	char Q[100] = { NULL };
	char YN[100] = { NULL };
	strcpy(v->data, gets(Q));
	v->par = par;

	printf("Question if yes to '%s' ?", Q);
	if (strncmp(gets(YN), "yes", 3) == 0) {
		if (depth(v) >= 5) { // 질문의 개수가 6개 이상이 되지 않도록 예외처리
			printf("You almost make 5 continuous questions!\n"); 
			v->left = makeExternalNode(v);
		}
		else v->left = makeInternalNode(v);
	}
	else {
		if (depth(v) <= 2) { // 질문의 개수가 2개 이하로 되지 않도록 예외처리
			printf("You have to make at least 3 continuous questions!\n");
			v->left = makeInternalNode(v);
		}
		else v->left = makeExternalNode(v);
	}

	printf("Question if no to '%s' ?", Q);
	if (strncmp(gets(YN), "yes", 3) == 0) {
		if (depth(v) >= 5) {
			printf("You almost make 5 continuous questions!\n");
			v->right = makeExternalNode(v);
		}
		else v->right = makeInternalNode(v);
	}
	else {
		if (depth(v) <= 2) {
			printf("You have to make at least 3 continuous questions!\n");
			v->right = makeInternalNode(v);
		}
		else v->right = makeExternalNode(v);
	}
	return v;
}

void runDecisionTree(node* v) {
	printf("***Please answer questions\n");
	processNode(v);
}

void processNode(node* v) {
	printf("%s\n", v->data);
	char YN[100] = { NULL };
	if (v->left != 0 && v->right != 0) {
		if (strncmp(gets(YN), "yes", 3) == 0) processNode(v->left);
		else processNode(v->right);
	}
}

int depth(node* v) {
	if (root == v) return 0;
	else return 1 + depth(v->par);
}

void free_tree(node* v) {
	if (v != NULL) {
		free_tree(v->left);
		free_tree(v->right);
		putnode(v);
	}
	return;
}
