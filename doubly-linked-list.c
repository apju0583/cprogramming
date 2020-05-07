#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);
void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("2019038005 software 김강민\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) 
{
	if (*h != NULL) //headNode가 NULL이 아니면
		freeList(*h); //할당된 메모리를 해제

	*h = (headNode*)malloc(sizeof(headNode)); //메모리를 동적 할당
	(*h)->first = NULL; //헤드노드가 NULL을 가르키게 함

	return 1;
}

int freeList(headNode* h)
{
	listNode* p = h->first;
	listNode* prev = NULL;
	
	while (p != NULL)
	{
		prev = p;
		p = p->rlink;
		free(prev);
	}

	free(h);
	
	return 0;
}


void printList(headNode* h) 
{
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) 
{
	listNode* node = (listNode*)malloc(sizeof(listNode)); //메모리 동적할당

	node->key = key; //node의 key에 사용자가 입력한 key값 대입
	node->llink = NULL; //node의 왼쪽 링크를 NULL로 초기화
	node->rlink = NULL; //node의 오른쪽 링크를 NULL로 초기화

	if (h->first == NULL) //h가 가리키는 첫 노드가 NULL일 경우
	{
		h->first = node; //h가 node를 가리키게 함
		return 0; //0을 반환하며 종료
	}

	listNode* n = h->first; //n이라는 리스트를 지정후 h가 가리키게 함

	while (n->rlink != NULL) //n의 오른쪽 링크가 널 값이 아닐때 까지 반복 (노드가 끝까지 가게함)
	{
		n = n->rlink; //n이 다음 노드를 가리키게 함 (한 노드씩 이동)
	}

	n->rlink = node; //n의 오른쪽 링크에 node를 연결해줌
	node->llink = n; //node의 왼쪽 링크에 n을 연결해 서로 연결되게 함

	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) 
{
	if (h->first == NULL) //첫 노드가 NULL일 경우
	{
		printf("nothing to delete\n"); //지울 것이 없다는 메시지 출력
		return 0; //0을 반환하며 종료
	}

	listNode* n = h->first; //n이라는 리스트를 지정후 h가 가리키게 함 
	listNode* trail = NULL; //trail이라는 리스트를 지정후 NULL로 초기화

	if (n->rlink == NULL) //n의 오른쪽 링크가 NULL일 경우 (노드가 하나인 경우)
	{
		h->first = NULL; //h가 NULL값을 가리키게 함
		free(n); //n의 메모리를 해제
		return 0; //0을 반환하며 종료
	}

	while (n-> rlink != NULL) //n의 오른쪽 링크가 널 값이 아닐때 까지 반복 (노드가 끝까지 가게함)
	{
		trail = n; //trail에 n 노드 값을 지정
		n = n->rlink; //n이 다음 노드를 가리키게 함 (한 노드씩 이동) 
	}

	trail->rlink = NULL; //trail의 오른쪽 링크가 NULL값을 지정
	free(n); //n의 메모리를 해제

	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) 
{
	listNode* node = (listNode*)malloc(sizeof(listNode)); //메모리 동적할당
	
	node->key = key; //node의 key에 사용자가 입력한 key값 대입
	node->llink = NULL; //node의 왼쪽 링크를 NULL로 초기화
	node->rlink = NULL; //node의 오른쪽 링크를 NULL로 초기화

	if (h->first == NULL) //h가 가리키는 첫 노드가 NULL일 경우
	{
		h->first = node; //h가 node를 가리키게 함
		return 0; //0을 반환하며 종료
	}
	
	node->llink = NULL; //node의 왼쪽 링크에 NULL을 지정
	node->rlink = h->first; //node의 오른쪽 링크가 첫 노드를 가리키게 지정

	listNode *temp = h->first; //temp라는 리스트를 지정 후 첫 노드를 가리키게 지정

	temp->llink = node; //temp의 왼쪽 링크에 node를 연결
	h->first = node; //h가 가리키는 첫 노드를 node로 지정하여 연결

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) 
{
	if (h->first == NULL) //h가 가리키는 첫 노드가 NULL일 경우
	{
		printf("nothing to delete\n"); //지울 것이 없다는 메시지 출력
		return 0; //0을 반환하며 종료
	}

	listNode* n = h->first; //n이라는 리스트를 지정 후 첫 노드를 가리키게함
	
	h->first = n->rlink; //h가 n의 오른쪽 링크를 가리키게 함 (n의 다음노드를 가리키게 함)
	free(n); //n의 메모리를 해제

	return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) 
{
	if (h->first == NULL) //h가 가리키는 첫 노드가 NULL일 경우
	{
		printf("nothing to inver\n"); //바꿀 것이 없다는 메시지 출력
		return 0; //0을 반환하며 종료
	}

	listNode *n = h->first; //n이라는 리스르를 지정 후 첫 노드가 가리키게 함
	listNode *trail = NULL; //이전 노드와 다음 노드를 연결하기 위한 리스트인 trail을 지정 후 NULL로 초기화
	listNode *middle = NULL; //n 노드와 trail 노드 사이를 연결할 리스트인 middle을 지정 후 NULL로 초기화

	while (n != NULL) //n의 오른쪽 링크가 널 값이 아닐때 까지 반복 (노드가 끝까지 가게함)
	{
		trail = middle; //trail에 middle 노드 값을 지정
		middle = n; //middle에 n 노드 값을 지정
		n = n->rlink; //n이 다음 노드를 가리키게 함 (한 노드씩 이동) 
		middle->llink = n; //middle의 왼쪽 링크에 n 노드를 연결
		middle->rlink = trail; //middle의 오른쪽 링크에 trail 노드를 연결
	}

	h->first = middle; //첫 노드가 middle을 가리키게 함

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) 
{
	listNode* node = (listNode*)malloc(sizeof(listNode)); //메모리 동적할당

	node->key = key; //node의 key에 사용자가 입력한 key값 대입
	node->llink = NULL; //node의 왼쪽 링크를 NULL로 초기화
	node->rlink = NULL; //node의 오른쪽 링크를 NULL로 초기화

	if (h->first == NULL) //h가 가리키는 첫 노드가 NULL일 경우
	{
		h->first = node; //h가 node를 가리키게 함
		return 0; //0을 반환하며 종료
	}
	listNode *n = h->first; //n이라는 리스트를 지정 후 첫 노드가 가리키게 함
 	while (n != NULL) //n이 NULL이 아닐 경우 계속 반복
	{
		if (n->key >= key) //n노드의 키값이 사용자가 입력한 키값보다 클 경우
		{
			if (n == h->first) //n이 첫 노드일 경우 (처음에 삽입해야할 경우)
			{
				insertFirst (h, key); //첫 노드에 삽입하는 insertFirst를 호출
			}
			else //중간에 삽입해야할 경우
			{
				node->llink = n; //node의 왼쪽 링크에 n을 연결
				node->rlink = n->rlink; //node의 오른쪽링크에 n의 오른쪽 링크인 다음 노드를 연결
				n->llink->rlink = node; //n 노드에 node를 지정
			}
						return 0;
		}
		n = n->rlink; //n이 다음 노드를 가리키게 함 (한 노드씩 이동) 
	}
	insertLast(h, key); //마지막에 삽입해야할 경우 insertLast를 호출
	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) 
{
	if (h->first == NULL) //첫 노드가 NULL일 경우
	{
		printf("nothing to delete\n"); //삭제할 것이 없다는 메시지 출력
		return 0; //0을 반환하며 종료
	}
	listNode *n = h->first; //n 리스트를 생성 후 첫 노드가 가리키게 함

	while (n != NULL) //n이 NULL이 아닐 때 까지 반복
	{
		if (n->key == key) //n의 키값이 사용자가 입력한 키값일 경우
		{
			if (n == h->first) //n이 첫 노드일 경우 (처음에 삽입해야할 경우) 
			{
				deleteFirst(h); //첫 번째 노드를 삭제하는 deleteFirst 함수 호출
			}
			else if (n->rlink == NULL) //n의 오른쪽 링크가 NULL값일 경우 (마지막 노드를 삭제해야 할 경우)
			{
				deleteLast(h); //마지막 노드를 삭제하는 deleteLast 함수 호출
			}
			else
			{
				n->llink->rlink = n->rlink; //n의 왼쪽 노드의 오른쪽 링크를 n의 오른쪽 노드로 지정
				n->rlink->llink = n->llink; //n의 오른쪽 노드의 왼쪽 링크를 n의 왼쪽 노드로 지정

				free(n); //n의 메모리를 해제
			}
			return 0;
		}
		n = n->rlink; //n이 다음 노드를 가리키게 함 (한 노드씩 이동)
	}
	return 1;
}
