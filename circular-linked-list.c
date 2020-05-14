#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);

int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	printf("software 2019038005 KGM\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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

int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h)
{
	if(h->rlink == h) //h의 오른쪽 링크가 h를 가리킬 경우 (h 노드 하나 뿐일경우)
	{
		free(h); //h의 메모리를 해제
		return 0; //0을 반환하며 종료
	}

	listNode *p = h->rlink; //p노드를 지정해 h의 오른쪽링크값을 지정
	listNode *prev = NULL; //prev 노드를 지정해 NULL로 초기화

	while (p != NULL && p != h) //p가 NULL이 아니고 h가 아닐 때까지 반복
	{
		prev = p; //prev노드에 p노드값을 저장
		p = p->rlink; //p노드에 p의 오른쪽링크인 다음 노드값을 지정
		free(prev); //prev의 메모리를 해제
	}

	free(h); //h의 메모리를 해제
	
	return 0;
}

void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);

	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) 
{
	listNode *node = (listNode*)malloc(sizeof(listNode)); //메모리 동적할당

	node->key = key; //node의 key 값에 사용자가 입력한 key 값을 대입
	node->llink = NULL; //node의 왼쪽 링크를 NULL로 초기화
	node->llink = NULL; //node의 오른쪽 링크를 NULL로 초기화

	if (h->rlink == h) //h의 오른쪽 링크가 h를 가리킬 경우 (h 노드 하나 뿐일경우) 
	{
		h->llink = node; //h의 왼쪽 링크에 node를 연결
		h->rlink = node; //h의 오른쪽 링크에 node를 연결

		node->llink = node; //node의 왼쪽 링크에 node 지정 (자기자신을 가리키게함)
		node->rlink = node; //node의 오른쪽 링크에 node 지정 (자기자신을 가리키게함)
	}

	else
	{
		h->llink->rlink = node; //h 이전 노드의 오른쪽 링크에 node를 연결
		node->llink = h->llink; //node의 왼쪽 링크에 h 이전 노드를 연결
		h->llink = node; //h의 왼쪽 링크에 node를 연결
		node->rlink = h; //node의 오른쪽 링크에 h를 연결
	}

	return 1;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) 
{
	if (h->rlink == h || h == NULL) //h가 NULL 혹은 자기자신을 가리키는 경우
	{
		printf("nothing to delete\n"); //지울것이 없다는 메시를 출력
		return 0; //0을 반환하며 종료
	}

	listNode *n = h->llink; //n노드에 h의 왼쪽링크 값을 지정

	n->llink->rlink = h; //n의 전 노드의 오른쪽 링크에 h를 연결
	h->llink = n->llink; //h의 왼쪽링크에 n의 이전노드를 연결
	free(n); //n의 메모리를 해제

	return 1;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) 
{
	listNode *node = (listNode*)malloc(sizeof(listNode)); //메모리 동적 할당

	node->key = key; //node의 key 값에 사용자가 입력한 key 값을 대입
	node->llink = NULL; //node의 왼쪽 링크를 NULL로 초기화
	node->llink = NULL; //node의 오른쪽 링크를 NULL로 초기화

	node->rlink = h->rlink; //node의 오른쪽 링크에 h의 다음 노드 값을 지정
	h->rlink->llink = node; //h의 다음 노드의 왼쪽 링크에 node를 연결
	node->llink = h; //node의 왼쪽 링크에 h를 연결
	h->rlink = node; //h의 오른쪽 링크에 node를 연결

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) 
{
	if (h == NULL || h->rlink == h) //h가 NULL 혹은 자기자신을 가리키는 경우
	{
		printf("nothing to delete\n"); //지울것이 없다는 메시를 출력
		return 0; //0을 반환하며 종료
	}

	listNode *n = h->llink; //n노드에 h의 왼쪽링크 값을 지정

	n->rlink->llink = h; //n의 다음 노드의 왼쪽 링크를 h와 연결
	h->rlink = n->rlink; //h의 오른쪽 링크에 n의 다음 노드를 연결

	free(n); //n의 메모리를 해제

	return 1;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) 
{
	if (h-> rlink == h || h == NULL) //h가 NULL 혹은 자기자신을 가리키는 경우
	{
		printf("nothing to invert\n"); //바꿀 것이 없다는 메시지 출력
		return 0; //0을 반환하며 종료
	}

	listNode *n = h->rlink; //n노드에 h의 오른쪽 링크 값 지정
	listNode *trail = NULL; //trail 노드에 h값 지정
	listNode *middle = NULL; //middle 노드에 h값 지정

	while (n != NULL && n != h) //n이 NULL이 아니고 h가 아닐 때까지 반복
	{
		trail = middle; //trail에 middle 값 지정
		middle = n; //middle에 n 값 지정
		n = n->rlink; //n을 오른쪽으로 이동
		middle->llink = n; //middle의 왼쪽 링크에 n을 연결
		middle->rlink = trail; //middle의 오른쪽 링크에 trail을 연결
	}

	h->llink = h->rlink; //h의 왼쪽링크에 h의 오른쪽 링크 값을 지정
	h->rlink = middle; //h의 오른쪽 링크에 middle값을 지정

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) 
{
	listNode *node = (listNode*)malloc(sizeof(listNode)); //메모리 동적 할당
	listNode *n = h->rlink; //n노드에 h의 오른쪽 링크 값 지정

	node->key = key; //node의 key 값에 사용자가 입력한 key 값을 대입
	node->llink = NULL; //node의 왼쪽 링크를 NULL로 초기화
	node->llink = NULL; //node의 오른쪽 링크를 NULL로 초기화

	if (h->rlink == h) //h의 오른쪽 링크가 h를 가리킬 경우 (h 노드 하나 뿐일경우)
	{
		insertFirst(h, key); //첫번째 노드에 값을 넣은 insertFirst 호출
		return 0; //0을 반환하며 종료
	}

	while (n != NULL && n != h) //n이 NULL이 아니고 h도 아닐때 까지 반복
	{
		if (n->key >= key) //n노드의 키값이 사용자가 입력한 키값보다 클 경우
		{
			if (n == h->rlink) //n이 첫 노드일 경우 (처음에 삽입해야할 경우)
			{
				insertFirst(h, key); //첫 노드에 삽입하는 insertFirst를 호출
				return 0; //0을 반환하며 종료
			}
			else //중간에 삽입할 경우
			{
				node->llink = n->llink; //node의 왼쪽 링크에 n의 이전노드 연결
				node->rlink = n; //node의 오른쪽 링크에 n을 연결
				n->llink->rlink = node; //n의 이전노드의 오른쪽 링크에 node를 연결
			}
			return 0; //0을 반환하며 종료
		}
		n = n-> rlink; //n을 오른쪽으로 이동
	}
	insertLast(h, key); //마지막에 삽입해야할 경우 insertLast 호출
	return 0; 
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) 
{
	if (h == NULL || h->rlink == h) //h가 NULL 혹은 자기자신을 가리키는 경우
	{
		printf("nothing to delete\n"); //지울것이 없다는 메시를 출력
		return 0; //0을 반환하며 종료
	}
	listNode *n = h->llink; //n노드에 h의 왼쪽쪽 링크 값을 지정

	while (n != NULL && n != h) //n이 NULL이 아니고 h도 아닐때 까지 반복
	{
		if (n->key == key) //n노드의 키값이 사용자가 입력한 키값보다 클 경우
		{
			if (n == h->rlink) //n이 첫 노드일 경우 (처음에 삽입해야할 경우)
			{
				deleteFirst(h); //첫 노드를 삭제하는 deleteFirst 함수 호출
				return 0; //0을 반환하며 종료
			}

			else if (n->rlink == h) //n의 오른쪽 링크가 h를 가리킬 경우(마지막일 때)
			{
				deleteLast(h); //마지막 노드를 지우는 deleteLast함수 호출
				return 0; //0을 반환하며 종료
			}
			else
			{
				n->llink->rlink = n->rlink; //n이전 노드의 오른쪽 링크를 n 다음노드로 지정
				n->rlink->llink = n->llink; //n다음 노드의 오니쪽 링크를 n 이전노드로 지정
				free(n); //n의 메모리를 해제
			}
			return 0;
		}
	n = n->rlink; //n을 오른쪽으로 이동
	}
	return 0;
}
