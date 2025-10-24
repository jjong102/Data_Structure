#include <stdio.h>

void shell_sort(int num_array[], int sz) {
  // 1. gap : sz/2--> 반씩 줄이면서 --> 1이 될때 까지..

  int gap = 0;
  int i = 0;
  int k = 0;

  for (gap = sz / 2; gap > 0; gap = gap / 2) {

    // insertion sort 각각의 그룹에 대해서 수행한다.
    for (i = 0; i < gap; i++) {

      // 이곳에서 insertion sort를 구현한다. (gap만큼 움직여서 비교하는 for문)
      for (k = i + gap; k < sz; k = k + gap) {
        int me = num_array[k]; // 일단.나보다 큰 애가 있을 수 있으므로 자리를
                               // 잠시 비켜준다.
        int d = 0; // 비교할 대상, 내 앞에 있는 애들...
        for (d = k - gap; d >= 0 && num_array[d] > me; d = d - gap) {
          num_array[d + gap] = num_array[d];
        }
        num_array[d + gap] = me;
      }
    }
  }
}

int main(void) {
  int nums[] = {23, 32, 34, 100, 87, 76, 23, 65, 2, 90, 21, 1, 3};
  int sz = sizeof(nums) / sizeof(nums[0]);

  printf("sz is %d\n", sz);

  printf("-------------shell sort---------------\n");
  shell_sort(nums, sz);

  for (int i = 0; i < sz; i++) {
    printf("%d\n", nums[i]);
  }

  return 0;
}
