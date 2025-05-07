// spanning tree, 신장 트리
// - 모든 vertex들이 연결된 subgraph

// minimum spanning tree, 최소신장트리
// - 최소한의 edge개수로 모든 vertex를 연결하는 spanning tree
// - vertex개수 - 1이 최소 edge개수
// - 만약, weighted 그래프라고 하면, MST는 weight의 합이 최소

// MST의 응용
// - 최소 비용으로 도로 건설
// - 최소 비용으로 네트워크망 건설

// MST 알고리즘
// - Prim Algorithm
//	- 특징: vertex 기준
//		1. 시작 vertex를 정한다.
//		2. 시작 vertex를 '포함'되었다고 표시한다.
//		3. 포함 vertex에서 불포함 vertex로 연결된 edge중에 가장 작은
// weight를 작는 edge를 찾는다.
//		4. edge로 연결된 불포함 vertex를 포함되었다고 표기한다.
//		5. 3번으로 반복하는데, n-1개의  edge가 선택될 때까지.... (n은
// vertex의 개수) 		O(n^2)
//
// - Kruska Algorithm
//	- Prim Algorithm 보다는 빠름 O(E log E), 족보를 잘 관리해줘야 한다.
//(구현이 복잡함)
//	- 특징: edge 기준
//	아이디어: 가장 작은 weight를 갖는 edge를 찾아서 순서대로 추가, 다만 edge
// 추가로 인해서 cycle이 안 생길경우에만 추가
//		1. 가장 작은 weight를 가지는 edge를 선택한다.
//			v1 - edge - v2
//		2. v1과 v2가 family인지 검사해서, -------> union-find
//			- family가 아니면, edge를 MST에 추가하고
//			- v1과 v2를 결혼시켜서 family로 만든다.
//		3. 1번으로 반복, n-1개의 edge가 선택될 때까지.
//
//  - Kruska Algorithm에 같은 집안 사람 찾기
//		- family tree
//			A B C D E F G H
//			0 1 2 3 4 5 6 7
//			0 1 2 3 4 5 0 7 (<- A와 G가 결혼 한 경우 [낮은 숫자의
// 집안을 따른다.]) 			0 1 2 3 4 2 0 0 (<- A-G-H가 family가
// 되고, C-F가 family사 되었을때) 			0 1 0 3 4 0 0 0 (<-
// A-G-H-C-F가 family가 되었을때)
//
//
//
// Graph 알고리즘의 꽃 Dijkstra 알고리즘, 최단경로찾기 알고리즘
//
// 네비게이션
// 게임에서 유닛 이동
//
// Dijstra algorithm -> A* Algorithm
//
//
// Dijstra algorithm : 특정 출발지점에 다른 모든 지점까지의 최단 거리
//
// prev: 가기 직전에 누구를 방문했는가..
// dist: 시작점으로 부터 가지까지 거리
// final: 최단 거리가 알려져 있냐 아니냐?
//
//
//		 A  B   C   D   E
// prev  A -1  -1  -1  -1
// dist  0 999 999 999 999
// final 1  0   0   0   0

//		 A  B   C   D   E
// prev  A  A  -1  -1  -1
// dist  0  1  999 999 999
// final 1  1   0   0   0

//		 A  B   C   D   E
// prev  A  A   A  -1  -1
// dist  0  1   1 999 999
// final 1  1   1   0   0

//		 A  B   C   D   E
// prev  A  A   A   C  -1
// dist  0  1   1   2 999
// final 1  1   1   1   0

//		 A  B   C   D   E
// prev  A  A   A   C   B
// dist  0  1   1   2   2
// final 1  1   1   1   1

#include <stdio.h>
#define NV 5

// - Prim Algorithm
void addEdge(int graph[][NV], int v1, int v2, int weight) {
  graph[v1][v2] = weight;
  graph[v2][v1] = weight;
}

// graph :
// sVertex : start vertex

void perform_MST_Prim(int graph[][NV], int sVertex) {
  // visited way
  int visited[NV] = {
      0,
  }; // MST를 구성하는 vertex에 포함되었는지를 표시. 1포함, 0불포함

  visited[sVertex] = 1; // start vertex는 MST에 포함되었다고 표시...

  // 찾아야 되는 edge 개수 : NV-1
  for (int i = 0; i < NV - 1; i++) { // NV-1개의ㅏ edge를 찾는다.

    int minDist = 99999;
    int visted_vertex = -1;
    int nonvisited_Vertex = -1;

    // visited --> non-visited,, 가장 작은 weight를 갖는 것을 찾는다.
    for (int j = 0; j < NV; j++) {
      // visited를 찾는다.
      if (visited[j] == 1) {

        for (int k = 0; k < NV; k++) {
          if (visited[k] == 0) { // 방문하지 않은 애들 중에서..... j ----> k
            if ((graph[j][k] > 0) &&
                graph[j][k] < minDist) { // j -->k edge가 있고, 지금까지 알려진
                                         // weight보다 작을때.

              minDist = graph[j][k];
              visted_vertex = j;
              nonvisited_Vertex = k;
            }
          }
        }
      }
    }

    // MST에 새롭게 추가될 edge를 출력
    printf("%d --- %d\n", visted_vertex, nonvisited_Vertex);
    visited[nonvisited_Vertex] = 1;
  }
}

void perform_MST_Kruskal(int graph[][NV]) {

  int family[NV] = {0, 1, 2, 3, 4};

  // NV-1 개수 만큼의 edge를 찾는다.
  for (int cnt = 0; cnt < NV - 1; cnt++) {

    int v1 = -1;
    int v2 = -1;
    int minDist = 9999999;
    // 가장 weight가 작은 edge를 찾아서, MST에 포함시킨다.
    for (int i = 0; i < NV; i++) {
      for (int j = i + 1; j < NV; j++) {

        // 1. 경로가 있고
        // 2. 같은 family가 아니고,
        // 3. 지금까지 알려진 minDist보다 짧은 edge면...
        if (graph[i][j] > 0 && family[i] != family[j] &&
            minDist > graph[i][j]) {
          minDist = graph[i][j];
          v1 = i;
          v2 = j;
        }
      }
    }

    // 가장 짧은 edge를 찾았으므로...
    printf("%d --- %d\n", v1, v2);
    // 결혼식 거행... v1과 v2 가문의 결혼 진행  ==>  cycle 방지를 위해서
    int old_family = family[v2];
    int new_family = family[v1];
    for (int k = 0; k < NV; k++) {
      if (family[k] == old_family) {
        family[k] = new_family;
      }
    }
  }
}

int main(void) {

  int graph[NV][NV];

  addEdge(graph, 0, 1, 100); // 0 ---> 1 dege, weight = 100
  addEdge(graph, 0, 2, 10);
  addEdge(graph, 1, 2, 40);
  addEdge(graph, 1, 3, 50);
  addEdge(graph, 2, 3, 1);
  addEdge(graph, 3, 4, 10);

  // MST by Prim
  // perform_MST_Prim(graph, 0); // graph에 대해서, strat vertex = 0로 하여
  // MST를 Prim알고리즘으로 찾는다.

  // MST bty Kruskal
  perform_MST_Kruskal(graph);
  return 0;
}