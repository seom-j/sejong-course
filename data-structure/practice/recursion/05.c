#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

void hanoi(int, char, char, char);

int main(void) {
	int n;
	scanf("%d", &n);
	hanoi(n, 'A', 'B', 'C');
}

void hanoi(int n, char from, char aux, char to){
	if (n == 1) {
		printf("%c %c\n", from, to);
	}

	else {
		hanoi(n - 1, from, to, aux);
		printf("%c %c\n", from, to);
		hanoi(n - 1, aux, from, to);
	}
}
