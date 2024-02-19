#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

void update(int a, int b, int w, int arr[][7]);

int main(){
	int arr[7][7];
	int a, b, w;
	int nodeNum;
	char com;

	for (int i = 1; i < 7; i++){
		for (int j = 1; j < 7; j++)
			arr[i][j] = -1;
	}
	arr[1][2] = 1;
	arr[1][3] = 1;
	arr[1][4] = 1;
	arr[1][6] = 2;
	arr[2][1] = 1;
	arr[2][3] = 1;
	arr[3][1] = 1;
	arr[3][2] = 1;
	arr[3][5] = 4;
	arr[4][1] = 1;
	arr[5][3] = 4;
	arr[5][5] = 4;
	arr[5][6] = 3;
	arr[6][1] = 2;
	arr[6][5] = 3; // 초기화

	while (1){
		scanf("%c", &com);
		if (com == 'a') {
			scanf("%d", &nodeNum); getchar();
			if (nodeNum < 1 || nodeNum > 6) {
				printf("-1\n");
				continue;
			}
			for (int i = 1; i < 7; i++) {
				if (arr[nodeNum][i] != -1)
					printf(" %d %d", i, arr[nodeNum][i]);
			}
			printf("\n");
		}
		if (com == 'm') {
			scanf("%d %d %d", &a, &b, &w);
			update(a, b, w, arr);
		}
		if (com == 'q') {
			break;
		}
	} // 명령어별 명령 수행

	return 0;
}

void update(int a, int b, int w, int arr[][7]) {
	if (a < 1 || a > 6 || b < 1 || b > 6) {
		printf("-1\n");
		return;
	}
	if (w == 0) {
		arr[a][b] = -1;
		arr[b][a] = -1;
	}
	else {
		arr[a][b] = w;
		arr[b][a] = w;
	}
	return;
}
