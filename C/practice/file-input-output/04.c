#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main(void) {
	char fn1[21] = { '\0' }, fn2[21] = { '\0' }, c;
	gets(fn1);
	FILE* fp1 = fopen(fn1, "a");
	if (fp1 == NULL) {
		printf("Couldn't open file");
		return -1;
	}
	gets(fn2);
	FILE* fp2 = fopen(fn2, "r");
	if (fp2 == NULL) {
		printf("Couldn't open file");
		return -1;
	}

	fputc(fgetc(fp2), fp1);
	while (!feof(fp2)) {
		fputc(fgetc(fp2), fp1);
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}
