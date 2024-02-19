#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

struct vector {
	int x, y, z;
};

int main() {
	struct vector v1, v2, v3;
	scanf("%d%d%d", &v1.x, &v1.y, &v1.z);
	scanf("%d%d%d", &v2.x, &v2.y, &v2.z);

	v3.x = v1.x * v2.x;
	v3.y = v1.y * v2.y;
	v3.z = v1.z * v2.z;

	printf("%d %d %d\n%d", v3.x, v3.y, v3.z, v3.x + v3.y + v3.z);
}
