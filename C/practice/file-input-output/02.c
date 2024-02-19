#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main(void) {
	int d = 0, cnt = 0, sum = 0;
	double avg = 0;

	FILE* fp = fopen("data.txt", "r");
	if (fp == NULL) {
		printf("Couldn't open file");
		return -1;
	}

	while (!feof(fp)) {
		fscanf(stdin, "%d", &d);
		sum += d;
		cnt += 1;
	}
	avg = sum / (double)cnt;
	fclose(fp);

	fp = fopen("data.txt", "w");
	if (fp == NULL) {
		printf("Couldn't open file");
		return -1;
	}

	fprintf(stdout, "%d\n%d\n%.2lf", cnt, sum, avg);

	fclose(fp);
}

