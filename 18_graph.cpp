//----------------------------------------------
// graph
// 그래프는 (V,E) 로 표시
//	정점 (vertex)
//	간선 (edge)
//
// 그래프의 종류
//	undirected graph : 무방향 그래프
//	directed graph : 방향 그래프
//	weighted graph :  가중치 그래프
//		간선에 비용이나 가중치가 할당된 그래프
//		네트워크라고도 함.
//
// graph 표현의 예
//	adjacent vertex : 간선에 의해 직접 연결된 정점
//	degree : 하나의 정점에 연결된 다른 그래프의 수
//
// path
//	무방향 그래프의 정점 s로 부터 정점 e까지의 경로
// length
//	몇개를 거쳐 왔느냐!
//	 simple
//		경로 중에서 반복되는 간선이 없는 경로
//	 cycle
//		시작 정점과 종료 정점이 동일한 경로
//
//	connected graph
//	tree
//  complete graph
//		모든 정점이 연결되어 있는 그래프
//
// 그래프 표현 방법 1.
//	2차원 행렬을 이용해서 그래프를 표현
//		장. 직관적이다.
//		단. 메모리가 무지하게 많이 든다. (매모리 효율성 ↓)
//
// 그래프 표현 방법 2.
//	SLL로 표현
//----------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#define NUM_VTX 6

struct node {
  int vtx;
  struct node *next;
};

struct node *graph[NUM_VTX];

// int graph[NUM_VTX][NUM_VTX];
//
// void addEdge(int v1, int v2) {
//
//	graph[v1][v2] = 1;
//	graph[v2][v1] = 1;
//	return;
// }
//
//
// int isThereEdge(int v1, int v2) {
//	return graph[v1][v2];
// }

void _addEdge(int v1, int v2) { // v1  -->  v2

  // v2로 가는 node를 만든다.
  struct node *_v2 = (struct node *)malloc(sizeof(struct node));
  _v2->vtx = v2;
  _v2->next = 0;

  struct node *cur = graph[v1];

  if (cur == 0) {
    graph[v1] = _v2; // 널 포인터는 아직 메모리가 할당되어 있는 상태가 아니기
                     // 때문에 null pointer를 가리키는 pointer의 값을 바꿔도
                     // 값이 바뀌지 않아요!

    return;
  }

  else {
    while (cur->next != 0) {
      cur = cur->next;
    }
    cur->next = _v2;
    return;
  }
}
void addEdge(int v1, int v2) { // v1--> v2, v2--> v1

  // v1 --> v2
  _addEdge(v1, v2);

  // v2 --> v1
  _addEdge(v2, v1);
}
int isThereEdge(int v1, int v2) {
  struct node *cur = graph[v1];

  while (cur != 0) {
    if (cur->vtx == v2) {
      return 1;
    } else {
      cur = cur->next;
    }
  }
  return 0;
}

// 그래프 탐색 알고리즘을 이용해서
// DFS: depth first search -> stack
// BFS: breadth first search -> queue
// 목적 : 특정 vertex에서 갈 수 있는, 도달할 수 있는 vertex들을 모두 찾기
// 위해서....

// DFS는 stack을 이용
// 1. 시작하는 vtx를 stack에 넣어버려 (A 넣기)
// 2. stack에서 꺼내 (stack이 빌때까지) (A 방문) - A가 방문했다고 표시
// 3. A가 갈 수 있는 곳을 다 넣어 버려 (B, C) (방문한 vtx, stack에 들어가 있는
// 것 빼고) ---- 무한 반복

// BFS는 queue를 이용
// 1. A를 queue넣기
// 2. A를 queue에서 꺼내기 (A 방문) - A 방문했다고 표시
// 3. A가 갈 수 있는 곳 다 넣어 버려 (B,C) (방문, queue에 존재 빼고)

//  DFS를 위한 stack
int stack_DFS[NUM_VTX];
int top = -1;
void push(int v) {
  if (top == NUM_VTX - 1) {
    return;
  }
  top++;
  stack_DFS[top] = v;
  return;
}
int pop() {
  if (top == -1) {
    return -999;
  }
  int res = stack_DFS[top];
  top--;
  return res;
}

// BFS를 위한 queue
int queue_BFS[NUM_VTX];
int front = 0;
int rear = 0;

void enqueue(int v) {
  if (front == (rear + 1) % NUM_VTX) {
    return; // que is full
  }
  queue_BFS[rear] = v;
  rear = (rear + 1) % NUM_VTX;
  return;
}
int dequeue() {
  if (front == rear) {
    return -999; // que empty
  }
  int res = queue_BFS[front];
  front = (front + 1) % NUM_VTX;
  return res;
}

// stack안에 v가 이미 있으면 1
// 아니면 0을 반환
int checkDuplication(int v) {
  // stack이 비어있으면, v가 없다.
  if (top == -1) {
    return 0;
  }
  for (int i = 0; i <= top; i++) { // stack을 다 뒤져가며 v가 있는지 검사!
    if (stack_DFS[i] == v) {
      return 1;
    }
  }
  return 0;
}

// _v에서 시작하여, DFS 시행
void do_DFS(int _v) {
  // 1. stack_DFS : push, pop, checkDuplication
  // 2. visited : 방문했는지 여부를 나타내는 1차원 배열
  int visited[NUM_VTX] = {
      0,
  }; // 모두다 방문하지 않았음.

  // 알고리즘
  //
  // 시작 vertex를 stack에 넣는다.
  //
  // 반복 -- stack이 빌때까지
  //	stack에서 pop ---> m
  //	m을 방문했다고 표시하고,
  //  m을 화면에 출력
  //  for (m에 연결된 각각의 vertex에 대해서)
  //		if (stack에 없고, visited가 아니면)
  //		   ==> push
  push(_v);

  while (1) {
    int m = pop();
    if (m == -999) {
      break;
    }
    if (visited[m] == 0) {
      visited[m] = 1;
      printf("%d vertex를 방문했음\n", m);
    }
    struct node *_cur = graph[m];
    while (_cur != 0) {
      // if (checkDuplication(_cur->vtx) == 0 && visited[_cur->vtx] == 0) {
      if (visited[_cur->vtx] == 0) {
        push(_cur->vtx);
      }
      _cur = _cur->next;
    }
  }
}

void do_BFS(int v) {
  int visited[NUM_VTX] = {
      0,
  };

  enqueue(v);
  while (1) {
    int m = dequeue();
    if (m == -999) {
      break;
    }
    if (visited[m] == 0) {
      visited[m] = 1;
      printf("%d vertex를 방문하였음\n", m);
    } else {
      printf("%d ------ 중복\n", m);
    }
    struct node *_cur = graph[m];
    while (_cur != 0) {
      if (visited[_cur->vtx] == 0) {
        push(_cur->vtx);
      }
      _cur = _cur->next;
    }
  }
}

int main(void) {

  addEdge(0, 3); // 3 --> 0
  addEdge(0, 1);
  addEdge(0, 2);
  addEdge(1, 4);
  addEdge(2, 4);
  addEdge(2, 4);
  addEdge(3, 5);
  addEdge(4, 5);

  // do_DFS(0); // 0번 vertex부터 시작해서 DFS 시행

  do_BFS(0); // 1번 vertex부타 시작해서 BFS 시행

  return 0;
}