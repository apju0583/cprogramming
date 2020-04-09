#include <stdio.h>

struct student1
{
	char lastName;
	int studentId;
	char grade;
};

typedef struct
{
	char lastName;
	int studentId;
	char grade;
} student2;

int main()
{
	struct student1 st1 = {'A', 100, 'A'}; //st1을 선언하여 값을 초기화

	printf("소프트웨어 2019038005 김강민\n");

	printf("st1.lastName = %c\n", st1.lastName); //st1 구조체에서 lastName 출력
	printf("st1.studentId = %d\n", st1.studentId); //st1 구조체에서 studentId 출력
	printf("st1.grade = %c\n\n", st1.grade); //st1 구조체에서 grade 출력

	student2 st2 = {'B', 200, 'B'}; //st2을 선언하여 값을 초기화

	printf("st2.lastName = %c\n", st2.lastName); //st2구조체에서 lastName 출력
	printf("st2.studentId = %d\n", st2.studentId); //st2 구조체에서 studentId 출력
	printf("st2.grade = %c\n\n", st2.grade); //st2 구조체에서 grade 출력

	student2 st3; //st3 구조체 선언

	st3 = st2; //st3에 st2의 값들을 대입

	printf("st3.lastName = %c\n", st3.lastName); //st3구조체에서 lastName 출력
	printf("st3.studentId = %d\n", st3.studentId); //s32 구조체에서 studentId 출력
	printf("st3.grade = %c\n", st3.grade); //st3 구조체에서 grade 출력

	return 0;
}
