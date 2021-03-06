#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);

int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

void printStack();

int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf("software 2019038005 KGM\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;


		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}

void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

void iterativeInorder(Node* node)
{
	while(node != NULL)
	{
		while (node != NULL) //node가 NULL이 아닐 때 까지
		{
			push(node); //스택 삽입
			node = node->left; //node를 왼쪽 자식 노드로 이동
		}

		node = pop(); //스택 삭제

		if (node == NULL) //공백 스택일 경우
			break; //반복문 탈출

		printf(" [%d] ", node->key); //키값 출력
		node = node->right; //노드의 오른쪽 자식 노드로 이동
	}
}

void levelOrder(Node* ptr)
{
	int front = 0; //front 선언 후 0으로 초기화
	int rear = 0; //rear 선언 후 0으로 초기화

	Node* queue[MAX_QUEUE_SIZE];

	if (ptr == NULL) //공백 트리일 경우
		return;

	enQueue(ptr); //큐에 루트노드 삽입

	while(1)
	{
		ptr = deQueue(); //deQueue를 호출하여 값을 ptr에 저장

		if (ptr) //ptr이 NULL이 아닐 경우
		{
			printf("%d", ptr->key); //ptr의 키값을 출력

			if (ptr->left) //ptr의 왼쪽 자식이 있을 경우
				enQueue(ptr->left); //왼쪽 자식에 노드 삽입

			if (ptr->right) //ptr의 오른쪽 자식이 있을 경우
				enQueue(ptr->right); //오른쪽 자식에 노드 삽입
		}

		else break; //NULL 일 경우 반복문 탈출
	}
}

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteNode(Node* head, int key)
{
	/* 부모노드, 자식노드, 자식노드의 부모, 삭제할 노드, 삭제할 노드의 자손 */
	 Node* par, * son, * son_par, * nodedelete, * nodedelete_son;

    par = NULL; //부모노드를 NULL로 지정
    nodedelete = head->left; //삭제할 노드를 헤드의 왼쪽 노드로 지정

    while (nodedelete != NULL && nodedelete->key != key) //삭제할 노드가 NULL이 아니고 그 키값이 찾는 키 값이 아닐때 까지 반복
    {
        par = nodedelete; //부모 노드에 삭제할 노드의 값을 지정 
        
		if (key < par->key) //찾는 키 값이 더 작을 경우
			nodedelete = par->left; //왼쪽 노드로 이동

		else //찾는 키 값이 더 클 경우
			nodedelete = par->right; //오른쪽 노드로 이동
    }

    if (nodedelete->left == NULL && nodedelete->right == NULL) //첫번째 노드일 경우
    {
        if (par) //부모노드가 NULL이 아닐 경우
        {
            if (par->left == nodedelete) //부모노드의 왼쪽 노드가 삭제할 노드와 같을 경우
                par->left = NULL; //왼쪽 노드를 NULL로 지정
            else //아닐 경우 (오른쪽 노드와 같을 경우)
                par->right = NULL; //오른쪽 노드를 NULL로 지정
        }
        else
            head->left = NULL; //head의 왼쪽 노드를 NULL로 지정
    }

    else if ((nodedelete->left == NULL) || (nodedelete->right == NULL)) //서브트리가 하나 있을 경우
    {
       	if (nodedelete->left != NULL) //삭제할 노드의 왼쪽 노드가 NULL 이 아닐 경우
	    	nodedelete_son = nodedelete->left; //삭제할 노드의 자식을 삭제할 노드의 왼쪽 노드값으로 지정

		else //NULL일 경우 (오른쪽 노드가 NULL이 아닐 경우)
			nodedelete_son = nodedelete->right; //삭제할 노드의 자식을 삭제할 노드의 오른쪽 노드값으로 지정
        
		if (par) //부모노드가 NULL이 아닐 경우
        {
            if (par->left == nodedelete) //부모 노드의 왼쪽 노드가 삭제할 노드와 같을 경우
                par->left =	nodedelete_son; //부모 노드의 왼쪽 노드에 삭제할 노드의 자식 노드를 지정
            else //부모 노드의 오른쪽 노드가 삭제할 노드와 같을 경우
                par->right = nodedelete_son; //부모 노드의 오른쪽 노드에 삭제할 노드의 자식 노드를 지정
        }
        
		else //부모노드가 NULL일 경우
            head->left = nodedelete_son; //head의 왼쪽 노드에 삭제할 노드의 자식 노드를 연결
    }

    else //서브트리가 둘 있을 경우
    {
        son_par = nodedelete; //오른쪽 서브트리에서 가장 작은 값 찾음  suc_p = 18
        son = nodedelete->right; //suc는 삭제노드의 오른쪽 서브트리  suc = 26
       
	    while (son->left != NULL) //자식 노드의 왼쪽 노드가 NULL이 아닐때 까지 반복 (가장 왼쪽으로 이동)
        {
            son_par = son; //자식의 부모 노드에 자식 노드를 지정
            son = son->left; //자식 노드에 자식 노드의 왼쪽 노드를 지정
        }
     
        if (son_par->left == son) //자식의 부모노드의 왼쪽 노드가 자식 노드와 같을 경우 (삭제 노드의 부모와 자식을 연결)
            son_par->left = son->right; //자식 노드의 오른쪽 노드를 그 부모의 왼쪽 노드에 연결
    
        else //다를 경우
            son_par->right = son->right; //자식 노드의 오른쪽 노드가 있을 경우 그 부모의 오른쪽 노드에 연결

        nodedelete->key = son->key; //삭제할 노드의 키 값을 자식의 키 값과 동일하게 해줌
        nodedelete = son; //삭제할 노드와 자식 노드를 동일학 해줌
    }
	
    free(nodedelete); //노드를 삭제
	return 0;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}

Node* pop()
{
	if (top >= 0) //top이 0 이상 일 경우 (값이 존재)
		return stack[top--]; //스택을 반환하고 top의 값을 1 감소
}

void push(Node* aNode)
{
	if (top < MAX_STACK_SIZE - 1 && aNode != NULL) //top이 스택사이즈를 초과하지 않거나 aNODE가 NULL이 아닐경우
		stack[++top] = aNode; //aNode를 추가
}

Node* deQueue()
{
	if (front == rear) //front와 rear 가 같을 경우
		printf("Queue is empty"); //큐가 비었다는 메시지 출력

	front = (front + 1) % MAX_QUEUE_SIZE; //++front
	return queue[front];
}

void enQueue(Node* aNode)
{
	if (rear == MAX_QUEUE_SIZE - 1) //큐가 꽉 찼을 경우
		printf("Queue is full"); //큐가 꽉 찼다는 메시지 출력

	queue[++rear] = aNode;
}
