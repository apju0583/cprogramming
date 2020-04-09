#include <stdio.h>
#include <stdlib.h>

void main()
{
	int **x;

	printf("소프트웨어 2019038005 김강민\n");

	printf("sizeof(x) = %lu\n", sizeof(x)); //x의 바이트 수
	printf("sizeof(*x) = %lu\n", sizeof(*x)); //*x의 바이트 수
	printf("sizeof(**x) = %lu\n", sizeof(**x)); //**x의 바이트 수
}
