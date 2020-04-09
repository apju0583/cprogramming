#include <stdio.h>
#include <stdlib.h>

void main()
{
	int list[5];
	int *plist[5];

	list[0]=10;
	list[1]=11;

	plist[0] = (int*)malloc(sizeof(int)); //동적메모리 할당

	printf("소프트웨어 2019038005 김강민\n");

	printf("list[0] = %d\n", list[0]); //list[0]의 값 출력
	printf("address of list = %p\n", list); //list의 주소 (=list[0]의 주소) 출력
	printf("address of list[0] = %p\n", &list[0]); //list[0]의 주소 출력
	printf("address of list + 0 = %p\n", list+0); //list+0의 주소(=list[0]의 주소) 출력
	printf("address of list + 1 = %p\n", list+1); //list+1의 주소(=list[1]의 주소) 출력
	printf("address of list + 2 = %p\n", list+2); //list+2의 주소(=list[2]의 주소) 출력
	printf("address of list + 3 = %p\n", list+3); //list+3의 주소(=list[3]의 주소) 출력
	printf("address of list + 4 = %p\n", list+4); //list+4의 주소(=list[4]의 주소) 출력
	printf("address of list[4] = %p\n", &list[4]); //list[4]의 주소 출력

	free(plist[0]); //할당 해제
}
