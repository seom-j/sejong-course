#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

struct std {
	char name[10], id[11], gr; // 구조체 선언
};

int main(void) {
	struct std c[5], che; // 구조체 선언
	char c_name[10] = { NULL }, year[5] = { NULL }; //배열 선언
	int print = 0; // 프린트 갯수 변수 선언

	for (struct std* pc = c; pc < c + 5; pc++) scanf("%s %s %c", &pc->name, &pc->id, &pc->gr); // 입력
	scanf("%s", c_name); // 입력
	for (struct std* pc = c; pc < c + 5; pc++) if (strcmp(c_name, &pc->name) == 0) che = *pc; // 이름 같으면 새로운 구조체에 저장

	for (struct std* pc = c; pc < c + 5; pc++) {
		if (strcmp(&pc->name, che.name) == 0) continue; //이름 같으면 지나가기
		if (strncmp(&pc->id, che.id, 4) == 0 && pc->gr == che.gr) { // id앞 4자리와 등급이 같다면
			printf("%s ", pc->name); // 프린트 이름
			print += 1; // 프린트 갯수 더하기
		}
	}

	if (print == 0) printf("%d", print); // 프린트값 없으면 0 출력
	strncpy(year, che.id, 4); // id앞 4자리 복사
	printf("\n%d %d", atoi(year), atoi(year) % 131); // 요구사항 출력
}
