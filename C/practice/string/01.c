#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int main() {
	char str[20] = { NULL };
	scanf("%s", str);
	for (int i = 0; str[i] != 0; i++) if (str[i] >= 'a' && str[i] <= 'z') printf("%c", str[i]);
}
