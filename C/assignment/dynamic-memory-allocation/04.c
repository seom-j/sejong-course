#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct t {
	char name[21];
	int pay;
	char inout;
	char start[9];
	char citynamee[21];
};
struct c {
	char* cityname;
	int c_n;
};

int main(void) {
	int n, s_cnt = 0;
	scanf("%d", &n);
	getchar();

	struct c* cp;
	cp = (struct c*)malloc(n * sizeof(struct c));//
	if (cp == NULL) {
		printf("Not Enough Memory.");
		return -1;
	} // city 동적할당

	char tmp[21];
	for (struct c* pp = cp; pp < cp + n; pp++) {
		scanf("%s", tmp);
		getchar();
		pp->cityname = (char*)malloc(strlen(tmp) + 1);//
		if (pp->cityname == NULL) {
			printf("Not Enough Memory.");
			return -1;
		} // cityname 동적할당
		strcpy(pp->cityname, tmp);
	} // city 이름 저장
	for (struct c* pp = cp; pp < cp + n; pp++) {
		scanf("%d", &pp->c_n);
		s_cnt += pp->c_n;
		getchar();
	} // city 개수 저장


	struct t** tp;
	int i = 0;
	tp = (struct t**)malloc(n * sizeof(struct t*));//
	if (tp == NULL) {
		printf("Not Enough Memory.");
		return -1;
	}

	for (struct c* pp = cp; pp < cp + n; pp++) {
		tp[i] = (struct t*)malloc(pp->c_n * sizeof(struct t));//
		if (tp[i] == NULL) {
			printf("Not Enough Memory.");
			return -1;
		} // 이차원 구조체 동적할당
		for (struct t* tpp = tp[i]; tpp < tp[i] + pp->c_n; tpp++) {
			strcpy(tpp->citynamee, pp->cityname);
			scanf("%s %d %c %s", &tpp->name, &tpp->pay, &tpp->inout, &tpp->start);
		}
		i += 1;
	} // trip 저장


	int b_pay = tp[0]->pay;
	struct t tb_pay = *tp[0];

	i = 0;
	for (struct c* pp = cp; pp < cp + n; pp++) {
		for (struct t* tpp = tp[i]; tpp < tp[i] + pp->c_n; tpp++) {
			if (tpp->pay > b_pay) {
				b_pay = tpp->pay;
				tb_pay = *tpp;
			}
			if (tpp->pay == b_pay) {
				if (strcmp(tpp->start, tb_pay.start) < 0) {
					tb_pay = *tpp;
				}
			}
		}
		i++;
	} // 제일 비싼 곳 찾기


	printf("%s %s %d %s %c\n", tb_pay.citynamee, tb_pay.name, tb_pay.pay, tb_pay.start, tb_pay.inout);
	//출력

	for (struct c* pp = cp; pp < cp + n; pp++) {
		if (cp->cityname != NULL) {
			free(cp->cityname);
			cp->cityname = NULL;
		}
	}
	if (cp != NULL) {
		free(cp);
		cp = NULL;
	}
	for (int i = 0; i < 3; i++) {
		if (tp[i] != NULL) {
			free(tp[i]);
			tp[i] = NULL;
		}
	}
	if (tp != NULL) {
		free(tp);
		tp = NULL;
	}
	i = 0;

	return 0;
}
