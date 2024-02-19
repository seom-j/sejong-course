#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main(void) {
	FILE* fp = NULL;
	int d, cnt=0, sum=0;
	double avg;
	fp = fopen("data.txt", "w");
	if (fp == NULL) {
		printf("File open error");
		return 0;
	}
	scanf("%d", &d);
	while (!feof(stdin)) {
		fprintf(fp, "%d\n", d);
		scanf("%d", &d);
	}
	fclose(fp);

	fp = fopen("data.txt", "r");
	if (fp == NULL) {
		printf("File open error");
		return 0;
	}

	fscanf(fp, "%d", &d);
	while (!feof(fp)) {
		cnt+=1;
		sum += d;
		fscanf(fp, "%d", &d);
	}
	avg = (double) sum / cnt;
	fclose(fp);
	printf("%d\n%d\n%.2f", cnt, sum, avg);

	return 0;
}
