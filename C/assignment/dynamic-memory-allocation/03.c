#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct student {
	char* name; // 학생 이름
	char id[5]; // 학생 학번
	int numSubject; // 과목 개수
	struct subject* psub; // 과목 구조체 포인터
	double avg; // 모든 과목의 평균 점수
};
struct subject {
	char* name; // 과목 이름
	double score; // 과목 점수
};


int main(void) {
	int n;
	scanf("%d", &n);
	getchar();// n 입력

	struct student* p;
	p = (struct student*)malloc(n * sizeof(struct student));
	if (p == NULL) return -1; // 구조체 동적 할당

	char str[101];
	for (struct student* pp = p; pp < p + n; pp++) {
		gets(str);

		int strcnt = strlen(str), wid = 0;
		char wo[51][101] = { NULL }, * pstr = str;
		for (char* p = str; p < str + strcnt + 1; p++) {
			if (*p == 0 || *p == ' ') {
				*p = 0;
				strcpy(wo[wid++], pstr);
				pstr = p + 1;
			}
		} // 단어 자르기

		pp->name = (char*)malloc(strlen(wo[0]) + 1);
		if (pp->name == NULL) return -1;
		strcpy(pp->name, wo[0]); //이름

		strcpy(pp->id, wo[1]); // 학번

		pp->numSubject = (wid - 2) / 2; // 과목 개수

		pp->psub = (struct subject*)malloc(pp->numSubject * sizeof(struct subject));
		if (pp->psub == NULL) return -1; // 과목구조체 동적할당

		int spidx = 2;
		double s_sum = 0;
		for (struct subject* ps = pp->psub; ps < pp->psub + pp->numSubject; ps++) {
			ps->name = (char*)malloc(strlen(wo[spidx]) + 1);
			if (ps->name == NULL) return -1; // 이름 동적할당

			strcpy(ps->name, wo[spidx]); // 이름 저장

			ps->score = (double)atoi(wo[spidx + 1]);

			s_sum += ps->score;
			spidx += 2;
		} // 과목 구조체 포인터
		pp->avg = s_sum / pp->numSubject; // 평균점수

		for (int i = 0; i < pp->numSubject; i++) {
			for (int j = 0; j < strlen(wo[i]); j++) wo[i][j] = 0;
		}
		for (char* strp = str; strp < str + strlen(str); strp++) *strp = 0;
		//비우기
	}

	struct student tmp;
	struct subject stmp;
	for (struct student* qq = p; qq < p + n - 1; qq++) {
		for (struct student* pp = p; pp < p + n - 1; pp++) {
			if (pp->avg < (pp + 1)->avg ||
				pp->avg == (pp + 1)->avg && strcmp(pp->id, (pp + 1)->id)>0) {
				tmp = *pp;
				*pp = *(pp + 1);
				*(pp + 1) = tmp;
			}
		} // 평균별, 학번별 정렬
	}

	for (struct student* qq = p; qq < p + n; qq++) {
		for (struct subject* xx = qq->psub; xx < qq->psub + qq->numSubject - 1; xx++) {
			for (struct subject* yy = qq->psub; yy < qq->psub + qq->numSubject - 1; yy++) {
				if (yy->score < (yy + 1)->score) {
					stmp = *yy;
					*yy = *(yy + 1);
					*(yy + 1) = stmp;
				}
			}
		}
	} // 학생별 과목 점수별 정렬

	int k;
	scanf("%d", &k);
	struct student k_s = *(p + k - 1);
	printf("%s %s %.2lf %s %.2lf", k_s.name, k_s.id, k_s.avg, k_s.psub->name, k_s.psub->score);

	return 0;

	
	for (struct student* pp = p; pp < p + n; pp++) {
		for (struct subject* ps = pp->psub; ps < pp->psub + pp->numSubject; ps++) {
			if (ps->name != NULL) {
				free(ps->name);
				ps->name = NULL;
			}
		}
		if (pp->psub != NULL) {
			free(pp->psub);
			pp->psub = NULL;
		}
		if (pp->name != NULL) {
			free(pp->name);
			pp->name = NULL;
		}
	}
	if (p != NULL) {
		free(p);
		p = NULL;
	}
}
