#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)

typedef struct table {
	int key;
	int elem;
	int status;
	// status : 0 : 비활성화
	// status : 1 : 활성화 & 내부 원소 존재
}table;

table* hashTable;
int M = 23, q = 19; // M = 23, q = 19 (23보다 조금 작은 소수)

int h1(int);
int h2(int);
int getNextBucket(int, int, int);

void deactivate(int d);
void activate(int d);
int inactive(int d);
int active(int d);

void insertItem(int key);
int findElement(int key);
int removeElement(int key);
void printHashTable();

// 함수 원형함수

int main() {
	int key;
	int elem;
	char com;
	hashTable = (table*)calloc(M, sizeof(table));
	// calloc 사용 -> 0으로 초기화 -> 비어있음을 의미하도록 초기화되어있음

	while (1) {
		scanf("%c", &com);
		// read in command, key, element triple
		switch (com) {
		case 'f':
			scanf("%d", &key);
			elem = findElement(key);
			if (elem != -1) {
				printf("%d\n", elem);
			}
			break;
		case 'i':
			scanf("%d", &key);
			insertItem(key);
			break;
		case 'r':
			scanf("%d", &key);
			elem = removeElement(key);
			if (elem != -1) {
				printf("%d\n", elem);
			}
			break;
		case 'p':
			printHashTable();
			break;
		case 'q':
			exit(-1);
			break;
		}
		// 해당 명령어에 알맞은 명령 수행 
		// 과제지의 주요 함수 설계 의사코드에 따름
	}
	free(hashTable); // 동적할당 해제
	return 0;
}


int h1(int x) {
	return x % M;
} // 첫번째 해시함수
int h2(int x) {
	return q - (x % q);
} // 두번째 해시함수
int getNextBucket(int v, int i, int key) {
	return (v + i * h2(key)) % M;
} // 이중해싱 getNextBucket

void deactivate(int d) {
	hashTable[d].status = 0;
} // 버켓 d를 비활성화
void activate(int d) {
	hashTable[d].status = 1;
}// 버켓 d를 활성화
int inactive(int d) {
	if (hashTable[d].status == 0) {
		return 1;
	}
	return 0;
}// 버켓 d가 비활성인지 여부를 반환
int active(int d) {
	if (hashTable[d].status == 1) {
		return 1;
	}
	return 0;
}// 버켓 d가 활성인지 여부를 반환

void insertItem(int key) {
	if (key > 99 || key < 0) {
		// elem을 key로 대체하므로 원소 제한 동일하게 진행
		// printf("NotValidElement\n"); -> elem 범위 over시 예외 문구
		return;
	} // 저장 원소 0 ~ 99로 제한 (아닐 경우 명령수행 거절)
	for (int i = 0; i < M; i++) {
		if (hashTable[i].key == key && active(i) == 1) {
			printf("ExistKey\n");
			return;
		}
	} // 중복 키 여부 확인 (중복 키 존재시 안내메시지 / 명령수행 거절)
	int v = h1(key), i = 0, b;
	while (i < M) {
		b = getNextBucket(v, i, key);
		if (hashTable[b].status == 0) {
			hashTable[b].key = key;
			hashTable[b].elem = key;
			activate(b);
			// 비어있을 경우 Set bucket hashTable[b] to (key, elem)

			/* for (int j = 0; j < i; j++) { // 충돌 횟수 출력
				printf("collision");
			}
			printf("%d\n", b); */
			return;
		}
		else {
			i++;
		}
	}
	printf("Overflow\n");
	// 만원일 경우 안내메시지 / 명령수행 X
	return;
}
int findElement(int key) {
	int v = h1(key), i = 0, b;
	while (i < M) {
		b = getNextBucket(v, i, key);
		if (hashTable[b].key == key && active(b) == 1) {
			return hashTable[b].elem;
			// 존재할 경우(key 동일 & 활성화) hashTable[b]의 elem return 
			// 찾은 elem 을 출력하기 위함
		}
		else {
			i++;
		}
	}
	printf("NoSuchKey\n");
	// 존재하지 않을 경우 ( 원소는 0 ~ 99이므로 -1 반환 )
	return -1;
}
int removeElement(int key) {
	int v = h1(key), i = 0, b;
	while (i < M) {
		b = getNextBucket(v, i, key);
		if (hashTable[b].key == key && active(b) == 1) {
			// 키 동일 & 활성화 상태 -> 비활성화
			deactivate(b);
			return hashTable[b].elem;
			// 비활성화 후 hashTable[b]의 elem return 
			// 찾은 elem 을 출력하기 위함
		}
		else {
			i++;
		}
	}
	printf("NoSuchKey\n");
	// 존재하지 않을 경우 ( 원소는 0 ~ 99이므로 -1 반환 )
	return -1;
}

void printHashTable() {
	for (int i = 0; i < M; i++) {
		printf(" %2d", i);
	}
	printf("\n");
	// 배열 첨자 출력
	for (int i = 0; i < M; i++) {
		if (inactive(i) == 1) {
			printf("  .");
		} // 활성화되어있지 않은 경우 (비활성화 || 비어있을 경우)
		else {
			printf(" %2d", hashTable[i].elem);
		} // 그렇지 않을 경우 (활성화되어있을 경우) 해당 원소 출력
	}
	printf("\n");
	// 저장 원소 출력
}
