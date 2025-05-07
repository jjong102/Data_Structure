#include <stdio.h>

void showNums(int nums[], int sz) {
  for (int i = 0; i < sz; i++) {
    printf("%d ---> ", nums[i]);
  }
  printf("\n");
}
// nums 배열의
// idxa 위치의 값과
// idxb 위치의 값을 바뀌어주는 함수

void doSwap(int nums[], int idxa, int idxb) {
  int temp = nums[idxa];
  nums[idxa] = nums[idxb];
  nums[idxb] = temp;
}

void quick_sort(int nums[], int start, int end, int real_sz) {

  int pivot = start;
  int low = start + 1;
  int high = end;
  if (start >= end) { // 탈출 조건
    return;
  }

  while (low <= high) {

    while (nums[low] <= nums[pivot] && low <= end) {
      low++;
    }

    while (nums[high] >= nums[pivot] && high >= start + 1) {
      high--;
    }

    if (low < high) {
      doSwap(nums, low, high);
    }
  }

  // pivot이 자기 자리를 찾아가도록 한다.
  doSwap(nums, pivot, high);

  showNums(nums, real_sz); // sizeof를 사용하여 개수를 구할 수 없음.

  quick_sort(nums, start, high - 1, real_sz);
  quick_sort(nums, high + 1, end, real_sz);
}

int main(void) {
  int nums[] = {23, 32, 34, 100, 87, 76, 23, 65, 2, 90, 21, 1, 3};

  int sz = sizeof(nums) /
           sizeof(nums[0]); // sizeof는 바이트 단위로 변수의 크기를 반환함.
                            // 이렇게 설정하면  sz에 개수가 들어감.

  showNums(nums, sz);
  quick_sort(nums, 0, sz - 1, sz);
  showNums(nums, sz);

  return 0;
}
