#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	printf("software 2019038005 KGM");

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h)
{
	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

void inorderTraversal(Node* ptr)
{
	if (ptr == NULL) //ptr이 NULL값일 경우 (값이 비었을 때)
		return;

	inorderTraversal(ptr->left); //ptr의 왼쪽 노드로 함수 재귀호출
	printf("%d\n", ptr->key); //key값 출력 
	inorderTraversal(ptr->right); //ptr의 오른쪽 노드로 함수 재귀호출
}

void preorderTraversal(Node* ptr)
{
	if (ptr == NULL)
		return;

	printf("%d\n", ptr->key); //key값 출력
	preorderTraversal(ptr->left); //ptr의 왼쪽 노드로 함수 재귀호출
	preorderTraversal(ptr->right); //ptr의 오른쪽 노드로 함수 재귀호출
}

void postorderTraversal(Node* ptr)
{
	if (ptr == NULL)
		return;

	postorderTraversal(ptr->left); //ptr의 왼쪽 노드로 함수 재귀호출
	postorderTraversal(ptr->right); //ptr의 오른쪽 노드로 함수 재귀호출
	printf("%d\n", ptr->key); //key값 출력
}

int insert(Node* head, int key)
{//사용자가 입력한 값이 이미 있을 경우
	Node* temp = head->left; //temp 노드를 지정 후 head의 왼쪽 노드로 지정
	Node* n = (Node*)malloc(sizeof(Node)); //메모리 할당
	n->key = key; //n의 key값을 사용자가 입력한 key값으로 지정
	n->left = NULL; //n의 왼쪽노드를 NULL로 초기화
	n->right = NULL; //n의 오른쪽노드를 NULL로 초기화

	if (head->left == NULL) //아무것도 없을 경우
	{
		head->left = n; //n 노드를 추가
		return 0; //0을 반환하며 종료
	}

	else //노드가 있을 경우
	{
		while (1)
		{
			if (key > temp->key) //사용자가 입력한 키 값이 temp의 키값보다 클 경우
			{
				if (temp->right == NULL) //temp의 오른쪽 노드가 비었을 경우
				{
					temp->right = n; //temp의 오른쪽 노드에 n 노드를 연결
					return 0; //0을 반환하며 종료
				}

				else //temp의 오른쪽 노드가 있을 경우
					temp = temp->right; //오른쪽 노드로 이동
			}

			else if (key < temp->key) //사용자가 입력한 키 값이 temp의 키값보다 작을 경우
			{
				if (temp->left == NULL) //temp의 왼쪽 노드가 비었을 경우
				{
					temp->left = n; //temp의 왼쪽 노드에 n 노드를 연결
					return 0; //0을 반환하며 종료
				}

				else //temp의 왼쪽 노드가 있을 경우
					temp = temp->left; //왼쪽 노드로 이동
			}

			else //사용자가 입력한 값이 이미 있을 경우
				return 0; //0을 반환하며 종료
		}
	}
}

int deleteLeafNode(Node* head, int key)
{
	Node* n = head->left; //n 노드 선언 후 head의 왼쪽 노드로 지정

	if (n == NULL) //head 노드가 NULL 일 경우
		return n;

	else if (key < n->key) //키 값이 head의 키값보다 작을 경우
		n->left = deleteLeafNode(n->left, key); //head 노드를 왼쪽 서브트리로 이동

	else if (key > n->key) //키 값이 head의 키값보다 클 경우
		n->right = deleteLeafNode(n->right, key); //head 노드를 오른쪽 서브트리 이동

	else //값이 일치할 경우
	{
		if (n->left == NULL && n->right == NULL) //자식노드가 없을 경우 (리프 노드)
		{
			free(n); //head 메모리 해제
			n = NULL; //NULL 로 지정
		}
	}
	return n;
}

Node* searchRecursive(Node* ptr, int key)
{
	if (!ptr) //값이 없을 경우
		return NULL; //NULL 반환

	if (key == ptr->key) //값이 일치할 경우
		return ptr; //노드 주소 반환

	else if (key < ptr->key) //값이 작은 경우
		searchRecursive(ptr->left, key); //왼쪽 서브트리로 이동

	else //값이 큰 경우
		searchRecursive(ptr->right, key); //오른쪽 서브트리로 이동

}

Node* searchIterative(Node* head, int key)
{
	Node* n = head->left; //n 노드 선언 후 head의 왼쪽 노드로 지정

	while (n) //NULL이 아닐때 까지 반복
	{
		if (key == n->key) //값이 일치할 경우
			return n; //노드 주소 반환

		else if (key < n->key) //값이 작은 경우
			n = n->left; //왼쪽 서브트리로 이동

		else //값이 큰 경우
			n = n->right; //오른쪽 서브트리로 이동
	}
	return NULL; //값이 없을 경우 NULL 반환
}

int freeBST(Node* head)
{
	if (head == NULL) //head가 NULL일 경우
		return 0;

	freeBST(head->left); //왼쪽 서브트리로 이동하며 해제
	freeBST(head->right); //오른쪽 서브트리로 이동하며 해제
	free(head); //head값 해제
}
