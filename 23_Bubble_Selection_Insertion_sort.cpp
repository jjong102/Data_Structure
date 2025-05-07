//------------------------------------------------
// Bubble sort
// Selection sort
// Insertion sort
//------------------------------------------------

#include <stdio.h>
#define SZ 5

int main_bubbule(void) {
  int num[] = {5, 4, 3, 2, 1};

  for (int j = 0; j < SZ - 1; j++) {
    // 1번 돌아갔음.
    for (int i = 0; i < SZ - 1 - j; i++) {
      if (num[i] > num[i + 1]) {
        // swap
        int temp = num[i];
        num[i] = num[i + 1];
        num[i + 1] = temp;
      }
    }
  }

  for (int i = 0; i < SZ; i++) {
    printf("%d\n", num[i]);
  }

  return 0;
}

int main_selection(void) {
  int num[] = {5, 4, 3, 2, 1};

  for (int j = 0; j < SZ; j++) {
    // 제일 작은 애 찾기
    int sidx = j;
    // 1번 돌아갔음.
    for (int i = j; i < SZ; i++) {
      if (num[i] < num[sidx]) {
        sidx = i;
      }
    }
    int temp = num[j];
    num[j] = num[sidx];
    num[sidx] = temp;
  }

  for (int i = 0; i < SZ; i++) {
    printf("%d\n", num[i]);
  }

  return 0;
}

int main_insertion(void) {
  int num[] = {5, 4, 3, 2, 1};
  for (int j = 0; j < SZ - 1; j++) {
    // 1번 돌아갔음.
    for (int i = j + 1; i >= 0; i--) {
      if (num[i] < num[i - 1]) {
        int temp = num[i];
        num[i] = num[i - 1];
        num[i - 1] = temp;
      } else {
        break;
      }
    }
  }

  for (int i = 0; i < SZ; i++) {
    printf("%d\n", num[i]);
  }

  return 0;
}