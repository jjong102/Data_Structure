//----------------------------------------
// 반복을 이용한 recursion
//----------------------------------------
#include <stdio.h>

// 반복으로 푸는게 좋다, 더 빠르다 (recursion 항상 함수 공간이 많이 생겨,
// 비효율적이다)
int factorial(int n) {

  int result = 1;
  int i;
  for (i = 1; i <= n; i++) {
    result = result * i;
  }

  return result;
}

int main(void) {
  int n = 5;
  int k = factorial(n);

  printf("%d의 factorial은 %d입니다.\n", n, k);

  return 0;
}