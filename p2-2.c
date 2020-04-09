#include <stdio.h>

void print1 (int *ptr, int rows);

int main()
{
	int one[] = {0,1,2,3,4};

	printf("소프트웨어 2019038005 김강민\n");

	printf("one = %p\n", one); //one의 값 출력
	printf("&one = %p\n", &one); //one의 주소 출력
	printf("&one[0] = %p\n\n", &one[0]); //&one[0]의 주소 출력

	print1(&one[0],5); //함수 호출

	return 0;
}

void print1 (int *ptr, int rows)
{
	int i;

	printf("Address \t Contents\n");

	for (i=0;i<rows;i++)
		printf("%p \t %5d\n", ptr+i, *(ptr +i)); //주소와 인덱스 값 출력

	printf("\n");
}
