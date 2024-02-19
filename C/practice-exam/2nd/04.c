#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct student {
	char id[6];
	int f, s;
	double sa;
	char pof;
};

typedef struct student(com);

int main(void) {
	int n, pcnt = 0;
	scanf("%d", &n);

	com* c, tmp;
	c = (com*)malloc(sizeof(com) * n);
	if (c == NULL) return -1;
	for (com* pc = c; pc < c + n; pc++) {
		scanf("%s %d %d", &pc->id, &pc->f, &pc->s);
		pc->sa = pc->f * 0.4 + pc->s * 0.6;
	}

	for (com* qc = c; qc < c + n-1; qc++) {
		for (com* pc = c; pc < c + n-1; pc++) {
			if (pc->sa < (pc + 1)->sa) {
				tmp = *pc;
				*pc = *(pc + 1);
				*(pc + 1) = tmp;
			}
		}
	} // 우선 평균순으로 정렬
	for (com* pc = c; pc < c + n; pc++) {
		if (pc < c + (int)(n * 0.6)) {
			pc->pof = 'p';
			pcnt += 1;
		}
		if ((c + (int)(n * 0.6) - 1)->sa == pc->sa) {
			pc->pof = 'p';
			pcnt += 1;
		} //동점자
	}

	for (com* qc = c; qc < c + n - 1; qc++) {
		for (com* pc = c; pc < c + n - 1; pc++) {
			if (pc->s < (pc + 1)->s) {
				tmp = *pc;
				*pc = *(pc + 1);
				*(pc + 1) = tmp;
			}
		}
	} // 2차 인증순 정렬
	for (com* pc = c; pc < c + n; pc++) {
		if (pcnt > (int)(n * 0.8) 
			&& (c + (int)(n * 0.8)-1)->s != pc->s) break; //동점자 없고 80프로 이상이면 종료
		if ( pcnt < (c + (int)(n * 0.8)) && pc->pof!='p') {
			pc->pof = 'p';
			pcnt+=1;
		} // p인 사람의 수가 80프로 이내에 들면서 p가 아닌 사람
		if ((c + (int)(n * 0.8)-1)->s == pc->s) {
			pc->pof = 'p';
			pcnt += 1;
		} //동점자
	}

	for (com* qc = c; qc < c + n - 1; qc++) {
		for (com* pc = c; pc < c + n - 1; pc++) {
			if (strcmp(pc->id,(pc+1)->id)>0) {
				tmp = *pc;
				*pc = *(pc + 1);
				*(pc + 1) = tmp;
			}
		}
	} // 학번순 정렬

	for (com* pc = c; pc < c + n; pc++) {
		if (pc->pof == 'p') printf("%s\n", pc->id);
	} // p이면 출력

	if (c != NULL) {
		free(c);
		c = 0;
	}
}
