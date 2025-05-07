//----------------------------------------
// recursion을 이용한 factorial 구현
// recursion을 사용할때 조심해야함, 마약과 같은 존재
// 메모리 할당이 많이 됨, 초기값이 바운스 되기 전까지는 메모리 도둑
//----------------------------------------
#include <stdio.h>

int factorial(int n) {
  // 탈출조건을 항상 만들어줘야함
  if (n == 1) {
    return 1;
  }
  return n * factorial(n - 1);
}

int main(void) {
  int n = 5;
  int k = factorial(n);

  printf("%d의 factorial은 %d입니다.\n", n, k);

  return 0;
}
