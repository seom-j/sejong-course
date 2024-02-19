#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int main() {
	char str[101] = { NULL }, * ps = str;
	char w[51][101] = { NULL }, tmp[101] = { NULL };

	gets(str);
	int cnt = strlen(str), n, cntw=0;
	scanf("%d", &n);
	
	for (int i = 0; i < cnt + 1; i++) {
		if (str[i] == ' ' || str[i] == 0) {
			str[i] = 0;
			strcpy(w[cntw++], ps);
			ps = &str[i + 1];
		}
	}

	printf("%s\n", w[n-1]);

	for (int i = 0; i < cntw - 1; i++) {
		for (int j = 0; j < cntw - 1; j++) {
			if (strcmp(w[j], w[j+1]) > 0) {

				for (int k = 0; w[j][k] != 0; k++) tmp[k] = w[j][k];
				for (int k = 0; w[j][k] != 0; k++) w[j][k] = 0;

				for (int k = 0; w[j + 1][k] != 0; k++) w[j][k] = w[j + 1][k];
				for (int k = 0; w[j + 1][k] != 0; k++) w[j + 1][k] = 0;

				for (int k = 0; tmp[k] != 0; k++) w[j + 1][k] = tmp[k];
				for (int k = 0; tmp[k] != 0; k++) tmp[k] = 0;
			}
		}
	}


	printf("%s", w[0]);

}
