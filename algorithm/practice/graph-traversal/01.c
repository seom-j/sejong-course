#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

typedef struct node{
	int adjnode;
	struct node *next;
}node;

typedef struct vertex{
	int visit;
	struct node *head;
}vertex;

void update_adjlist(vertex *arr, int k);
void DFS(int s, vertex *arr);
void freeAll(vertex *arr, int n);
//함수 원형 선언

int main(){
	vertex arr[101];
	int n, m, s;
	int a, b;
	scanf("%d %d %d", &n, &m, &s);
	for (int i = 1; i <= n; i++)
	{
		arr[i].visit = 0;
		arr[i].head = (node *)malloc(sizeof(node));
		arr[i].head->next = NULL;
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &a, &b);
		update_adjlist(arr + a, b);
		update_adjlist(arr + b, a);
	}
	DFS(s, arr);
	freeAll(arr, n);
	return 0;
}


void update_adjlist(vertex *arr, int k){
	node *cur, *prev, *newnode;
	cur = arr->head->next;
	prev = arr->head;

	while (cur != NULL)	{
		if (cur->adjnode > k)
			break;
		cur = cur->next;
		prev = prev->next;
	}
	newnode = (node *)malloc(sizeof(node));
	newnode->adjnode = k;
	newnode->next = cur;
	prev->next = newnode;
	return;
}

void DFS(int s, vertex *arr){
	node *cur = (arr + s)->head->next;
	(arr + s)->visit = 1;
	printf("%d\n", s);
	while (cur != NULL)
	{
		if ((arr + cur->adjnode)->visit == 0)
		{
			DFS(cur->adjnode, arr);
		}
		cur = cur->next;
	}
	return;
}

void freeAll(vertex *arr, int n){
	node *cur, *prev;
	for (int i = 1; i <= n; i++)
	{
		cur = (arr + i)->head->next;
		prev = (arr + i)->head;
		while (cur != NULL)
		{
			free(prev);
			prev = cur;
			cur = cur->next;
		}
		free(prev);
	}
	return;
}
