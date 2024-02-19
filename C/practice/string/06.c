#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int main(void) {
	char s1[41] = { NULL }, s2[21] = { NULL };
	scanf("%s %s", s1, s2);
	int l1 = strlen(s1), l2 = strlen(s2), id, o;
	scanf("%d %d", &id, &o);

	for (char* p = s1; p < s1 + strlen(s1); p++) {
		if (s1 + id == p) {
			
			for (char* q = s1 + l1; q >= p; q--) *(q + l2) = *q;
			if (o==0) for (char* q = p, *r = s2; r < s2 + l2; q++, r++) *q = *r;
			else  for (char* q = p, *r = s2+l2-1; r >=s2; q++, r--) *q = *r;
		}
	}
	
	printf("%s", s1);

	return 0;
}
