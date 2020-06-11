#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);

/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);

int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL) //배열이 비어있지 않을 경우
		free(a); //동적 메모리 해제
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a) //선택정렬
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j]) //min의 원소 값이 더 클 경우
			{
				min = a[j]; //min에 해당 원소 값을 대입
				minindex = j; //minindex에 해당 인덱스 값 대입
			}
		}
		a[minindex] = a[i]; //바꿀 위치의 원소값 대입
		a[i] = min; //가장 작은 값을 가진 원소를 앞으로 이동 
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a) //삽입 정렬
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; //t에 배열의 원소값 한개를 대입
		j = i; //j에 i값 대입
		while (a[j-1] > t && j > 0) //t보다 앞의 원소 값이 크고 j가 0 이상 일때 까지 반복
		{
			a[j] = a[j-1]; //앞의 원소 값을 대입 (오른쪽으로 이동)
			j--; //j-1
		}
		a[j] = t; //반복문을 마친 후 알맞는 자리에 값을 삽입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a) //버블 정렬
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) //앞의 원소가 뒤의 원소보다 클 때
			{
				t = a[j-1]; //t에 앞의 원소 값 저장
				a[j-1] = a[j]; //앞의 원소에 뒤의 원소값 대입
				a[j] = t; //뒤의 원소에 앞의 원소 값 대입
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a) //셸 정렬
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++) //원소간의 간격을 둠
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) //h의 간격만큼 떨어진 원소를 묶음
			{
				v = a[j]; 
				k = j;
				while (k > h-1 && a[k-h] > v) //정렬을 해야하는지 판단
				{
					a[k] = a[k-h]; //위치를 바꾸어 큰 원소를 뒤에 가게함
					k -= h; //k의 값을 감소 시켜 바꿀 원소의 인덱스값을 저장
				}
				a[k] = v; //작은 원소를 앞에 대입
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n) //퀵 정렬
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1]; //피봇의 위치를 가장 마지막 원소로 지정
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v); //i번째 원소랑 비교하며 그 값이 v 보다 작으면 한칸을 증가시킴
			while(a[--j] > v); //j번째 원소랑 비교하며 그 값이 v 보다 크면 한칸을 감소시킴

			if (i >= j) break; //i가 j와 같거나 넘어설 경우 반복문 종료

			/* swap */
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		/* swap */
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i); //v를 기준으로 왼쪽 그룹을 새로 quickSort
		quickSort(a+i+1, n-i-1); //v를 기준으로 오른쪽 그룹을 새로 quickSort
	}
	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1; 

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i]; //키값 지정
		hashcode = hashCode(key); //키값을 해시코드로 나타냄
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key; //해시테이블에 키 값을 대입
		} 
		
		else 
		{
			index = hashcode; //인덱스에 해시코드값을 대입

			while(hashtable[index] != -1) //해시테이블의 값이 -1이 아니면 반복
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; //
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //키 값을 넣어줌
		}
	}
	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}
