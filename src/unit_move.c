#include <stdio.h>
#define MAP_SZ 10
#define SZ MAP_SZ *MAP_SZ

// Dijkstra 구조체
struct dij {
  int prev; // 직전에 누구를 거치는가
  int dist; // 최단거리
  int done; // 최단거리 찾았는가
};

// Dijkstra 알고리즘을 돌리기 위한 테이블
struct dij dtable[SZ];

struct rc {
  int r;
  int c;
};

// 0은 빈공간
// 1은 벽
int map[MAP_SZ][MAP_SZ] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, {0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

// row와 col을 idx로 바꾸는 함수
int rc2idx(int r, int c) { return (r * MAP_SZ + c); }
// idx를 row와 col으로 바꾸는 함수
struct rc idx2rc(int idx) {
  struct rc temp = {idx / MAP_SZ, idx % MAP_SZ};
  return temp;
}

int graph[SZ][SZ];

// (r1, c1) ---> (r2, c2) : 에지 추가
void addEdge(int r1, int c1, int r2, int c2) {
  int v1 = rc2idx(r1, c1);
  int v2 = rc2idx(r2, c2);
  graph[v1][v2] = 1;
  graph[v2][v1] = 1;
}

void initGraph() {

  for (int i = 0; i < MAP_SZ; i++) {
    for (int j = 0; j < MAP_SZ; j++) {

      if (map[i][j] == 1) { // 벽
        continue;           // 벽 생략
      }

      //----- 오른쪽
      // 경계안이고, 벽이 아니면, edge 연결 (i,j) ---> (i, j+1)
      if ((j + 1) < MAP_SZ && map[i][j + 1] != 1) {
        addEdge(i, j, i, j + 1);
      }

      //------ 아래쪽
      // 경계안이고, 벽이 아니면, edge 연결 (i,j) ---> (i+1, j)
      if ((i + 1) < MAP_SZ && map[i + 1][j] != 1) {
        addEdge(i, j, i + 1, j);
      }
    }
  }
}

void printGraph() {

  for (int i = 0; i < SZ; i++) {
    for (int j = 0; j < SZ; j++) {
      printf("%d  ", graph[i][j]);
    }
    printf("\n");
  }
}

void initDTable(int _sidx) {
  for (int i = 0; i < SZ; i++) {

    if (i == _sidx) { // 자기자신
      dtable[i].dist = 0;
      dtable[i].prev = _sidx;
      dtable[i].done = 1;
    } else if (graph[_sidx][i] > 0) {
      dtable[i].dist = graph[_sidx][i];
      dtable[i].prev = _sidx;
      dtable[i].done = 0;
    } else {
      dtable[i].dist = 99999999; // 무한대, 길이 없음.
      dtable[i].prev = -1;
      dtable[i].done = 0;
    }
  }
}

int findMinDistVtx() {
  // dtable에서 , 최단 경로가 결정되지 않은 것들중, 가장 짧은 거리
  int minDis = 999;
  int minIdx = -1;
  for (int i = 0; i < SZ; i++) {
    if (dtable[i].done == 0 && dtable[i].dist < minDis) {
      minDis = dtable[i].dist;
      minIdx = i;
    }
  }
  return minIdx;
}

// (r1, c1) : 출발점
// (r2, c2) : 도착점
void do_dijkstra(int r1, int c1, int r2, int c2) {

  int sidx = rc2idx(r1, c1); // Graph에서 편한 index로 변환한다.
  int tidx = rc2idx(r2, c2);

  initDTable(sidx);

  // dijkstra 알고리즘 무한 수행
  while (1) {

    // done == 0 인 것들 중에서, 거리가 가장 짧은 것
    int res = findMinDistVtx();

    dtable[res].done = 1;
    if (res == tidx) { // 목적지를 찾았으면,
      break;
    }
    for (int i = 0; i < SZ; i++) {
      if (dtable[i].done == 0) { // 아직 최단 경로가 결정되지 않았으며,
        if (graph[res][i] >
            0) { // res(방금 최단 경로가 결정된 애)에서 갈 수 있는 길이 있으면,
          // res를 통해서 가는 길이, 기존에 원래 있던 길보다 짧으면,
          if (dtable[i].dist > dtable[res].dist + graph[res][i]) {
            dtable[i].prev = res;
            dtable[i].dist = dtable[res].dist + graph[res][i];
          }
        }
      }
    }
  }
}

void printDTable() {

  printf("idx   prev   dist    done\n");
  for (int i = 0; i < SZ; i++) {
    printf("%d   %d   %d    %d\n", i, dtable[i].prev, dtable[i].dist,
           dtable[i].done);
  }
}

void printMap() {
  for (int i = 0; i < MAP_SZ; i++) {
    for (int j = 0; j < MAP_SZ; j++) {
      printf("%d  ", map[i][j]);
    }
    printf("\n");
  }
}

int main() {

  initGraph();
  // printGraph();

  int r1 = 5;
  int c1 = 5;

  int r2 = 9;
  int c2 = 9;

  do_dijkstra(r1, c1, r2, c2);

  // printDTable();

  // 경로를 출력해 보자. (역순으로 출력해 보자)
  int t = rc2idx(r2, c2);
  int s = rc2idx(r1, c1);

  int temp = t;
  while (1) {
    // printf("%d \n", temp);
    struct rc k = idx2rc(temp);
    map[k.r][k.c] = 8;
    temp = dtable[temp].prev;
    if (temp == s) {
      // printf("%d \n", temp);
      struct rc k = idx2rc(temp);
      map[k.r][k.c] = 8;
      break;
    }
  }

  printMap();

  return 0;
}