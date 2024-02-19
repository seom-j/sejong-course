#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct st {
	char* str; // 문자열 저장
	int cnt1; // 자음 수 저장
	int cnt2; // 모음 수 저장
	int num; // 숫자 저장
	int result1; // 곱셈결과 저장
	int result2; // 곱셈결과 저장
};

int main(void) {
	int n, ma, mi;
	scanf("%d", &n);
	getchar(); // n 임력 

	struct st* p, ptmp;
	p = (struct st*)malloc(n * sizeof(struct st));
	if (p == NULL) return -1; // 구조체 동적할당 & 성공여부

	char tmp[101]; // tmp 선언

	for (struct st* pp = p; pp < p + n; pp++) { 
		scanf("%s", tmp);
		pp->str = (char*)malloc(strlen(tmp) + 1);
		if (pp->str == NULL) return -1; // 문자열 동적할당 & 성공여부
		strcpy(pp->str, tmp);

		pp->cnt1 = 0;
		pp->cnt2 = 0;
		for (char* sp = pp->str; sp < pp->str + strlen(pp->str); sp++) {
			if (*sp == 'a' || *sp == 'e' || *sp == 'i' || *sp == 'o' || *sp == 'u'
				|| *sp == 'A' || *sp == 'E' || *sp == 'I' || *sp == 'O' || *sp == 'U')
				pp->cnt2 += 1; // 모음수
			else if ((*sp >= 'a' && *sp <= 'z') || (*sp >= 'A' && *sp <= 'Z'))
				pp->cnt1 += 1; // 자음수
			else if (*sp >= '0' && *sp <= '9')
				pp->num = *sp - '0'; // 숫자
		}
		pp->result1 = pp->num * pp->cnt1;
		pp->result2 = pp->num * pp->cnt2;
		if (pp->result1 < pp->result2) {
			pp->result2 = pp->num * pp->cnt1;
			pp->result1 = pp->num * pp->cnt2;
		} // 대입
	}
	
	for (struct st* qq = p; qq < p + n-1; qq++) {
		for (struct st* pp = p; pp < p + n - 1; pp++) {
			ma = pp->result1;
			mi = pp->result2;
			if (ma < mi) {
				ma = pp->result2;
				mi = pp->result1;
			}
			if ((pp->result1 < (pp + 1)->result1)
				||( pp->result1 == (pp + 1)->result1)&& (pp->result2 < (pp + 1)->result2)) {
				ptmp = *pp;
				*pp = *(pp + 1);
				*(pp + 1) = ptmp;
			}
		}
	} // 판단, 정렬

	for (struct st* pp = p; pp < p + n ; pp++) printf("%s\n", pp->str); // 출력
	

	for (struct st* pp = p; pp < p + n; pp++) {
		if (pp->str != NULL) {
			free(pp->str);
			pp->str = NULL;
		}
	}
	if (p != NULL) {
		free(p);
		p = NULL;
	} // 해제
	
	return 0;
}
