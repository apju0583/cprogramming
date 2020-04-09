#include <stdio.h>
#define MAX_SIZE 100

float sum(float [], int);
float input[MAX_SIZE], answer;
int i;

void main(void)
{
	for(i=0;i<MAX_SIZE;i++)
		input[i]=i; //각 배열에 값 대입

	printf("소프트웨어 2019038005 김강민\n");

	printf("address of input = %p\n", input); //input의 주소 출력

	answer = sum(input, MAX_SIZE); //합을 나타낼 변수 지정 후 함수 호출
	printf("The sum is : %f\n", answer); //합의 값 출력
}

float sum(float list[], int n)
{
	printf("value of list = %p\n", list); //list의 값 출력
	printf("address of list = %p\n", &list); //list의 주소 출력

	int i;
	float tempsum = 0; //합을 0으로 초기화

	for(i=0;i<n;i++)
		tempsum += list[i]; //각 배열의 값을 모두 더함

	return tempsum; //합의 값을 반환
}
