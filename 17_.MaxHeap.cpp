// max heap 구현

#include <stdio.h>

#define HEAP_SZ 100

int heap[HEAP_SZ + 1];
int idx = 0;

void addToMaxHeap(int _v) {
  // 1. heap full
  if (idx == HEAP_SZ) {
    printf("heap full\n");
  }
  idx++;
  heap[idx] = _v;

  // upheap 과정
  int _cur = idx; // 나의 인덱스
  while (_cur > 1) {
    int _p = _cur / 2; // 부모 인덱스
    if (heap[_p] >= heap[_cur]) {
      return;
    } else { // 부모가 나의 위치로 오고, 나는 부모 위치로.
      heap[_p] = heap[_cur];
      int temp = heap[_p];
      heap[_cur] = temp;
      _cur = _p; // <---- 중요, 내가 부모의 위치로 upheap!!!
    }
  }
}

// 예외, maxheap이 비어있으면 -999를 반환
int delFromMaxHeap(void) {
  // heap empty
  if (idx == 0) {
    return -999;
  }

  int res = heap[1]; // heap에서 꺼내는 것은 항상 idx 1번

  // root가 나감으로써, 붕괴된 maxheap을 재건하는 과정

  // 1. 맨 마지막 것을 root위치로 옮기고
  heap[1] = heap[idx];
  // 2. idx 감소
  idx--;

  // downheap 과정
  int _cur = 1; // 현재 나의 위치
  while (1) {
    int child_idx = 2 * _cur; // 나의 왼쪽자식 인덱스
    if (child_idx > idx) {
      break;
    }
    // 일단 오른쪽 자식이 있고,
    if ((child_idx <= idx - 1) && (heap[child_idx] < heap[child_idx + 1])) {
      child_idx = child_idx + 1; // 오른자식이 나와의 비교 대상
    }

    if (heap[_cur] >= heap[child_idx]) {
      break; // 내가 자식보다 커
    } else { // 자식자리로 내려가야한다.
      int temp = heap[_cur];
      heap[_cur] = heap[child_idx];
      heap[child_idx] = temp;
      _cur = child_idx;
    }
  }

  return res;
}

int main(void) {

  addToMaxHeap(20);
  addToMaxHeap(30);
  addToMaxHeap(5);
  addToMaxHeap(40);
  addToMaxHeap(15);

  // addToMaxHeap이 제대로 구현되었는지 확인하기 위해서
  /*for (int i = 1; i <= idx; i++) {
          printf ("%d    %d\n", i, heap[i]);
  }*/
  while (1) {
    int res = delFromMaxHeap();
    if (res == -999) {
      break;
    }
    printf("%d\n", res);
  }

  return 0;
}