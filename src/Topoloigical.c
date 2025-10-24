// Topological sort

#include <stdio.h>
#define SZ 6 // vertex 개수가 6개
// 2차원 배열로 구현한 graph

void addDEdge(
    int _sv, int _ev,
    int g[][SZ]) { // 2차원 배열을 받을때는 마지막 배열 개수만 맞으면 됨.
  g[_sv][_ev] = 1;
  return;
}

void initIndgree(int g[][SZ], int ideg[]) {
  // 모든 edge를 뒤져가면서,
  // indegree 배열을 채워나간다.
  for (int i = 0; i < SZ; i++) {   // 시작 vertex
    for (int j = 0; j < SZ; j++) { // 종점 vertex
      if (g[i][j] > 0) {
        ideg[j]++;
      }
    }
  }
}

// indegree 테이블에서 indegree == zero인
// vertex 번호를 반환하는 함수

int findZeroIndegreeVertex(int indeg[]) {
  for (int i = 0; i < SZ; i++) {
    if (indeg[i] == 0) {
      return i;
    }
  }

  return -1; // error case, topo_sort가 끝, 또는  cycle로 인해서 topo_sort
             // 불가능
}

void topo_sort(int g[][SZ], int indeg[]) {

  while (1) {
    int v = findZeroIndegreeVertex(indeg);
    if (v == -1) {
      return; // 끝....
    }
    printf("%d  \n", v);
    indeg[v] = -1; // 나를 찾지 말거라..

    // v로 부터 나가는 outdegree edge의 목표 vertex들의
    // indegree를 1씩 감소
    for (int i = 0; i < SZ; i++) {
      if (g[v][i] > 0) {
        indeg[i]--;
      }
    }
  }
}

int main(void) {
  int graph[SZ][SZ] = {
      0,
  }; // 모두 edge가 없는 것을 초기화

  // 각 vertex의 indegree 정보를 가진 배열
  int indegree[SZ] = {
      0,
  };

  addDEdge(0, 1, graph);
  addDEdge(0, 2, graph);
  addDEdge(0, 3, graph);
  addDEdge(1, 4, graph);
  addDEdge(2, 4, graph);
  addDEdge(2, 5, graph);
  addDEdge(3, 5, graph);
  addDEdge(5, 2, graph);
  // indegree 배열을 초기화 하는 함수
  initIndgree(graph, indegree);

  // Topolgical sort 알고리즘
  topo_sort(graph, indegree);

  // initGraph();
  return 0;
}

// Dijkstra 알고리즘
//- 한계: 출발점 지정, 나머지 모든 지점까지 최단
//
//
// Floyd 알고리즘
//- 모든 점 사이의 최단 경로
//  if (G[i][j] > G [i][k] + G[k][i]) {
//		G[i][j] = G[i][j] + G[k][j]
// }