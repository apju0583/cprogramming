#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 20 /* you can change value 20 */

typedef struct Vertex 
{ 
    int num; /* vertex number */ 
    struct Vertex* link; /* link to a next adjacent vertext */ 
} Vertex;

typedef struct VertexHead 
{ 
    Vertex* head; /* linked list of all adjacent vertices */ 
} VertexHead;

typedef struct Graph 
{ 
    VertexHead* vlist; /* list of all vertices: vlist[MAX_VERTEX] */ 
} Graph;

int createGraph(Graph** graph); /* empty graph creation */
int destroyGraph(Graph* graph); /* deallocating all allocated memory */ 
int insertVertex(Graph* graph, int key); /* vertex insertion */ 
int deleteVertex(Graph* graph, int key); /* vertex deletion */
int insertEdge(Graph* graph, int from, int to); /* new edge creation between two vertices */ 
int deleteEdge(Graph* graph, int from, int to); /* edge removal */ 
int depthFS(Graph* graph, int start); /* depth firt search using stack */ 
int breathFS(Graph* graph, int start); /* breadth first search using queue */
int printGraph(Graph* graph); /* printing graph with vertices and edges */


int main()
{
	Graph* graph = NULL;  
    char command;
    int from, to, key;

	printf("software 2019038005 KGM\n");
	
    do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                      Term Project                              \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph       = z      Destroy Graph              = d \n");
		printf(" Insert vertex          = i      Delete vertex              = v \n");
		printf(" Insert Edge            = e      Delete Edge                = g \n");
        printf(" depthFS                = f      breathFS                   = b \n");
		printf(" Print Graph            = p      Quit                       = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf("%c", &command);

		switch(command) 
        {
		case 'z': case 'Z':
			createGraph(&graph);
			break;
		
        case 'd': case 'D':
			destroyGraph(graph);
			break;

		case 'i': case 'I':
            printf("vertex key = ");
			scanf("%d", &key);
			insertVertex(graph, key);
			break;

		case 'v': case 'V':
			printf("vertex key = ");
			scanf("%d", &key);
			deleteVertex(graph, key);
			break;

		case 'e': case 'E':
			printf("from & to = ");
			scanf("%d %d", &from, &to);
			insertEdge(graph, from, to);
			break;

		case 'g': case 'G':
			printf("from & to = ");
			scanf("%d %d", &from, &to);
			deleteEdge(graph, from, to);
			break;

		case 'f': case 'F':
			printf("key = ");
			scanf("%d", &key);
			depthFS(graph, key);
			break;

        case 'b': case 'B':
			printf("key = ");
			scanf("%d", &key);
			breathFS(graph, key);
			break;

		case 'p': case 'P':
			printGraph(graph);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while(command != 'q' && command != 'Q');
	return 1;
}

int createGraph(Graph** graph)
{
    if (*graph != NULL) //그래프가 비어있지 않을 경우
        destroyGraph(*graph); //그래프 삭제

    *graph=(Graph*)malloc(sizeof(Graph)); //동적 메모리 할당
    (*graph)->vlist = (VertexHead*)malloc(MAX_VERTEX*sizeof(VertexHead)); //동적 메모리 할당

    for (int i = 0; i < MAX_VERTEX; i++)
        (*graph)->vlist[i].head = NULL; //그래프의 vlist head 값을 NULL로 초기화
    
    return 1;
}

int destroyGraph(Graph* graph)
{
    if (graph == NULL) //그래프가 비었을 경우
    {
        printf("Graph is Empty\n");
        return 0; //0을 반환하며 종료
    }

    Vertex* ptr;
    Vertex* prev;

    for (int i = 0; i < MAX_VERTEX; i++)
    {
        ptr = g->vlist[i].head; //ptr의 위치를 설정
				
        while(ptr != NULL) //ptr이 NULL이 아니면 반복
		{
		    prev = ptr; //prev에 ptr의 값을 저장
			ptr = ptr->link; //ptr의 값을 변경시켜 위치 변경
			free(prev); //prev 해제
        }
    }

    free(graph->vlist); //vlist 해제
    free(graph); //graph 해제
    return 1;
}

int insertVertex(Graph* graph, int key)
{
    if (key > MAX_VERTEX || key <= 0) //key값이 범위를 벗어날 경우
    {
        printf("invalid key\n");
        return 0;
    }

    Vertex* v = (Vertex*)malloc(sizeof(Vertex)); //새로 넣을 값을 저장한 변수 지정 후 메모리 할당
    v->num = key; //num에 key값 저장
    v->link = NULL; //link를 NULL로 초기화

    for (int i = 0; i < MAX_VERTEX; i++)
    {
        if (key == i+1)
        {
            if (graph->vlist[i].head == NULL) //head가 비었을 경우
            {
                graph->vlist[i].head = v; //해당 값에 v 대입
                return 0;
            }
        }
    }
}

int deleteVertex(Graph* graph, int key)
{
    if (graph == NULL) //graph가 비었을 경우
    {
        printf("graph is empty\n");
        return 0; //0을 반환하며 종료
    }

     if (key > MAX_VERTEX || key <= 0) //key값이 범위를 벗어날 경우
    {
        printf("invalid key\n");
        return 0;
    }

    Vertex* ptr = graph->vlist[key].head; //ptr변수 선언후 그래프의 헤드값 지정
    Vertex* prev = NULL; //prev 선언 후 NULL로 초기화
    Vertex* temp = NULL; //temp 선언 후 NULL로 초기화

    for (int i = 0; i < MAX_VERTEX; i++)
    {
        while (p != NULL)
        {
            if (ptr->num == key)
            {
                if (prev == NULL) //첫 정점을 삭제해야 할 경우
                    graph->vlist[i]/head = ptr->link; //그래프 값을 다음 것으로 연결

                else
                    prev->link = ptr->link; //다음 정점과 연결

                temp = ptr; //temp에 값 저장
                ptr = ptr->link; //ptr 이동
                free(temp); //temp 해제
            }
        }
    }
    return 1;
}

int insertEdge(Graph* graph, int from, int to)
{
    if (graph == NULL) //그래프가 비었을 경우
    {
        printf("graph is empty\n");
        return 0;
    }
    
    if (from > MAX_VERTEX || from <= 0 || to > MAX_VERTEX || to <= 0) //값이 범위를 벗어날 경우
    {
        printf("invalid key");
    }

    Vertex* ptr;

    if (graph->vlist[from].head == NULL) //정점에 간선이 없을 경우
    {
        graph->vlist[from].head->num = to;
        graph->vlist[from].head->link = NULL;
    }

    while (ptr->link != NULL) //마지막 까지 이동
    {
        ptr = ptr->link; //ptr 이동
    }

    ptr->link->num = to;
    ptr->link->link = NULL; 

    return 1;
}

int deleteEdge(Graph* graph, int from, int to)
{
    if (graph == NULL) //그래프가 비었을 경우
    {
        printf("graph is empty\n");
        return 0;
    }
    
    if (from > MAX_VERTEX || from <= 0 || to > MAX_VERTEX || to <= 0) //값이 범위를 벗어날 경우
    {
        printf("invalid key");
    }

    Vertex* ptr = graph->vlist[from].head;

    while (ptr != NULL)
    {
        if (ptr->num == from) //바로 다음 값을 지워야 할 때
        {
            graph->vlist[from].head = ptr->link; //다음 값 저장
            free(ptr); //ptr 해제
            return 1;
        }

        else
            ptr = ptr->link //ptr 이동
    }
    
    return 1;
}

int depthFS(Graph* graph, int start)
{

}

int breathFS(Graph* graph, int start)
{

}

int printGraph(Graph* graph)
{
    for (int i = 0; i < MAX_VERTEX; i++)
    {
        Vertex* ptr = graph->vlist[i].head;

        while (ptr != NULL) //ptr이 NULL이 아니면 반복
        {
            ptr = ptr->link; //ptr 이동
            
            if (ptr != NULL)
            {
                printf("%d", ptr->num);
            }
        }
    }
}
