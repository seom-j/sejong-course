#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

struct st {
	char name[10]; //학생이름
	char book[5][20]; //인증시험 본 책 이름 (예) History Politics
	int score[5]; //위 책에 대한 인증시험 점수 (예) 60 40
	int cnt, pcnt; //인증시험 본 책의 권수, 통과한 책의 권수
};

int main(void) {
	struct st c[100];
	int n, cn = 0, ccnt;
	char book[20];
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		c[i].pcnt = 0;

		scanf("%s", &c[i].name);

		for (int j = 0;; j++) {
			scanf("%s", book);
			if (book[0] == '0') break;
			strcpy(&c[i].book[j], book);
			scanf("%d", &c[i].score[j]);
			if (c[i].score[j] >= 50) c[i].pcnt += 20;
		}
	}

	for (int i = 0; i < n; i++) printf("%s %d%%\n", c[i].name, c[i].pcnt);
}
