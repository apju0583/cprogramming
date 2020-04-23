#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);

element getElement();


int main(void)
{
	QueueType *cQ = createQueue();
	element data;

	char command;

	printf("소프트웨어 2019038005 김강민\n");

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ,&data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType)); //cQ 동적메모리 할당
	cQ->front = 0; //cQ의 front를 0으로 초기화
	cQ->rear = 0; //cQ의 rear를 0으로 초기화
	return cQ;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}

int isEmpty(QueueType *cQ)
{
	if (cQ->front == cQ->rear) //cQ의 front와 rear가 가리키는 값이 같을 경우
		return 1; //1을 반환

	else //같지 않을 경우
		return 0; //0을 반환
}

int isFull(QueueType *cQ)
{
   if(((cQ->rear+1) % MAX_QUEUE_SIZE) == cQ->front) //rear++의 값이 front와 같을 경우
	   return 1; //1을 반환

   else //같지 않을 경우
	   return 0; //0을 반환
}

void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ) != 1) //isFull을 호출하여 나온 값이 1이 아닐 경우
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //cQ->rear의 값을 1 증가시킴
}

void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ) != 1) //isEmpty를 호출하여 나온 값이 1이 아닐 경우
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; //cQ->front의 값을 1 증가시킴
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //first에 front+1 의 값을 대입
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //last에 rear+1 의 값을 대입

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}
