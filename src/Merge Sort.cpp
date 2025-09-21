#include <stdio.h>
#include <stdlib.h>

void do_merge(int nums[], int tarry[], int start, int mid, int end) {

  int lstart = start;
  int lend = mid;
  int rstart = mid + 1;
  int rend = end;
  int i = lstart; // 왼쪽 조각의 현재 위치
  int j = rstart; // 오른쪽 조각의 현재 위치
  int t = lstart;

  while (1) {

    if ((i > lend) && (j > rend)) { // merge가 끝난 상태
      break;
    }

    if (j > rend) { // 왼쪽 조각에 숫자가 남은 경우
      tarry[t] = nums[i];
      t++;
      i++;
    }

    else if (i > lend) { // 오른쪽 조각의 숫자가 남은 경우
      tarry[t] = nums[j];
      t++;
      j++;
    }

    else { // 양쪽에 숫자가 남아 있으므로, 작은 숫자를 찾아서 넣는다.
      if (nums[i] < nums[j]) { // 왼쪽 조각 숫자가 작다.
        tarry[t] = nums[i];
        t++;
        i++;
      } else { // 오른쪽 조각 숫자가 크다.
        tarry[t] = nums[j];
        t++;
        j++;
      }
    }
  }

  // tarry에 merge된 결과가 있다.
  // 이것을 원래 배열에 복사해서 넣어야 한다.
  for (i = start; i <= end; i++) {
    nums[i] = tarry[i];
  }
}

void merge_sort(int nums[], int start, int end, int tarry[]) {
  // 탈출조건
  if (start == end) {
    return;
  }

  merge_sort(nums, start, (start + end) / 2, tarry);   // 왼쪽을 merge sort
  merge_sort(nums, (start + end) / 2 + 1, end, tarry); // 오른쪽을 merge sort
  // 왼쪽과 오른쪽을 merge 한다.
  do_merge(nums, tarry, start, (start + end) / 2, end);
}

int main(void) {

  int nums[] = {23, 32, 34, 100, 87, 65, 2, 90, 21, 1, 3};
  int sz = sizeof(nums) / sizeof(nums[0]);
  // merge sort를 구현하기 위한 임시 저장소
  int *tarry = (int *)malloc(sizeof(int) * sz);

  // nums: 정렬대상 배열
  //  0 : 시작 index
  //  1 : 종료 index
  //  임시배열 : extra space
  merge_sort(nums, 0, sz - 1, tarry);
  free(tarry);
  for (int i = 0; i < sz; i++) {
    printf("%d -->", nums[i]);
  }
  printf("\n");
  return 0;
}