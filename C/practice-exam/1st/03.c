#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

void StringAdd(char arr[], char ch, int index);
int Convetor(char x);

int main() {
	char num[18] = { NULL }, p = '+', c = '*';
	scanf("%s", num);

	for (int i = 0; num[i] != 0; i++) {
		if (Convetor(num[i]) % 2 == 0 && Convetor(num[i + 1]) % 2 == 0 && num[i + 1] != 0) {
			StringAdd(num, c, i + 1);
			i += 1;
		}
		else if ( Convetor(num[i]) % 2 == 1 && Convetor(num[i + 1]) % 2 == 1 && num[i + 1] != 0) {
			StringAdd(num, p, i + 1);
			i += 1;
		}
	}
	printf("%s", num);
}

void StringAdd(char arr[], char ch, int index) {
	int cnt = strlen(arr) + 1;
	for (cnt; cnt > index; cnt--) {
		arr[cnt] = arr[cnt - 1];
	}
	arr[index] = ch;
}

int Convetor(char x) {
	return (x - '0');
}
