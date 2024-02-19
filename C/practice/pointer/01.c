#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)


int main(void) {
	int x, y, z;
	int* px, * py, * pz, * tmp;
	scanf("%d %d %d", &x, &y, &z);
	px = &x;
	py = &y;
	pz = &z;
	tmp = pz;
	pz = py;
	py = px;
	px = tmp;
	printf("%d %d %d", *px, *py, *pz);
}
