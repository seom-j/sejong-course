#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int main(void) {
	char str1[100] = { NULL }, str2[100] = { NULL };
	gets(str1);
	gets(str2);
	int f , cnt = 0;
	for (int i = 0; str1[i] != 0; i++) {
		f = 0;
		if ((i == 0 || str1[i - 1] == ' ' || str1[i - 1] == '.') && str1[i] == str2[0]) {
			for (int j = 0; str2[j]!=0; j++) {
				if (str1[i + j] != str2[j]) f = 1;
			}
			if (f == 0 && (str1[i+strlen(str2)]==' '|| str1[i + strlen(str2)] == 0|| str1[i + strlen(str2)] == '.')) cnt += 1;
		}
	}
	printf("%d", cnt);
}
