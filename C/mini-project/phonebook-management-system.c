#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

struct info {
	char* name;
	char* phone;
	char* bi;
}; // 동적할당

int regist(int, struct info*);
void showall(int, struct info*);
int delete(int, struct info*);
void find_b(int, struct info*);

int main(void) {
	struct info** class;
	int menu_num, input_num = 0, max_num = 0;
	printf("Max_num:"); // 고정
	scanf("%d", &max_num);
	class = (struct info**)malloc(sizeof(struct info*));
	if (class == NULL) return -1;
	class[0] = (struct info*)malloc(sizeof(struct info)*max_num);
	if (class[0] == NULL) return -1;

	for (;;) {
		printf("*****Menu*****\n");
		printf("<1.Registration><2.ShowAll><3.Delete><4.FindByBirth><5.Exit>\n");
		printf("Enter_the_menu_number:"); // 고정]
		scanf("%d", &menu_num);

		//1
		if (menu_num == 1) {
			if (input_num == max_num) {
				printf("OVERFLOW\n");
				continue;
			}
			input_num = regist(input_num, class[0]);
			continue;
		}
		//2
		if (menu_num == 2) {
			showall(input_num, class[0]);
			continue;
		}
		//3
		if (menu_num == 3) {
			input_num = delete(input_num, class[0]);
			continue;
		}
		//4
		if (menu_num == 4) {
			find_b(input_num, class[0]);
			continue;
		}
		//5
		if (menu_num == 5) break;
	}

	for (int i = 0; i < input_num; i++) {
		if (class[0][i].name != NULL) {
			class[0][i].name = NULL;
			free(class[0][i].name);
		}
		if (class[0][i].phone != NULL) {
			class[0][i].phone = NULL;
			free(class[0][i].phone);
		}
		if (class[0][i].bi != NULL) {
			class[0][i].bi = NULL;
			free(class[0][i].bi);
		}
	}
	if (class[0] != NULL) {
		class[0] = NULL;
		free(class[0]);
	}
	if (class != NULL) {
		class = NULL;
		free(class);
	} //동적할당 해제
}

int regist(int input_num, struct info* class) { //1
	char tname[101] = { NULL };
	char tphone[101] = { NULL };
	char tbi[101] = { NULL };
	int idx = 0, f = 0;

	printf("Name:"); // 고정]
	scanf("%s", tname);
	for (int i = 0; i < input_num; i++) {
		if (strcmp(tname, class[i].name) < 0) {
			idx = i;
			for (int j = input_num - 1; j >= idx; j--) *(class + j + 1) = *(class + j);
			f = 1;
			if (class[idx].name != NULL) {
				class[idx].name = NULL;
				free(class[idx].name);
			}
			if (class[idx].bi != NULL) {
				class[idx].bi = NULL;
				free(class[idx].bi);
			}
			if (class[idx].phone != NULL) {
				class[idx].phone = NULL;
				free(class[idx].phone);
			}
			break;
		}
	} // [저장할 인덱스 찾기, 밀기]
	if (f == 0) idx = input_num; // 맨 뒤인 경우
	input_num += 1;

	class[idx].name = (char*)malloc(strlen(tname) + 1);
	if (class[idx].name == NULL) return -1;
	strcpy(class[idx].name, tname);

	printf("Phone_number:"); // 고정]
	scanf("%s", tphone);
	class[idx].phone = (char*)malloc(strlen(tphone) + 1);
	if (class[idx].phone == NULL) return -1;
	strcpy(class[idx].phone, tphone);

	printf("Birth:"); // 고정]
	scanf("%s", tbi);
	class[idx].bi = (char*)malloc(strlen(tbi) + 1);
	if (class[idx].bi == NULL) return -1;
	strcpy(class[idx].bi, tbi);
	printf("<<%d>>\n", input_num); // [입력 & 입력 완료]
	return input_num;
}

void showall(int input_num, struct info* class) { //2
	if (input_num > 0) {
		for (int i = 0; i < input_num; i++) {
			printf("%s %s %s\n", class[i].name, class[i].phone, class[i].bi);
		}
	}// [등록된 사람이 있으면 출력]
}

int delete(int input_num, struct info* class) { //3
	if (input_num == 0) {
		printf("NO MEMBER\n");
		return input_num;
	} // 저장된 이름이 없을 경우

	char i_name[21] = { NULL };
	printf("Name:"); // 고정]
	scanf("%s", i_name);
	for (int i = 0; i < input_num; i++) {
		if (strcmp(class[i].name, i_name) == 0) {
			for (int j = i; j < input_num; j++) {
				*(class + j) = *(class + j + 1);
			}
			input_num -= 1;
			if (class[input_num].name != NULL) {
				class[input_num].name = NULL;
				free(class[input_num].name);
			}
			if (class[input_num].bi != NULL) {
				class[input_num].bi = NULL;
				free(class[input_num].bi);
			}
			if (class[input_num].phone != NULL) {
				class[input_num].phone = NULL;
				free(class[input_num].phone);
			}
		}
	} // [구조체 당겨서 대입 & 갯수 줄이기]
	return input_num;
}

void find_b(int input_num, struct info* class) { //4
	char i_b_m[3] = { NULL };
	printf("Birth:"); // 고정]
	scanf("%s", i_b_m);
	if (strlen(i_b_m) == 1) {
		for (int i = 0; i < input_num; i++) {
			if (strncmp(class[i].bi + 5, i_b_m, 1) == 0) {
				printf("%s %s %s\n", class[i].name, class[i].phone, class[i].bi);
			}
		}
	}
	else if (strlen(i_b_m) == 2) {
		for (int i = 0; i < input_num; i++) {
			if (strncmp(class[i].bi + 4, i_b_m, 2) == 0) {
				printf("%s %s %s\n", class[i].name, class[i].phone, class[i].bi);
			}
		}
	}
}
