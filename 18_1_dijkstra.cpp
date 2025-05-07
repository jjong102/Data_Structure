// Dijsktra Algorithm
//
//
// 0. 초기화 한다.
//	-prev 직전에 누구를 거쳤는가
//	-dist 최단 거리
//	-done 최단 경로를 찾았는가
// 1. v = 시작 vertex
// 2. v로 부터 갈 수 있는 새로운 경로 update
// 3. v <= final = 0인 vertex들 중에
//	  dist가 가장 짧은 것 v[final] = 1

#include <stdio.h>
#define G_SZ 7

typedef struct {
  int prev; // 직전에 거친 vertex 번호
  int dist; // start vertex --> 목적지까지 거리.
  int done; // 최단 거리를 찾았는가? 1:yes, 0: no
} DijkstraElement;

void initDTable(DijkstraElement dtable[]) {
  for (int i = 0; i < G_SZ; i++) {
    dtable[i].prev = -1;
    dtable[i].dist = 99999;
    dtable[i].done = 0;
  }
}

// dtable에서 dist가 가장 짧고, done = 0 vertex를 찾아서,
// 그 번호를 반환
// 만약, 모든 vertex들의 done = 1이면, -1을 반환 == >Dijkstra 알고리즘의 종료를
// 의미
int find_shortest_path_vertex(DijkstraElement dtable[]) {

  int vertex_idx = -1;    // 최단 거리가 결정되는 vertex 번호
  int vertex_dist = 9999; // 그 vertex의 최단거리

  for (int i = 0; i < G_SZ; i++) {
    if (dtable[i].done == 0 && dtable[i].dist < vertex_dist) {
      vertex_idx = i;
      vertex_dist = dtable[i].dist;
    }
  }
  return vertex_idx;
}

void showDTable(DijkstraElement dtable[]) {
  for (int i = 1; i < G_SZ; i++) {
    printf("%5d ", i);
  }
  printf("\n");

  // prev
  for (int i = 1; i < G_SZ; i++) {
    printf("%5d ", dtable[i].prev);
  }
  printf("------prev\n");
  // dist
  for (int i = 1; i < G_SZ; i++) {
    printf("%5d ", dtable[i].dist);
  }
  printf("------dist\n");
  // done
  for (int i = 1; i < G_SZ; i++) {
    printf("%5d ", dtable[i].done);
  }
  printf("------done\n");
}

// s : start vertex 번호
// e : end vertex 번호
// s ---> e까지 가는 경로를 (중간 vertex포함해서) 보여준다.
void showPath(int s, int e, DijkstraElement dtable[]) {

  int current = e;
  while (current != s) {
    printf("%d\n", current);
    current = dtable[current].prev;
  }
  printf("%d\n", s);
}

int main(void) {

  DijkstraElement dtable[G_SZ];
  int graph[G_SZ][G_SZ] = {
      {-1, -1, -1, -1, -1, -1, -1}, {-1, -1, 3, -1, 15, -1, -1},
      {-1, 3, -1, 30, 2, -1, -1},   {-1, -1, 30, -1, -1, 3, 4},
      {-1, 15, 2, -1, -1, 1, -1},   {-1, -1, -1, 3, 1, -1, 20},
      {-1, -1, -1, 4, -1, 20, -1}};
  // dtable 초기화
  initDTable(dtable);

  // start vertex = 1
  // start vertex에서 직접 도달할 수 있는 vertex들에 대해서
  // dtable을 갱신한다.
  int start_vertex = 1;
  dtable[start_vertex].done = 1;

  for (int i = 0; i < G_SZ; i++) {
    if (graph[start_vertex][i] !=
        -1) { // start_vertex --->i까지 직접 가는 길이 있으면,
      dtable[i].dist = graph[start_vertex][i];
      dtable[i].prev = start_vertex;
    }
  }

  while (1) {
    int v = find_shortest_path_vertex(dtable);
    if (v == -1) { // dijkstra 알고리즘 완료
      break;
    }
    // v를 통해서 갱신되는 경로가 더 잛은 vertex들을 찾아서,
    // 해당 dtable을 갱신

    dtable[v].done = 1; // v까지는 최단 경로가 결정되었다.

    // 최단 경로가 정해진 것을 통해서 길을 찾아나간다.
    for (int i = 0; i < G_SZ; i++) {
      // dtable에서 가장 짧은 거리를 가진 vertex이면서, done = 0인 vertex를
      // 찾는다.
      if (graph[v][i] > -1 && dtable[i].done == 0) {
        // i까지 최단경로가 결정되지 않은 것들 중에서...
        // v를 통해서 i까지 가는 길이 기존 알려진 것보다 더 짧으면서

        // 이미 알려진 거리 > v를 통해서 가는 길
        if (dtable[i].dist > dtable[v].dist + graph[v][i]) {
          dtable[i].dist = dtable[v].dist + graph[v][i];
          dtable[i].prev = v;
        }
      }
    }
  }

  showDTable(dtable);
  printf("------------------\n");
  showPath(1, 6, dtable);

  return 0;
}