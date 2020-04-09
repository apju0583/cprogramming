#include <stdio.h>

struct student
{
	char lastName[13]; //13 바이트 차지
	int studentId; //4 바이트 차지
	short grade; //2 바이트 차지
};

int main()
{
	struct student pst; //pst 구조체 선언

	printf("소프트웨어 2019038005 김강민\n");

	printf("size of student = %ld\n", sizeof(struct student)); //student 구조체의 바이트 수
	printf("size of int = %ld\n", sizeof(int)); //int형의 바이트 수
	printf("size of short = %ld\n", sizeof(short)); //short형의 바이트 수

	return 0;
}
